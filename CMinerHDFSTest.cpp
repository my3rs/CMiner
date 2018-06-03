/// CMinerHDFS test

#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

#include <boost/algorithm/string.hpp>
#include <vector>
#include <exception>
using std::exception;
#include <fstream>
using std::ifstream;

using std::vector;

#include "Miner/CMinerHDFS.h"
#include "Miner/FileAccessLog.h"


static string LOG_PATH = "./audit.log";
static CMinerHDFS miner;





/**
 * Read logs from filePath
 * parse them into FileAccessLog object list
 **/
vector<string> getLogs(const string filePath) {
    vector<string> logs;

    ifstream infile(filePath);
    string line;

    try {
        while(std::getline(infile, line)) {
            FileAccessLog log = FileAccessLog::parse(line);
            if (log.isValid()) {
                vector<string> logParts;
                string src = log.getSrc();
                boost::split(logParts, src, boost::is_any_of("-"), boost::token_compress_on);
                logs.emplace_back(logParts[2]);
            }
        }
    }
    catch (exception &e) {
        cout << "Standard Exception: "<<e.what()<<endl;
        infile.close();
    }

    infile.close();
    return logs;
}


/**
 * Mine by step and display details of every step
 **/
void testByStep(string filePath) {
    miner.setMinSupport(3);
    miner.setWindowSize(26);

    // Read file
    vector<string> logs = getLogs(filePath);
    miner.setInputSeqence(logs);

    cout << "=== input sequence:\n";
    for (auto log : logs) {
        cout << log << " ";
    }
    cout << "\n\n";

    // Split file access log into segments
    miner.cutAccessSequence();
    cout << "=== input segments:\n";
    vector<vector<string>> segments = miner.getInputSegments();
    for (auto seg : segments) {
        for (auto entry : seg) {
            cout << entry<<" ";
        }
        cout << "\n";
    }
    cout << "\n\n";
    
    // Get frequent subsequence with length of 1
    miner.generateFirstDs();
    
    // Mine: Frequent subsequences
    HDFSSubseqSuffix ss = miner.getSeqFromDs();
    miner.candidateFreSubsequences(ss.getSubsequence(), ss.getOccerTimes());
    cout << "=== frequent subsequences:\n";
    for (auto entry : miner.getFreSubsequences()) {
        cout << entry.first << "=" << entry.second << ", ";
    }
    cout << "\n\n";

    // Filter: Closed frequent subsequences
    miner.genClosedFreSubsequences();
    cout << "=== closed frequent subsequences:\n";
    for (auto entry : miner.getClosedFreSubsequences()) {
        cout << entry.first << "=" << entry.second << ", ";
    }
    cout << "\n\n";

    // Generate: rules
    miner.generateRules();
    cout << "=== rules:\n";
    for (auto entry : miner.getRules()) {
        cout << entry.first << "\n";
    }
    miner.clear();
}

int main(int argc, char* argv[]) {

    testByStep(LOG_PATH);

}