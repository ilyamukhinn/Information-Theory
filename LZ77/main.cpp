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

    std::vector <char> Str;

    FILE* fout;
    FILE* fin;

    fopen_s(&fin, argv[1], "r");
    fopen_s(&fout, argv[2], "w");

    std::cout << "Start" << std::endl;

    Functions::Read_file(fin, Str);
    auto code = Functions::Encode(Str);
    auto Message = Functions::Decode(code);
    Functions::Write_file(fout, code, Message);

    std::cout << "End" << std::endl;

    return 0;
}
