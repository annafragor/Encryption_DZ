#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib> // srand
#include <time.h>

using namespace std;
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
		cout << originalTxt.length() << endl;
		cout << blocksNum << endl;
		for(int i = 0; i < blocksNum; i++)
		{
			cout << blocks[i]->plainTxt << endl;
		}
		return;
	}
			
					/*TYPES OF PADDING*/
	// DD DD DD DD 00 00 00 04 (block = 8 bytes)
	void ansiX923(int blockSize) 
	{
		if (wasDivided == true)
			throw Err(0);
		else
		{
			int j = 0;
			int k = 0;
			string str;
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
			arr[blockSize - 1 - originalTxt.length()%blockSize] = blockSize - 1 - originalTxt.length()%blockSize;
			str += translate(arr, blockSize - originalTxt.length() % blockSize);
			blocks[blocksNum - 1] = new Block(str);
			delete[]arr;
			wasDivided = true;
			ansiX923_ = true;
		}
		return;
	}
	// DD DD DD DD 04 04 04 04 (block = 8 bytes)
	void pkcs7(int blockSize)
	{
		if (wasDivided == true)
			throw Err(0);
		else
		{
			int j = 0;
			int k = 0;
			string str;
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
			pkcs7_ = true;
		}
		return;
	}
	// DD DD DD DD 81 A6 23 04 ((empty-1) - random, last - number of empty) (block = 8 bytes)
	void iso10126(int blockSize)
	{
		if (wasDivided == true)
			throw Err(0);
		else
		{
			int j = 0;
			int k = 0;
			string str;
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
				arr[i] = (rand()%255)%29; //случайные числа от 0 до 255 (mod 29)
			}
			arr[blockSize - 1 - originalTxt.length() % blockSize] = blockSize - originalTxt.length() % blockSize;
			str += translate(arr, blockSize - originalTxt.length() % blockSize);
			blocks[blocksNum - 1] = new Block(str);
			delete[]arr;
			wasDivided = true;
			iso10126_ = true;
		}
		return;

	}

	friend class Block;
	friend class Skitala;
	friend class Vigenere;
	friend class Scrambler<Skitala>;
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
	Block* block;
	char** tabulaRecta;
	string key;
	string cTxt; //ciphered text
public:
	Vigenere(){};
	Vigenere(Block* obj, string keyword) : cTxt(""), block(obj)
	{
		tabulaRecta = new char*[29];
		for (int i = 0; i < 29; i++)
			tabulaRecta[i] = new char[29];

		tabulaRecta[0] = "abcdefghijklmnopqrstuvwxyz .?";
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

	string cipher()
	{
		string result;
		for (int i = 0; i < 8; i++)
		{
			result += tabulaRecta[fromChar(key[i])][fromChar(block->plainTxt[i])];
		}
		cTxt = result;
		return result;
	}
	string decipher()
	{
		string result;
		int k = 0;
		for (int i = 0; i < 8; i++)
		{
			while (tabulaRecta[fromChar(key[i])][k] != cTxt[i])
			{
				k++;
			}
			result += fromInt(k);
		}
		return result;
	}

	void tryA()
	{
		PlainText* pl = new PlainText("abcdefghabcdefghabc");
		pl->iso10126(8);
		Vigenere v(pl->blocks[0], "key");
		cout << "wanna to shifr " << pl->blocks[0]->plainTxt << endl;
		cout << "ciphered:      " << v.cipher() << endl;
		cout << "deciphered:    " << v.decipher() << endl;
		delete pl;
		return;
	}

	friend class PlainText;
	~Vigenere() //????? don't work ????
	{
		//for (unsigned int i = 0; i < 29; i++)
		//	delete[] tabulaRecta[i];
		//delete[] tabulaRecta;
	}
};

class Hill //C = P*K; P = C*K^(-1)
{
	int** k; //матрица ключ
	Block block; //шифруемый блок
	int* c; //столбец зашифрованный
	string cipheredTxt; //translated c
public:
	Hill(){};


	friend class Block;
	~Hill(){};
};


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


template <class T>
class Scrambler
{
	PlainText* p;
	Block* c[255]; //ciphered blocks
//	T alg;

public:
	Scrambler<>(){};
	Scrambler<>(PlainText* obj) : p(obj);

	//template <class T>
	void ecbCipher(char ch)
	{
		switch (ch)
		{
		case 'i': //iso10126
			p->iso10126(8);
			break;
		case 'a': //ansiX923
			p->ansiX923(8);
			break;
		case 'p': //pkcs7
			P->pkcs7(8);
			break;
		}
		for (int i = 0; i < p->blocksNum; i++)
		{
			T alg(p->blocks[i]);
			cout << "  ciphered[" << i << "]: " << alg.cipher() << endl;
			cout << "deciphered[" << i << "]: " << alg.decipher() << endl;
		}
	}
	void ecbDecipher()
	{

	}
	friend class PlainText;
	friend class Skitala;
	friend class Vigenere;
	friend class Hill;
	~Scrambler<>(){};
};

int main()
{
	try
	{
		int p[4] = { 0, 1, 2, 3 };
		translate("hello.");
		translate(p, 4);

		cout << "....." << endl;
		Vigenere s;
		s.tryA();
		cout << endl << "....." << endl;
		int** pp = new int*[3];
		for (int i = 0; i < 3; i++)
			pp[i] = new int[3];
		for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			pp[i][j] = rand() % 10;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				cout << pp[i][j] << " ";
			cout << endl;
		}
		cout << "....." << endl;

		PlainText* pl = new PlainText("abcdefghabcdefghabc");
		Scrambler<Skitala>;
		Scrambler<Skitala> obj(pl);
		obj.ecbCipher('a');

	//	cout << endl << "det = " << det(pp, 3);
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
		}
	}
	system("pause");
	return 0;
}
