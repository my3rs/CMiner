

#include "CMinerAuthor.h"


CMinerAuthor::CMinerAuthor(string inputSequence, int windowSize, int maxGap, int minSupport, float minConfidence) {
    this->inputSequence = inputSequence;
    this->windowSize = windowSize;
    this->maxGap = maxGap;
    this->minSupport = minSupport;
    this->minConfidence = minConfidence;
}