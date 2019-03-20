#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Word.h"

class Txt_File
{
public:
	Txt_File(const std::string & dir);
	~Txt_File();
	std::vector<std::string> get_lines();
	std::fstream * get_file();
private:
	std::fstream * file;
	std::string directory;
	bool open();
	void close();
};

