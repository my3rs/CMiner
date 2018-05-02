//
// Created by root on 01/05/18.
//

#include "../Utils/StringUtils.h"
#include "CMinerHDFS.h"
#include <string.h>

CMinerHDFS::CMinerHDFS() {
    windowSize = 5;
    maxGap = windowSize - 2;
    minSupport = 4;
    minConfidence = 1.0f;

    maxSeqLength = 0;
}

CMinerHDFS::CMinerHDFS(vector<string> inputSequence, int windowSize,
                       int maxGap, int minSupport, float minConfidence)
{
    this->windowSize = windowSize;
    this->maxGap = maxGap;
    this->minSupport = minSupport;
    this->minConfidence = minConfidence;

    this->inputSequence = inputSequence;
    this->inputSequence = inputSequence;

    this->maxSeqLength = 0;
}

void CMinerHDFS::cutAccessSequence() {
    // 检查输入日志序列
    if (inputSequence.empty() || inputSequence.size() == 0) {
        std::cout<<"Input Sequence is null! Exit...\n";
        return;
    }

    // 对输入日志序列进行分段
    int winNum =  -1;
    for (int i = 0; i < inputSequence.size(); i++) {

        // 开始一个新窗口
        if (i / windowSize > winNum) {
            auto newWindow = new vector<string>;
            newWindow->insert(inputSequence[i]);
            inputSegments.insert(newWindow);
            winNum = i / windowSize;
            delete(newWindow);
        }
        // 在旧窗口中追加访问项
        else {
            inputSegments[winNum].insert(inputSequence[i]);
        }
    }
}

void CMinerHDFS::generateFirstDs() {
    auto fileAccessTimes = new map<string, int>;

    // 统计每个文件访问的次数，同时记录suffix
    for (int i = 0; i < inputSegments.size(); i++) {
        vector<string> segment = inputSegments[i];

        for (int k = 0; k < segment.size(); k++) {
            string currentFile = segment[k];

            // 统计每个文件出现的次数
            auto iter = fileAccessTimes->find(currentFile);
            if (iter == fileAccessTimes->end()) {
                int count = 0;
                fileAccessTimes->insert({currentFile, count+1});
            } else {
                int count = fileAccessTimes[currentFile];
                fileAccessTimes->erase(iter);
                fileAccessTimes->insert({currentFile, count+1});
            }

            // 判断当前文件在当前窗口中是否被统计过
            int start = 0;
            for (; start < segment.size() && start < k; start ++) {
                if (strcasecmp(currentFile.c_str(), segment[start].c_str()) == 0) {
                    break;
                }
            }
            if (start != k || start == segment.size() - 1) {
                continue;
            }

            // 记录suffix
            string suffix = "";
            for (int j = start + 1; j < segment.size(); j++) {
                suffix += segment[j];
                suffix += "|";
            }
            if (Ds.find(currentFile) == Ds.end()) {
                Ds.insert({currentFile, HDFSSubseqSuffix()});
            }
            Ds[currentFile].addSuffix(suffix);

        }
    }

    // 过滤掉出现次数小于minSupport的子序列
    for (auto entry : *fileAccessTimes) {
        if (entry.second < minSupport) {
            Ds.erase(entry.first);
        } else {
            Ds[entry.first].setOccerTimes(entry.second);
            Ds[entry.first].setSubsequence(entry.first);
        }
    }

    delete(fileAccessTimes);
}


void CMinerHDFS::getSeqFromDs() {
    if (Ds.empty()) {
        return nullptr;
    }
    return Ds.begin()->second;
}

void CMinerHDFS::candidateFreSubsequences(string currentSubseq, int occerTimes) {

    // 添加当前序列至 候选频繁子序列集合中
    freSubsequences.insert({currentSubseq, occerTimes});

    // 添加当前序列至 候选频发子序列对应的长度层次中
    vector<string> vtmp;
    StringUtils::split_by_string(currentSubseq, "\\|", vtmp);
    int seqLen = vtmp.size();
    if (seqLen > maxSeqLength) {
        maxSeqLength = seqLen;
    }
    if(freSubsequencesTier.find(seqLen) == freSubsequencesTier.end()) {
        freSubsequencesTier.insert({seqLen, map<string, int>()});
    }
    freSubsequencesTier[seqLen].insert({currentSubseq, occerTimes});

    // 获取当前序列的后缀集合
    set<string> currentDs = Ds[currentSubseq].getSuffixes();

    // 从当前的后缀集合中计算出只包含一个访问序列的频繁子序列集合
    set<string> oneFileFreSubseqs = generateOneCharFreSubseq(currentDs);

    // 一次扫描每一个后缀集合中 只包含1个文件的频繁子序列
    for (auto file : oneFileFreSubseqs) {

        // 类似AA这种不检测
        if (strcasecmp(currentSubseq.c_str(), file.c_str()) == 0) {
            continue;
        }

        // 检测 currentSubseq连接file是否为frequent subsequence，同时，记录file有效出现时的新suffix
        string newSeq = currentSubseq + "|" + file;
        set<string> newDs;
        int endCount = 0;

        for (string suffix : currentDs) {
            if (suffix.find(file) != string::npos) {
                vector<string> suffixFiles;
                StringUtils::split_by_string(suffix, "\\|", suffixFiles);

                for (int i = 0; i < suffixFiles.size() && i <= maxGap; i++) {
                    if (i == suffixFiles.size() - 1) {
                        endCount ++;
                    } else if (strcasecmp(suffixFiles[i].c_str(), file.c_str()) == 0) {
                        // todo : there may be some thing wrong
                        newDs.insert(suffix.substr(suffix.find(suffixFiles[i+1])));
                        break;
                    }
                }
            }
        }

        // 对于达到minSupport的新序列，递归调用
        if (newDs.size() + endCount >= minSupport) {
            Ds.insert({newSeq, HDFSSubseqSuffix(newSeq, newDs.size() + endCount, newDs)});

            // 处理完毕，从Ds中移除
            Ds.erase(currentSubseq);
            candidateFreSubsequences(newSeq, newDs.size()+endCount);
        }
    }

    // 处理完毕，从Ds中移除
    Ds.erase(currentSubseq);

    // 继续处理下一个
    HDFSSubseqSuffix nextSeq = getSeqFromDs();
    if (nextSeq != nullptr) {
        candidateFreSubsequences(nextSeq.getSubsequence(), nextSeq.getOccerTimes());
    }

}

void CMinerHDFS::genClosedFreSubsequences() {

    // 检查候选频繁子序列层次是否为空
    if (freSubsequencesTier.empty() || freSubsequencesTier.size() == 0) {
        std::cout<<"Candidate Frequent Sequences is  null! Exit...\n";
        return;
    }

    // 每层、依次检查每一个frequent subsequence，从中挑选出closed frequent subsequence
    for (int i = this->maxSeqLength; i > 0; i--) {

        // 最长序列都是closed的
        if (i == this->maxSeqLength) {
            for (auto &entry : this->freSubsequencesTier[i]) {
                closedFreSubsequences.insert({entry.first, entry.second});
            }
        }

        // closed条件：
        // 不是任何frequent subsequence的子序列
        // 或
        // 是子序列 && support 与 大于父序列的support
         else {
            // 依次检查当前层每一个序列
            for(auto &entry : this->freSubsequencesTier[i]) {
                bool isSubseq = false;

                // 当前序列 与 其父层（直接父序列）中每一个序列的关系：是否为子序列、support大小关系
                for (auto &superEntry : this->freSubsequencesTier[i+1]) {

                    // 是子序列
                    if(StringUtils::endWith(superEntry.first, "|" + entry.first)
                            || strncmp(superEntry.first.c_str(), (entry.first + "|").c_str(), entry.first.size() + 1) == 0
                            || superEntry.first.find("|" + entry.first + "|") != string::npos)
                    {
                        isSubseq = true;

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
                if (!isSubseq) {
                    closedFreSubsequences.insert({entry.first, entry.second});
                }
            }
        }
    }

}

map<string, HDFSRule> CMinerHDFS::generateRules() {
    // 检查候选频繁子序列、Closed频繁子序列是否为空
    if (freSubsequences.size() == 0 || freSubsequences.empty()) {
        std::cout<<"Candidate Frequent Sequences is null! Exit...\n";
        return;
    }
    if (closedFreSubsequences.size() == 0 || closedFreSubsequences.empty()) {
        std::cout<<"Closed Frequent Sequences is null! Exit...\n";
        return;
    }

    // 依次处理每一个closed frequent subsequence，获取rules
    for (auto &closedEntry : closedFreSubsequences) {
        string closedSeq = closedEntry.first;
        int closedSeqConf = closedEntry.second;
        vector<string> accessFiles;
    }
}

set<string> CMinerHDFS::generateOneCharFreSubseq(set<string> segments) {
    map<string, int> fileAccessTimes;
    set<string> oneFileFreSubseqs;

    // 统计每个文件出现的次数
    for (auto segment : segments) {
        vector<string> files;
        StringUtils::split_by_string(segmeng, "\\|", files);
        for (auto file : files) {
            // 统计每个文件出现的次数
            int count = fileAccessTimes.find(file) != fileAccessTimes.end()
                        ? fileAccessTimes[file] : 0;
            auto  iter = fileAccessTimes.find(file);
            if (iter != fileAccessTimes.end()) {
                fileAccessTimes.erase(iter);
            }
            fileAccessTimes.insert({file, count + 1});
        }
    }

    // 过滤掉出现次数小于minSupport的子序列
    for (auto &entry : fileAccessTimes) {
        if (entry.second >= minSupport) {
            oneFileFreSubseqs.insert(entry.first);
        }
    }

    return oneFileFreSubseqs;
}

