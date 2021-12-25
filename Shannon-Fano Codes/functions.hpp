#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

struct result 
{
	std::vector<std::string> Codes;
	float Ave_Len;
};

namespace Functions 
{
	void Read_file(std::ifstream& fin, std::vector<char>& Alphabet, std::vector<float>& Probability, int& Arity);
	result Encode(const std::vector<char>& Alphabet, const std::vector<float>& Probability, const int& Arity);
	void Write_file(std::ofstream& fout, const result& res);
}

#endif // ! FUNCTIONS_H
