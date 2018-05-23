/**
 * 将HDFS中的audit.log中的日志行转换成日志对象。
 * Audit.log是HDFS中的监控日志，需要配置开启，它会记录所有对文件的操作。
 * 详情参见：http://wiki.apache.org/hadoop/HowToConfigure 中的 Log4j Configuration部分
 */
#ifndef CMINER_FILEACCESSLOG_H
#define CMINER_FILEACCESSLOG_H

#include <string>

class FileAccessLog {
private:
    // Log记录格式：time: ugi= ip= cmd= Miner=	dst= perm=
    // 范例：2013-11-21 17:24:54,697: ugi=root	ip=/127.0.0.1	cmd=open	Miner=/input/access_log_1	dst=null	perm=null
    std::string time;   // 客户端访问文件的时间：yyyy-MM-dd HH:mm:ss,SSS
    std::string ugi;    // 客户端的用户标识
    std::string ip;     // 客户端的IP
    std::string cmd;    // 文件访问的具体操作，包括：open|create|delete|rename|mkdirs|listStatus|setReplication|setOwner|setPermission
    std::string src;    // 文件操作中源文件地址
    std::string dst;    // 文件操作中目标文件地址
    std::string perm;   // 操作权限
    bool valid = true;

public:
    friend std::ostream& operator << (std::ostream &output, FileAccessLog &log);

    std::vector<std::string> &split( const std::string &str,
                                     const std::string &delimiters,
                                     std::vector<std::string> &elems,
                                     bool skip_empty = true );

    static FileAccessLog parse(std::string logLine);

    std::string getTime();

    void setTime(std::string time);

    std::string getUgi();

    void setUgi(std::string ugi);

    std::string getIp();

    void setIp(std::string ip);

    std::string getCmd();

    void setCmd(std::string cmd);

    std::string getSrc();

    void setSrc(std::string src);

    std::string getDst();

    void setDst(std::string dst);

    std::string getPerm();

    void setPerm(std::string perm);

    bool isValid();

    void setValid(bool valid);
};


#endif //CMINER_FILEACCESSLOG_H
