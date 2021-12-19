// C++ program to illustrate Rail Fence Cipher
// Encryption and Decryption

#include <iostream>

using namespace std;

// function to encrypt a message
string encryption(string plain_text, int key)
{
	// create the matrix to cipher plain text
	// key = rows , length(text) = columns
	char rail[key][(plain_text.length())];

	// filling the rail matrix to distinguish filled
	// spaces from blank ones
	for (int i=0; i < key; i++)
		for (int j = 0; j < plain_text.length(); j++)
			rail[i][j] = '\n';

	// to find the direction
	bool dir_down = false;
	int row = 0, col = 0;

	for (int i=0; i < plain_text.length(); i++)
	{
		// check the direction of flow
		// reverse the direction if we've just
		// filled the top or bottom rail
		if (row == 0 || row == key-1)
			dir_down = !dir_down;

		// fill the corresponding alphabet
		rail[row][col++] = plain_text[i];

		// find the next row using direction flag
		if (dir_down == true)
			row++;
		else
			row--;
		//dir_down?row++ : row--;
	}

	//now we can construct the cipher using the rail matrix
	string result;
	for (int i=0; i < key; i++)
		for (int j=0; j < plain_text.length(); j++)
			if (rail[i][j]!='\n')
				result.push_back(rail[i][j]);

	return result;
}

// This function receives cipher-text and key
// and returns the original text after decryption
string decryption(string cipher_text, int key)
{
	// create the matrix to cipher plain text
	// key = rows , length(text) = columns
	char rail[key][cipher_text.length()];

	// filling the rail matrix to distinguish filled
	// spaces from blank ones
	for (int i=0; i < key; i++)
		for (int j=0; j < cipher_text.length(); j++)
			rail[i][j] = '\n';

	// to find the direction
	bool dir_down;

	int row = 0, col = 0;

	// mark the places with '*'
	for (int i=0; i < cipher_text.length(); i++)
	{
		// check the direction of flow
		if (row == 0)
			dir_down = true;
		if (row == key-1)
			dir_down = false;

		// place the marker
		rail[row][col++] = '*';

		// find the next row using direction flag
		dir_down?row++ : row--;
	}

	// now we can construct the fill the rail matrix
	int index = 0;
	for (int i=0; i<key; i++)
		for (int j=0; j<cipher_text.length(); j++)
			if (rail[i][j] == '*' && index<cipher_text.length())
				rail[i][j] = cipher_text[index++];


	// now read the matrix in zig-zag manner to construct
	// the resultant text
	string result;

	row = 0, col = 0;
	for (int i=0; i< cipher_text.length(); i++)
	{
		// check the direction of flow
		if (row == 0)
			dir_down = true;
		if (row == key-1)
			dir_down = false;

		// place the marker
		if (rail[row][col] != '*')
			result.push_back(rail[row][col++]);

		// find the next row using direction flag
		dir_down?row++: row--;
	}
	return result;
}

//driver program to check the above functions
int main()
{
	cout << encryption("attack at once", 2) << endl;
	cout << encryption("Geeks for Geeks", 3) << endl;
	cout << encryption("defend the east wall", 3) << endl<<endl;

	cout<<"*************************************************************************"<<endl<<endl;

	//Now decryption of the same cipher-text
	cout << decryption("atc toctaka ne",2) << endl;
	cout << decryption("Gsreek o ekefGs",3) << endl;
	cout << decryption("dnhaweedtees alf  tl",3) << endl;

	return 0;
}

