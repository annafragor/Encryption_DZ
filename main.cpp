#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cstdlib> //srand
#include <time.h>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

class Err
{
	int k;
public:
	Err(int k_v) : k(k_v){};
	int errType() const
	{
		return k;
	}
	~Err(){};
};

int fromChar(char c)
{
	int result;
	switch (c)
	{
	case 'a': result = 0; break;
	case 'b': result = 1; break;
	case 'c': result = 2; break;
	case 'd': result = 3; break;
	case 'e': result = 4; break;
	case 'f': result = 5; break;
	case 'g': result = 6; break;
	case 'h': result = 7; break;
	case 'i': result = 8; break;
	case 'j': result = 9; break;
	case 'k': result = 10; break;
	case 'l': result = 11; break;
	case 'm': result = 12; break;
	case 'n': result = 13; break;
	case 'o': result = 14; break;
	case 'p': result = 15; break;
	case 'q': result = 16; break;
	case 'r': result = 17; break;
	case 's': result = 18; break;
	case 't': result = 19; break;
	case 'u': result = 20; break;
	case 'v': result = 21; break;
	case 'w': result = 22; break;
	case 'x': result = 23; break;
	case 'y': result = 24; break;
	case 'z': result = 25; break;
	case '|': result = 26; break;
	case '.': result = 27; break;
	case '?': result = 28; break;
	default:
		throw out_of_range("wrong input symbol");
	}
	return result;
}
vector<int> translate(string str)
{
	vector<int> result;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		result.push_back(fromChar(str[i]));
	}
	return result;
}
char fromInt(int i)
{
	char result;
	switch (i)
	{
	case 0: result = 'a'; break;
	case 1: result = 'b'; break;
	case 2: result = 'c'; break;
	case 3: result = 'd'; break;
	case 4: result = 'e'; break;
	case 5: result = 'f'; break;
	case 6: result = 'g'; break;
	case 7: result = 'h'; break;
	case 8: result = 'i'; break;
	case 9: result = 'j'; break;
	case 10: result = 'k'; break;
	case 11: result = 'l'; break;
	case 12: result = 'm'; break;
	case 13: result = 'n'; break;
	case 14: result = 'o'; break;
	case 15: result = 'p'; break;
	case 16: result = 'q'; break;
	case 17: result = 'r'; break;
	case 18: result = 's'; break;
	case 19: result = 't'; break;
	case 20: result = 'u'; break;
	case 21: result = 'v'; break;
	case 22: result = 'w'; break;
	case 23: result = 'x'; break;
	case 24: result = 'y'; break;
	case 25: result = 'z'; break;
	case 26: result = '|'; break;
	case 27: result = '.'; break;
	case 28: result = '?'; break;
	default:
		throw out_of_range("wrong input symbol!");
	}
	return result;
}
string translate(vector<int> arr, int length)
{
	string result;
	for (int i = 0; i < length; i++)
	{
		result += fromInt(arr[i]);
	}
	return result;
}
int inv(int num, int mod)
{
	if (num >= mod)
		throw Err(4);
	int i = 0;
	int pr = -1;
	while (pr%mod != 1)
	{
		i++;
		pr = i*num;
		if (i >= 29)
			throw out_of_range("no inv for your det");
	}
	return i;
}
int determ(vector<vector<int>> Arr, int size)
{
	int i, j;
	int det = 0;
	vector<vector<int>> matr;
	if (size == 1)
	{
		det = Arr[0][0];
	}
	else if (size == 2)
	{
		det = Arr[0][0] * Arr[1][1] - Arr[0][1] * Arr[1][0];
	}
	else
	{
		for (i = 0; i < size; ++i)
		{
			for (j = 0; j < size - 1; ++j)
			{
				if (j < i)
					matr.push_back(Arr[j]);
				else
					matr.push_back(Arr[j + 1]);
			}
			det += (int)pow(-1., (i + j))*determ(matr, size - 1)*Arr[i][size - 1];
		}
	//	vector<vector<int>>().swap(matr)
	}
	if (det >= 0)
		det = det % 29;
	else{
		while (det < 0)
			det += 29;
	}
	return det;
}
bool ifZeroStr(int* str, int n)
{
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		if (str[i] != 0)
			k++;
	}
	if (k == 0)
		return true;
	else
		return false;
}
vector<vector<int>> transp(vector<vector<int>> matr, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int k = matr[i][j];
			matr[i][j] = matr[j][i];
			matr[j][i] = k;
		}
	}
	return matr;
}


class Skitala //минус - первый и последний символ совпадают
{
	char parchmentTable[2][4];
	string str; // what we want to chipher or decipher
public:
	Skitala(){};
	Skitala(string str_v) : str(str_v)
	{
		for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++)
			parchmentTable[i][j] = '\0';

		if (str.length() != 8)
			throw out_of_range("block for cipher skitala is unsuitable");
	}

	string e()
	{
		string result;
		int k = 0;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 4; j++, k++)
			{
				parchmentTable[i][j] = str[k];
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				result += parchmentTable[j][i];
			}
		}
		cout << endl << "want  to  cipher:   " << str;
		cout << endl << "ciphered skitala:   " << result << endl;
		return result;
	}
	string d()
	{
		string result;
		int k = 0;

		string pD = "";//deciphered plain text

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++, k++)
			{
				parchmentTable[j][i] = str[k];
			}
		}
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result += parchmentTable[i][j];
			}
		}
		cout << "deciphered skitala: " << result << endl;
		return result;
	}

	~Skitala(){};
};

class Vigenere
{
	char tabulaRecta[29][29];
	string key;
	string str; // what we want to chipher or decipher
public:
	Vigenere(){};
	Vigenere(string str_v, string keyword) : str(str_v)
	{
		strcpy((char*)tabulaRecta[0], "abcdefghijklmnopqrstuvwxyz|.?");
		for (int i = 1; i < 29; i++)
		{
			for (int j = 0; j < 28; j++)
				tabulaRecta[i][j] = tabulaRecta[i - 1][j + 1];
			tabulaRecta[i][28] = tabulaRecta[i - 1][0];
		}

		if (keyword.length() == 8)
			key = keyword;
		else
		{
			for (unsigned int i = 0; i < 8 / keyword.length(); i++)
				key += keyword;
			for (unsigned int i = 0; i < 8 % keyword.length(); i++)
			{
				key += keyword[i];
			}
		}
	}

	string e()
	{
		string result;

		for (int i = 0; i < 8; i++)
		{
			result += tabulaRecta[fromChar(key[i])][fromChar(str[i])];
		}
		cout << "want to cipher:      " << str << endl;
		cout << "ciphered vigenere:   " << result << endl;
		return result;
	}
	string d()
	{
		string result;
		int k = 0;

		for (int i = 0; i < 8; i++)
		{
			k = 0;
			while (tabulaRecta[fromChar(key[i])][k] != str[i])
			{
				k++;
			}
			result += fromInt(k);
		}
		cout << "want to decipher:    " << str << endl;
		cout << "deciphered vigenere: " << result << endl;

		return result;
	}

	~Vigenere(){};
};
											/*TYPES OF PADDING*/
// DD DD DD DD 00 00 00 04 (block = 8 bytes)
class ansiX923
{
	string fullblock;
public:
	ansiX923(){};
	ansiX923(string block) : fullblock("")
	{
		fullblock += block;
		vector<int> arr(8 - block.length());
		for (int i = 0; i < 8 - block.length(); i++)
			arr[i] = 0;
		arr[8 - block.length() - 1] = 8 - block.length() - 1;
		fullblock += translate(arr, 8 - block.length());
	}

	string add() 
	{	return fullblock;	}

	~ansiX923(){};
};
// DD DD DD DD 04 04 04 04 (block = 8 bytes) 
class pkcs7
{
	string fullblock;
public:
	pkcs7(){};
	pkcs7(string block) : fullblock("")
	{
		fullblock += block;
		vector<int> arr(8 - block.length());
		for (int i = 0; i < 8 - block.length(); i++)
			arr[i] = 8 - block.length() - 1;
		fullblock += translate(arr, 8 - block.length());
	}

	string add()
	{	return fullblock; 	}

	~pkcs7(){};
};
// DD DD DD DD 81 A6 23 04 ((empty-1) - random, last - number of empty) (block = 8 bytes) 
class iso10126
{
	string fullblock;
public:
	iso10126(){};
	iso10126(string block) : fullblock("")
	{
		fullblock += block;
		vector<int> arr(8 - block.length());
		srand((unsigned int)time(0));
		for (unsigned int i = 0; i < 8 - block.length(); i++)
		{
			arr[i] = rand() % 29; //случайные числа от 0 до 255 (mod 29)
		}
		arr.push_back(8 - block.length() - 1);		
		fullblock += translate(arr, 8 - block.length());
	}

	string add()
	{	return fullblock;	}

	~iso10126(){};
};

class ECB
{
	string key;
	string finalText;
	bool wasDivided;
public:
	ECB() : key(""), finalText(""), wasDivided(false) {};
	ECB(string key_v) : key(key_v), finalText(""), wasDivided(false) {}; //for Vigenere

	string e(char algType)
	{
		string str;
		char ch;
		fstream Fp("plainText.txt");
		Fp.seekg(0, ios_base::beg);
		while (!Fp.eof())
		{
			str = "";
			while (!Fp.eof())
			{
				Fp >> ch;
				str += ch;
				if (str.length() == 8)
					break;
			}
			if (str.length() != 8)
			{
				//ansiX923 a(str);
				//str = a.add();
				//pkcs7 p(str);
				//str = p.add();
				iso10126 i(str);
				str = i.add();
				wasDivided = true;
			}
			switch (algType)
			{
			case 'v':
				Vigenere* v = new Vigenere(str, key);
				finalText += v->e();
				delete v;
				break;
			}
		}		
		Fp.close();
		fstream Fс("cipheredText.txt");
		Fс << finalText;
		Fс.close();
		return str;
	}
	string d(char algType)
	{
		string str;
		char ch;
		finalText = "";
		fstream Fp("cipheredText.txt");
		while (!Fp.eof())
		{
			str = "";
			while (!Fp.eof())
			{
				Fp >> ch;
				str += ch;
				if (str.length() == 8)
					break;
			}
			if (str.length() != 8)
				break;
			switch (algType)
			{
			case 'v':
				Vigenere v(str, key);
				finalText += v.d();
				break;
			}
		}
		if (wasDivided)
		{
			vector<int> o = translate(finalText);
			finalText = string(finalText.begin(), finalText.end() - o[finalText.length() - 1] - 2);
		}
		Fp.close();
		fstream Fc("decipheredText.txt");
		Fc << "fTxt = " << finalText;
		Fc.close();
		return str;
	}

	~ECB(){};
};

int main()
{
	try
	{
		ECB g("key");
		g.e('v');
		g.d('v');
		
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
	}

	system("pause");
	return 0;
}
