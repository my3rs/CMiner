#ifndef MINER_UTILS_H
#define MINER_UTILS_H

#include <string>
using std::string;

#include <vector>
using std::vector;

class Utils {
public:
    static vector<string> getRandomLogs(int length);
    static string getRandomStr(int length);
};


#endif //MINER_UTILS_H
