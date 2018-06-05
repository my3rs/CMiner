#include <string>
using std::string;

#include <iostream>
using std::cout;
#include "Miner/CMinerAuthor.h"
#include "Utils/Utils.h"

static CMinerAuthor miner;

void testByStep(string seqence) {
    clock_t start = clock();
    miner.setInputSequeuece(seqence);

    miner.cutAccessSequence();
    miner.generateFirstDs();

    // mining
    SubseqnenceSuffix ss = miner.getSeqFromDs();
    miner.candidateFreSubsequences(ss.getSubsequence(), ss.getOccurtimes());

    miner.genClosedFreSubsequences();   // filter: close frequent subsequence
    miner.generateRules();
    clock_t end = clock();


    cout << "================== Generating Corrlation Rules ======================\n";
    cout << "Window size:\t" << miner.getWindowSize() << "\n";
    cout << "Max Gap:\t" << miner.getMaxGap() << "\n";
    cout << "Min Support:\t" << miner.getMinSupport() << "\n";
    cout << "Min Confidence:\t" << miner.getMinConfidence() << "\n";

    cout << "Input Sequence Length:\t\t" << miner.getInputSequeuece().size() << "\n";
    cout << "Input Segments Length:\t\t" << miner.getInputSegments().size() << "\n";
    cout << "Frequent Subsequences:\t\t{";
    for (const auto &entry : miner.getFreSubsequences()) {
        cout << entry.first << "=" << entry.second << ", ";
    }
    cout << "\b}\n";
    cout << "Closed Frequent Subsequences:\t{";
    for (const auto &entry : miner.getCloseFreSubsequencs()) {
        cout << entry.first << "=" << entry.second << ", ";
    }
    cout << "\b}\n";
    cout << "Rules Numer:\t" << miner.getRules().size() <<"\n";
    for (const auto &entry : miner.getRules()) {
        cout << "\t" << entry.first << "=" << entry.second << "\n";

    }

    cout << "Mining Time: " << (end - start)*1.0 / CLOCKS_PER_SEC << " s.\n";

    miner.clear();
}

int main(int argc, char* argv[]) {
    // 输出关联关系挖掘过程中的每一步中间结果
    string seqence = Utils::getRandomStr(100000);

    testByStep(seqence);
}