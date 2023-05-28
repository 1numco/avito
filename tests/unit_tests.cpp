#include "pipeline.hpp"
#include "core_functions.hpp"
#include <gtest/gtest.h>
#include <functional>


template <typename Function, typename... Args>
void CommonTest(const std::string & inputString, const std::string & desiredOutput, const Function& pipelineFunction, Args &&...args) {
    std::istringstream inputFile(inputString);
    std::ostringstream output;
    pipelineFunction(inputFile, output, std::forward<Args>(args)...);
    ASSERT_EQ(output.str(), desiredOutput);
}



TEST(UnitTestForMapPlusSorting, EmptyFile) {
    CommonTest("", "", Pipeline::SimpleRun<decltype(map_plus_sort)>, map_plus_sort);
}

TEST(UnitTestForMapPlusSorting, NoWords) {
    CommonTest("123 !@#$%", "", Pipeline::SimpleRun<decltype(map_plus_sort)>, map_plus_sort);
}

TEST(UnitTestForMapPlusSorting, SingleWord) {
    CommonTest("Hello", "1 hello", Pipeline::SimpleRun<decltype(map_plus_sort)>, map_plus_sort);
}

TEST(UnitTestForMapPlusSorting, MultipleOccurrences) {
    CommonTest("hello world hello hello", "3 hello\n1 world", Pipeline::SimpleRun<decltype(map_plus_sort)>, map_plus_sort);
}

TEST(UnitTestForMapPlusSorting, MixedCase) {
    CommonTest("Hello WoRld! This is a TeSt. Hello WORLD", "2 hello\n2 world\n1 a\n1 is\n1 test\n1 this", Pipeline::SimpleRun<decltype(map_plus_sort)>, map_plus_sort);
}

TEST(UnitTestForMapPlusSorting, CaseInsensitive) {
    CommonTest("Hello hello HELLO", "3 hello", Pipeline::SimpleRun<decltype(map_plus_sort)>, map_plus_sort);
}

TEST(UnitTestForMapPlusSorting, MixedSymbolsAndWords) {
    CommonTest("Hello@W0rld! This#is_a_TeSt. Hello WORLD", "2 hello\n1 a\n1 is\n1 rld\n1 test\n1 this\n1 w\n1 world", Pipeline::SimpleRun<decltype(map_plus_sort)>, map_plus_sort);
}

TEST(UnitTestForMapPlusSorting, NumbersInWords) {
    CommonTest("hello12 world123 hello12", "2 hello\n1 world", Pipeline::SimpleRun<decltype(map_plus_sort)>, map_plus_sort);
}

TEST(UnitTestForMapPlusSorting, MultipleSpacesBetweenWords) {
    CommonTest("hello      world   hello", "2 hello\n1 world", Pipeline::SimpleRun<decltype(map_plus_sort)>, map_plus_sort);
}

TEST(UnitTestForMapPlusSorting, SpecialCharactersAsWords) {
    CommonTest("!@#$%^&*()", "", Pipeline::SimpleRun<decltype(map_plus_sort)>, map_plus_sort);
}



TEST(UnitTestForUnorderedMapPlusSorting, EmptyFile) {
    CommonTest("", "", Pipeline::SimpleRun<decltype(unordered_map_plus_sort)>, unordered_map_plus_sort);
}

TEST(UnitTestForUnorderedMapPlusSorting, NoWords) {
    CommonTest("123 !@#$%", "", Pipeline::SimpleRun<decltype(unordered_map_plus_sort)>, unordered_map_plus_sort);
}

TEST(UnitTestForUnorderedMapPlusSorting, SingleWord) {
    CommonTest("Hello", "1 hello", Pipeline::SimpleRun<decltype(unordered_map_plus_sort)>, unordered_map_plus_sort);
}

TEST(UnitTestForUnorderedMapPlusSorting, MultipleOccurrences) {
    CommonTest("hello world hello hello", "3 hello\n1 world", Pipeline::SimpleRun<decltype(unordered_map_plus_sort)>, unordered_map_plus_sort);
}

TEST(UnitTestForUnorderedMapPlusSorting, MixedCase) {
    CommonTest("Hello WoRld! This is a TeSt. Hello WORLD", "2 hello\n2 world\n1 a\n1 is\n1 test\n1 this", Pipeline::SimpleRun<decltype(unordered_map_plus_sort)>, unordered_map_plus_sort);
}

TEST(UnitTestForUnorderedMapPlusSorting, CaseInsensitive) {
    CommonTest("Hello hello HELLO", "3 hello", Pipeline::SimpleRun<decltype(unordered_map_plus_sort)>, unordered_map_plus_sort);
}

TEST(UnitTestForUnorderedMapPlusSorting, MixedSymbolsAndWords) {
    CommonTest("Hello@W0rld! This#is_a_TeSt. Hello WORLD", "2 hello\n1 a\n1 is\n1 rld\n1 test\n1 this\n1 w\n1 world", Pipeline::SimpleRun<decltype(unordered_map_plus_sort)>, unordered_map_plus_sort);
}

TEST(UnitTestForUnorderedMapPlusSorting, NumbersInWords) {
    CommonTest("hello12 world123 hello12", "2 hello\n1 world", Pipeline::SimpleRun<decltype(unordered_map_plus_sort)>, unordered_map_plus_sort);
}

TEST(UnitTestForUnorderedMapPlusSorting, MultipleSpacesBetweenWords) {
    CommonTest("hello      world   hello", "2 hello\n1 world", Pipeline::SimpleRun<decltype(unordered_map_plus_sort)>, unordered_map_plus_sort);
}

TEST(UnitTestForUnorderedMapPlusSorting, SpecialCharactersAsWords) {
    CommonTest("!@#$%^&*()", "", Pipeline::SimpleRun<decltype(unordered_map_plus_sort)>, unordered_map_plus_sort);
}



TEST(UnitTestForMapPlusPriorityQueue, EmptyFile) {
    CommonTest("", "", Pipeline::SimpleRun<decltype(map_plus_priority_queue)>, map_plus_priority_queue);
}

TEST(UnitTestForMapPlusPriorityQueue, NoWords) {
    CommonTest("123 !@#$%", "", Pipeline::SimpleRun<decltype(map_plus_priority_queue)>, map_plus_priority_queue);
}

TEST(UnitTestForMapPlusPriorityQueue, SingleWord) {
    CommonTest("Hello", "1 hello", Pipeline::SimpleRun<decltype(map_plus_priority_queue)>, map_plus_priority_queue);
}

TEST(UnitTestForMapPlusPriorityQueue, MultipleOccurrences) {
    CommonTest("hello world hello hello", "3 hello\n1 world", Pipeline::SimpleRun<decltype(map_plus_priority_queue)>, map_plus_priority_queue);
}

TEST(UnitTestForMapPlusPriorityQueue, MixedCase) {
    CommonTest("Hello WoRld! This is a TeSt. Hello WORLD", "2 hello\n2 world\n1 a\n1 is\n1 test\n1 this", Pipeline::SimpleRun<decltype(map_plus_priority_queue)>, map_plus_priority_queue);
}

TEST(UnitTestForMapPlusPriorityQueue, CaseInsensitive) {
    CommonTest("Hello hello HELLO", "3 hello", Pipeline::SimpleRun<decltype(map_plus_priority_queue)>, map_plus_priority_queue);
}

TEST(UnitTestForMapPlusPriorityQueue, MixedSymbolsAndWords) {
    CommonTest("Hello@W0rld! This#is_a_TeSt. Hello WORLD", "2 hello\n1 a\n1 is\n1 rld\n1 test\n1 this\n1 w\n1 world", Pipeline::SimpleRun<decltype(map_plus_priority_queue)>, map_plus_priority_queue);
}

TEST(UnitTestForMapPlusPriorityQueue, NumbersInWords) {
    CommonTest("hello12 world123 hello12", "2 hello\n1 world", Pipeline::SimpleRun<decltype(map_plus_priority_queue)>, map_plus_priority_queue);
}

TEST(UnitTestForMapPlusPriorityQueue, MultipleSpacesBetweenWords) {
    CommonTest("hello      world   hello", "2 hello\n1 world", Pipeline::SimpleRun<decltype(map_plus_priority_queue)>, map_plus_priority_queue);
}

TEST(UnitTestForMapPlusPriorityQueue, SpecialCharactersAsWords) {
    CommonTest("!@#$%^&*()", "", Pipeline::SimpleRun<decltype(map_plus_priority_queue)>, map_plus_priority_queue);
}



TEST(UnitTestForFinalFunction, EmptyFile) {
    CommonTest("", "", FinalFunction);
}

TEST(UnitTestForFinalFunction, NoWords) {
    CommonTest("123 !@#$%", "", FinalFunction);
}

TEST(UnitTestForFinalFunction, SingleWord) {
    CommonTest("Hello", "1 hello", FinalFunction);
}

TEST(UnitTestForFinalFunction, MultipleOccurrences) {
    CommonTest("hello world hello hello", "3 hello\n1 world", FinalFunction);
}

TEST(UnitTestForFinalFunction, MixedCase) {
    CommonTest("Hello WoRld! This is a TeSt. Hello WORLD", "2 hello\n2 world\n1 a\n1 is\n1 test\n1 this", FinalFunction);
}

TEST(UnitTestForFinalFunction, CaseInsensitive) {
    CommonTest("Hello hello HELLO", "3 hello", FinalFunction);
}

TEST(UnitTestForFinalFunction, MixedSymbolsAndWords) {
    CommonTest("Hello@W0rld! This#is_a_TeSt. Hello WORLD", "2 hello\n1 a\n1 is\n1 rld\n1 test\n1 this\n1 w\n1 world", FinalFunction);
}

TEST(UnitTestForFinalFunction, NumbersInWords) {
    CommonTest("hello12 world123 hello12", "2 hello\n1 world", FinalFunction);
}

TEST(UnitTestForFinalFunction, MultipleSpacesBetweenWords) {
    CommonTest("hello      world   hello", "2 hello\n1 world", FinalFunction);
}

TEST(UnitTestForFinalFunction, SpecialCharactersAsWords) {
    CommonTest("!@#$%^&*()", "", FinalFunction);
}



TEST(UnitTestForFinalFunctionUpgraded, EmptyFile) {
    CommonTest("", "", FinalFunctionUpgraded);
}

TEST(UnitTestForFinalFunctionUpgraded, NoWords) {
    CommonTest("123 !@#$%", "", FinalFunctionUpgraded);
}

TEST(UnitTestForFinalFunctionUpgraded, SingleWord) {
    CommonTest("Hello", "1 hello", FinalFunctionUpgraded);
}

TEST(UnitTestForFinalFunctionUpgraded, MultipleOccurrences) {
    CommonTest("hello world hello hello", "3 hello\n1 world", FinalFunctionUpgraded);
}

TEST(UnitTestForFinalFunctionUpgraded, MixedCase) {
    CommonTest("Hello WoRld! This is a TeSt. Hello WORLD", "2 hello\n2 world\n1 a\n1 is\n1 test\n1 this", FinalFunctionUpgraded);
}

TEST(UnitTestForFinalFunctionUpgraded, CaseInsensitive) {
    CommonTest("Hello hello HELLO", "3 hello", FinalFunctionUpgraded);
}

TEST(UnitTestForFinalFunctionUpgraded, MixedSymbolsAndWords) {
    CommonTest("Hello@W0rld! This#is_a_TeSt. Hello WORLD", "2 hello\n1 a\n1 is\n1 rld\n1 test\n1 this\n1 w\n1 world", FinalFunctionUpgraded);
}

TEST(UnitTestForFinalFunctionUpgraded, NumbersInWords) {
    CommonTest("hello12 world123 hello12", "2 hello\n1 world", FinalFunctionUpgraded);
}

TEST(UnitTestForFinalFunctionUpgraded, MultipleSpacesBetweenWords) {
    CommonTest("hello      world   hello", "2 hello\n1 world", FinalFunctionUpgraded);
}

TEST(UnitTestForFinalFunctionUpgraded, SpecialCharactersAsWords) {
    CommonTest("!@#$%^&*()", "", FinalFunctionUpgraded);
}