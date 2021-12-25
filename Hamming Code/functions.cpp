#include "functions.hpp"

#include <math.h>

//Reading message from the input file
void Functions::Read_file(FILE* fin, std::vector<char>& Str)
{
	char ch = '\0';

	while ((ch = fgetc(fin)) != EOF)
	{
		Str.push_back(ch);
	}

	fclose(fin);
}

//Encoding functions
std::vector<std::bitset<12>> Functions::Encode(const std::vector<char>& Str)
{
	std::vector<std::bitset<12>> Codes;

	int Str_size = Str.size();
	for (int i = 0; i < Str_size; i++)
	{
		std::string str_code = ((std::bitset<8>)Str[i]).to_string(); //Getting 8-digit binary code of the message symbol

		for (int j = 0; j < 4; j++) //Adding control bits
		{
			str_code.insert(pow(2,j) - 1, "0");
		}

		int control_bits[4] = { 0 }; //Array of sums of bit values that are "controlled" by control bits

		int pow_num = 0; //A number that determines the power of two to obtain the number of the control bit and determine the step of the pass through the code
		int start = 0; //The number of the control bit, this is the same place from which we begin to pass the code

		for (int p = 0; p < 4; p++)
		{
			start = pow(2, pow_num) - 1; 
			pow_num++; 

			for (int j = start; j < 12; j += pow(2, pow_num)) //pow(2, pow_num) determines the step of the pass through the code
			{
				for (int k = j; k < j + pow(2, pow_num - 1); k++) //pass cycle from j to j + step/2 to go through half of the segment of bits, and skip the second
				{												  
					if ((k < 12) && (str_code[k] == '1'))
					{
						control_bits[p]++; 
					}
				}
			}

			control_bits[p] = control_bits[p] % 2; //Getting value of control bit

			str_code[pow(2, p) - 1] = (char)(((int)'0') + control_bits[p]); //Writing value of control bit into code
		}

		Codes.push_back((std::bitset<12>)str_code);
	}
	
	return Codes;
}

//Function of checking correctness of codes
void Functions::Check_codes(std::vector<std::bitset<12>>& Codes)
{
	int Codes_size = Codes.size();
	for (int i = 0; i < Codes_size; i++)
	{
		std::string str_code = Codes[i].to_string();

		//Zeroing the values of the control bits
		for (int j = 0; j < 4; j++)
		{
			str_code[pow(2, j) - 1] = '0';
		}

		int control_bits[4] = { 0 };

		int pow_num = 0;
		int start = 0;

		for (int p = 0; p < 4; p++)
		{
			start = pow(2, pow_num) - 1;
			pow_num++;

			for (int j = start; j < 12; j += pow(2, pow_num)) 
			{
				for (int k = j; k < j + pow(2, pow_num - 1); k++) 
				{												  
					if ((k < 12) && (str_code[k] == '1')) 
					{
						control_bits[p]++;
					}
				}
			}

			control_bits[p] = control_bits[p] % 2; 

			str_code[pow(2, p) - 1] = (char)(((int)'0') + control_bits[p]); 
		}

		bool mis_flag = false; //A flag that is set if a discrepancy was found in the received and calculated codes
		int num_incorrect_bit = 0; //Error bit number

		for (int j = 0; j < 12; j++) //Finding erroe bit number
		{
			if (str_code[j] != Codes[i].to_string()[j])
			{
				mis_flag = true;
				num_incorrect_bit += j;
			}
		}

		if (mis_flag) //Replacing the bit in case of an error
		{
			Codes[i][num_incorrect_bit].flip();
			std::cout << "Code number " << i << " fixed" << std::endl;
			Codes[i] = (std::bitset<12>)str_code;
		}
	}
}

//Deconding function
std::vector<char> Functions::Decode(const std::vector<std::bitset<12>>& Codes)
{
	std::vector<char> Message;
	int Codes_size = Codes.size();
	for (int i = 0; i < Codes_size; i++)
	{
		std::string str_code = Codes[i].to_string();

		std::string temp_str = "";

		for (int j = 0; j < 12; j++) //The cycle of dropping control bits
		{
			if ((j != 0) && (j != 1) && (j != 3) && (j != 7))
			{
				temp_str += str_code[j];
			}
		}

		Message.push_back(((std::bitset<8>)temp_str).to_ulong());
	}

	return Message;
}

//Writing the results into output file
void Functions::Write_file(FILE* fout, const std::vector<std::bitset<12>>& Codes, const std::vector<char>& Message) 
{
	std::string str_out = "";
	int Codes_size = Codes.size();
	for (int i = 0; i < Codes_size; i++)
	{
		str_out = Codes[i].to_string();

		for (int j = 0; j < 12; j++)
		{
			fprintf(fout, "%c", str_out[j]);
		}

		fprintf(fout, "\n");
	}

	fprintf(fout, "\nMessage = ");

	int Message_size = Message.size();
	for (int i = 0; i < Message_size; i++)
	{
		fprintf(fout, "%c", Message[i]);
	}

	fclose(fout);
}