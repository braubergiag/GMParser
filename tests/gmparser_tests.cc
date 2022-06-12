
#include <gtest/gtest.h>
#include "../include/gmparser.h"
#include <filesystem>
#include <sstream>

// Demonstrate some basic assertions.
TEST(GMParser, HandleTags) {


{
    GMQuery gm_query;
    std::istringstream is("# Header 1\n");
    std::ostringstream os;
    is >> gm_query;
    os << gm_query;
    ASSERT_EQ(os.str(),"<h1>Header 1</h1>\n");
}

{
    GMQuery gm_query;
    std::istringstream is("## Header 2\n");
    std::ostringstream os;
    is >> gm_query;
    os << gm_query;
    ASSERT_EQ(os.str(),"<h2>Header 2</h2>\n");
}
{
    GMQuery gm_query;
    std::istringstream is("### Header 3\n");
    std::ostringstream os;
    is >> gm_query;
    os << gm_query;
    ASSERT_EQ(os.str(),"<h3>Header 3</h3>\n");
}
{
    GMQuery gm_query;
    std::istringstream is("* list element\n");
    std::ostringstream os;
    is >> gm_query;
    os << gm_query;
    ASSERT_EQ(os.str(),"<li>list element</li>\n");
}
{
    GMQuery gm_query;
    std::istringstream is("> some quote\n");
    std::ostringstream os;
    is >> gm_query;
    os << gm_query;
    ASSERT_EQ(os.str(),"<blockquote>some quote</blockquote>\n");
}
{
    GMQuery gm_query;
    std::istringstream is("=> http://some-address.com link\n");
    std::ostringstream os;
    is >> gm_query;
    os << gm_query;
    ASSERT_EQ(os.str(),"<a href=\"http://some-address.com\">link</a>\n");
}
{
    GMQuery gm_query;
    std::istringstream input("```\nsome text\nsome text\n```\n");
    std::ostringstream os;
     for (std::string line; std::getline(input,line); ) {
        std::istringstream is(line);
        is >> gm_query;
        os << gm_query;
    }
    ASSERT_EQ(os.str(),"<pre>\nsome text\nsome text\n</pre>\n");
}








}

TEST(GMParser, HandleIncludedTags) {
    {
    GMQuery gm_query;
    std::istringstream input("```\n# some text\n## some text\n```\n");
    std::ostringstream os;
     for (std::string line; std::getline(input,line); ) {
        std::istringstream is(line);
        is >> gm_query;
        os << gm_query;
    }
    ASSERT_EQ(os.str(),"<pre>\n<h1>some text</h1>\n<h2>some text</h2>\n</pre>\n");
}
{
    GMQuery gm_query;
    std::istringstream input("```\n# some text\n\nsome text\n\n```\n");
    std::ostringstream os;
     for (std::string line; std::getline(input,line); ) {
        std::istringstream is(line);
        is >> gm_query;
        os << gm_query;
    }
    ASSERT_EQ(os.str(),"<pre>\n<h1>some text</h1>\n\nsome text\n\n</pre>\n");
}



}
