
#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

#include "../include/site_generator.h"
#include "../include/gmparser.h"
namespace fs = std::filesystem;

TEST(SiteGenerator, HandleStructure) {

    std::string relative_in_path = "../tests/InputDir";
    

    fs::create_directories(relative_in_path + "/sub_dir_1");
    fs::create_directories(relative_in_path + "/sub_dir_2/sub_sub_dir_1/");
    fs::create_directories(relative_in_path + "/sub_dir_3");

    std::ofstream(relative_in_path + "/sub_dir_1/test.txt").put('z');
    std::ofstream(relative_in_path + "/sub_dir_2/page_1.gmi").put('#');
    std::ofstream(relative_in_path + "/sub_dir_2/sub_sub_dir_1/page_2.gmi").put('#');
    std::ofstream(relative_in_path + "/page_3.gmi").put('#');
    std::ofstream(relative_in_path + "/file_1.mp3").put('@');

    std::string relative_out_path = "../tests/OutputDir";
    SiteGenerator site_generator(relative_in_path,relative_out_path);
    site_generator.Generate();

    ASSERT_TRUE(fs::exists(relative_out_path +  "/sub_dir_1/test.txt"));
    ASSERT_TRUE(fs::exists(relative_out_path +  "/sub_dir_2/page_1.html"));
    ASSERT_TRUE(fs::exists(relative_out_path +  "/sub_dir_2/sub_sub_dir_1/page_2.html"));
    ASSERT_TRUE(fs::exists(relative_out_path +  "/page_3.html"));
    ASSERT_TRUE(fs::exists(relative_out_path +  "/file_1.mp3"));
    ASSERT_TRUE(fs::exists(relative_out_path +  "/sub_dir_3"));

    fs::remove_all(relative_in_path);
    fs::remove_all(relative_out_path);

}

