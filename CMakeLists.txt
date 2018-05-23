PROJECT(Miner)

CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

ADD_SUBDIRECTORY(Miner)
ADD_SUBDIRECTORY(LRUCache)

ADD_EXECUTABLE(CMinerSimulatorTest CMinerSimulatorTest.cpp CMinerSimulator.cpp Simulator.cpp)
TARGET_LINK_LIBRARIES(CMinerSimulatorTest lru_cache miner)