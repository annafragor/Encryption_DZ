#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;
int* translate(string str)
{
	int* result = new int[str.length()];
	for (int i = 0; i < str.length(); i++)
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

class Block //размер блока по умолчанию 8 байт
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
	char operator[](int i)
	{
		return plainTxt[i];
	}

	friend class PlainText;
	~Block(){};
};

class PlainText
{
	string originalTxt;
	Block* blocks[255]; //массив указателей на блоки
	int blocksNum;
public:
	PlainText() : originalTxt(""), blocks(), blocksNum(0){};
	PlainText(string text) : originalTxt(text), blocks(), blocksNum((text.length()-1)/8 + 1){};

	void print()
	{
		cout << originalTxt.length() << endl;
		cout << blocksNum << endl;
		for(int i = 0; i < blocksNum; i++)
		{
			cout << blocks[i]->plainTxt;
		}
		return;
	}
	/*TYPES OF PADDING*/
	void ansiX923() // DD DD DD DD 00 00 00 04 (block = 8 bytes)
	{
		int j = 0;
		int k = 0;
		string str;
		for (int i = 0; i < blocksNum - 1; i++)
		{
			for (j; j < k + 8; j++)
			{
				str += originalTxt[j];
			}
			k = j;
			blocks[i] = new Block(str);
			str = "";
		//	blocks[i]->print();
		}
		for (unsigned int i = 0; i < originalTxt.length() % 8; i++, j++)
		{
			str += originalTxt[j];
		}
		int* arr = new int[8 - originalTxt.length() % 8];
		for (int i = 0; i < 8 - 1 - originalTxt.length() % 8; i++)
		{
			arr[i] = 0;
		}
		arr[8 - 1 - originalTxt.length() % 8] = 10;
		str += translate(arr, 8 - originalTxt.length() % 8);
		blocks[blocksNum-1] = new Block(str);
	//	blocks[blocksNum - 1]->print();
		delete[]arr;
	}
	void pkcs7() // DD DD DD DD 04 04 04 04 (block = 8 bytes)
	{

	}
	void iso10126() // DD DD DD DD 81 A6 23 04 ((empty-1) - random, last - number of empty) (block = 8 bytes)
	{

	}



	friend class Block;
	~PlainText()
	{
		for (int i = 0; i < sizeof(blocks) / sizeof(blocks[0]); i++)
		{
			delete blocks[i];
		}
	}
};

int main()
{
	try
	{
		int p[4] = { 0, 1, 2, 3 };
		translate("hello.");
		translate(p, 4);

		PlainText* pl = new PlainText("abcdefghabcdefghabc");
		cout << "....." << endl;
		pl->ansiX923();
		pl->print();
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
	}
	system("pause");
	return 0;
}
