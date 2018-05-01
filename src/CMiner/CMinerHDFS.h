/**
 * 挖掘HDFS Audit Log中文件访问的关联关系
 * 采用C-Miner算法，使用DFS算法生成候选频繁子序列。
 */

#ifndef CMINER_CMINERHDFS_H
#define CMINER_CMINERHDFS_H

#include <vector>
#include <string>
#include <map>

#include "HDFSRule.h"

class CMinerHDFS {
protected:
    int     windowSize;     // 窗口大小，每个片段的长度
    int     maxGap;         // 频繁子序列中两个相邻字符（事件）间的最大间隔
    int     minSupport;     // 频繁序列的最小出现次数
    float   minConfidence;  // 关联规则的最小confidence，confidence(a->b) = support(b)/support(a)

    std::vector<std::string>                inputSequence;       // 文件访问序列
    std::vector<std::vector<std::string>>   inputSegments;       // 文件访问序列的分段，每段长度为windowSize
    std::map<std::string, int>              freSubsequences;     // 候选频繁子序列，对应其出现的次数
    std::map<std::string, int>              closedFreSubsequences;       // Closed频繁子序列
    std::map<std::string, HDFSRule>         rules;               // 关联规则

};


#endif //CMINER_CMINERHDFS_H
