#include "pipeline.hpp"
#include "core_functions.hpp"
#include <gtest/gtest.h>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem; 

bool check_on_empty(std::ifstream & f1, std::ifstream & f2, bool & success)
{
    if (f1.peek() != std::ifstream::traits_type::eof() &&
        f2.peek() != std::ifstream::traits_type::eof()) {
        success = false;
    }
}

bool check_on_equal(std::ifstream & f1, std::ifstream & f2, bool & success)
{
    std::string lineEtalon, lineOutput;
    while (std::getline(f1, lineEtalon) && std::getline(f2, lineOutput)) {
        if (lineEtalon != lineOutput) {
            success = false;
            break;
        }
    }

    // Check if both files have reached EOF
    if (!f1.eof() || !f2.eof()) {
        success = false;
    }
}

template <typename CheckFunction, typename Function, typename... Args>
void CommonTest(const std::string & type, const CheckFunction& checkFunction, const Function& pipelineFunction, Args &&...args) {
    std::string currentFilePath = __FILE__;

    fs::path inputPath = currentFilePath;
    inputPath = inputPath.parent_path().parent_path();
    (inputPath /= "text_files") /= type + "_input.txt";
    std::ifstream inputFile{inputPath.string()};

    fs::path outputPath = currentFilePath;
    outputPath = outputPath.parent_path().parent_path();
    (outputPath /= "text_files") /= type + "_output.txt";
    std::ofstream outputFile{outputPath.string()};

    pipelineFunction(inputFile, outputFile, std::forward<Args>(args)...);

    outputFile.close();
    
    fs::path etalonPath = currentFilePath;
    etalonPath = etalonPath.parent_path().parent_path();
    (etalonPath /= "text_files") /= type + "_etalon_output.txt";

    std::ifstream etalonFile(etalonPath.string());
    std::ifstream outputFile1(outputPath.string());

    bool success = true;

    checkFunction(etalonFile, outputFile1, success);
    etalonFile.close();
    outputFile1.close();
    ASSERT_EQ(success, true);
}


TEST(FunctionalTestForMapPlusSorting, EmptyFile) {
    CommonTest("empty",  check_on_empty, Pipeline::SimpleRun<decltype(map_plus_sort)>, map_plus_sort);
}

TEST(FunctionalTestForMapPlusSorting, RussianFile) {
    CommonTest("russian",  check_on_empty,  Pipeline::SimpleRun<decltype(map_plus_sort)>, map_plus_sort);
}

TEST(FunctionalTestForMapPlusSorting, SmallFile) {
    CommonTest("small", check_on_equal, Pipeline::SimpleRun<decltype(map_plus_sort)>, map_plus_sort);
}

TEST(FunctionalTestForMapPlusSorting, MiddleSizeFile) {
    CommonTest("middle", check_on_equal, Pipeline::SimpleRun<decltype(map_plus_sort)>, map_plus_sort);
}

TEST(FunctionalTestForMapPlusSorting, LargeFile) {
    CommonTest("large", check_on_equal, Pipeline::SimpleRun<decltype(map_plus_sort)>, map_plus_sort);
}



TEST(FunctionalTestForUnorderedMapPlusPriorityQueue, EmptyFile) {
    CommonTest("empty",  check_on_empty, Pipeline::SimpleRun<decltype(unordered_map_plus_sort)>, unordered_map_plus_sort);
}

TEST(FunctionalTestForUnorderedMapPlusPriorityQueue, RussianFile) {
    CommonTest("russian",  check_on_empty,  Pipeline::SimpleRun<decltype(unordered_map_plus_sort)>, unordered_map_plus_sort);
}

TEST(FunctionalTestForUnorderedMapPlusPriorityQueue, SmallFile) {
    CommonTest("small", check_on_equal, Pipeline::SimpleRun<decltype(unordered_map_plus_sort)>, unordered_map_plus_sort);
}

TEST(FunctionalTestForUnorderedMapPlusPriorityQueue, MiddleSizeFile) {
    CommonTest("middle", check_on_equal, Pipeline::SimpleRun<decltype(unordered_map_plus_sort)>, unordered_map_plus_sort);
}

TEST(FunctionalTestForUnorderedMapPlusPriorityQueue, LargeFile) {
    CommonTest("large", check_on_equal, Pipeline::SimpleRun<decltype(unordered_map_plus_sort)>, unordered_map_plus_sort);
}



TEST(FunctionalTestForMapPlusPriorityQueue, EmptyFile) {
    CommonTest("empty",  check_on_empty, Pipeline::SimpleRun<decltype(map_plus_priority_queue)>, map_plus_priority_queue);
}

TEST(FunctionalTestForMapPlusPriorityQueue, RussianFile) {
    CommonTest("russian",  check_on_empty,  Pipeline::SimpleRun<decltype(map_plus_priority_queue)>, map_plus_priority_queue);
}

TEST(FunctionalTestForMapPlusPriorityQueue, SmallFile) {
    CommonTest("small", check_on_equal, Pipeline::SimpleRun<decltype(map_plus_priority_queue)>, map_plus_priority_queue);
}

TEST(FunctionalTestForMapPlusPriorityQueue, MiddleSizeFile) {
    CommonTest("middle", check_on_equal, Pipeline::SimpleRun<decltype(map_plus_priority_queue)>, map_plus_priority_queue);
}

TEST(FunctionalTestForMapPlusPriorityQueue, LargeFile) {
    CommonTest("large", check_on_equal, Pipeline::SimpleRun<decltype(map_plus_priority_queue)>, map_plus_priority_queue);
}



TEST(FunctionalTestForFinalFunction, EmptyFile) {
    CommonTest("empty",  check_on_empty, FinalFunction);
}

TEST(FunctionalTestForFinalFunction, RussianFile) {
    CommonTest("russian",  check_on_empty,  FinalFunction);
}

TEST(FunctionalTestForFinalFunction, SmallFile) {
    CommonTest("small", check_on_equal, FinalFunction);
}

TEST(FunctionalTestForFinalFunction, MiddleSizeFile) {
    CommonTest("middle", check_on_equal, FinalFunction);
}

TEST(FunctionalTestForFinalFunction, LargeFile) {
    CommonTest("large", check_on_equal, FinalFunction);
}
