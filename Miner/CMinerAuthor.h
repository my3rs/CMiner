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

public:
    CMinerAuthor() : CMinerBase() {}


};


#endif //MINER_CMINERAUTHOR_H
