#pragma once

#include <string>
#include <iostream>

#define MSG(msg) { std::cout << msg; system("pause>0"); }
#define PAUSE { system("pause>0"); }

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