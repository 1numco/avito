#include "pipeline.hpp"
#include <experimental/filesystem>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::experimental::filesystem; 

template <typename Function>
bool PerformanceTest(const std::string & InputPath, const std::string & OutputPath, Function function)
{
    constexpr int test_count = 10000;
    std::vector<int> time_vec;
    time_vec.reserve(test_count);
    Pipeline pl;
    for (int i = 0; i < test_count; i++)
    {
        std::ifstream fin(InputPath);

        std::ofstream fout(OutputPath);
        if (!fin.is_open() || !fout.is_open()) 
        {
            std::cerr << "Failed to open the files." << std::endl;
            return false;
        }
        pl.MeasuredRun<decltype(function)>(fin, fout, function);
        time_vec.emplace_back(pl.GetLastKeyFunctionRuntime());

        fin.close();
        fout.close();
    }

    std::cout << "Avarage runtime: " << std::accumulate(time_vec.begin(), time_vec.end(), 0) / static_cast<double>(test_count) << " us" << std::endl;
    return true;
}

int main(int argc, char *argv[])
{
    std::string currentFilePath = __FILE__;

    fs::path inputPath = currentFilePath;
    inputPath = inputPath.parent_path().parent_path();
    (inputPath /= "text_files") /= "small_input.txt";

    fs::path outputPath = currentFilePath;
    outputPath = outputPath.parent_path().parent_path();
    (outputPath /= "text_files") /= "small_output.txt";

    std::cout << "Test for map_plus_sort function on small input:                 ";
    PerformanceTest(inputPath.string(), outputPath.string(), map_plus_sort);
    std::cout << "Test for unordered_map_plus_sort function on small input:       ";
    PerformanceTest(inputPath.string(), outputPath.string(), unordered_map_plus_sort);
    std::cout << "Test for map_plus_priority_queue function on small input:       ";
    PerformanceTest(inputPath.string(), outputPath.string(), map_plus_priority_queue);

    (inputPath = inputPath.parent_path()) /= "middle_input.txt";
    (outputPath = outputPath.parent_path()) /= "middle_output.txt";

    std::cout << std::endl;
    std::cout << "Test for map_plus_sort function on middle size input:           ";
    PerformanceTest(inputPath.string(), outputPath.string(), map_plus_sort);
    std::cout << "Test for unordered_map_plus_sort function on middle size input: ";
    PerformanceTest(inputPath.string(), outputPath.string(), unordered_map_plus_sort);
    std::cout << "Test for map_plus_priority_queue function on middle size input: ";
    PerformanceTest(inputPath.string(), outputPath.string(), map_plus_priority_queue);

    (inputPath = inputPath.parent_path()) /= "large_input.txt";
    (outputPath = outputPath.parent_path()) /= "large_output.txt";

    std::cout << std::endl;
    std::cout << "Test for map_plus_sort function on large input:                 ";
    PerformanceTest(inputPath.string(), outputPath.string(), map_plus_sort);
    std::cout << "Test for unordered_map_plus_sort function on large input:       ";
    PerformanceTest(inputPath.string(), outputPath.string(), unordered_map_plus_sort);
    std::cout << "Test for map_plus_priority_queue function on large input:       ";
    PerformanceTest(inputPath.string(), outputPath.string(), map_plus_priority_queue);

    return 0;
}