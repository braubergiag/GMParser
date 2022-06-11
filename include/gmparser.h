#pragma once
#include <filesystem>
#include <functional>


namespace fs = std::filesystem;

using Pred =  std::function<bool(fs::directory_entry)>;
enum class GMQueryType {
    h1,h2,h3,
    li,
    blockquote,
    a_href,
    pre,
    pod_str
};
struct GMQuery {
    GMQueryType type;
    std::string entry;
    std::string open_t, close_t;
    inline static bool tag_is_opened{true};
};

std::istream& operator>>( std::istream & is,GMQuery & gm_query);
std::ostream& operator<<(std::ostream & os,const GMQuery & gm_query);
class GMParser {
public:
    static void Parse(const fs::path & src,const  fs::path & target);
    static bool Filter(const fs::directory_entry &  dir_entry) {
        return fs::path(dir_entry).extension() == ".gmi" && (! dir_entry.is_directory());
    };


};




