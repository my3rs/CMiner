//
// Created by root on 01/05/18.
//

#include "CMinerSimulator.h"
#include <boost/algorithm/string.hpp>

CMinerSimulator::CMinerSimulator(int fileCacheSize) : Simulator(fileCacheSize) {
    this->miner;
    this->miner.setMaxGap(2);
}

void CMinerSimulator::setDataSet(vector <string> logs) {
    this->miner.setInputSeqence(logs);
}

void CMinerSimulator::generateRules() {
    this->miner.startMining();
}

vector<string> CMinerSimulator::getPredictFiles(string currentFile) {
    string nextFile = "";


    // 将当前读取的文件考虑到序列中
    if (currentPrefix.empty()) {
        this->currentPrefix = currentFile;
    } else {
        currentPrefix += ("|" + currentFile);
    }

    // 在规则中搜索序列，若找到，则返回
    bool starts = false;
    for(auto entry : this->miner.getRules()) {
        // 「只是」以当前序列开头，非相等：保证找出a->c,a|b->这种情况
        if (boost::starts_with(entry.first, currentPrefix)) {
            nextFile = entry.second.getPrediction();
        } else {
            starts = true;
        }
    }

    // 规则中未找到该序列，有四种可能
    if (boost::equals(currentPrefix, currentFile)) {
        // 1. 序列仅包含一个文件，且没有匹配的：跳过，从下一个文件重新开始
        if (!starts) {
            currentPrefix = "";
            currentGap = 0;
        }
        // 2. 有匹配的序列前缀，但是并未完整形成：以当前序列为基础，继续生成
        else {
            currentGap = 0;
        }
    } else {
        // 1. 没有匹配到规则序列，且超过maxGap：直接以当前文件作为新序列开头，重新生成
        if (!starts && currentGap > miner.getMaxGap()) {
            currentPrefix = currentFile;
        }
        // 2. 有匹配的序列前缀，但是并未完整形成：以当前序列为基础，继续生成
        else if (starts) {
            currentGap = 0;
        }
        // 3. 没有匹配的序列前缀，且不是序列开头，Gap也没有超过：让其在gap范围内继续扩展一层
        else {
            currentGap ++;
        }
    }

    vector<string> predictSuffixes;
    if (!nextFile.empty()) {
        predictSuffixes.emplace_back(nextFile);
    }

    return predictSuffixes;
}