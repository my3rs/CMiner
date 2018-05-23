//
// Created by cyril on 3/15/18.
//

#include "CMinerBase.h"

CMinerBase::CMinerBase() {
    // 设置默认参数
    this->windowSize = 5;
    this->maxGap = this->windowSize - 2;
    this->minSupport = 4;
    this->minConfidence = 1.0f;
    this->maxSeqLength = 0;

    // 创建对象
//    this->inputSegments = new std::vector<std::string>;
}

void CMinerBase::cutAccessSequence() {
    // 检查输入字符串是否合法
    if (inputSequence.empty()) {
        std::cout<<"Input Sequence is null! Exit...\n";
        return;
    }

    // 对输入字符串进行分段
    int start = 0;
    int end = start + windowSize;

    while (end < inputSequence.length()) {
        // TODO in java: and, in C++ widowSize. so end is not used
        inputSegments.push_back(inputSequence.substr(start, windowSize));
        end += windowSize;
    }
    inputSegments.push_back(inputSequence.substr(start));
}

void CMinerBase::genClosedFreSubsequences() {

    // 检查候选频繁子序列是否为空
    if (freSubsequencesTier.empty()) {
        std::cout<<"Candidate Frequent Sequence is null! Exit...\n";
        return;
    }

    // 每层、依次检查每一个frequent subsequence，从中挑选出closed frequent subsequence
    for (int i=this->maxSeqLength; i>0; i--) {

        // 最长序列都是 closed 的（因为没有父序列）
        if (i == this->maxSeqLength) {
            auto it1 = freSubsequencesTier[i];
            for (auto e1 : it1) {
                closedFreSubsequences.insert(e1);
            }
        }
        // closed条件：
        // 不是任何frequent subsequence的子序列
        // 或
        // 是子序列 && support 与 大于父序列的support
        else {
            // 依次检查当前层每一个序列
            auto entrySet = freSubsequencesTier[i];
            for(auto entry : entrySet) {
                bool isSubSubseq = false;

                // 当前序列 与 其父层（直接父序列）中每一个序列的关系：是否为子序列、support大小关系
                auto superEntrySet = this->freSubsequencesTier[ i + 1 ];
                for (auto superEntry : superEntrySet) {
                    // 是子序列
                    if (superEntry.first.find(entry.first) != std::string::npos) {
                        isSubSubseq = true;

                        // 大于所有父序列的support
                        if (entry.second > superEntry.second) {
                            closedFreSubsequences.insert({entry.first, entry.second});

                            // 虽然这一次大于，但是有可能是有小于等于的父序列的，所以需要检测完
                            continue;
                        } else {
                            closedFreSubsequences.erase(entry.first);

                            // 一票否定，无需继续检测
                            break;
                        }
                    }
                }

                // 不是任何frequent subsequence的子序列
                if (!isSubSubseq) {
                    closedFreSubsequences.insert({entry.first, entry.second});
                }
            }
        }
    }
}

std::map<std::string, Rule> CMinerBase::generateRules() {
    // 检查候选频繁子序列、Closed频繁子序列是否为空
    if (freSubsequences.empty()) {
        std::cout<<"Candidate Frequent Sequences is null! Exit...\n";
        return rules;
    }
    if (closedFreSubsequences.empty()) {
        std::cout<<"Closed Frequent Sequences is null! Exit...\n";
        return rules;
    }

    // 依次处理每一个closed frequent subsequence，获取rules
    for (auto closedEntry : closedFreSubsequences) {
        std::string closedSeq = closedEntry.first;
        int closedSeqConf = closedEntry.second;

        // 只有一个字符序列，无法导出关系，跳过
        if (closedSeq.length() == 1) {
            continue;
        }

        // 开始生成rule
        for (int historyStart = 0; historyStart < closedSeq.length() - 1; historyStart ++) {
            // 生成history子序列
            for (int historyEnd = historyStart + 1; historyEnd < closedSeq.length(); historyEnd ++) {
                std::string history = closedSeq.substr(historyStart, historyEnd - historyStart);
                float historyConf = freSubsequences[history] * 1.0F;

                // 生成prediction子序列（只有一个字符）
                for (int predictionStart = historyEnd; predictionStart < closedSeq.length(); predictionStart ++) {
                    std::string prediction = closedSeq.substr(predictionStart, 1);
                    float newRuleConf = freSubsequences[prediction] / historyConf;

                    // 当前规则confidence不够，跳过
                    if (newRuleConf < minConfidence) {
                        continue;
                    }

                    // 关联规则生成成功，放入规则集合中
                    std::string ruleStr = history + "|" + prediction;
                    if (rules.find(ruleStr) == rules.end()) {
                        rules.insert({ruleStr, Rule{history, prediction, closedSeqConf, newRuleConf}});
                    } else {
                        if (rules.find(ruleStr)->second.getSupport() < closedSeqConf) {
                            rules.find(ruleStr)->second.setSupport(closedSeqConf);
                        }
                    }
                }
            }
        }
    }
    return rules;
}

std::map<std::string, Rule> CMinerBase::startMining() {
    // 对初始访问序列分段
    cutAccessSequence();

    // 挖掘：频繁子序列
    candidateFreSubsequences();

    // 过滤：Closed频繁子序列
    genClosedFreSubsequences();

    // 生成：关联规则
    generateRules();

    return rules;
};

void CMinerBase::clear() {
    inputSegments.clear();
    freSubsequences.clear();
    closedFreSubsequences.clear();
    freSubsequencesTier.clear();
    rules.clear();

    maxSeqLength = 0;
}

int CMinerBase::getWindowSize() {
    return this->windowSize;
}

void CMinerBase::setWindowSize(int windowSize) {
    this->windowSize = windowSize;
}

int CMinerBase::getMaxGap() {
    return this->maxGap;
}

void CMinerBase::setMaxGap(int maxGap) {
    this->maxGap = maxGap;
}

int CMinerBase::getMinSupport() {
    return minSupport;
}

void CMinerBase::setMinSupport(int minSupport) {
    this->minSupport = minSupport;
}

float CMinerBase::getMinConfidence() {
    return minConfidence;
}

void CMinerBase::setMinConfidence(float minConfidence) {
    this->minConfidence = minConfidence;
}

std::string CMinerBase::getInputSequeuece() {
    return inputSequence;
}

void CMinerBase::setInputSequeuece(std::string inputSequeuece) {
    this->inputSequence = inputSequeuece;
}

std::vector<std::string> CMinerBase::getInputSegments() {
    return this->inputSegments;
}

std::map<std::string, int> CMinerBase::getFreSubsequences() {
    return this->freSubsequences;
}

std::map<std::string, int> CMinerBase::getCloseFreSubsequencs() {
    return this->closedFreSubsequences;
}

std::map<std::string, Rule> CMinerBase::getRules() {
    return this->rules;
};
std::map<int, std::map<std::string, int>> CMinerBase::getFreSubsequencesTier() {
    return this->freSubsequencesTier;
}

int CMinerBase::getMaxSeqLength() {
    return this->maxSeqLength;
}

std::ostream& operator<<(std::ostream& os, const CMinerBase & cb) {
    os <<"\n================= Generation Correlation Rules ==============\n"
       <<"Window size:\t"<<this->windowSize<<"\n"
       <<"Max Gap:\t"<<this->maxGap<<"\n"
       <<"Min Support:\t"<<this->minSupport<<'\n'
       <<"Min Confidence:\t"<<this->minConfidence<<"\n"
       <<"Input Sequence Length:\t\t"<<this->inputSequence.length()<<"\n"
       <<"Input Segments Length:\t\t"<<this->inputSegments.size()<<"\n"
       <<"Frequent Subsequences:\t\t"<<this->freSubsequences<<"\n"
       <<"Closed Frequent Subsequences:\t"<<this->closedFreSubsequences<<"\n";

       return os;
}