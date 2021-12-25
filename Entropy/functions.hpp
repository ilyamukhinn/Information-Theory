#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

//The quantity of information per one symbol and Entropy
struct result 
{
	std::vector<double> Inf_Quantity;
	double Entropy;
};

namespace Functions 
{
	void Read_file(std::ifstream & fin, std::vector<char>& Alphabet, std::vector<float>& Probability);
	result Get_Entropy(const std::vector<char>& Alphabet, const std::vector<float>& Probability);
	void Write_file(std::ofstream& fout, const result& res);
}

#endif // ! FUNCTIONS_H
