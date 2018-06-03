/**
 * 关联规则对象：
 * 		history -> prediction，并包含其发生的权重confidence。
 * 		closed frequent subsequence拆分为history和prediction，
 * 		    它们也都是frequent subsequence。
 */
#ifndef CMINER_RULE_H
#define CMINER_RULE_H

#include <string>
#include <iostream>


class Rule {
private:
    std::string history;
    std::string prediction;
    int support;                // 可以生成该规则的所有 closed 频繁子序列中的最大 support
    float confidence;           // support(prediction)/support(history)
public:
    Rule(std::string history, std::string prediction, int support, float confidence);
    friend std::ostream& operator << (std::ostream &output, Rule &rule);

    std::string getHistory();
    std::string getPrediction();
    int getSupport();
    float getConfidence();

    void setHistory(std::string history);
    void setPrediction(std::string prediction);
    void setSupport(int support);
    void setConfidence(float confidence);

    friend std::ostream& operator<<(std::ostream& os, const Rule &r);
};


#endif //CMINER_RULE_H
