//credit to adam sampson for load files and die functions

#ifndef FILES_H
#define FILES_H

#include <string>

void die(const std::string& error_message);

void load_namesfile(const std::string& names_filename, std::string& names_str);

void load_names(std::string& str);

void load_passfile(const std::string& pass_filename, std::string& pass_str);

void load_passwords(std::string& str);

#endif