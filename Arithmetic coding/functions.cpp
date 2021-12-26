#include "functions.hpp"

//Reading input data
void Functions::Read_file(FILE* fin, std::vector<char>& Str)
{
	char ch = '\0';

	while ((ch = fgetc(fin)) != EOF)
	{
		Str.push_back(ch);
	}

	fclose(fin);
}

//Encoding function
Code Functions::Encode(const std::vector<char>& Str)
{
	//Getting an alphabet based on input message
	std::vector<char> Alphabet;
	Alphabet.push_back(Str[0]);

	for (int i = 0; i < Str.size(); i++)
	{
		int check = 0;
		for (int j = 0; j < Alphabet.size(); j++)
		{
			if (Alphabet[j] != Str[i])
			{
				check++;
			}
		}

		if (check == Alphabet.size())
		{
			Alphabet.push_back(Str[i]);
		}
	}

	//Getting probabilities of message symbols 
	mpf_t* Probability = new mpf_t[Alphabet.size()];

	mpf_t count, inc, Str_size;
	mpf_init2(count, 9999);
	mpf_init2(inc, 9999);
	mpf_set_d(inc, 1.0);
	mpf_init2(Str_size, 9999);
	mpf_set_d(Str_size, (double)Str.size());

	int Prob_size = Alphabet.size();

	for (int i = 0; i < Prob_size; i++)
	{
		mpf_set_d(count, 0.0);
		for (int j = 0; j < Str.size(); j++)
		{
			if (Str[j] == Alphabet[i])
			{
				mpf_add(count, count, inc);
			}
		}

		mpf_init2(Probability[i], 9999);
		mpf_div(Probability[i], count, Str_size);
	}

	mpf_clear(count);
	mpf_clear(inc);
	mpf_clear(Str_size);

	//Getting a segment, which is used for data encoding
	mpf_t* Segment = new mpf_t[Alphabet.size() + 1];

	mpf_t New_seg;
	mpf_init2(New_seg, 9999);
	mpf_set_d(New_seg, 0.0);
	mpf_init2(Segment[0], 9999);

	int Segment_size = Prob_size + 1;

	for (int i = 1; i < Segment_size; i++)
	{
		mpf_init2(Segment[i], 9999);
		mpf_add(New_seg, New_seg, Probability[i - 1]);
		mpf_set(Segment[i], New_seg);
	}

	mpf_clear(New_seg);

	//Encode data
	Code obj;

	obj.Alphabet = Alphabet;
	obj.Probabilities = Probability;
	obj.Message_size = Str.size();

	mpf_t* temp_Segment = new mpf_t[Alphabet.size() + 1];
	mpf_t next_Seg, temp_sub, temp_mul, temp_two;
	mpf_init2(next_Seg, 9999);
	mpf_init2(temp_sub, 9999);
	mpf_init2(temp_mul, 9999);
	mpf_init2(temp_two, 9999);
	mpf_set_d(temp_two, 2.0);

	for (int i = 0; i < Str.size(); i++)
	{
		for (int j = 0; j < Alphabet.size(); j++)
		{
			if (Str[i] == Alphabet[j])
			{
				if (i == Str.size() - 1)
				{
					mpf_init2(obj.code, 9999);
					mpf_add(Segment[j], Segment[j], Segment[j + 1]);
					mpf_div(Segment[j], Segment[j], temp_two);
					mpf_set(obj.code, Segment[j]);
				}
				else
				{
					int prob_index = 0;
					mpf_set(next_Seg, Segment[j]);

					for (int p = 0; p < Segment_size; p++)
					{
						if (p == 0)
						{
							mpf_init2(temp_Segment[p], 9999);
							mpf_set(temp_Segment[p], Segment[j]);
						}
						else if (p == Segment_size - 1)
						{
							mpf_init2(temp_Segment[p], 9999);
							mpf_set(temp_Segment[p], Segment[j + 1]);
						}
						else
						{
							mpf_sub(temp_sub, Segment[j + 1], Segment[j]);
							mpf_mul(temp_mul, temp_sub, Probability[prob_index]);
							mpf_add(next_Seg, next_Seg, temp_mul);

							mpf_init2(temp_Segment[p], 9999);
							mpf_set(temp_Segment[p], next_Seg);

							prob_index++;
						}
					}
					
					for (int p = 0; p < Segment_size; p++)
					{
						mpf_set(Segment[p], temp_Segment[p]);
					}
				}

				j = Alphabet.size();
			}
		}
	}

	for (int i = 0; i < Segment_size; i++)
	{
		mpf_clear(Segment[i]);
		mpf_clear(temp_Segment[i]);
	}
	mpf_clear(next_Seg);
	mpf_clear(temp_sub);
	mpf_clear(temp_mul);
	mpf_clear(temp_two);

	return obj;
}

//Decode function
std::vector<char> Functions::Decode(const Code& obj)
{
	//Getting a segment, which is used for data decoding
	mpf_t* Segment = new mpf_t[obj.Alphabet.size() + 1];
	mpf_t New_seg;
	mpf_init2(New_seg, 9999);
	mpf_set_d(New_seg, 0.0);
	mpf_init2(Segment[0], 9999);
	int Segment_size = obj.Alphabet.size() + 1;

	for (int i = 1; i < Segment_size; i++)
	{
		mpf_init2(Segment[i], 9999);
		mpf_add(New_seg, New_seg, obj.Probabilities[i - 1]);
		mpf_set(Segment[i], New_seg);
	}

	mpf_clear(New_seg);

	//Decode data
	mpf_t Code, Numerator, DeNumerator;
	mpf_init2(Numerator, 9999);
	mpf_init2(DeNumerator, 9999);

	mpf_init2(Code, 9999);
	mpf_set(Code, obj.code);

	std::vector<char> Message;
	bool exit = false;
	int exit_check = 0;

	while (!exit)
	{
		for (int i = 0; i < Segment_size - 1; i++)
		{
			if ((mpf_cmp(Code, Segment[i]) >= 0) && (mpf_cmp(Code, Segment[i + 1]) < 0))
			{
				Message.push_back(obj.Alphabet[i]);
				mpf_sub(Numerator, Code, Segment[i]);
				mpf_sub(DeNumerator, Segment[i + 1], Segment[i]);
				mpf_div(Code, Numerator, DeNumerator);
				exit_check++;
				i = Segment_size - 1;
			}

			if (exit_check == obj.Message_size)
			{
				exit = true;
			}
		}
	}

	for (int i = 0; i < Segment_size; i++)
	{
		mpf_clear(Segment[i]);
	}

	mpf_clear(Code);
	mpf_clear(Numerator);
	mpf_clear(DeNumerator);

	return Message;
}

//Writing results into output file
void Functions::Write_file(FILE* fout, const Code& obj, const std::vector<char>& Message) {
	fprintf(fout, "Code = ");
	mpf_out_str(fout, 10, 0, obj.code);
	fprintf(fout, "\nMessage = ");

	for (int i = 0; i < Message.size(); i++)
	{
		fprintf(fout, "%c", Message[i]);
	}

	fclose(fout);
}
