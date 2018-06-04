#include "Utils.h"


vector<string> Utils::getRandomLogs(int length) {
    string baseStr = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    vector<string> ret;
    int range = baseStr.size();
    for (int i = 0; i < length; i++) {
        ret.emplace_back(baseStr.substr(lrand48() % range, 1));
    }

    return ret;
}

string Utils::getRandomStr(int length) {
    string baseStr = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string ret = "";
    int range = baseStr.size();
    for (int i = 0; i < length; i++) {
        ret += baseStr.substr(lrand48()%range, 1);
    }

    return ret;
}