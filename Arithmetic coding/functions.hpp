#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <iostream>
#include <vector>
//#include "mpir.h"
#include "lib_mpir_gc/x64/Release/mpir.h"

struct Code {
	mpf_t code;
	std::vector<char> Alphabet;
	mpf_t* Probabilities;
	int Message_size;
};

namespace Functions {
	void Read_file(FILE* fin, std::vector<char>& Str);
	Code Encode(const std::vector<char>& Str);
	std::vector<char> Decode(const Code& obj);
	void Write_file(FILE* fout, const Code& obj, const std::vector<char>& Message);
}

#endif // ! FUNCTIONS_H
