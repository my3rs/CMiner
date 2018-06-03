

#include <boost/algorithm/string.hpp>
#include "CMinerAuthor.h"


CMinerAuthor::CMinerAuthor(string inputSequence, int windowSize, int maxGap, int minSupport, float minConfidence) {
    this->inputSequence = inputSequence;
    this->windowSize = windowSize;
    this->maxGap = maxGap;
    this->minSupport = minSupport;
    this->minConfidence = minConfidence;
}

void CMinerAuthor::candidateFreSubsequences() {
    throw "Need argument!";
}

map<string, Rule> CMinerAuthor::startMining() {
    // split access sequence into segments
    cutAccessSequence();

    // get frequent sequence with length of 1
    generateFirstDs();

    // Mining: frequent subsequence
    SubseqnenceSuffix ss = getSeqFromDs();
    candidateFreSubsequences(ss.getSubsequence(), ss.getOccurtimes());

    // filter: closed frequent subsequence
    genClosedFreSubsequences();

    // generate: rules
    generateRules();

    return rules;
}


void CMinerAuthor::clear() {
    CMinerBase::clear();
    Ds.clear();
}

void CMinerAuthor::generateFirstDs() {
    map<string, int> charAccessTimes;

    // count occurrence times of each char
    // record suffix at the same time
    for (auto segment : this->inputSegments) {
        for (int k = 0; k < segment.size(); k++) {
            string currentChar = segment.substr(k, 1);

            // count appearance times of each char
            int count = charAccessTimes.find(currentChar) == charAccessTimes.end() ? 0 : charAccessTimes[currentChar];
            charAccessTimes[currentChar] = count + 1;

            // record suffix, each char only recorded once
            int start = segment.find(currentChar);
            if (start != k || start == segment.size() - 1)
                continue;
            if (this->Ds.find(currentChar) == this->Ds.end())
                this->Ds.emplace(currentChar, SubseqnenceSuffix());
            this->Ds[currentChar].addSuffix(segment.substr(start + 1));
        }
    }

    // filter out those subsequence whose occurrence times is less than minSupport
    for (auto entry : charAccessTimes) {
        if (entry.second < minSupport)
            Ds.erase(entry.first);
        else {
            Ds[entry.first].setOccurTimes(entry.second);
            Ds[entry.first].setSubsequence(entry.first);
        }
    }
}

void CMinerAuthor::candidateFreSubsequences(string currentSubseq, int occurTimes) {
    // add current sequence to candidate frequent subsequence set
    freSubsequences.emplace(currentSubseq, occurTimes);

    // 添加当前序列到候选频繁子序列对应的长度层次中
    unsigned long seqLen = currentSubseq.length();
    if (seqLen > maxSeqLength)
        maxSeqLength = seqLen;
    if (freSubsequencesTier.find(seqLen) == freSubsequencesTier.end())
        freSubsequencesTier.emplace(seqLen, map<string, int> ());
    freSubsequencesTier[seqLen].emplace(currentSubseq, occurTimes);


    // get suffix set of current sequence
    set<string> currentDs = Ds[currentSubseq].getSuffixes();

    // 从当前的后续集合中计算出一个字符长度的频繁子序列集合
    set<string> oneCharFreSubseqs = generateOneCharFreSubseq(currentDs);

    // 一次扫描每一个后缀集合中长度为1的频繁子序列
    for (const auto &alpha : oneCharFreSubseqs) {
        // 类似AA这种不要检测
        if (boost::algorithm::ends_with(currentSubseq, alpha))
            continue;

        // 检测 currentSubseq 连接 alpha 是否为 frequent subsequence,同时，记录alpha有效出现时的新suffix
        string newSeq = currentSubseq + alpha;
        set<string> newDs;
        unsigned long endCount = 0;
        for (const auto &suffix : currentDs) {
            unsigned long position  = suffix.find_first_of(alpha);
            if (position == suffix.size() - 1) {
                endCount ++;
            } else if (position >= 0 && position <= maxGap) {
                newDs.emplace(suffix.substr(position + 1));
            }
        }

        // 对于到达minSupport的新序列，递归调用
        if (newDs.size() + endCount >= minSupport) {
            Ds.emplace(newSeq, SubseqnenceSuffix(newSeq, newDs.size() + endCount, newDs));

            // 处理完毕，从Ds中移除
            Ds.erase(currentSubseq);

            candidateFreSubsequences(newSeq, newDs.size() + endCount);
        }
    }

    // 处理完毕，从Ds中移除
    Ds.erase(currentSubseq);

    // 继续处理下一个
    try {
        SubseqnenceSuffix newSeq = getSeqFromDs();
        candidateFreSubsequences(newSeq.getSubsequence(), newSeq.getOccurtimes());
    } catch (std::range_error e) {

    }

}

SubseqnenceSuffix CMinerAuthor::getSeqFromDs() {
    if (Ds.empty())
        throw std::range_error("Ds empty!");
    return Ds.begin()->second;
}

set<string> CMinerAuthor::generateOneCharFreSubseq(set<string> segments) {
    map<string, int> charAccessTimes;
    set<string> oneCharFreSubseqs;

    // count occurrence times of each char
    for (const string &segment : segments) {
        for (unsigned long k = 0; k < segment.size(); k ++) {
            string currentChar = segment.substr(k, 1);

            int count = charAccessTimes.find(currentChar) == charAccessTimes.end() ? 0 : charAccessTimes[currentChar];
            charAccessTimes[currentChar] = count + 1;
        }
    }

    // filter out subsequence whose occurrence times < minSupport
    for (const auto &entry : charAccessTimes) {
        if (entry.second >= minSupport) {
            oneCharFreSubseqs.emplace(entry.first);
        }
    }

    return oneCharFreSubseqs;
}