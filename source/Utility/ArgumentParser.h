#pragma once

#include <iostream>
#include <vector>

class ArgumentParser
{
public:
    static ArgumentParser& Get()
    {
        static ArgumentParser parser;
        return parser;
    }

    void Init(int argc, char** argv);
    void Parse();

private:
    std::vector<std::string> m_args{};
};