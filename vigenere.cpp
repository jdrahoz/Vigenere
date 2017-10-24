
// --------------------------------------------------- //
// vigenere.cpp
// --------------------------------------------------- //

// includes
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// function declarations
void bruteForceCrack (string m, int k_length, int fw_length);
void getKeys (string* possible_keys, int num_keys, char alphabet[], int alphabet_length, char str[], int current_length,  int k_length);
string encrypt (string m, string k);
string decrypt (string m, string k);
char intToChar (int x);
int charToInt (char x);

// --------------------------------------------------- //
// main function
// --------------------------------------------------- //

int main ()
{
	cout << "\n------------------------------------------------\n";
	cout << "\n----------- BREAKING VIGENERE CIPHER -----------\n";

	string ciphertext = "MTZHZEOQKASVBDOWMWMKMNYIIHVWPEXJA";
	int keyLength = 4;
	int firstWordLength = 10;

	cout << "\n------------------------------------------------\n";
	cout << "CIPHERTEXT : " << ciphertext << "\n";
	cout << "KEY LENGTH : " << keyLength << "\n";
	cout << "FIRST WORD LENGTH : " << firstWordLength << "\n";
	cout << "\n------------------------------------------------\n";

	bruteForceCrack (ciphertext, keyLength, firstWordLength);

	cout << "\n--------------- DECRYPTION DONE ----------------\n";
	cout << "\n------------------------------------------------\n";
}

// --------------------------------------------------- //
// brute force cracker
// --------------------------------------------------- //

void bruteForceCrack (string m, int k_length, int fw_length)
{
	// calculate number of possible keys
	int num_keys = 1;
	for (int i = 0; i < k_length; i++)
	{
		num_keys = num_keys * 26;
	}

	// generate array of all possible keys
	string* possible_keys = new string [num_keys];
	for (int i = 0; i < num_keys; i++)
	{
		possible_keys[i] = ".";
	}

	cout << "GENERATING KEYS\n";

	// recursive function to generate keys
	char alphabet [26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char arr[10]= "";
    getKeys (possible_keys, num_keys, alphabet, 26, arr, 0, k_length);

	cout << "ATTEMPTING DECRYPTION\n";

	// get first word to test
	string fw = m.substr (0, fw_length);

	// generate plaintext from each possible key
	for (int i = 0; i < num_keys; i++)
	{
		// decrypt first word
		string fw_decrypted = decrypt (fw, possible_keys[i]);

		// check if plaintext word is in dictionary
		ifstream  stream ("dictionary.txt");
		string word;
		while (getline (stream, word))
		{
			// found!
		    if (word.find (fw_decrypted) != string::npos && word.length () == fw_length)
			{
				cout << "POSSIBLE PLAINTEXT FOUND!\n";
				cout << "KEY : " << possible_keys[i] << "\n";


				// decrypt whole ciphertext using key
				string whole_decrypted = decrypt (m, possible_keys[i]);
		        cout << whole_decrypted << "\n";
		    }
		}
	}

	cout << "ALL KEYS TESTED\n";

	// delete arrays
	delete[] possible_keys;
}

// --------------------------------------------------- //
// helper functions
// --------------------------------------------------- //

void getKeys (string* possible_keys, int num_keys, char alphabet[], int alphabet_length, char str[], int current_length,  int k_length)
{
	// base case: string is at correct length
    if (current_length == k_length)
    {
		// add to list of possible keys
		for (int i = 0; i < num_keys; i++)
		{
			if (possible_keys[i] == ".")
			{
				possible_keys[i] = str;
				return;
			}
		}
        return;

	// recursive step: add another letter
    } else
    {
		// add each letter of alphabet
        for (int i = 0; i < alphabet_length; i++)
        {
            str[current_length] = alphabet[i];
            getKeys (possible_keys, num_keys, alphabet, alphabet_length, str, current_length + 1, k_length);
        }
    }
}

// --------------------------------------------------- //
// encrypt and decrypt functions
// --------------------------------------------------- //

string encrypt (string m, string k)
{
	// remove all spaces
	m.erase (remove (m.begin (), m.end (), ' '), m.end ());

	// convert m to uppercase
	int i = 0;
	while (m[i])
	{
		m[i] = toupper (m[i]);
		i++;
	}
	i = 0;

	// convert m to number array
	i = 0;
	int m2[m.length ()];
	while (m[i])
	{
		m2[i] = charToInt (m[i]);
		i++;
	}

	// convert k to number array
	i = 0;
	int k2[k.length ()];
	while (k[i])
	{
		k2[i] = charToInt (k[i]);
		i++;
	}

	// encrypt
	i = 0;
	int i2 = 0;
	while (m[i])
	{
		i2 = i % k.length ();
		m2[i] = (m2[i] + k2[i2]) % 26;
		i++;
	}

	// convert m back to char array
	i = 0;
	while (m[i])
	{
		m[i] = intToChar (m2[i]);
		i++;
	}

	// return encrypted m
	return m;
}

string decrypt (string m, string k)
{
	// convert m to number array
	int i = 0;
	int m2[m.length ()];
	while (m[i])
	{
		m2[i] = charToInt (m[i]);
		i++;
	}

	// convert k to number array
	i = 0;
	int k2[k.length ()];
	while (k[i])
	{
		k2[i] = charToInt (k[i]);
		i++;
	}

	// decrypt
	i = 0;
	int i2 = 0;
	while (m[i])
	{
		i2 = i % k.length ();
		m2[i] =  m2[i] - k2[i2];
		if (m2[i] < 0)
		{
			m2[i] = 26 + m2[i];
		}
		i++;
	}

	// convert m back to char array
	i = 0;
	while (m[i])
	{
		m[i] = intToChar (m2[i]);
		i++;
	}

	// return decrypted m
	return m;
}

// --------------------------------------------------- //
// helper functions
// --------------------------------------------------- //

char intToChar (int x)
{
	return "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[x];
}

int charToInt (char x)
{
	return (int) x - 65;
}
