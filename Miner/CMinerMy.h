/**
 * 挖掘序列中事件（字符）的关联关系
 * 实现《C-Miner: Mining Block Correlations in Storage Systems》中所述的C-Miner算法结果，
 * 但具体生成Candidate Frequent Subsequences算法不同：BFS，多轮扫描。
 */

#ifndef CMINER_CMINERMY_H
#define CMINER_CMINERMY_H

#include "CMinerBase.h"

class CMinerMy : public CMinerBase {
public:
    CMinerMy() : CMinerBase() {};
    CMinerMy(std::string inputSequence, int windowSize, int maxGap, int minSupport, float minConfidence)
            : CMinerBase(inputSequence, windowSize, maxGap, minSupport, minConfidence) {}
    void candidateFreSubsequences() override ;
};


#endif //CMINER_CMINERMY_H
