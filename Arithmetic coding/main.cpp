#include "functions.hpp"

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cout << "incorrect command line! "
            "Waited: command in_file out_file"
            << std::endl;
        exit(1);
    }

    std::vector<char> Str;

    FILE* fout;
    FILE* fin;

    fopen_s(&fin, argv[1], "r");
    fopen_s(&fout,argv[2], "w");

    std::cout << "Start" << std::endl;

    Functions::Read_file(fin, Str);
    auto Code = Functions::Encode(Str);
    auto Message = Functions::Decode(Code);
    Functions::Write_file(fout, Code, Message);

    if (Code.code->_mp_size != 0)
    {
        int Probabilities_size = Code.Alphabet.size();
        for (int i = 0; i < Probabilities_size; i++)
        {
            mpf_clear(Code.Probabilities[i]);
        }

        mpf_clear(Code.code);
    }

    std::cout << "End" << std::endl;

    return 0;
}
