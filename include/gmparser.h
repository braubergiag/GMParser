#pragma once
#include <filesystem>
namespace fs = std::filesystem;
class GMParser {
public:
    static void Parse(const fs::path & src,const  fs::path & target);

private:
};


