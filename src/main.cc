
#include "../include/site_generator.h"
#include <string>


int main(int argc, char *argv[]) {
    #if 1
    if (argc != 3) {
        std::cerr << "Expected ./Program src_dir targer_dir \n";
        return 1;
    }

    #endif
    SiteGenerator sitegen(argv[1],argv[2]);
    try {
        sitegen.Generate();
    } catch (std::runtime_error & ex) {
        std::cerr << ex.what() << std::endl;
    } 
   


    
}