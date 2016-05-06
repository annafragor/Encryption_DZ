#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>
#include <cstdlib> // srand
#include <time.h>

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
int* translate(string str)
{
	int* result = new int[str.length()];
	for (unsigned int i = 0; i < str.length(); i++)
	{
		result[i] = fromChar(str[i]);
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
string translate(int* arr, int length)
{
	string result;
	for (int i = 0; i < length; i++)
	{
		result += fromInt(arr[i]);
	}
	return result;
}
double determ(int** Arr, int size)
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
			det += (double)pow(-1., (i + j))*determ(matr, size - 1)*Arr[i][size - 1];
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

class Block 
{
	string plainTxt;//content of this block	
public:
	Block() : plainTxt(""){};
	Block(string str) : plainTxt(str){};

	void print()
	{
		cout << plainTxt << endl;
	}

	friend class PlainText;
	friend class Skitala;
	friend class Hill;
	friend class Vigenere;
	~Block(){};
};

class PlainText
{
	string originalTxt;
	Block* blocks[255];
	int blocksNum;
	bool wasDivided;
	bool ansiX923_;
	bool pkcs7_;
	bool iso10126_;
public:
	PlainText() : originalTxt(""), blocksNum(0), wasDivided(false),
		ansiX923_(false), pkcs7_(false), iso10126_(false)
	{
		for (int i = 0; i < 255; i++)
			blocks[i] = nullptr;
	}
	PlainText(string text) : originalTxt(text), blocksNum((text.length() - 1) / 8 + 1), 
		wasDivided(false), ansiX923_(false), pkcs7_(false), iso10126_(false)
	{
		for (int i = 0; i < 255; i++)
			blocks[i] = nullptr;
	}
	void print()
	{
		for(int i = 0; i < blocksNum; i++)
		{
			cout << blocks[i]->plainTxt << endl;
		}
		return;
	}
			
					/*TYPES OF PADDING*/
	// DD DD DD DD 00 00 00 04 (block = 8 bytes) WORK!
	void ansiX923(int blockSize) 
	{
		if (wasDivided == true)
			throw Err(0);
		else
		{
			int j = 0;
			int k = 0;
			string str;
			if (originalTxt.length() % blockSize == 0)
			{
				for (int i = 0; i < blocksNum; i++)
				{
					for (j; j < k + blockSize; j++)
					{
						str += originalTxt[j];
					}
					k = j;
					blocks[i] = new Block(str);
					str = "";
				}
			}
			else{
				for (int i = 0; i < blocksNum - 1; i++)
				{
					for (j; j < k + blockSize; j++)
					{
						str += originalTxt[j];
					}
					k = j;
					blocks[i] = new Block(str);
					str = "";
				}
				for (unsigned int i = 0; i < originalTxt.length() % blockSize; i++, j++)
				{
					str += originalTxt[j];
				}
				int* arr = new int[blockSize - originalTxt.length() % blockSize];
				for (unsigned int i = 0; i < blockSize - 1 - originalTxt.length() % blockSize; i++)
				{
					arr[i] = 0;
				}
				arr[blockSize - 1 - originalTxt.length() % blockSize] = blockSize - 1 - originalTxt.length() % blockSize;
				str += translate(arr, blockSize - originalTxt.length() % blockSize);
				blocks[blocksNum - 1] = new Block(str);
				delete[]arr;
				wasDivided = true;
				if (originalTxt.length() % blockSize != 0)
					ansiX923_ = true;
				originalTxt = "";
				for (int i = 0; i < blocksNum; i++){
					originalTxt += blocks[i]->plainTxt;
				}
			}
		}
		return;
	}
	// DD DD DD DD 04 04 04 04 (block = 8 bytes) CHANGE LIKE ANSI
	void pkcs7(int blockSize)
	{
		if (wasDivided == true)
			throw Err(0);
		else
		{
			int j = 0;
			int k = 0;
			string str;
			if (originalTxt.length() % blockSize == 0)
			{
				for (int i = 0; i < blocksNum; i++)
				{
					for (j; j < k + blockSize; j++)
					{
						str += originalTxt[j];
					}
					k = j;
					blocks[i] = new Block(str);
					str = "";
				}
			}
			else{
				for (int i = 0; i < blocksNum - 1; i++)
				{
					for (j; j < k + blockSize; j++)
					{
						str += originalTxt[j];
					}
					k = j;
					blocks[i] = new Block(str);
					str = "";
				}
				for (unsigned int i = 0; i < originalTxt.length() % blockSize; i++, j++)
				{
					str += originalTxt[j];
				}
				int* arr = new int[blockSize - originalTxt.length() % blockSize];
				for (unsigned int i = 0; i < blockSize - originalTxt.length() % blockSize; i++)
				{
					arr[i] = blockSize - 1 - originalTxt.length() % blockSize;
				}
				str += translate(arr, blockSize - originalTxt.length() % blockSize);
				blocks[blocksNum - 1] = new Block(str);
				delete[]arr;
				wasDivided = true;
				if (originalTxt.length() % blockSize != 0)
					pkcs7_ = true;
			}
		}
		return;
	}
	// DD DD DD DD 81 A6 23 04 ((empty-1) - random, last - number of empty) (block = 8 bytes) CHANGE LIKE ANSI
	void iso10126(int blockSize)
	{
		if (wasDivided == true)
			throw Err(0);
		else
		{
			int j = 0;
			int k = 0;
			string str;
			if (originalTxt.length() % blockSize == 0)
			{
				for (int i = 0; i < blocksNum; i++)
				{
					for (j; j < k + blockSize; j++)
					{
						str += originalTxt[j];
					}
					k = j;
					blocks[i] = new Block(str);
					str = "";
				}
			}
			else{
				for (int i = 0; i < blocksNum - 1; i++)
				{
					for (j; j < k + blockSize; j++)
					{
						str += originalTxt[j];
					}
					k = j;
					blocks[i] = new Block(str);
					str = "";
				}
				for (unsigned int i = 0; i < originalTxt.length() % blockSize; i++, j++)
				{
					str += originalTxt[j];
				}
				int* arr = new int[blockSize - originalTxt.length() % blockSize];
				srand((unsigned int)time(0));
				for (unsigned int i = 0; i < blockSize - 1 - originalTxt.length() % blockSize; i++)
				{
					arr[i] = rand() % 29; //случайные числа от 0 до 255 (mod 29)
				}
				arr[blockSize - 1 - originalTxt.length() % blockSize] = blockSize - originalTxt.length() % blockSize - 1;
				str += translate(arr, blockSize - originalTxt.length() % blockSize);
				blocks[blocksNum - 1] = new Block(str);
				delete[]arr;
				wasDivided = true;
				if (originalTxt.length() % blockSize != 0)
					iso10126_ = true;
			}
		}
		return;

	}

	friend class Block;
	friend class Skitala;
	friend class Vigenere;
	friend class Hill;
	~PlainText()
	{
		for (int i = 0; i < sizeof(blocks) / sizeof(blocks[0]); i++)
		{
			delete blocks[i];
		}
	}
};

class Skitala //минус - первый и последний символ совпадают
{
	int n; // num of rows
	int m; // num of columns
	char parchmentTable[2][4]; 
	string cipherText;
	Block* block;
public:
	Skitala(){};
	Skitala(Block* plain_bl) : cipherText(""), 
		block(plain_bl), n(2), m(4)
	{
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 4; j++)
				parchmentTable[i][j] = '\0';
	}

	string cipher()
	{
		int k = 0;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 4; j++, k++)
			{
				parchmentTable[i][j] = block->plainTxt[k];
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				cipherText += parchmentTable[j][i];
			}
		}
		return cipherText;
	}
	string decipher()
	{
		int k = 0;
		if (cipherText == "")
			throw Err(1);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++, k++)
			{
				parchmentTable[j][i] = cipherText[k];
			}
		}
		string result;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result += parchmentTable[i][j];
			}
		}
		return result;
	}

	void tryAlgorithm()
	{
		PlainText* pl = new PlainText("abcdefghabcdefghabc");
		pl->iso10126(8);
		Skitala sk(pl->blocks[0]);
		cout << "ciphered:   " << sk.cipher() << endl;
		cout << "deciphered: " << sk.decipher() << endl;
		delete pl;
		return;
	}

	friend class PlainText;
	~Skitala(){};
};

class Vigenere
{
	PlainText* plTxt;
	char** tabulaRecta;
	string key;
	string cTxt; //ciphered text
public:
	Vigenere(){};
	Vigenere(PlainText* obj, string keyword) : cTxt(""), plTxt(obj)
	{
		tabulaRecta = new char*[29];
		for (int i = 0; i < 29; i++)
			tabulaRecta[i] = new char[29];

		strcpy((char*)tabulaRecta[0], "abcdefghijklmnopqrstuvwxyz .?");
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

	//ECB (режим простой замены)
	string cipher()
	{
		string result;

		for (int x = 0; x < plTxt->blocksNum; x++)
		{
			for (int i = 0; i < 8; i++)
			{
				result += tabulaRecta[fromChar(key[i])][fromChar(plTxt->blocks[x]->plainTxt[i])];
			}
		}
		cTxt += result;
		return result;
	}

	//ECB (режим простой замены)
	string decipher()
	{
		string result;
		int k = 0;
		cout << "cTxt = " << cTxt << endl;
		PlainText* blocksC = new PlainText(cTxt);//делим строку зашифрованного текста на блоки по 8
		blocksC->pkcs7(8);
		blocksC->print();

		for (int x = 0; x < plTxt->blocksNum; x++)
		{
			for (int i = 0; i < 8; i++)
			{
				k=0;
				while (tabulaRecta[fromChar(key[i])][k] != blocksC->blocks[x]->plainTxt[i])
				{
					k++;
				}
				result += fromInt(k);
			}
		}
		return result;
	}

	//void tryA()
	//{
	//	Vigenere v(plTxt, "key");
	//	cout << "wanna to shifr " << plTxt->originalTxt << endl;
	//	cout << "ciphered:      " << v.cipher() << endl;
	//	cout << "deciphered:    " << v.decipher() << endl;
	//	cout << "okkk";
	//	return;
	//}

	friend class PlainText;
	~Vigenere() //????? don't work ????
	{
		for (unsigned int i = 0; i < 29; i++)
			delete[] tabulaRecta[i];
		delete[] tabulaRecta;
	}
};

class Hill //C = K*P; P = K^(-1)*C
{
	int** k; //матрица ключ 8x8
	int key;
	PlainText* plTxt; //шифруемый текст
	int* c; 
	string cTxt; //translated c
public:
	Hill(){};
	Hill(PlainText* obj, int key_) : plTxt(obj), cTxt(""), c(nullptr), key(key_)
	{
		srand(key_);
		k = new int*[8];
		for (int i = 0; i < 8; i++){
			k[i] = new int[8];
			for (int j = 0; j < 8; j++)
				k[i][j] = rand() % 29;
		}
	}

	string cipher()
	{
		for (int x = 0; x < plTxt->blocksNum; x++){
			int* p = translate(plTxt->blocks[x]->plainTxt); //вектор открытого текста
			c = new int[8];
			for (int i = 0; i < 8; i++)
				c[i] = 0;

			for (int i = 0; i < 8; i++){
				for (int j = 0; j < 8; j++)
					c[i] += k[i][j] * p[j];
				c[i] = c[i] % 29;
			}

			cTxt += translate(c, 8);
			delete[] c;
			delete[] p;
		}
		cout << endl << "want to cipher:  " << plTxt->originalTxt;
		cout << endl << "ciphered hill:   " << cTxt << endl;
		return cTxt;
	}

	string decipher()
	{
		k = invMatr(k);
		string pD = "";//deciphered plain text
		cout << "cTxt= " << cTxt << endl;
		PlainText* blocksC = new PlainText(cTxt);//делим строку зашифрованного текста на блоки по 8
		blocksC->pkcs7(8);
//		blocksC->print();
		cout << "----------------------" << endl;

		for (int x = 0; x < blocksC->blocksNum; x++){

			c = translate(blocksC->blocks[x]->plainTxt);

			int* p = new int[8];
			for (int i = 0; i < 8; i++)
				p[i] = 0;

			for (int i = 0; i < 8; i++){
				for (int j = 0; j < 8; j++)
					p[i] += k[i][j] * c[j];
				p[i] = p[i] % 29;
			}

			pD += translate(p, 8);
			delete[] p;
		}
		delete blocksC;
		delete[] c;
	
		//int* o = translate(ppp);
		//cout << o[ppp.length()-1] << endl;
		//if ((plTxt->ansiX923_==true) || (plTxt->iso10126_==true) || (plTxt->pkcs7_==true)){
		//	for (int i = 0; i < o[ppp.length()-1]; i++){
		//		ppp.erase(ppp.begin() + (ppp.length() - 1));
		//	}
		//}
		//delete o;
		cout << "deciphered hill: " << pD << endl;
		return pD;
	}
	
	friend int** invMatr(int**);
	friend class PlainText;

	//~Hill()
	//{
	//	for (int i = 0; i<)
	//}
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
				add[i][j-1] = matr[i][j];
			else if (i > x && j < y)
				add[i-1][j] = matr[i][j];
			else if (i>x && j>y)
				add[i-1][j-1] = matr[i][j];
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
			invM[i][j] = 0;
			invM[i][j] = determ(add, 7);
			invM[i][j] = invM[i][j] * invDet;
			invM[i][j] = invM[i][j] * pow(-1., (i + j));
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
	//for (int i = 0; i < 8; i++)
	//	delete[] add[i];
	//delete[] add;
	return matr;
}


int main()
{
	try
	{
		int** pp = new int*[8];
		for (int i = 0; i < 8; i++)
			pp[i] = new int[8];
		for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			pp[i][j] = rand() % 29;		
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
				cout << pp[i][j] << " ";
			cout << endl;
		}
		cout << "--------------" << endl;
		pp = invMatr(pp);
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
				cout << pp[i][j] << " ";
			cout << endl;
		}

		PlainText* pl = new PlainText("abcdefghabcdefghabc");
		pl->iso10126(8);
		Hill h(pl, 0);
		h.cipher();
		h.decipher();

		cout << "------------VIGENERE-------------" << endl;
		PlainText* plv = new PlainText("i am machine i never sleep");
		plv->iso10126(8);
		Vigenere v(plv, "key");
	//	cout << "wanna to shifr " << plv->originalTxt << endl;
		cout << "ciphered:      " << v.cipher() << endl;
		cout << "deciphered:    " << v.decipher() << endl;
		cout << "okkk";
		cout << "here";
		delete plv;
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
	}
	catch (Err& err)
	{
		switch (err.errType())
		{
		case 0:
			cerr << "this plain text has already been divided into blocks" << endl;
			break;
		case 1:
			cerr << "there's nothing to decipher" << endl;
			break;
		case 4:
			cerr << "number isn't in ring" << endl;
		}
	}
	system("pause");
	return 0;
}
