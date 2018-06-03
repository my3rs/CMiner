ADD_LIBRARY(miner STATIC CMinerBase.cpp CMinerHDFS.cpp FileAccessLog.cpp HDFSRule.cpp HDFSSubseqSuffix.cpp)
ADD_LIBRARY(miner_author STATIC CMinerAuthor.cpp CMinerBase.cpp SubseqnenceSuffix.cpp Rule.cpp)
