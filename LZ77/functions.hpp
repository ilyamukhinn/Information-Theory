#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <iostream>
#include <vector>

//Code consists sequences of symbols with offsets and lengths of these sequences in message
struct Code 
{
	std::vector<int> offsets, lengths;
	std::vector<char> symbols;
};

namespace Functions 
{
	void Read_file(FILE* fin, std::vector<char>& Str);
	Code Encode(const std::vector<char>& Str);
	std::vector<char> Decode(const Code& code);
	void Write_file(FILE* fout, const Code& code, const std::vector<char>& Message);
}

#endif // ! FUNCTIONS_H
