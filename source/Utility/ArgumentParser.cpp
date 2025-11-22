#include "ArgumentParser.h"
#include "GenerateFileHashes.h"

void ArgumentParser::Init(int argc, char** argv)
{
    if (!argv)
    {
        return;
    }

    for (int i = 0; i < argc; i++)
    {
        m_args.push_back(argv[i]);
    }
}

void ArgumentParser::Parse()
{
    for (const auto& arg : m_args)
    {
        if (arg == "-gen_hashes")
        {
            GenerateFileHashes("C:\\xampp\\htdocs\\cache");
        }
    }
}