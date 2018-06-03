#include "Utils.h"


vector<string> Utils::getRandomLogs(int length) {
    string baseStr = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    vector<string> ret;
    int range = baseStr.size();
    for (int i = 0; i < length; i++) {
        ret.emplace_back(baseStr.substr(lrand48() % range, 1));
    }

    return ret;
}