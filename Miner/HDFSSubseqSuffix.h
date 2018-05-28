/**
 * 记录每个候选频繁序列（HDFS文件访问序列）在window中的最大后缀
 */

#ifndef CMINER_HDFSSUBSEQSUFFIX_H
#define CMINER_HDFSSUBSEQSUFFIX_H

#include <string>
#include <set>

class HDFSSubseqSuffix {
private:
    std::string subsequence;
    int occerTimes;
    std::set<std::string> suffixes;

public:
    HDFSSubseqSuffix();

    HDFSSubseqSuffix(std::string subsequence, int occerTimes, std::set<std::string> suffixes);

    void addSuffix(std::string suffix);

    std::string getSubsequence();

    void setSubsequence(std::string subsequence);

    int getOccerTimes();

    void setOccerTimes(int occertimes);

    std::set<std::string> getSuffixes();

    void setSuffixes(std::set<std::string> suffixes);
};


#endif //CMINER_HDFSSUBSEQSUFFIX_H
