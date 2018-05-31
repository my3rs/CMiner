#include "SubseqnenceSuffix.h"

SubseqnenceSuffix::SubseqnenceSuffix() {
    occurTimes = 0;
}

SubseqnenceSuffix::SubseqnenceSuffix(string subsequence, int occurTimes, set<string> suffixes) {
    this->subsequence = subsequence;
    this->occurTimes = occurTimes;
    this->suffixes = suffixes;
}

void SubseqnenceSuffix::addSuffix(string suffix) {
    this->suffixes.emplace(suffix);
}

string SubseqnenceSuffix::getSubsequence() {
    return this->subsequence;
}

void SubseqnenceSuffix::setSubsequence(string subsequence) {
    this->subsequence = subsequence;
}

int SubseqnenceSuffix::getOccurtimes() {
    return this->occurTimes;
}

void SubseqnenceSuffix::setOccurTimes(int occurTimes) {
    this->occurTimes = occurTimes;
}

set<string> SubseqnenceSuffix::getSuffixes() {
    return this->suffixes;
}

void SubseqnenceSuffix::setSuffixes(set<string> suffixes) {
    this->suffixes = suffixes;
}