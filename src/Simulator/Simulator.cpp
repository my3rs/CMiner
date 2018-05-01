
#include <fstream>
#include <exception>
#include "Simulator.h"
#include "../Utils/StringUtils.h"
#include "../CMiner/FileAccessLog.h"

Simulator::Simulator(int fileCacheSize) {
    this->FILE_CACHE = new cache::LRUCache(fileCacheSize);
}

std::vector<std::string> Simulator::getDataSet(std::string filePath, std::string cutCommonPrefix) {
    std::vector<std::string> logs;
    std::ifstream infile(filePath);
    std::string line;

    try {

        while(std::getline(infile, line)) {
            FileAccessLog log = FileAccessLog::parse(line);
            if (log.isValid()) {
                if(!cutCommonPrefix.empty()) {
                    std::string src = log.getSrc();
                    if (src.find_first_of(cutCommonPrefix) > -1) {
                        src.erase(src.find(cutCommonPrefix), cutCommonPrefix.size());
                        logs.push_back(src);
                    }
                } else {
                    logs.push_back(log.getSrc());
                }
            }
        }
    }
    catch (exception &e) {
        cout<<"Standard Exception: "<<e.what()<<endl;
        infile.close();
    }

    infile.close();

    return logs;
}

std::string Simulator::getFileFromCache(std::string fileName) {
    std::string targetFile;
    try {
        targetFile = FILE_CACHE.get(fileName);
    } catch (std::range_error &e) {
        FILE_CACHE.put(fileName);
        cout<<e.what()<<endl;
        targetFile = NULL;
    }
    return targetFile;


}

void Simulator::putFileIntoCache(std::string fileName, std::string file) {
    FILE_CACHE.put(fileName, file);
}