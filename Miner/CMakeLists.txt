ADD_LIBRARY(miner_hdfs STATIC CMinerBase.cpp CMinerHDFS.cpp FileAccessLog.cpp HDFSRule.cpp HDFSSubseqSuffix.cpp)
ADD_LIBRARY(miner_author STATIC CMinerAuthor.cpp CMinerBase.cpp SubseqnenceSuffix.cpp Rule.cpp)
ADD_LIBRARY(miner_my STATIC CMinerMy.cpp CMinerBase.cpp Rule.cpp)
ADD_LIBRARY(miner_base STATIC CMinerBase.cpp FileAccessLog.cpp)
