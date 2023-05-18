#include <iostream>
#include <fstream>
#include <pipeline.hpp>
#include <map>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <vector>
#include <numeric>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " [input_file] [output_file]" << std::endl;
        return 1;
    }

    std::ifstream fin(argv[1]);
    if (!fin)
    {
        std::cerr << "Error: cannot open input file: " << argv[1] << std::endl;
        return 1;
    }

    std::ofstream fout(argv[2]);
    if (!fout)
    {
        std::cerr << "Error: cannot open output file: " << argv[2] << std::endl;
        return 1;
    }

    FinalFunction(fin, fout);

    fin.close();
    fout.close();
    return 0;
}
