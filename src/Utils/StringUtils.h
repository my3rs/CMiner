//
// Created by root on 01/05/18.
//

#ifndef CMINER_STRINGUTILS_H
#define CMINER_STRINGUTILS_H


class StringUtils {
public:
    static std::vector<std::string> &FileAccessLog::split( const std::string &str,
                                                           const std::string &delimiters,
                                                           std::vector<std::string> &elems,
                                                           bool skip_empty = true );
};


#endif //CMINER_STRINGUTILS_H
