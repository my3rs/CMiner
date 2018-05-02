/**
 * 挖掘HDFS Audit Log中文件访问的关联关系
 * 采用C-Miner算法，使用DFS算法生成候选频繁子序列。
 */

#ifndef CMINER_CMINERHDFS_H
#define CMINER_CMINERHDFS_H

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <map>
using std::map;
#include <set>
using std::set;

#include "HDFSRule.h"
#include "HDFSSubseqSuffix.h"

class CMinerHDFS {
protected:
    int     windowSize;     // 窗口大小，每个片段的长度
    int     maxGap;         // 频繁子序列中两个相邻字符（事件）间的最大间隔
    int     minSupport;     // 频繁序列的最小出现次数
    float   minConfidence;  // 关联规则的最小confidence，confidence(a->b) = support(b)/support(a)

    vector<string>                inputSequence;       // 文件访问序列
    vector<vector<string>>   inputSegments;       // 文件访问序列的分段，每段长度为windowSize
    map<string, int>              freSubsequences;     // 候选频繁子序列，对应其出现的次数
    map<string, int>              closedFreSubsequences;       // Closed频繁子序列
    map<string, HDFSRule>         rules;               // 关联规则
    map<string, HDFSSubseqSuffix> Ds;                  // 存储frequent subsequence在每个segments中的最长suffix

    // 按候选频繁子序列的长度进行分层，相同长度的子序列存储在同一层中，例如：
    //     freSubsequences: {abc=4, b=4, c=5, a=5, ac=5, ab=4, bc=4}
    //	   freSubsequencesTier：{1={b=4, c=5, a=5}, 2={ac=5, ab=4, bc=4}, 3={abc=4}}
    map<int, map<string, int>>   freSubsequencesTier;
    int     maxSeqLength;   // 候选频繁子序列中，最长序列的长度

    /**
    * 从输入的segments中计算出只包含一个访问的频繁子序列集合，并返回
    */
    set<string> generateOneCharFreSubseq(set<string> segments);

public:
    CMinerHDFS();
    CMinerHDFS(vector<string> inputSequence, int windowSize,
               int maxGap, int minSupport, float minConfidence);

    /**
	 * 采用non-overlapped cutting方法将访问序列划分为多个固定长度的短序列片段。
	 *
	 * 生成:	List<List<FileAccessLog>> inputSegments
	 */
	 void cutAccessSequence();

    /**
    * 获取长度为1的频繁序列，以及各个频繁子序列的后缀集合
    *
    * 生成:	Map<String, HDFSSubseqSuffix> Ds
    */
    void generateFirstDs();

    /**
	 * 从Ds集合中挑选出一个子序列，作为处理使用
	 */
	 HDFSSubseqSuffix getSeqFromDs();

    /**
    * DFS 产生候选频繁子序列集合（Frequent Subsequences），满足：
    * 		1）相距不大于maxGap的访问子序列（没必要连续）
    * 		2）出现次数满足frequent要求，即不小于minSupport
    *
    * 生成:	Map<String, Integer> freSubsequences
    * 		Map<Integer, Map<String, Integer>> freSubsequencesTier;
    */
    void candidateFreSubsequences(string currentSubseq, int occerTimes);

    /**
	 * 产生Closed Frequent Subsequences，满足：
	 * 		1. 是候选频繁子序列（Frequent Subsequences）的子集
	 * 		2. 满足Closed条件：与所有super-subsequences的support不同
	 *
	 * 生成:	Map<String, Integer> closedFreSubsequences
	 */
	 void genClosedFreSubsequences();

    /**
    * 生成关联规则，满足：
    * 		1. 规则格式：子序列（长度>=1） -> 后续子序列（长度=1）
    * 		2. 从Closed Frequent Subsequences中生成
    * 		3. 每个Rule的confidence不小于minConfidence
    * 		4. 多个Closed Frequent Subsequences产生相同的rule，取最大support作为rule的support
    *
    * 生成:	Map<String, HDFSRule> rules
    */
    map<string, HDFSRule> generateRules();
};


#endif //CMINER_CMINERHDFS_H
