/**
 * 将HDFS中的audit.log中的日志行转换成日志对象。
 * Audit.log是HDFS中的监控日志，需要配置开启，它会记录所有对文件的操作。
 * 详情参见：http://wiki.apache.org/hadoop/HowToConfigure 中的 Log4j Configuration部分
 */
#ifndef CMINER_FILEACCESSLOG_H
#define CMINER_FILEACCESSLOG_H

#include <string>
using std::string;

class FileAccessLog {
private:
    // Log记录格式：time: ugi= ip= cmd= Miner=	dst= perm=
    // 范例：2013-11-21 17:24:54,697: ugi=root	ip=/127.0.0.1	cmd=open	Miner=/input/access_log_1	dst=null	perm=null
    string time;   // 客户端访问文件的时间：yyyy-MM-dd HH:mm:ss,SSS
    string ugi;    // 客户端的用户标识
    string ip;     // 客户端的IP
    string cmd;    // 文件访问的具体操作，包括：open|create|delete|rename|mkdirs|listStatus|setReplication|setOwner|setPermission
    string src;    // 文件操作中源文件地址
    string dst;    // 文件操作中目标文件地址
    string perm;   // 操作权限
    bool valid = true;

public:
    friend std::ostream& operator << (std::ostream &output, FileAccessLog &log);

    static FileAccessLog parse(string logLine);

    string getTime();

    void setTime(string time);

    string getUgi();

    void setUgi(string ugi);

    string getIp();

    void setIp(string ip);

    string getCmd();

    void setCmd(string cmd);

    string getSrc();

    void setSrc(string src);

    string getDst();

    void setDst(string dst);

    string getPerm();

    void setPerm(string perm);

    bool isValid();

    void setValid(bool valid);
};


#endif //CMINER_FILEACCESSLOG_H
