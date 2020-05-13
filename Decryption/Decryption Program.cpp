// Discrete Math Decryption.cpp 

#include <iostream>
#include<string>
#include<fstream>

using namespace::std;

class Encryption
{

	char *keys;
	string plainText;
	int shiftValue;

	void decrypt(string cipher, int shift)
	{
		shift = shift % 66;
		shift *= -1;

		for (int i = 0; i < (int)cipher.length(); i++)
		{
			int index = this->getIndex(cipher[i]);

			if (index != -1)
			{
				index += shift;

				if (index > 65)
				{
					index = index - 66;
				}

				else if (index < 0)
				{
					index = index + 66;
				}

				this->plainText += keys[index];
			}
		}
	}

	int getIndex(char alphanumb)
	{
		for (int i = 0; i < 66; i++)
		{
			if (keys[i] == alphanumb)
				return i;
		}

		return -1;
	}

public:
	
	void findShiftValue()
	{
		char cipherAlpha;

		ifstream fin;
		fin.open("Assignment 1_Cipher.txt");

		fin >> cipherAlpha;

		this->shiftValue = this->getIndex(cipherAlpha) - 17;

	}

	Encryption()
	{
		this->plainText = "";
		this->shiftValue = 0;
		keys = new char[66];

		keys[0] = '\n';
		keys[1] = ' ';
		keys[2] = ',';
		keys[3] = '.';

		for (int i = 4; i < 66; i++)
		{
			if (i <= 13)
			{
				keys[i] = (i - 4) + 48;
			}

			if (i > 13 && i <= 39)
			{
				keys[i] = i + 51;
			}

			if (i > 39 && i <= 65)
			{
				keys[i] = i + 57;
			}
		}
	}

	void readFile()
	{
		ifstream fin;
		fin.open("Assignment 1_Cipher.txt");

		string cipherTemp = "";

		while (!fin.eof())
		{
			getline(fin, cipherTemp);
			cipherTemp+='\n';

			this->decrypt(cipherTemp, this->shiftValue);
		}

        plainText=plainText.substr(0, plainText.length() - 1);
		cout << "\n Decryption Successfull (output in Assignment 1_plaintext_out.txt)\n\n";

		fin.close();
	}

	void writeFile()
	{
		ofstream fout;

		fout.open("Assignment 1_plaintext_out.txt");

		fout << this->plainText;

		fout.close();
	}

};

int main()
{
	Encryption obj;

	obj.findShiftValue();
	obj.readFile();
	
	obj.writeFile();

}


