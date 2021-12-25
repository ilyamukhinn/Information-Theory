#include "functions.hpp"

//Reading message from input file
void Functions::Read_file(FILE* fin, std::vector<char>& Str) {
	char symbol = '\0';

	while ((symbol = fgetc(fin)) != EOF)
	{
		Str.push_back(symbol);
	}

	fclose(fin);
}

//Coding function
Code Functions::Encode(const std::vector<char>& Str) {

	Code code;

	for (int i = 0; i < Str.size(); i++)
	{
		bool check = false;
		int cont_len = 0;
		int temp_cont_len = 1;
		int temp_j = 0;
		for (int j = i; j > -1; j--)
		{
			if ((Str[i] == Str[j]) && (j != i))
			{
				temp_cont_len = 1;
				if (i < Str.size() - 2)
				{
					for (int Str_index_i = i + 1, Str_index_j = j + 1; Str_index_j < i; Str_index_i++, Str_index_j++)
					{
						if (i < Str.size() - temp_cont_len - 1)
						{
							if (Str[Str_index_i] == Str[Str_index_j])
							{
								temp_cont_len++;
							}
							else
							{
								Str_index_j = i;
							}
						}
					}
				}

				if(temp_cont_len > cont_len)
				{
					cont_len = temp_cont_len;
					temp_j = j;
				}

				check = true;
			}
		}		

		if ((check == true) && (i != Str.size() - 1))
		{
			code.offsets.push_back(i - temp_j);
			code.lengths.push_back(cont_len);
			code.symbols.push_back(Str[i + cont_len]);
			i += cont_len;
		}
		else
		{
			code.offsets.push_back(0);
			code.lengths.push_back(0);
			code.symbols.push_back(Str[i]);
		}
	}

	return code;
}

//Decoding function
std::vector<char> Functions::Decode(const Code& code)
{
	std::vector<char> Message;
	for (int i = 0; i < code.symbols.size(); i++)
	{
		if (code.lengths[i] == 0)
		{
			Message.push_back(code.symbols[i]);
		}
		else
		{
			int Current_Msg_size = Message.size();
			for (int j = 0; j < code.lengths[i]; j++)
			{
				Message.push_back(Message[Current_Msg_size - code.offsets[i] + j]);
			}

			Message.push_back(code.symbols[i]);
		}
	}

	return Message;
}

//Writing results of coding and decoding into output file
void Functions::Write_file(FILE* fout, const Code& code, const std::vector<char>& Message)
{
	for (int i = 0; i < code.symbols.size(); i++)
	{
		fprintf(fout, "(%d,%d,%c)\n", code.offsets[i], code.lengths[i], code.symbols[i]);
	}

	for (int i = 0; i < Message.size(); i++)
	{
		fprintf(fout, "%c", Message[i]);
	}

	fclose(fout);
}
