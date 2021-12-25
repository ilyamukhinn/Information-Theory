#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <iostream>
#include <vector>
#include <bitset>

namespace Functions 
{
	void Read_file(FILE* fin, std::vector<char>& Str);
	std::vector<std::bitset<12>> Encode(const std::vector<char>& Str);
	void Check_codes(std::vector<std::bitset<12>>& Codes);
	std::vector<char> Decode(const std::vector<std::bitset<12>>& Codes);
	void Write_file(FILE* fout, const std::vector<std::bitset<12>>& Codes, const std::vector<char>& Message);
}

#endif // ! FUNCTIONS_H
