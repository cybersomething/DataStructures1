//credit to Adam Sampson and Geeks 4 Geeks for inspiration with implementing rolling hash code
#include <cassert>
#include <iostream>
#include <fstream>

#include <assert.h>
#include "files.h"

//include library and variables for the system clock to run
#include <chrono>
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using the_clock = std::chrono::steady_clock;

//include the standard libraries for cout, cin, endl and string.
using std::cout;
using std::cin;
using std::endl;
using std::string;

//Create booleans to detect if name and password has been found
bool nameFound = false;
bool passFound = false;	

//set macro 'd' to 256, which is representative of the alphabet in ASCII
#define d 256

//Find_name function to be executed when the main function calls it, passes in the username and name_text variable from main.
int find_name(string username, string name_text)
{
	int username_hash = 0;
	int name_text_hash = 0;
	int hash = 1;

	//prime number is as high because if it's smaller, the total number of hash values are reduced
	//this means there are more hash matches increasing the time spent checking each matching hash
	const int prime_number = 101;

	//this variable is set to the number of characters in the the name and in the name text file.
	int name_len = username.size();
	int name_text_len = name_text.size();

	int i;

	//setting the hash value to the hash multiplied by the macro, then divided by the prime_number
	for (i = 0; i < name_len - 1; i++)
		hash = (hash * d) % prime_number;

	//getting the username hash and the first part of text file hash.
	for (i = 0; i < name_len; i++)
	{
		username_hash = (d * username_hash + username[i]) % prime_number;
		name_text_hash = (d * name_text_hash + name_text[i]) % prime_number;
	}

	//begin rolling hash and checking to see if there's a match
	for (i = 0; i < name_text_len - name_len; i++)
	{
		//if there's a match between the username hash and the text hash...
		if (username_hash == name_text_hash)
		{
			int j;
			//check to see if it matches, if not carry on till it matches or reaches end of text
			for (j = 0; j < name_len; j++) {
				if (name_text[i + j] != username[j])
					break;
			}
			//if it does match, set nameFound to true and then return the nameFound variable
			if (j == name_len)
			{
				nameFound = true;
				return nameFound;
			}
		}

		//code for rolling hash, if there's not a match get rid of the leading character hash and calculate the next character hash
		if (i < name_text_len - name_len) {
			name_text_hash = (d * (name_text_hash - name_text[i] * hash) + name_text[i + name_len]) % prime_number;
			//if it's a negative hash, create a positive hash
			if (name_text_hash < 0)
				name_text_hash = (name_text_hash + prime_number);
		}
	}
	//if a match is not found, return nameFound with set false boolean
	return nameFound;
}


int find_pass(string password, string pass_text)
{
	int pass_hash = 0;
	int pass_text_hash = 0;
	int hash = 1;

	//prime number is as high because if it's smaller, the total number of hash values are reduced
	//this means there are more hash matches increasing the time spent checking each matching hash
	const int prime_number = 101;

	//this variable is set to the number of characters in the password and the password text file.
	int pass_len = password.size();
	int pass_text_len = pass_text.size();

	int i;

	//setting the hash value to the hash multiplied by the macro, then divided by the prime_number
	for (i = 0; i < pass_len - 1; i++)
		hash = (hash * d) % prime_number;

	//getting the password hash and the first part of text file hash.
	for (i = 0; i < pass_len; i++)
	{
		pass_hash = (d * pass_hash + password[i]) % prime_number;
		pass_text_hash = (d * pass_text_hash + pass_text[i]) % prime_number;
	}

	//begin rolling hash and checking to see if there's a match
	for (i = 0; i <= pass_text_len - pass_len; i++)
	{
		//if there's a match between the password hash and the text hash...
		if (pass_hash == pass_text_hash)
		{
			int j;
			//check to see if it matches, if not carry on till it matches or reaches end of text
			for (j = 0; j < pass_len; j++) {
				if (pass_text[i + j] != password[j])
					break;
			}
			//if it does match, set nameFound to true and then return the nameFound variable
			if (j == pass_len)
			{
				passFound = true;
				return passFound;
			}
		}

		//code for rolling hash, if there's not a match get rid of the leading character hash and calculate the next character hash
		if (i < pass_text_len - pass_len) {
			pass_text_hash = (d * (pass_text_hash - pass_text[i] * hash) + pass_text[i + pass_len]) % prime_number;
			if (pass_text_hash < 0)
				pass_text_hash = (pass_text_hash + prime_number);
		}
	}

	//if not found, return passFound with set value of false.
	return passFound;
}

int main(int argc, char* argv[])
{
	std::string username;
	std::string password;

	//prompt user to enter username and password
	cout << "Welcome to the Password Finder" << endl;
	cout << "This program will see if your username and password has been leaked in a databreach." << endl;
	cout << "Please enter your username" << endl;
	cin >> username;
	cout << "Now enter your password." << endl;
	cin >> password;


	//finding name within database excerpt
	string name_text;
	load_names(name_text);
	load_namesfile("names.txt", name_text);

	//finding password within database excerpt
	string pass_text;
	load_passwords(pass_text);
	load_passfile("rockyou.txt", pass_text);

	//start the clock, to perform measurements
	the_clock::time_point startTime = the_clock::now();

	nameFound = find_name(username, name_text);
	passFound = find_pass(password, pass_text);

	//end the clock, to perform measurements
	the_clock::time_point endTime = the_clock::now();
	auto time_taken = duration_cast<milliseconds>(endTime - startTime).count();

	//Look at boolean variable for nameFound and passFound, if true display the warning and explain that the user/password has been found, 
	//if false post a small warning to look after account
	if (nameFound == true)
	{
		std::cout << "**********WARNING**********" << endl;
		std::cout << "Your name was found within a breached database! Take measures to secure your accounts now." << endl;
		std::cout << "***************************" << endl;
	}
	else
	{
		std::cout << "!!! ATTENTION !!!" << endl;
		std::cout << "Your name was not found within a breached database. You are safe, however it may be worthwhile taking precautionary measures to secure your account from an attack." << endl;
		std::cout << "!!! ********* !!!" << endl;
	}

	if (passFound == true)
	{
		std::cout << "**********WARNING**********" << endl;
		std::cout << "Your password was found within a breached database! Change your password immediately!" << endl;
		std::cout << "****************************" << endl;
	}
	else
	{
		std::cout << "!!! ATTENTION !!!" << endl;
		std::cout << "Your password was not found within a breached database. It may be worthwhile taking precautionary measures to secure your account however." << endl;
		std::cout << "!!! ********* !!!" << endl;
	}

	//Display how long it taken the program to run
	std::cout << "It taken the Rabin Karp program: " << time_taken << " milliseconds to run." << endl;

	return 0;
}