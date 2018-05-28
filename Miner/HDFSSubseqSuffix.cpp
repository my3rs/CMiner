//
// Created by root on 01/05/18.
//

#include "HDFSSubseqSuffix.h"

HDFSSubseqSuffix::HDFSSubseqSuffix() {
    occerTimes = 0;
}

HDFSSubseqSuffix::HDFSSubseqSuffix(std::string subsequence, int occerTimes, std::set<std::string> suffixes) {
    this->subsequence = subsequence;
    this->occerTimes = occerTimes;
    this->suffixes = suffixes;
}

void HDFSSubseqSuffix::addSuffix(std::string suffix) {
    this->suffixes.insert(suffix);
}

std::string HDFSSubseqSuffix::getSubsequence() {
    return subsequence;
}

void HDFSSubseqSuffix::setSubsequence(std::string subsequence) {
    this->subsequence = subsequence;
}

int HDFSSubseqSuffix::getOccerTimes() {
    return occerTimes;
}

void HDFSSubseqSuffix::setOccerTimes(int occertimes) {
    this->occerTimes = occertimes;
}

void HDFSSubseqSuffix::setSuffixes(std::set<std::string> suffixes) {
    this->suffixes = suffixes;
}

std::set<std::string> HDFSSubseqSuffix::getSuffixes() {
    return this->suffixes;
}