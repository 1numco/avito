#pragma once
#include <map>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <vector>
#include <numeric>
#include <istream>
#include <ostream>
#include <sstream>
#include <iterator>
#include <chrono>
#include <iostream>
#include <fstream>


auto map_plus_priority_queue(const std::vector<std::string> &words)
{
    std::unordered_map<std::string, int> freq;
    for (auto &word : words)
    {
        freq[word]++;
    }
    auto comp = [](const auto &left, const auto &right)
    {
        if (left.second != right.second)
        {
            return left.second < right.second;
        }
        else
        {
            return left.first > right.first;
        }
    };
    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, decltype(comp)> queue(freq.begin(), freq.end(), comp);
    return queue;
}

auto map_plus_sort(const std::vector<std::string> &words)
{

    std::map<std::string, int> freq;
    for (auto &word : words)
    {
        freq[word]++;
    }
    std::vector<std::pair<std::string, int>> vec(freq.begin(), freq.end());

    std::sort(vec.begin(), vec.end(), [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
              {
                  if (a.second != b.second)
                  {
                      return a.second > b.second;
                  }
                  else
                  {
                      return a.first < b.first;
                  }
              });
    return vec;
}

auto unordered_map_plus_sort(const std::vector<std::string> &words)
{
    std::unordered_map<std::string, int> freq;
    for (auto &word : words)
    {
        freq[word]++;
    }
    std::vector<std::pair<std::string, int>> vec(freq.begin(), freq.end());

    std::sort(vec.begin(), vec.end(), [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
              {
                  if (a.second != b.second)
                  {
                      return a.second > b.second;
                  }
                  else
                  {
                      return a.first < b.first;
                  }
              });
    return vec;
}

void FinalFunction(std::istream &fin, std::ostream &fout)
{
    std::unordered_map<std::string, int> freq;
    std::string line;
    std::string word;
    while (fin >> line)
    {
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        std::replace_if(
            line.begin(), line.end(), [](char c)
            { return !std::isalpha(c); },
            ' ');
        for (char & c : line)
        {
            if (c != ' ')
            {
                word += c;
            }
            else
            {
                if (!word.empty())
                {
                    freq[word]++;
                    word.clear();
                }
            }
        }
        if (!word.empty())
        {
            freq[word]++;
            word.clear();
        }
    }

    auto comp = [](const auto &left, const auto &right)
    {
        if (left.second != right.second)
        {
            return left.second < right.second;
        }
        else
        {
            return left.first > right.first;
        }
    };


    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, decltype(comp)> queue(freq.begin(), freq.end(), comp);

    std::string enter = "";
    for (; !queue.empty(); queue.pop())
    {
        fout << enter;
        if (enter.empty())
        {
            enter = "\n";
        }
        auto &top = queue.top();
        fout << top.second << " " << top.first;
    }
}

void FinalFunctionUpgraded(std::istream &fin, std::ostream &fout)
{
    std::unordered_map<std::string, int> freq;
    freq.reserve(1000);
    const size_t chunkSize = INT16_MAX;
    char buffer[chunkSize];
    int length = 0;
    int begin = 0;
    std::string tail;
    tail.reserve(30);
    auto fill_map = [&buffer, &chunkSize, &freq, &length, &begin, &fin, &tail]()
    {
        const int bytesRead = fin.gcount();
        
        for (int i = 0; i < bytesRead; ++i)
        {
            if (std::isalpha(buffer[i]))
            {
                if (!length)
                {
                    begin = i;
                }
                ++length;
                buffer[i] = std::tolower(buffer[i]);
            }
            else if (length > 0)
            {
                if (!tail.empty())
                {
                    ++freq[tail + std::string(buffer+begin, length)];
                    tail.clear();
                }
                else
                {
                    ++freq[std::string(buffer+begin, length)];
                }
                length = 0;
                begin = 0;
            }
            else
            {
                if (!tail.empty())
                {
                    ++freq[tail];
                    tail.clear();
                }
            }
        }
        if (length > 0)
        {
            tail = std::string(buffer+begin, length);
            length = 0;
            begin = 0;
        }
    };


    while (fin.read(buffer, chunkSize))
    {
        fill_map();
    }
    fill_map();
    if (length > 0)
    {
        ++freq[std::move(tail)];
    }

    auto comp = [](const auto &left, const auto &right)
    {
        if (left.second != right.second)
        {
            return left.second < right.second;
        }
        else
        {
            return left.first > right.first;
        }
    };

    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, decltype(comp)> queue(std::make_move_iterator(freq.begin()), std::make_move_iterator(freq.end()), comp);

    if (!queue.empty())
    {
        auto &top = queue.top();
        fout << top.second << ' ' << top.first;
        queue.pop();
    }
    for (; !queue.empty(); queue.pop())
    {        
        auto &top = queue.top();
        fout << '\n' << (top.second) << ' ' << top.first;
    }
}