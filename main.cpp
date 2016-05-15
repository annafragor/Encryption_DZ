#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib> //srand
#include <time.h>
#include <vector>
#include <fstream>
//#include <conio.h>
#include <memory>

using namespace std;

string alphabet = "abcdefghigklmnopqrstuvwxyz|.?";
int fromChar(char c)
{	return alphabet.find(c);	}
char fromInt(int i)
{	return alphabet[i];	}
vector<int> translate(string str)
{
	vector<int> result;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		result.push_back(fromChar(str[i]));
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
		throw out_of_range("wrong number for inv");
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
int determ(int** Arr, int size)
{
	int i, j;
	int det = 0;
	int** matr;
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
		matr = new int*[size - 1];
		for (i = 0; i < size; ++i)
		{
			for (j = 0; j < size - 1; ++j)
			{
				if (j < i)
					matr[j] = Arr[j];
				else
					matr[j] = Arr[j + 1];
			}
			det += (int)pow(-1., (i + j))*determ(matr, size - 1)*Arr[i][size - 1];
		}
		delete[] matr;
	}
	if (det >= 0)
		det = det % 29;
	else{
		while (det < 0)
			det += 29;
	}
	return det;
}
int** transp(int** matr, int n)
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
vector<int> summ(vector<int> v1, vector<int> v2)
{
	vector<int> result(v1.size());
	if (v1.size() != v2.size())
		throw out_of_range("vectors can't be folded\n");
	for (unsigned int i = 0; i < v1.size(); i++){
		result[i] = v2[i] + v1[i];
		if (result[i] >= 0)
			result[i] = result[i] % 29;
		else{	
			while (result[i] < 0)
				result[i] += 29;
		}
	}
	return result;
}
vector<int> delta(vector<int> d, vector<int> vect) //d - vect
{
	vector<int> result(d.size());
	if (d.size() != vect.size())
		throw out_of_range("vectors can't be subtracted\n");
	for (unsigned int i = 0; i < d.size(); i++){
		result[i] = d[i] - vect[i];
		if (result[i] >= 0)
			result[i] = result[i] % 29;
		else{
			while (result[i] < 0)
				result[i] += 29;
		}
	}
	return result;
}

class Cipher
{
public:
	Cipher(){};
	virtual string e(string str) = 0;
	virtual string d(string str) = 0;
	~Cipher(){};
};

class Hill : public Cipher
{
	int** k; // key matrix 8x8
//	string str; // what we want to chipher or decipher
public:
	Hill(){};
	Hill(int key_)
	{
		srand(key_);
		k = new int*[8];
		for (int i = 0; i < 8; i++){
			k[i] = new int[8];
			for (int j = 0; j < 8; j++)
				k[i][j] = rand() % 29;
		}
	}

	string e(string str)
	{
		string result;
		vector<int> p = translate(str); // plain text vector
		vector<int> c(8); // coph text vector
		
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
				c[i] += k[i][j] * p[j];
			c[i] = c[i] % 29;
		}
		result = translate(c, 8);		
		cout << endl << "want to cipher:  " << str;
		cout << endl << "ciphered hill:   " << result << endl;
		return result;
	}
	string d(string str)
	{
		string result;
		k = invMatr(k);
		vector<int> c = translate(str);
		vector<int> p(8);
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++)
				p[i] += k[i][j] * c[j];
			p[i] = p[i] % 29;
		}
		result = translate(p, 8);		
		cout << "deciphered hill: " << result << endl;
		return result;
	}

	friend int** invMatr(int**);
	friend class PlainText;
	~Hill()
	{
		for (int i = 0; i < 8; i++)
			delete[] k[i];
		delete[] k;
	}
};
int** A(int** matr, int y, int x) //алгебраическое дополнение в данной ячейке матрицы matr
{
	int** add = new int*[7];
	for (int i = 0; i < 7; i++)
		add[i] = new int[7];

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
int** invMatr(int** matr/*size = 8*/)
{
	int invDet = inv(determ(matr, 8), 29);
	int** invM = new int*[8];
	for (int i = 0; i < 8; i++)
		invM[i] = new int[8];
	int** add;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			add = A(matr, i, j);
			invM[i][j] = (int)determ(add, 7) * invDet * (int)pow(-1., (i + j));
			invM = transp(invM, 8);
			if (invM[i][j] >= 0)
				invM[i][j] = invM[i][j] % 29;
			else{
				while (invM[i][j] < 0)
					invM[i][j] += 29;
			}
		}
	}

	for (int i = 0; i < 8; i++)
	for (int j = 0; j < 8; j++)
		matr[i][j] = invM[i][j];

	for (int i = 0; i < 8; i++)
		delete[] invM[i];
	delete[] invM;
	for (int i = 0; i < 7; i++)
		delete[] add[i];
	delete[] add;
	return matr;
}

class Skitala : public Cipher
{
	char parchmentTable[2][4];
//	string str; // what we want to chipher or decipher
public:
	Skitala()
	{
		for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++)
			parchmentTable[i][j] = '\0';
	}

	string e(string str)
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
	string d(string str)
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

class Vigenere : public Cipher
{
	char tabulaRecta[29][29];
	string key;
//	string str; // what we want to chipher or decipher
public:
	Vigenere(){};
	Vigenere(string keyword)
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

	string e(string str)
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
	string d(string str)
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

class Padding
{// block = 8 bytes
	char type;
public:
	Padding(){};
	Padding(char paddType) : type(paddType)	{}
	
	string pad(string block)
	{
		string fullblock;
		fullblock += block;
		vector<int> arr(8 - block.length());
		switch (type)
		{
		case 'a': // DD DD DD DD 00 00 00 04 (block = 8 bytes)
		{
					for (unsigned int i = 0; i < 8 - block.length(); i++)
						arr[i] = 0;
					arr[8 - block.length() - 1] = 8 - block.length() - 1;
		}
		case 'i': // DD DD DD DD 81 A6 23 04 ((empty-1) - random, last - number of empty) 
		{
					srand((unsigned int)time(0));
					for (unsigned int i = 0; i < 8 - block.length(); i++)
					{
						arr[i] = rand() % 29;
					}
					arr[8 - block.length() - 1] = 8 - block.length() - 1;
					break;
		}
		case 'p': // DD DD DD DD 04 04 04 04 (block = 8 bytes) 
		{
					  for (unsigned int i = 0; i < 8 - block.length(); i++)
						  arr[i] = 8 - block.length() - 1;
					  break;
		}
		}
		fullblock += translate(arr, 8 - block.length());
		return fullblock;
	}
	string unpad(string block)
	{
		if (block.length() == 0)
			return "";
		else if (block.length() == 1)
			return "";
		else
		{
		string cutblock;
		vector<int> o = translate(block);
		cutblock = string(block.begin(), block.end() - o[block.length() - 1] - 1);
		return cutblock;
		}
	}
	~Padding(){};
};

class Mode
{
protected:
	unique_ptr<Cipher> c;
public:
	Mode(Cipher* c_v) : c(c_v) {};
	virtual string e(string str) = 0;
	virtual string d(string str) = 0;
	~Mode(){}
};

class ECB : public Mode
{
public:
	ECB(Cipher* cipher) : Mode(cipher) {};

	string e(string str)
	{	
		return c->e( str);
	}
	string d(string str)
	{
		if (str.length() == 0)
			return "";
		return c->d(str);
	}
	~ECB(){};
};

class CBC : public Mode
{
private:	
	string vect;
public:
	CBC(Cipher* cipher, string vect_v) : Mode(cipher), vect(vect_v){}

	string e(string str)
	{
		vector<int> vec = translate(vect);
		vector<int> p = translate(str);
		str = translate(summ(p, vec), p.size());
		vect = c->e(str);
		return vect;
	}
	string d(string str)
	{
		if (str.length() == 0)
			return "";
		vector<int> vec = translate(vect);
		vector<int> p = translate(str);
		string dd = c->d(str);
		vect = str;
		return translate(delta(translate(dd), vec), dd.size());
	}	
	~CBC(){};
};

class OFB : public Mode
{
	string vect;
public:
	OFB(Cipher* cipher, string vect_v) : Mode(cipher), vect(vect_v) {}
	
	string e(string str)
	{
		vect = c->e(vect);
		return translate(summ(translate(vect), translate(str)), str.length());
	}
	string d(string str)
	{
		if (str.length() == 0)
			return "";
		vect = c->e(vect);
		return translate(delta(translate(str), translate(vect)), vect.length());
	}
	~OFB(){};
};

class CFB : public Mode
{
	string vect;
public:
	CFB(Cipher* cipher, string vect_v) : Mode(cipher), vect(vect_v) {};

	string e(string str)
	{
		vect = translate(summ(translate(c->e(vect)), translate(str)), vect.length());
		return vect;
	}
	string d(string str)
	{
		if (str.length() == 0)
			return "";
		string result = translate(delta(translate(str), translate(c->e(vect))), str.length());
		vect = str;
		return result;
	}
	~CFB(){};
};

int main()
{
	try
	{
		Cipher* ciph = new Skitala();
		Padding* p = new Padding('i');
		Mode* m = new ECB(ciph);

		string lastFinalText = "";
		bool ciphr = true;
		bool wasEnd = false;
		//ofstream f("cipheredText.txt");
		//f.close();
		//ofstream ff("decipheredText.txt");
		//ff.close();
		string str;
		char ch;
		string finalText = "";

	//	fstream Fp("plainText.txt");
		fstream Fp("cipheredText.txt");
		Fp.seekg(0, ios_base::beg);
//		fstream Fс("cipheredText.txt");
		fstream Fc("decipheredText.txt");

		while (!Fp.eof())
		{
			str = "";
			ch = '\0';
			while (!Fp.eof())
			{
				Fp >> ch;
				//if(Fp.fail())
				//	break;
				str += ch;
				if (str.length() == 8)
					break;
			}
			Fp >> ch;
			if (Fp.eof()){
				wasEnd = true;
			}
			else
				Fp.seekg(-1, Fp.cur);

			finalText = m->d(str);
			if (wasEnd){
				finalText = p->unpad(finalText);
				Fc << finalText;
				break;
			}
			Fc << finalText;
			//if (str.length() != 8)
			//{
			//	if (str.length() != 0)
			//		str = string(str.begin(), str.end() - 1);
			//	str = p->pad(str);
			//}

//			finalText = m->e(str);
			//////if(Fp.eof())
			//////	finalText = p->unpad(str);
		}
		Fp.close();
		Fc.close();
		
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
	}
	system("pause");
	return 0;
}
