
#include "../include/gmparser.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void GMParser::Parse(const fs::path & src,const  fs::path & target) {
    std::ifstream input(src);

    fs::path target_file_path = target / fs::path(src).filename().replace_extension(".html");
    std::ofstream output(target_file_path);
    // std::cout << "Parse " << target_file_path << "\n";
    bool pre_open = true; 
    for (std::string line; getline(input,line); ) {
        std::istringstream is(line);

        std::string command, entry;
        is >> command;
        is.get();
        if (command == "#") {
           
            getline(is,entry);
            output << "<h1>" << entry << "</h1>" << "\n";
        } else if (command == "##") {
            getline(is,entry);
            output << "<h2>" << entry << "</h2>" << "\n";
        } else if (command == "###") {
            getline(is,entry);
            output << "<h3>" << entry << "</h3>" << "\n";
        } else if (command == "=>") {
            std::string ref;
            is >> ref;
            is.get();
            getline(is,entry);
            output << R"(<a href=")" << ref << "\">" << entry << "</a>" << "\n"; 
        } else if (command == "*") {
            getline(is,entry);
            output << "<li>" << entry << "</li>" << "\n";
        } else if (command == ">") {
            getline(is,entry);
            output << "<blockquote>" << entry << "</blockquote>" << "\n";
        } else if (command == "```") {
            getline(is,entry);
            if (pre_open) {
                output << "<pre>\n";
                pre_open = false;
                continue;
            }
            output << "</pre>\n";
            pre_open = true;
        } else {

            output << line << "\n";
        }
        
    }
}