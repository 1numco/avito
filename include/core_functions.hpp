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