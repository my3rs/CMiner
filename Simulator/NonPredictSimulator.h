/**
 * LRUCache without prediction algorithm
 * */

#ifndef MINER_NONPREDICTSIMULATOR_H
#define MINER_NONPREDICTSIMULATOR_H

#include "Simulator.h"

class NonPredictSimulator : public Simulator {
public:
    explicit NonPredictSimulator(int fileCacheSize) : Simulator(fileCacheSize) {}
    vector<string> getPredictFiles(string currentFile) override ;


};


#endif //MINER_NONPREDICTSIMULATOR_H
