//
// Created by root on 01/05/18.
//

#include "FileAccessLog.h"
#include <exception>
using std::exception;
#include <vector>
using std::vector;

#include <iostream>
#include <strings.h>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

using std::cout;
using std::endl;



FileAccessLog FileAccessLog::parse(string logLine) {
    FileAccessLog log;
    // logPargs[0]: 2013-11-21 17:24:54,697
    // logParts[1]: ugi=root	ip=/127.0.0.1	cmd=open	Miner=/input/access_log_1	dst=null	perm=null
    // 解析出时间和日志段

    try {
        uint64_t timeEnd = logLine.find(": ");
        log.setTime(logLine.substr(0, timeEnd));
//        cout<<"time: "<<logLine.substr(0, timeEnd)<<endl;

        string info = logLine.substr(timeEnd+2);
//        cout<<"info: "<<info<<endl;
        vector<string> infoParts;

        boost::split(infoParts, info, boost::algorithm::is_any_of("\t"), boost::token_compress_on);
        log.setUgi(infoParts[0].substr(infoParts[0].find('=')+1));
        log.setIp(infoParts[1].substr(infoParts[1].find('=')+1));
        log.setCmd(infoParts[2].substr(infoParts[2].find('=')+1));
        log.setSrc(infoParts[3].substr(infoParts[3].find('=')+1));
        log.setDst(infoParts[4].substr(infoParts[4].find('=')+1));
        log.setPerm(infoParts[5].substr(infoParts[5].find('=')+1));

        // 只提取只读的OPEN操作
        if (strcasecmp(log.getCmd().c_str(), "open")) {
            log.setValid(false);
        }
    }
    catch (exception &e) {
        cout << "Standard exception: " << e.what() << endl;
    }

    return log;

}

std::ostream& operator <<(std::ostream &output, FileAccessLog &log) {
    output<<"\nValid:\t\t"<<log.valid
          <<"\nAccess Time:\t"<<log.time
          <<"\nAccess User:\t"<<log.ugi
          <<"\nRemote Address:\t"<<log.ip
          <<"\tCommand:\t"<<log.cmd
          <<"\tSource Path:\t"<<log.src
          <<"\tDestination:\t"<<log.dst
          <<"\tPermission:\t"<<log.perm
          <<"======================\n";
    return output;
}

string FileAccessLog::getCmd() {
    return cmd;
}

string FileAccessLog::getDst() {
    return dst;
}

string FileAccessLog::getIp() {
    return ip;
}

string FileAccessLog::getPerm() {
    return perm;
}

string FileAccessLog::getSrc() {
    return src;
}

string FileAccessLog::getTime() {
    return time;
}

string FileAccessLog::getUgi() {
    return ugi;
}

bool FileAccessLog::isValid() {
    return valid;
}

void FileAccessLog::setCmd(string cmd) {
    this->cmd = cmd;
}

void FileAccessLog::setDst(string dst) {
    this->dst = dst;
}

void FileAccessLog::setIp(string ip) {
    this->ip = ip;
}

void FileAccessLog::setPerm(string perm) {
    this->perm = perm;
}

void FileAccessLog::setSrc(string src) {
    this->src = src;
}

void FileAccessLog::setTime(string time) {
    this->time = time;
}

void FileAccessLog::setUgi(string ugi) {
    this->ugi = ugi;
}

void FileAccessLog::setValid(bool valid) {
    this->valid = valid;
}