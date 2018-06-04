//
// Created by cyril on 3/15/18.
//

#include "Rule.h"

Rule::Rule(std::string history, std::string prediction, int support, float confidence) {
    this->history = history;
    this->prediction = prediction;
    this->support = support;
    this->confidence = confidence;
}

std::ostream& operator <<(std::ostream &output, Rule &rule) {
    output<<"{rule="
          <<rule.history
          <<"->"<<rule.prediction
          <<", support="
          <<rule.support
          <<", confidence="
          <<rule.confidence
          <<"}";
    return output;
}

float Rule::getConfidence() {
    return this->confidence;
}

std::string Rule::getHistory() {
    return this->history;
}


std::string Rule::getPrediction() {
    return this->prediction;
}

int Rule::getSupport() {
    return this->support;
}

void Rule::setConfidence(float confidence) {
    this->confidence = confidence;
}

void Rule::setHistory(std::string &history) {
    this->history = history;
}

void Rule::setPrediction(std::string &prediction) {
    this->prediction = prediction;
}

void Rule::setSupport(int support) {
    this->support = support;
}

std::ostream& operator<<(std::ostream& out, const Rule  &r) {
    out << "{rule=" << r.history << "->" << r.prediction << ", support=" << r.support << ", confidence=" << r.confidence
        << "}";
    return out;
}