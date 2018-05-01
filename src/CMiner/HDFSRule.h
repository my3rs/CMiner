/**
 * HDFS访问日志的关联规则对象：
 * 		history -> prediction，并包含其发生的权重confidence。
 * 		closed frequent subsequence拆分为history和prediction，它们也都是frequent subsequence。
 */
#ifndef CMINER_HDFSRULE_H
#define CMINER_HDFSRULE_H

#include <vector>
#include <string>

class HDFSRule {
private:
    std::vector<std::string>    history;
    std::string                 prediction;
    int                         support;        // 可以生成该规则的所有closed frequent subsequence中的最大support
    float                       confidence;     // support(prediction)/support(history)

public:
    HDFSRule();

    HDFSRule(std::vector<std::string> history, std::string prediction, int support, float confidence);

    friend std::ostream& operator<<(std::ostream& os, const HDFSRule  &h);

    std::vector<std::string> getHistory();

    void setHistory(std::vector<std::string> history);

    std::string getPrediction(std::string prediction);

    void setPrediction(std::string prediction);

    int getSupport();

    void setSupport(int support);

    float getConfidence();

    void setConfidence(float confidence);

};


#endif //CMINER_HDFSRULE_H
