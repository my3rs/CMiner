//
// Created by cyril on 18-5-31.
//

#ifndef MINER_SUBSEQNENCESUFFIX_H
#define MINER_SUBSEQNENCESUFFIX_H

#include <string>
using std::string;

#include <set>
using std::set;

class SubseqnenceSuffix {
private:
    string  subsequence;
    int     occurTimes;
    set<string>     suffixes;

public:
    SubseqnenceSuffix();
    SubseqnenceSuffix(string subsequence, int occurTimes, set<string> suffixes);
    void addSuffix(string suffix);
    string getSubsequence();
    void setSubsequence(string subsequence);
    int getOccurtimes();
    void setOccurTimes(int occurTimes);
    set<string> getSuffixes();
    void setSuffixes(set<string> suffixes);
};


#endif //MINER_SUBSEQNENCESUFFIX_H
