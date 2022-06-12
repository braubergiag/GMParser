#include "../include/site_generator.h"


 void SiteGenerator::Generate() const {
    fs::create_directory(target_);
            for(const auto& dir_entry: fs::recursive_directory_iterator(src_)) {
                // std::cout << dir_entry.path() << "\n";
                // std::cout << fs::path(dir_entry).filename() << " " << dir_entry.is_directory() <<  "\n";
                const auto &p = dir_entry.path();             
                const auto relativeSrc = fs::relative(p, src_);


                if (dir_entry.is_directory()) {
                    fs::create_directory(target_ / relativeSrc);
                }
                const auto targetParentPath = target_ / relativeSrc.parent_path();
                fs::create_directories(targetParentPath);
                if (GMParser::Filter(dir_entry)) {
                    GMParser::Parse(dir_entry.path(), targetParentPath);
                    // std::cout << relativeSrc << "relative src\n";
                    // std::cout << targetParentPath << "target src\n";
                    continue;  
                } 
                fs::copy(p,targetParentPath,fs::copy_options::overwrite_existing);
            }

 }
