#include "functions.hpp"
#include <algorithm>

void Functions::Read_file(std::ifstream& fin, std::vector<char>& Alphabet, std::vector<float>& Probability, int& Arity)
{	
	int N = 0; 
	fin >> N; 

	char ch;
	for (int i = 0; i < N; i++)
	{
		fin >> ch;
		Alphabet.push_back(ch);
	}

	float prob = 0.0;
	for (int i = 0; i < N; i++)
	{
		fin >> prob;
		Probability.push_back(prob);
	}

	fin >> Arity; 
}

//"Container-leaf" of the code tree
class Container 
{
public:
	float probability = 0.0;
	std::string smb = "";
	std::string code = "";
	bool add_smb = false;
};

//Comparator of probalities
bool Compare_Probs(const Container& first, const Container& second) {
	return first.probability < second.probability;
}

//Comparator of lengths of "glued" symbols
bool Compare_Symbols(const Container& first, const Container& second) {
	return first.smb.size() > second.smb.size();
}

//Function of encoding input data
result Functions::Encode(const std::vector<char>& Alphabet, const std::vector<float>& Probability, const int& Arity) {
	result res;
	res.Ave_Len = 0.0; 
	float Prob_Sum = 0.0; 
	int zero_check = 0; 

	//Checking the correctness of the input probalities
	for (const auto& prob : Probability)
	{
		Prob_Sum += prob;

		if ((prob - 0.0) <= std::numeric_limits<float>::epsilon())
		{
			zero_check++;
		}
	}

	if ((abs(Prob_Sum - 1.0) >= std::numeric_limits<float>::epsilon()) || (zero_check == Probability.size()))
	{
		res.Ave_Len = -1.0;
		std::cout << "The probalities are incorrect" << std::endl;
		return res;
	}

	std::vector<Container> Cont_Vec; //Vector of "leaves" of code tree
	int Alphabet_size = Alphabet.size();
	//Adding start values into tree
	for (int i = 0; i < Alphabet_size; i++)
	{
		Container temp_Cont;
		temp_Cont.smb = Alphabet[i];
		temp_Cont.probability = Probability[i];
		Cont_Vec.push_back(temp_Cont);
	}

	//Counting the required number of fictitious symbols
	int k = 0, fictitious = 0;

	while (Cont_Vec.size() > Arity + k * (Arity - 1))
	{
		k++;
	}

	fictitious = Arity + k * (Arity - 1) - Cont_Vec.size();

	for (int i = 0; i < fictitious; i++) //Adding fictitious symbols into vector
	{
		Container temp_Cont;
		temp_Cont.probability = 0.0;
		temp_Cont.smb = "⁣"; //There is invisible separator as a fictitious symbol
		Cont_Vec.push_back(temp_Cont);
	}

	sort(Cont_Vec.begin(), Cont_Vec.end(), Compare_Probs); //Sorting start values by probalities

	std::vector<Container> Codes = Cont_Vec; //Vector which is needed for forming leaves codes

	if (Cont_Vec.size() <= Arity)
	{
		for (int i = 0; i < Cont_Vec.size(); i++)
		{
			Codes[i].code = std::to_string(i);
		}
	}
	else
	{
		for (int i = 0; i < Arity; i++) //Determining which characters will need to be appended to the code symbol
		{
			Cont_Vec[i].add_smb = true;
		}

		while (Cont_Vec.size() != 1)
		{
			int new_smb = Arity - 1; //New symbol of code

			for (int i = 0; i < Cont_Vec.size(); i++)
			{
				if (Cont_Vec[i].add_smb == true) //Finding the gluing, where new symbol of code is needed
				{
					for (int j = 0; j < Codes.size(); j++)
					{
						if (count(Cont_Vec[i].smb.begin(), Cont_Vec[i].smb.end(), Codes[j].smb[0])) 
						{
							Codes[j].code += std::to_string(new_smb); 
							if (new_smb == -1)
							{
								i = Cont_Vec.size();
								break;
							}
						}
					}

					new_smb--;
				}
			}

			int temp_start = 0;

			if (Arity <= Cont_Vec.size())
			{
				temp_start = Arity - 1;
			}
			else
			{
				temp_start = Cont_Vec.size();
			}

			sort(Cont_Vec.begin(), Cont_Vec.end(), Compare_Probs);

			for (int i = temp_start; i > 0; i--) //Adding probabilities and gluing symbols
			{
				Cont_Vec[0].probability += Cont_Vec[i].probability;
				Cont_Vec[0].smb += Cont_Vec[i].smb;
				Cont_Vec.erase(Cont_Vec.begin() + (i));
			}

			sort(Cont_Vec.begin(), Cont_Vec.end(), Compare_Probs);

			for (int i = 0; i < Cont_Vec.size(); i++)
			{
				if (i < Arity)
				{
					Cont_Vec[i].add_smb = true;
				}
				else
				{
					Cont_Vec[i].add_smb = false;
				}
			}

			sort(Cont_Vec.begin(), Cont_Vec.end(), Compare_Symbols); //Sorting the vector by the length of the glued characters
																	 //If the number of characters in the gluing is more than 1, then,
																	 //That you need to add code to them firstly to avoid
																	 //Situations when the code of one character = the beginning of the code of another
		}
	}

	//Reverse codes (now they are in reverse order)
	for (auto& code : Codes)
	{
		if ((code.probability - 0.0) > std::numeric_limits<float>::epsilon())
		{
			reverse(code.code.begin(), code.code.end());
			res.Ave_Len += code.probability * code.code.size();
			res.Codes.push_back(code.smb + " = " + code.code + " ");
		}
	}

	return res;
}

//Writing codes and their average length into output file
void Functions::Write_file(std::ofstream& fout, const result& res) 
{

	if (res.Ave_Len != (-1.0))
	{
		fout << "Codes: ";

		for (const auto& code : res.Codes)
		{
			fout << code << " ";
		}

		fout << std::endl << "Average Length = " << res.Ave_Len;
	}
}
