#include "GenerateFileHashes.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <format>

namespace fs = std::filesystem;

const std::vector<std::string> extensionsToLookFor = {
    ".rttex",
    ".ogg",
    ".mp3",
    ".wav"
};

void GenerateFileHashes(const std::string& basePath)
{
    fs::path cacheDir(basePath);

    if(!fs::exists(cacheDir))
    {
        ::printf("Fatal error while generating file hashes, cache path %s doesn't exist.\n", basePath.c_str());
        return;
    }

    std::ofstream("file_hashes.txt", std::ios::trunc);
    std::ofstream hashFile("file_hashes.txt", std::ios::app);

    for (const auto& file : fs::recursive_directory_iterator(cacheDir))
    {
        auto it = std::find(extensionsToLookFor.begin(), extensionsToLookFor.end(), file.path().extension().generic_string());

        if (it == extensionsToLookFor.end())
        {
            continue;
        }

        fs::path rel = fs::relative(file.path(), cacheDir);
        std::string relStr = rel.generic_string();

        unsigned int texHash = GetHashOfFile(file.path().generic_string());
        std::printf("Hash of file %s is %d\n", file.path().generic_string().c_str(), texHash);

        hashFile << std::format("{}|{}\n",
            relStr,
            texHash
        );
    }

    hashFile.close();
}