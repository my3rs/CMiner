//
// Created by root on 01/05/18.
//

#include "StringUtils.h"


std::vector<std::string> & StringUtils::split( const std::string &str,
                                                const std::string &delimiters,
                                                std::vector<std::string> &elems,
                                                bool skip_empty = true )
{
    std::string::size_type pos, prev = 0;
    while ( ( pos = str.find_first_of(delimiters, prev) ) != string::npos ) {
        if ( pos > prev ) {
            elems.emplace_back( str, prev, pos - prev );
        }
        prev = pos + 1;
    }
    if ( prev < str.size() ) elems.emplace_back( str, prev, str.size() - prev );
    return elems;
}

std::vector<string> & StringUtils::split_by_string(const std::string &str,
                                                   const std::string &delimiters,
                                                   std::vector <string> &elems,
                                                   bool skip_empty)
{
    std::string::size_type pos, prev = 0;
    while ( ( pos = str.find(delimiters, prev) ) != string::npos ) {
        if ( pos > prev ) {
            elems.emplace_back( str, prev, pos - prev );
        }
        prev = pos + 1;
    }
    if ( prev < str.size() ) elems.emplace_back( str, prev, str.size() - prev );
    return elems;
}


bool StringUtils::endWith(const char * str, const char * end) {
    bool result = false;

    if (str != NULL && end != NULL) {
        int l1 = strlen(str);
        int l2 = strlen(end);
        if (l1 >= l2) {
            if (strcmp(str + l1 - l2, end) == 0) {
                result = true;
            }
        }
    }

    return result;
}

bool StringUtils::endWith(string s, string e) {
    char *str = s.c_str();
    char *end = e.c_str();
    bool result = false;

    if (str != NULL && end != NULL) {
        int l1 = strlen(str);
        int l2 = strlen(end);
        if (l1 >= l2) {
            if (strcmp(str + l1 - l2, end) == 0) {
                result = true;
            }
        }
    }

    return result;
}