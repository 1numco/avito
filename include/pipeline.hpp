#pragma once

#include <core_functions.hpp>
#include <chrono>
#include <istream>
#include <ostream>

struct TimeMeasurer
{
    template <typename Function, typename... Args>
    auto operator()(Function function, Args &&...args)
    {
        auto start = std::chrono::high_resolution_clock::now();
        auto result = function(std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        return std::move(result);
    }
    int GetLastMeasuredRuntime()
    {
        return time;
    }

private:
    int time = 0;
};

std::vector<std::string> extract_words(std::istream &fin)
{
    std::vector<std::string> out;
    std::string word;
    while (fin >> word)
    {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        std::replace_if(
            word.begin(), word.end(), [](char c)
            { return !std::isalpha(c); },
            ' ');
        std::string subword;
        for (char c : word)
        {
            if (c != ' ')
            {
                subword += c;
            }
            else
            {
                if (!subword.empty())
                {
                    out.emplace_back(subword);
                    subword.clear();
                }
            }
        }
        if (!subword.empty())
        {
            out.emplace_back(subword);
        }
    }
    return out;
}

template <typename Container,
          typename = std::enable_if_t<
              std::disjunction_v<
                  std::is_same<
                      typename Container::value_type,
                      std::pair<std::string, int>>,
                  std::is_same<
                      typename Container::value_type,
                      std::pair<const std::string, int>>>

              >>
void write_dict(std::ostream &fout, const Container &container)
{
    std::string enter = "";
    for (const auto &p : container)
    {
        fout << enter;
        if (enter.empty())
        {
            enter = "\n";
        }
        fout << p.second << " " << p.first;
    }
}

template <typename T, typename Y, typename Z>
void write_dict(std::ostream &fout, std::priority_queue<T, Y, Z> &container)
{
    std::string enter = "";
    for (; !container.empty(); container.pop())
    {
        fout << enter;
        if (enter.empty())
        {
            enter = "\n";
        }
        auto &top = container.top();
        fout << top.second << " " << top.first;
    }
}

struct Pipeline
{
    template <typename Method,
              typename = std::enable_if_t<std::is_invocable_v<Method, std::vector<std::string> &>>,
              typename ReturnType = decltype(std::declval<Method>()(std::declval<std::vector<std::string> &>())),
              typename = std::enable_if_t<
                  std::disjunction_v<
                      std::is_same<
                          typename ReturnType::value_type,
                          std::pair<std::string, int>>,
                      std::is_same<
                          typename ReturnType::value_type,
                          std::pair<const std::string, int>>>>>
    static void SimpleRun(std::istream &fin, std::ostream &fout, Method frequencies_exctraction_method)
    {
        TimeMeasurer tm;
        auto words = extract_words(fin);
        auto friquencies = frequencies_exctraction_method(words);
        write_dict(fout, friquencies);
    }

    template <typename Method,
              typename = std::enable_if_t<std::is_invocable_v<Method, std::vector<std::string> &>>,
              typename ReturnType = decltype(std::declval<Method>()(std::declval<std::vector<std::string> &>())),
              typename = std::enable_if_t<
                  std::disjunction_v<
                      std::is_same<
                          typename ReturnType::value_type,
                          std::pair<std::string, int>>,
                      std::is_same<
                          typename ReturnType::value_type,
                          std::pair<const std::string, int>>>>>
    void MeasuredRun(std::istream &fin, std::ostream &fout, Method frequencies_exctraction_method)
    {
        TimeMeasurer tm;
        auto words = extract_words(fin);
        auto friquencies = tm(frequencies_exctraction_method, words);
        time = tm.GetLastMeasuredRuntime();
        write_dict(fout, friquencies);
    }

    int GetLastKeyFunctionRuntime()
    {
        return time;
    }

private:
    int time = 0;
};