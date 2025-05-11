#pragma once

#include <iostream>
#include <string>
#include <functional>

template<typename T>
inline T validatedInput(const std::string& prompt = "", const std::string& errorMsg = "", std::function<bool(const T&)> condition = nullptr)
{
    T value;
    bool isValid;

    do
    {
        if (!prompt.empty())
            std::cout << prompt;

        std::cin >> value;
        isValid = std::cin.good() && (std::cin.peek() == '\n');

        if (isValid && condition)
        {
            isValid = condition(value);
        }

        if (!isValid)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (!errorMsg.empty())
                std::cout << errorMsg;
        }
    }
    while (!isValid);

    return value;
}

template<>
inline std::string validatedInput<std::string>(const std::string& prompt, const std::string& errorMsg, std::function<bool(const std::string&)> condition)
{
    std::string value;
    bool isValid;

    if (!prompt.empty())
            std::cout << prompt;

    if (std::cin.peek() == '\n')
            std::cin.ignore();

    getline(std::cin, value);
    isValid = !value.empty();

    if (!value.empty() && !condition || condition(value))
    {
        return value;
    }
    else if (!errorMsg.empty())
    {
        std::cout << errorMsg;
    }
    return validatedInput<std::string>(prompt,errorMsg,condition);
}