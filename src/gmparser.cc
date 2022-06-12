
#include "../include/gmparser.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <set>
namespace fs = std::filesystem;




std::istream& operator>>( std::istream & is,GMQuery & gm_query) {
    std::string query_type, entry;
    const char space_ch = ' ';
    std::getline(is,query_type,space_ch);

    std::set<std::string> tags{"#","##","###","=>",">","*","```"};
    std::string last_tag;
    // Checking case, when start tag joined with content. Ex. #Header 2
    if (tags.count(query_type) == 0) {
        if (query_type.size() > 0) {
            for (const auto & tag : tags) {
                auto it = query_type.find(tag);
                if (it != std::string::npos && it == 0) {
                    last_tag = tag;
                    continue;
                }
            }
            if (! last_tag.empty()) {
                std::string str_reminder;
                std::getline(is,str_reminder);

                if (last_tag == "```") {
                    GMQuery::tag_is_rebuilded = true;
                }
                query_type.insert(last_tag.length(),1,space_ch);
                query_type.append(" ");
                query_type.append(str_reminder);

                GMQuery gmq;
                std::istringstream temp_is(query_type);
                temp_is >> gmq;
                gm_query = {gmq.type,gmq.entry,gmq.open_t,gmq.close_t};
                return is;
            }

        }
    }

    if (query_type == "#") {
        getline(is,entry);
        gm_query = {GMQueryType::h1,entry,"<h1>","</h1>"};
    } else if (query_type == "##") {
        getline(is,entry);
        gm_query = {GMQueryType::h2,entry,"<h2>","</h2>"};
    } else if (query_type == "###") {
        getline(is,entry);
        gm_query = {GMQueryType::h3,entry,"<h3>","</h3>"};
    } else if (query_type == "=>") {
        std::string ref_name;
        getline(is,entry,space_ch);
        getline(is,ref_name);
        gm_query = {GMQueryType::a_href,ref_name,"<a href=\"" + entry + "\">","</a>"};
    } else if (query_type == "*") {
        getline(is,entry);
        gm_query = {GMQueryType::li,entry,"<li>","</li>"};
    } else if (query_type == ">") {
        getline(is,entry);
        gm_query = {GMQueryType::blockquote,entry,"<blockquote>","</blockquote>"};
    } else if (query_type == "```") {

        if (gm_query.tag_is_opened) {
            if (GMQuery::tag_is_rebuilded) {
                getline(is,entry);
                gm_query = {GMQueryType::pre,entry,"<pre>\n",""};
                GMQuery::tag_is_rebuilded = false;
            } else {
                gm_query = {GMQueryType::pre,"","<pre>",""};
            }

            GMQuery::tag_is_opened = false;
        } else {
            if (GMQuery::tag_is_rebuilded) {
                getline(is, entry);
                gm_query = {GMQueryType::pre, entry, "", "</pre>"};
                GMQuery::tag_is_rebuilded = false;
            }
            else {
                gm_query = {GMQueryType::pre,"","","</pre>"};
            }
            GMQuery::tag_is_opened = true;
        }



    } else if (query_type.length() > 0) {
        getline(is,entry);
        // Here query_type is a simple string
        gm_query = {GMQueryType::pod_str,query_type + space_ch + entry};
    } else {
        gm_query = {GMQueryType::pod_str};
    }

    return is;
}

std::ostream& operator<<(std::ostream & os,const GMQuery & gm_query) {
    return os << gm_query.open_t << gm_query.entry << gm_query.close_t << "\n";
}

void GMParser::Parse(const fs::path & src,const  fs::path & target) {
    std::string target_ext = ".html";
    fs::path target_file_path = target / fs::path(src).filename().replace_extension(target_ext);

    std::ifstream input(src);
    std::ofstream output(target_file_path);

    GMQuery gm_query;
    for (std::string line; getline(input,line); ) {
        std::istringstream is(line); 
        is >> gm_query;
        output << gm_query;
    }   
}

