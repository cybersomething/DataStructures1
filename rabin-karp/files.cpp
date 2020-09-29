//Credit to Adam Sampson for load files and die functions

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "files.h"

using std::cerr;
using std::cout;
using std::ifstream;
using std::string;
using std::vector;

void die(const string& msg) {
	cerr << "Error: " << msg << "\n";
#ifdef _DEBUG
	abort();
#else
	exit(1);
#endif
}


void load_namesfile(const std::string& names_filename, std::string& names_str)
{
	std::string directory = "";
	for (int i = 0; i < 6; i++) {
		ifstream f(directory + names_filename, std::ios_base::binary);
		if (!f.good()) {
			directory = "../" + directory;
			continue;
		}

		// Seek to the end of the file to find its length.
		f.seekg(0, std::ios_base::end);
		const size_t length = f.tellg();

		// Seek back to the start of the file and read the data.
		vector<char> buf(length);
		f.seekg(0);
		f.read(buf.data(), length);
		names_str.assign(buf.begin(), buf.end());

		return;
	}

	die("Unable to find " + names_filename);
}

void load_names(std::string& name_str)
{
	load_namesfile("names.txt", name_str);
}

void load_passfile(const std::string& pass_filename, std::string& pass_str)
{
	std::string directory = "";
	for (int i = 0; i < 6; i++) {
		ifstream f(directory + pass_filename, std::ios_base::binary);
		if (!f.good()) {
			directory = "../" + directory;
			continue;
		}

		// Seek to the end of the file to find its length.
		f.seekg(0, std::ios_base::end);
		const size_t length = f.tellg();

		// Seek back to the start of the file and read the data.
		vector<char> buf(length);
		f.seekg(0);
		f.read(buf.data(), length);
		pass_str.assign(buf.begin(), buf.end());

		return;
	}

	die("Unable to find " + pass_filename);
}

void load_passwords(std::string& pass_str)
{
	load_passfile("rockyou.txt", pass_str);
}