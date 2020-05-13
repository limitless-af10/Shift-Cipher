// Discrete Math Encryption.cpp 

#include <iostream>
#include<string>
#include<fstream>

using namespace::std;

class Encryption
{
	
	char *keys;
	string cipher;

	void encrypt(string plainText, int shift)
	{
		shift = shift % 66;
		
		for (int i = 0; i < (int)plainText.length(); i++)
		{
			int index = this->getIndex(plainText[i]);

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
					
				this->cipher += keys[index];
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

	Encryption()
	{
		this->cipher = "";
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
		fin.open("Assignment 1_Plaintext.txt");

		string plainTemp = "";

		int shiftK;

		cout << "\n Enter value of K: ";
		cin >>shiftK;

		while (!fin.eof())
		{
			getline(fin,plainTemp);

			plainTemp += '\n';

			this->encrypt(plainTemp, shiftK);
		}

		fin.close();
	}

	void writeFile()
	{
		ofstream fout, fout2;

		fout2.open("Decryption\\Assignment 1_Cipher.txt");
		fout.open("Assignment 1_Cipher.txt");

		fout << this->cipher;
		fout2 << this->cipher;

		fout.close();
		fout2.close();

		cout << "\n Encryption Successfull (output stored in Assignment 1_Cipher.txt)\n\n";
	}

};

int main()
{
	Encryption obj;
	obj.readFile();
	obj.writeFile();
}
