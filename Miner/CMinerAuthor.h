/**
 * Mining relationships in sequent events(chars)
 * Implement CMiner algorithm in article C-Miner: Mining Block Correlations in Storage Systems
 * Use the author's core algorithm to generate Candidate Frequent Subsequences: DFS algorithm
 *
 * @author cyril
 * @date 2018-05-31
 * */

#ifndef MINER_CMINERAUTHOR_H
#define MINER_CMINERAUTHOR_H

#include <map>
using std::map;

#include <string>
using std::string;

#include "CMinerBase.h"
#include "SubseqnenceSuffix.h"

class CMinerAuthor : public CMinerBase {
private:
    // Store frequent subsequence's suffix with max length in segments.
    map<string, SubseqnenceSuffix> Ds;

    // 从输入的segments中计算出长度为1的频繁子序列集合，并返回
    set<string> generateOneCharFreSubseq(set<string>  segments);

public:
    CMinerAuthor() : CMinerBase() {}
    CMinerAuthor(string inputSequence, int windowSize, int maxGap, int minSupport, float minConfidence);
    void candidateFreSubsequences() override ;
    map<string, Rule> startMining();
    void clear();
    /* generate frequent sequence of length 1 and suffix of each frequent subsequence
     * produce map<string, SubsequenceSuffix> Ds
     * */
    void generateFirstDs();

    /* abstract method: DFS generate Frequent Subsequences  :
     * 1) access subsequences with a distance of no more than maxGap(not necessarily continuous)
     * 2) occurrence > minSupport
     *
     * @return
     * map<string, int> freSubsequences
     * map<int, map<string, int>> freSubsequencesTier
     *
     * */
    void candidateFreSubsequences(string currentSubseq, int occurTimes);

    SubseqnenceSuffix getSeqFromDs();


};


#endif //MINER_CMINERAUTHOR_H
