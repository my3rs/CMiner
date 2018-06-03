#include "NonPredictSimulator.h"

int main(int argc, char* argv[]) {
    for (int fileCacheSize = 1; fileCacheSize <= 50; fileCacheSize ++) {
        NonPredictSimulator simulator(fileCacheSize);

        vector<string> logs = simulator.getDataSet("./audit.log" ,"/user/root/input/sogou/query-log-");

        // no need to generate rules

        int hitCount = 0;

        for (string currentFile : logs) {
            string targetFile = simulator.getFileFromCache(currentFile);

            // miss
            if (targetFile.empty()) {

            }
            // hit
            else {
                hitCount ++;
            }

        }
        cout << "Cache size: " << fileCacheSize << "\t";
        cout << "Non-Predict Hit Ratio: " << hitCount * 1.0 / logs.size() << "\n";
    }
}