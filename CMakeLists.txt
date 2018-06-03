PROJECT(Miner)

CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

ADD_SUBDIRECTORY(Miner)
ADD_SUBDIRECTORY(LRUCache)
ADD_SUBDIRECTORY(Utils)

ADD_EXECUTABLE(CMinerSimulatorTest CMinerSimulatorTest.cpp CMinerSimulator.cpp Simulator.cpp)
TARGET_LINK_LIBRARIES(CMinerSimulatorTest lru_cache miner utils)

ADD_EXECUTABLE(CMinerHDFSTest CMinerHDFSTest.cpp)
TARGET_LINK_LIBRARIES(CMinerHDFSTest lru_cache miner)

ADD_EXECUTABLE(CMinerAuthorTest CMinerAuthorTest.cpp)
TARGET_LINK_LIBRARIES(CMinerAuthorTest miner_author)


ADD_EXECUTABLE(NonPredictSimulator NonPredictSimulator.cpp)
