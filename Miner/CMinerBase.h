#ifndef CMINER_CMINERBASE_H
#define CMINER_CMINERBASE_H

#include <ostream>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include "Rule.h"

class CMinerBase {
protected:
    int windowSize;     // 窗口大小，每个片段的长度
    int maxGap;         // 频繁子序列中两个相邻字符（事件）间的最大间隔
    int minSupport;     // 频繁子序列的最小出现次数
    float minConfidence;            // 关联规则的最小 confidence, confidence(a->b) = support(b) / support(a)
    string inputSequence;      // 文件访问序列

//    std::list<string> inputSegments;               // 文件访问序列的分段，每段长度为windowSize
    vector<string> inputSegments;
    map<string, int> freSubsequences;         //  候选频繁子歿，对应其出现的次数 abc:4
    map<string, int> closedFreSubsequences;   // closed frequent subsequence
    map<string, Rule> rules;                  // 关联规则

    // 按候选频繁子序列的长度进行分层，相同长度的子序列存储在同一层中，例如：
    //     freSubsequences: {abc=4, b=4, c=5, a=5, ac=5, ab=4, bc=4}
    //	   freSubsequencesTier：{1={b=4, c=5, a=5}, 2={ac=5, ab=4, bc=4}, 3={abc=4}}
    map<int, map<string, int>> freSubsequencesTier;
    int maxSeqLength;               // 候选频繁子序列中，最长序列的长度


public:
    CMinerBase();

    /**
	 * 采用non-overlapped cutting方法将访问序列划分为多个固定长度的短序列片段。
	 *
	 * 生成:	vector<string> inputSegments
	 */
    void cutAccessSequence();

    /**
	 * 虚拟函数：产生候选频繁子序列集合（Frequent Subsequences），满足：
	 * 		1）相距不大于maxGap的访问子序列（没必要连续）
	 * 		2）出现次数满足frequent要求，即不小于minSupport
	 *
	 * 生成:	Map<String, Integer> freSubsequences
	 * 		Map<Integer, Map<String, Integer>> freSubsequencesTier;
	 */
    virtual void candidateFreSubsequences() = 0;

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
	 * 生成:	Map<String, Rule> rules
	 */
	 map<string, Rule> generateRules();


    /**
    * 执行关联规则的挖掘过程
    *
    * @return rules
    */
    virtual map<string, Rule> startMining();

    /**
	 * 清除List/MAP对象占用的空间，恢复初始状态
	 */
    virtual void clear();

    /** 算法参数的 getters and setters */
    int getWindowSize();
    void setWindowSize(int windowSize);

    int getMaxGap();
    void setMaxGap(int maxGap);

    int getMinSupport();
    void setMinSupport(int minSupport);

    float getMinConfidence();
    void setMinConfidence(float minConfidence);

    string getInputSequeuece();
    void setInputSequeuece(string inputSequeuece);

    /** 中间结果的getters */
    vector<string> getInputSegments();
    map<string, int> getFreSubsequences();
    map<string, int> getCloseFreSubsequencs();
    map<string, Rule> getRules();
    map<int, map<string, int>> getFreSubsequencesTier();
    int getMaxSeqLength();

    friend std::ostream& operator<<(std::ostream& os, const CMinerBase &cb);
};


#endif //CMINER_CMINERBASE_H
