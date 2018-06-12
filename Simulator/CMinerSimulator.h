/**
 * 采用CMiner算法作为PredictCache的预测算法，模拟使用。
 */
#ifndef CMINER_CMINERSIMULATOR_H
#define CMINER_CMINERSIMULATOR_H

#include <string>
using std::string;

#include <map>
using std::map;


#include "Simulator.h"
#include "../Miner/CMinerHDFS.h"



class CMinerSimulator : public Simulator {
private:
    CMinerHDFS miner;
    string currentPrefix;
    int currentGap = 0;
public:
    explicit CMinerSimulator(int fileCacheSize);

    /// 根据当前访问上文和currentFile构成的Prefix，获取后续预测文件
    vector<string> getPredictFiles(string currentFile) override ;

public:
    void setDataSet(vector<string> logs);
    void generateRules();

};


#endif //CMINER_CMINERSIMULATOR_H
