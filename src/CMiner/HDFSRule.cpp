//
// Created by root on 01/05/18.
//

#include "HDFSRule.h"

HDFSRule::HDFSRule() {

}

HDFSRule::HDFSRule(std::vector<std::string> history, std::string prediction,
                   int support, float confidence)
{
    this->history = history;
    this->prediction = prediction;
    this->support = support;
    this->confidence = confidence;
}

std::ostream& operator<<(std::ostream& out, const HDFSRule & h) {
    out<<"{"
        <<"rule="<<h.history<<"->"<<h.prediction
        <<", support="<<h.support
        <<", confidence="<<h.confidence
        <<"}";
    return out;
}

void HDFSRule::setSupport(int support) {
    this->support = support;
}

int HDFSRule::getSupport() {
    return support;
}

float HDFSRule::getConfidence() {
    return confidence;
}

std::vector<std::string> HDFSRule::getHistory() {
    return history;
}

std::string HDFSRule::getPrediction(std::string prediction) {
    return prediction;
}

void HDFSRule::setConfidence(float confidence) {
    this->confidence = confidence;
}

void HDFSRule::setHistory(std::vector<std::string> history) {
    this->history = history;
}

void HDFSRule::setPrediction(std::string prediction) {
    this->prediction = prediction;
}

