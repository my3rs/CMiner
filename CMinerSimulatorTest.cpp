//#include <zconf.h>
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;
#include "CMinerSimulator.h"


vector<string> getRandomStr(int length) {
    string baseStr = "abcdefghijklmnopqrstuvwxyz";
    vector<string> ret;
    int range = baseStr.size();
    for (int i = 0; i < length; i++) {
        ret.emplace_back(baseStr.substr(lrand48() % range, 1));
    }

    return ret;
}


int main(int argc, char* argv[]) {
    vector<string> logs = getRandomStr(600);
    for (int fileCacheSize = 1; fileCacheSize <= 50; fileCacheSize ++) {
        CMinerSimulator simulator(fileCacheSize);

        // 获取数据集
//        vector<string> logs = simulator.getDataSet("./audit.log", "/user/root/input/sogou/query-log-");

        // 生成关联规则
        simulator.setDataSet(logs);
        simulator.generateRules();

        // 模拟读取数据，利用关联规则提高Cache命中率
        int hitCount = 0;
        int prefetchCount = 0;
        clock_t totalTime = 0;
        for (int i = 0; i < logs.size(); i++) {
            string currentFile = logs[i];

            clock_t start = clock();
            string targetFile = simulator.getFileFromCache(currentFile);
            // Miss
            if (targetFile.empty()) {

                // read miss causes prediction
                for (string file : simulator.getPredictFiles(currentFile)) {
                    simulator.putFileIntoCache(file, file);
                    prefetchCount ++;
                }
            }
            // Hit
             else {
                hitCount ++;
            }
            clock_t end = clock();
            totalTime += end - start;
        }

        // 输出命中率
        cout<<"Hit ratio of LRU Cache with CMiner: "<<hitCount*1.0/logs.size()<<endl;
    }
    logs.clear();
}