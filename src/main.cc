#include <iostream>
#include <fstream>

#include "../include/gmparser.h"
#include "../include/site_generator.h"

#include <string>



using std::cout; 
using std::cin;
using std::endl; 
using std::string;





int main() {
    string path = "/home/marshall/Programming/C++Projects/GMParser/TEST_DIR";
    string output_path = "/home/marshall/Programming/C++Projects/GMParser/OutputDir";
    SiteGenerator sitegen(path,output_path);
    sitegen.Generate();


    
}