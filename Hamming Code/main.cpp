#include "functions.hpp"

int main(int argc, char* argv[])
{
    if (argc != 3) 
    {
        std::cout << "incorrect command line! "
            "Waited: command in_file out_file"
            << std::endl;
        exit(1);
    }

    FILE* fin;
    FILE* fout;

    fopen_s(&fin, argv[1], "r");
    fopen_s(&fout, argv[2], "w");

    std::cout << "Start" << std::endl;
    
    std::vector<char> Str;

    Functions::Read_file(fin, Str);
    auto Codes = Functions::Encode(Str);
    Functions::Check_codes(Codes);
    auto Message = Functions::Decode(Codes);
    Functions::Write_file(fout, Codes, Message);

    std::cout << "End" << std::endl;

    return 0;
}
