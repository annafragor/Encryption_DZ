#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
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
	case ' ': result = 26; break;
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
	case 26: result = ' '; break;
	case 27: result = '.'; break;
	case 28: result = '?'; break;
	default:
		throw out_of_range("wrong input symbol");
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
			det += pow(-1., (i + j))*determ(matr, size - 1)*Arr[i][size - 1];
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

	string cipher()
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
	string decipher()
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

		//vector<int> o = translate(result);
		//if ((plTxt->ansiX923_ == true) || (plTxt->iso10126_ == true) || (plTxt->pkcs7_ == true)){
		//	for (int i = 0; i < o[result.length() - 1] + 1; i++){
		//		result.erase(result.begin() + (result.length() - 1));
		//	}
		//}
		//	delete o;

		cout << "deciphered skitala: " << result << endl;
		return result;
	}

	~Skitala(){};
};

class Hill // C = K*P; P = K^(-1)*C
{	
	vector<vector<int>> keyM; //key matrix
	string str; // what we want to chipher or decipher
public:
	Hill(){};
	Hill(string str_v, int key_v) : str(str_v)
	{
		srand(key_v);
		for (int i = 0; i < 8; i++)
		{
			vector<int> temp;
			for (size_t j = 0; j < 8; j++)
				temp.push_back(rand() % 29);
			keyM.push_back(temp);
		}		

		if (str.length() != 8)
			throw out_of_range("block for cipher hill is unsuitable");
	}

	string cipher()
	{
		string result;
		int ch = 0;
		vector<int> p = translate(str); //вектор открытого текста
		vector<int> c;
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++)
				ch += keyM[i][j] * p[j];
			c.push_back(ch % 29);
		}
		result += translate(c, 8);
		cout << endl << "want to cipher:  " << str;
		cout << endl << "ciphered hill:   " << result << endl;
		return result;
	}
	string decipher()
	{
		keyM = invMatr(keyM);
		cout << "ok";
		string pD = "";//deciphered plain text
		vector<int> c = translate(str); //we want to decipher this string
		vector<int> p(8); //here we'll write deciphered string in numbers

		for (int i = 0; i < 8; i++){
			int ph = 0;
			for (int j = 0; j < 8; j++)
				ph += keyM[i][j] * c[j];
			p.push_back(ph % 29);
		}
		
		pD += translate(p, 8);
//		cout << "pD =             " << pD << endl;
		cout << "deciphered hill: " << pD << endl;
		return pD;
	}

	friend vector<vector<int>> invMatr(vector<vector<int>>);
	friend class PlainText;

	~Hill(){}
};

vector<vector<int>> A(vector<vector<int>> matr, int y, int x) //алгебраическое дополнение в данной ячейке матрицы matr
{
	vector<vector<int>> add;
	for (int i = 0; i < 7; i++)
	{
		vector<int> temp;
		for (size_t j = 0; j < 7; j++)
			temp.push_back(0);
		add.push_back(temp);
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i < x && j < y)
				add[i][j] = matr[i][j];
			else if (i < x && j > y)
				add[i][j - 1] = matr[i][j];
			else if (i > x && j < y)
				add[i - 1][j] = matr[i][j];
			else if (i>x && j>y)
				add[i - 1][j - 1] = matr[i][j];
			else if (i == x || j == y)
				continue;
		}
	}
	return add;
}
vector<vector<int>> invMatr(vector<vector<int>> matr/*size = 8*/)
{
	int invDet = inv(determ(matr, 8), 29);
	cout << "," << endl;

	vector<vector<int>> invM;
	for (int i = 0; i < 8; i++)
	{
		vector<int> temp;
		for (size_t j = 0; j < 8; j++)
			temp.push_back(rand() % 29);
		invM.push_back(temp);
	}
	vector<vector<int>> add;
	cout << "ok" << endl;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			add = A(matr, i, j);
			invM[j][i] = determ(add, 7) * invDet * (int)pow(-1., (i + j));
			cout << ".";
			//invM[i][j] = determ(add, 7);
			//invM[i][j] = invM[i][j] * invDet;
			//invM[i][j] = invM[i][j] * (int)pow(-1., (i + j));
			//invM = transp(invM, 8);
			if (invM[i][j] >= 0)
				invM[i][j] = invM[i][j] % 29;
			else{
				while (invM[i][j] < 0)
					invM[i][j] += 29;
			}
		}
	}
	//for (int i = 0; i < 8; i++)
	//for (int j = 0; j < 8; j++)
	//	matr[i][j] = invM[i][j];
	return matr;
}


int main()
{
	try
	{
		//Skitala s("abcdefgh");
		//string ciph = s.cipher();
		//Skitala ss(ciph);
		//ss.decipher();


		Hill h("abcdefgh", 5); //5 - key, "abcdefgh" - we wanna decipher
		string ciph = h.cipher();
		Hill hh(ciph, 5);
		hh.decipher();
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
	}

	system("pause");
	return 0;
}
