
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include "../include/gmparser.h"
#include <filesystem>
#include <string>


using std::cout; 
using std::cin;

namespace fs = std::filesystem;



class SiteGenerator {
public:
    SiteGenerator(const std::string & src, const std::string & target) :
        src_(src),target_(target) {}

    void Generate() const;
    void SetSrc(const std::string & src) {src_ = src;}
    void SetTarget(const std::string & target) {target_ = target;}
private:
    std::string src_;
    std::string target_;

};
