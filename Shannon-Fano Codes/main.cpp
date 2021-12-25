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

    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);

    std::vector<char> Alphabet;
    std::vector<float> Probability;
    int Arity = 0;

    std::cout << "Start" << std::endl;

    Functions::Read_file(fin, Alphabet, Probability, Arity);
    auto res = Functions::Encode(Alphabet, Probability, Arity);
    Functions::Write_file(fout, res);

    std::cout << "End" << std::endl;

    return 0;
}
