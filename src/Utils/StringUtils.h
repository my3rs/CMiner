//
// Created by root on 01/05/18.
//

#ifndef CMINER_STRINGUTILS_H
#define CMINER_STRINGUTILS_H

#include <string>
using std::string

class StringUtils {
public:
    static std::vector<std::string> &split( const std::string &str,
                                                           const std::string &delimiters,
                                                           std::vector<std::string> &elems,
                                                           bool skip_empty = true );
    static std::vector<std::string> &split_by_string( const std::string &str,
                                            const std::string &delimiters,
                                            std::vector<std::string> &elems,
                                            bool skip_empty = true );
    bool endWith(const char * str, const char * endstr);
    bool endWith(string str, string endstr);
};


#endif //CMINER_STRINGUTILS_H
