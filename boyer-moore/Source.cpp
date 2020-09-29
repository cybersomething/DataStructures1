//credit to Adam Sampson for help with implementing boyer moore program
#include <cassert>
#include <iostream>

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

//Find_name function to be executed when the main function calls it, passes in the username and name_text variable from main.
int find_name(string username, string name_text)
{
	//this variable is set to the number of characters in the the name and in the name text file.
	int name_len = username.size();
	int name_text_len = name_text.size();

	//Setting the array called skip to 256, which is representative of the alphabet in ASCII
	int skip[256];

	
	for (int i = 0; i < 256; i++)
		skip[i] = name_len;
	for (int i = 0; i < name_len; ++i)
		skip[int(username[i])] = (name_len - 1) - i;

	//Start skipping through text
	for (int i = 0; i < name_text_len - name_len; i++)
	{
		//set s to skip variable
		int s = skip[int(name_text[i + name_len - 1])];

		//not a match, continue skipping
		if (s != 0) 
		{
			i += s - 1; 
			continue;
		}

		//If first character is a match, check that the name matches the string
		int j;
		for (j = 0; j < name_len; j++) 
		{
			//if string doesn't match username, break out for statement and keep skipping
			if (name_text[i + j] != username[j])
				break;
		}
		//if string does match name, set name found boolean to true and return variable
		if (j == name_len) 
		{
			nameFound = true;
			return nameFound;
		}
	}
	//if name is not found in text, return default variable set to false
	return nameFound;
}

//function to find password in file
int find_pass(string password, string pass_text)
{
	//set variable values to the number of characters within the password and password text file
	int pass_len = password.size();
	int pass_text_len = pass_text.size();

	//set skip array to 256, which represents the alpahabet in ASCII
	int skip[256];

	for (int i = 0; i < 256; ++i)
		skip[i] = pass_len;
	for (int i = 0; i < pass_len; i++)
		skip[int(password[i])] = (pass_len - 1) - i;

	//start skipping through password text
	for (int i = 0; i < pass_text_len - pass_len; i++)
	{
		//set s to the value of skip variable
		int s = skip[int((unsigned char)pass_text[i + pass_len - 1])];

		//if skip isn't equal to 0, there is no match, continue skipping
		if (s != 0) 
		{
			i += s - 1;
			continue;
		}
		//If first character is a match, check that the password matches the string
		int j;
		for (j = 0; j < pass_len; j++) 
		{
			//if string doesn't match password, break out for statement and keep skipping
			if (pass_text[i + j] != password[j])
				break;
		}
		//if string does match password, set passFound boolean to true and return variable
		if (j == pass_len)
		{
			passFound = true;
			return passFound;
		}
	}

	//if password is not found in text, return default variable set to false
	return passFound; // Not found.
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

	//look at boolean variable for nameFound and passFound, if true display the warning and explain that the user/password has been found, 
	//if false post a small warning to look after account
	if(nameFound == true)
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
	std::cout << "It taken the Boyer-Moore program: " << time_taken << " milliseconds to run." << endl;

	return 0;
}
