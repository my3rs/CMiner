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