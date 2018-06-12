#include "CMinerMy.h"


void CMinerMy::candidateFreSubsequences() {
    // 检查文件访问序列的分段是否为空
    if (inputSegments.empty() || inputSegments.size() == 0) {
        std::cout << "Input Sequences Segments is null! Exit...\n";
        return;
    }

    std::map<std::string, int> newSequencs;
    int currentSeqLen = 0;

    // 子序列长度没有限制，因此最大可以为windowSize，因此执行windowSize轮扫描
    while (++currentSeqLen <= windowSize) {
        // 挖掘关联子序列
        for (const std::string &segment : inputSegments) {
            // 初始第一轮扫描，获取最基础（每个字符）的出现次数
            if (1 == currentSeqLen) {
                for (int i = 0; i < segment.length(); i++) {
                    string oneCharStr = segment.substr(i, 1);
                    int count = newSequencs.find(oneCharStr) == newSequencs.end()
                                ? 0 : newSequencs[oneCharStr];
                    newSequencs[oneCharStr] = count + 1;
                }
            }
            // length > 1的序列挖掘
            else {
                for (auto &entry : freSubsequences) {
                    std::string prefix = entry.first;
                    // 序列的每次扫描长度 = 当前最长序列长度 + 1
                    if (prefix.length() < currentSeqLen - 1) {
                        continue;
                    }

                    // 这个POS的判断：
                    // 1. 顺序（非连续）包含该prefix中的所有字符即可
                    // 2. POS的值为prefix中最后一个字符在segment中的后一个位置
                    int pos = -1;
                    int lastPos = -1;
                    std::vector<char> v_prefix;
                    v_prefix.assign(prefix.begin(), prefix.end());
                    for (char c : v_prefix) {
                        lastPos = pos;
                        pos = segment.find(c);
                        if (pos == string::npos || pos <= lastPos) {
                            break;
                        }
                    }
                    if (pos == string::npos || pos <= lastPos) {
                        continue;
                    }

                    // 以prefix为关联序列开始，在segment中继续延伸关联序列
                    for (int i = pos + 1; i < segment.length() && (i - pos - 1) <= maxGap; i++) {
                        std::string oneCharStr = segment.substr(i, 1);
                        if (prefix.find(oneCharStr) != std::string::npos) {
                            continue;
                        }

                        std::string newSeq = prefix + oneCharStr;
                        int count = newSequencs.find(newSeq) == newSequencs.end()
                                    ? 0 : newSequencs[newSeq];
                        newSequencs[newSeq] = count + 1;
                    }
                }
            }
        }
        // 去除support < minSupport的序列
        for (auto& entry : newSequencs) {
            if (entry.second < getMinSupport()) {
                newSequencs.erase(entry.first);
            }
        }

        // 添加层次为currentSeqLen的subsequenceTier元素
        freSubsequencesTier.emplace(currentSeqLen, std::map<std::string, int>());

        // 将newSequences添加到subSequences、根据subSequence长度划分的Map中
        for (auto& entry : newSequencs) {
            freSubsequences.emplace(entry.first, entry.second);

            // 对得到的frequent subsequence根据subsequence的长度进行分组
            freSubsequencesTier[currentSeqLen].emplace(entry.first, entry.second);
        }

        // 更新最长序列的长度记录
        maxSeqLength = currentSeqLen;

        newSequencs.clear();

    }

}