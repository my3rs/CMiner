
#include <fstream>
#include <exception>
using std::exception;
#include "Simulator.h"
#include "../Miner/FileAccessLog.h"


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
                    if (src.find(cutCommonPrefix) != string::npos) {
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
        FILE_CACHE.put(fileName, fileName);
//        cout<<e.what()<<endl;
        targetFile = "";
    }
    return targetFile;


}

void Simulator::putFileIntoCache(std::string fileName, std::string file) {
    FILE_CACHE.put(fileName, file);
}