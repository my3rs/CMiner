#include <iostream>
using std::cout;

#include "Miner/CMinerMy.h"
#include "Utils/Utils.h"

static CMinerMy miner;

static void testByStep(string sequence) {
    miner.setInputSequeuece(sequence);

    clock_t start = clock();
    miner.cutAccessSequence();
    miner.candidateFreSubsequences();
    miner.genClosedFreSubsequences();
    miner.generateRules();
    clock_t end = clock();

    cout << "================== Generating Corrlation Rules ======================\n";
    cout << "Window size:\t" << miner.getWindowSize() << "\n";
    cout << "Max Gap:\t\t" << miner.getMaxGap() << "\n";
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
    string sequence = Utils::getRandomStr(10000);
    testByStep(sequence);
}