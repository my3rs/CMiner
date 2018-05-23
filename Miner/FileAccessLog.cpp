//
// Created by root on 01/05/18.
//

#include "FileAccessLog.h"
#include
#include <exception>

std::vector<std::string> &FileAccessLog::split( const std::string &str,
                                 const std::string &delimiters,
                                 std::vector<std::string> &elems,
                                 bool skip_empty = true )
{
    std::string::size_type pos, prev = 0;
    while ( ( pos = str.find_first_of(delimiters, prev) ) != string::npos ) {
        if ( pos > prev ) {
            elems.emplace_back( str, prev, pos - prev );
        }
        prev = pos + 1;
    }
    if ( prev < str.size() ) elems.emplace_back( str, prev, str.size() - prev );
    return elems;
}


FileAccessLog FileAccessLog::parse(std::string logLine) {
    FileAccessLog log = new FileAccessLog();
    // logPargs[0]: 2013-11-21 17:24:54,697
    // logParts[1]: ugi=root	ip=/127.0.0.1	cmd=open	Miner=/input/access_log_1	dst=null	perm=null
    // 解析出时间和日志段

    try {
        uint64_t timeEnd = logLine.find(": ");
        cout<<"time: "<<logLine.substr(0, timeEnd)<<endl;

        string info = logLine.substr(timeEnd+2);
        cout<<"info: "<<info<<endl;
        vector<string> infoParts;
        split(info, "\t", infoParts);
        log.setUgi(infoParts[0].substr(infoParts[0].find('=')+1));
        log.setIp(infoParts[1].substr(infoParts[1].find('=')+1));
        log.setCmd(infoParts[2].substr(infoParts[2].find('=')+1));
        log.setSrc(infoParts[3].substr(infoParts[3].find('=')+1));
        log.setDst(infoParts[4].substr(infoParts[4].find('=')+1));
        log.setPerm(infoParts[5].substr(infoParts[5].find('=')+1));

        // 只提取只读的OPEN操作
        if (!strcasecmp(log.getCmd().c_str(), "open")) {
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

std::string FileAccessLog::getCmd() {
    return cmd;
}

std::string FileAccessLog::getDst() {
    return dst;
}

std::string FileAccessLog::getIp() {
    return ip;
}

std::string FileAccessLog::getPerm() {
    return perm;
}

std::string FileAccessLog::getSrc() {
    return src;
}

std::string FileAccessLog::getTime() {
    return time;
}

std::string FileAccessLog::getUgi() {
    return ugi;
}

bool FileAccessLog::isValid() {
    return valid;
}

void FileAccessLog::setCmd(std::string cmd) {
    this->cmd = cmd;
}

void FileAccessLog::setDst(std::string dst) {
    this->dst = dst;
}

void FileAccessLog::setIp(std::string ip) {
    this->ip = ip;
}

void FileAccessLog::setPerm(std::string perm) {
    this->perm = perm;
}

void FileAccessLog::setSrc(std::string src) {
    this->src = src;
}

void FileAccessLog::setTime(std::string time) {
    this->time = time;
}

void FileAccessLog::setUgi(std::string ugi) {
    this->ugi = ugi;
}

void FileAccessLog::setValid(bool valid) {
    this->valid = valid;
}