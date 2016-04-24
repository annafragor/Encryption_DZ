#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib> //для srand
#include <time.h>

using namespace std;
int* translate(string str)
{
	int* result = new int[str.length()];
	for (unsigned int i = 0; i < str.length(); i++)
	{
		switch (str[i])
		{
		case 'a': result[i] = 0; break;
		case 'b': result[i] = 1; break;
		case 'c': result[i] = 2; break;
		case 'd': result[i] = 3; break;
		case 'e': result[i] = 4; break;
		case 'f': result[i] = 5; break;
		case 'g': result[i] = 6; break;
		case 'h': result[i] = 7; break;
		case 'i': result[i] = 8; break;
		case 'j': result[i] = 9; break;
		case 'k': result[i] = 10; break;
		case 'l': result[i] = 11; break;
		case 'm': result[i] = 12; break;
		case 'n': result[i] = 13; break;
		case 'o': result[i] = 14; break;
		case 'p': result[i] = 15; break;
		case 'q': result[i] = 16; break; 
		case 'r': result[i] = 17; break;
		case 's': result[i] = 18; break;
		case 't': result[i] = 19; break;
		case 'u': result[i] = 20; break;
		case 'v': result[i] = 21; break;
		case 'w': result[i] = 22; break;
		case 'x': result[i] = 23; break;
		case 'y': result[i] = 24; break;
		case 'z': result[i] = 25; break;
		case ' ': result[i] = 26; break;
		case '.': result[i] = 27; break;
		case '?': result[i] = 28; break;
		default:
			throw out_of_range("wrong input symbol");
		}
	}
	return result;
}
string translate(int* arr, int length)
{
	string result;
	for (int i = 0; i < length; i++)
	{
		switch (arr[i])
		{
		case 0: result += 'a'; break;
		case 1: result += 'b'; break;
		case 2: result += 'c'; break;
		case 3: result += 'd'; break;
		case 4: result += 'e'; break;
		case 5: result += 'f'; break;
		case 6: result += 'g'; break;
		case 7: result += 'h'; break;
		case 8: result += 'i'; break;
		case 9: result += 'j'; break;
		case 10: result += 'k'; break;
		case 11: result += 'l'; break;
		case 12: result += 'm'; break;
		case 13: result += 'n'; break;
		case 14: result += 'o'; break;
		case 15: result += 'p'; break;
		case 16: result += 'q'; break;
		case 17: result += 'r'; break;
		case 18: result += 's'; break;
		case 19: result += 't'; break;
		case 20: result += 'u'; break;
		case 21: result += 'v'; break;
		case 22: result += 'w'; break;
		case 23: result += 'x'; break;
		case 24: result += 'y'; break;
		case 25: result += 'z'; break;
		case 26: result += ' '; break;
		case 27: result += '.'; break;
		case 28: result += '?'; break;
		default:
			throw out_of_range("wrong input symbol");
		}
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
	string plainTxt;//содержание данного блока
	int* trPlainTxt;//translated - переведенный в числовой вид блок
	
public:
	Block() : trPlainTxt(nullptr), plainTxt(""){};
	Block(string str) : plainTxt(str), trPlainTxt(translate(str)){};

	void print()
	{
		cout << plainTxt << endl;
	}

	friend class PlainText;
	friend class Skitala;
	~Block(){};
};

class PlainText
{
	string originalTxt;
	Block* blocks[255]; //массив указателей на блоки
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
	int n; // количество строк
	int m; // количество столбцов
	char parchmentTable[2][4]; // пергаментная табличка :)
	string cipherText;
	Block* block; // указатель на шифруемый блок
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
		Skitala sk(pl->blocks[2]);
		cout << "ciphered:   " << sk.cipher() << endl;
		cout << "deciphered: " << sk.decipher() << endl;
		return;
	}

	friend class Block;
	friend class PlainText;
	~Skitala(){};
};


int main()
{
	try
	{
		int p[4] = { 0, 1, 2, 3 };
		translate("hello.");
		translate(p, 4);

		Skitala s;
		s.tryAlgorithm();
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
