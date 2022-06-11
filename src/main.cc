#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include "../include/gmparser.h"
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

// using Pred = std::function<bool(const fs::path)>;

using std::cout; 
using std::cin;
using std::endl; 
using std::string;
namespace fs = std::filesystem;


class SiteGenerator {
public:
    SiteGenerator(const string & src, const string & target) :
        src_(src),target_(target) {}

    void Generate( const std::function<bool(fs::directory_entry)>&  pred)  {
        fs::create_directory(target_);
        for(auto& dir_entry: fs::recursive_directory_iterator(src_)) {
            std::cout << dir_entry.path() << "\n";
            std::cout << fs::path(dir_entry).filename() << " " << dir_entry.is_directory() <<  "\n";
            const auto &p = dir_entry.path();             
            const auto relativeSrc = fs::relative(p, src_);


            if (dir_entry.is_directory()) {
                fs::create_directory(target_ / relativeSrc);
            }
            const auto targetParentPath = target_ / relativeSrc.parent_path();
            fs::create_directories(targetParentPath);
            if (pred(dir_entry)) {
                GMParser::Parse(dir_entry.path(), targetParentPath);
                std::cout << relativeSrc << "relative src\n";
                std::cout << targetParentPath << "target src\n";
                continue;  
            } 
            fs::copy(p,targetParentPath,fs::copy_options::overwrite_existing);
        }

    }

private:
    string src_;
    string target_;

};



int main() {
    string path = "/home/marshall/Programming/C++Projects/GMParser/TEST_DIR";
    string output_path = "/home/marshall/Programming/C++Projects/GMParser/OutputDir";

    SiteGenerator sitegen(path,output_path);
    std::string target_ext = ".gmi";
    const auto gmi_filter = [target_ext](const fs::directory_entry & dir_entry) -> bool {
        return   fs::path(dir_entry).extension() == target_ext && (! dir_entry.is_directory());

    };
    
    sitegen.Generate(gmi_filter);


    
}