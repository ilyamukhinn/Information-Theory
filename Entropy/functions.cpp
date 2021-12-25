#include "functions.hpp"

//Reading alphabet and probalities of symbols from file
void Functions::Read_file(std::ifstream& fin, std::vector<char>& Alphabet, std::vector<float>& Probability) {
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
}

//Calculation of Quantities of information and Entropy
result Functions::Get_Entropy(const std::vector<char>& Alphabet, const std::vector<float>& Probability) 
{
	result res;
	res.Entropy = 0.0;
	float Prob_Sum = 0.0;

	for (const auto& prob : Probability)
	{
		Prob_Sum += prob;
	}

	if (abs(Prob_Sum - 1.0) > 0.000001)
	{
		res.Entropy = -1.0;
		std::cout << "The probalities are incorrect" << std::endl;
		return res;
	}

	for (const auto& prob : Probability)
	{
		if (prob != 0.0)
		{
			float Inf_q = (-1.0) * (log(prob) / log(2));
			res.Inf_Quantity.push_back(Inf_q);
			res.Entropy += prob * Inf_q;
		}
		else
		{
			res.Inf_Quantity.push_back(INFINITY);
		}
	}

	return res;
}

//Writing calculated Quantities of information and Entropy into file
void Functions::Write_file(std::ofstream& fout, const result& res) 
{

	if (res.Entropy != -1.0)
	{
		fout << "Information Quantities: ";

		for (const auto& Inf_q : res.Inf_Quantity)
		{
			fout << Inf_q << " ";
		}

		fout << std::endl << "Entropy = " << res.Entropy;
	}
}
