#pragma once

#include <string>
#include <iostream>

#define MSG(msg) { std::cout << msg; std::cin.get(); }
#define PAUSE { std::cin.get();}

inline std::string addSpaces(const std::string& input)
{
    return " " + input + " ";
}

inline std::string toLower(const std::string& str)
{
    std::string result = str;
    for (char& c : result)
    {
        if (c >= 'A' && c <= 'Z')
        {
            c += ('a' - 'A');
        }
    }
    return result;
}