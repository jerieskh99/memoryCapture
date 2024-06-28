//
// Created by Jeries Khoury on 08/04/2024.
//

#include "deltaManager.h"


deltaManager::deltaManager(distanceFunction* distanceFunction, unsigned int memoryUSize,
                           unsigned long long captureSizeMega )
                           :dist_func(distanceFunction), memoryUnit(memoryUSize){
    full_delta = 0;
    captureSize = captureSizeMega << 20;

    memory_units_number = captureSize / memoryUSize;

    // Initialize the delta block vector.
    for (unsigned long long i=0ULL; i< memory_units_number; i++)
    {
        curr_delta_blocks.push_back(0.0);
    }

    threadCount = std::thread::hardware_concurrency(); // Determine the number of available cores
}

deltaManager::~deltaManager() {
    delete dist_func;
}

void deltaManager::calculateFullDelta(const vector<char> &baseImage, const vector<char> &newImage) {
    full_delta = dist_func->calculateDistanceBetweenPointsC(baseImage, newImage);
}

// For each memory unit, we calculate the distance and save it in the delta block vector.
void deltaManager::calculateDelta(const vector<char> &baseImage, const vector<char> &newImage) {
    for (int i=0; i<memory_units_number; i++)
    {
        curr_delta_blocks[i] = dist_func->calculateMUDistanceBetweenPointsC(baseImage, newImage, memoryUnit,
                                                                            i*memoryUnit,
                                                                            i*memoryUnit);
    }
};


void deltaManager::calculateDeltaParallel(const vector<char>& baseImage, const vector<char>& newImage) {
    std::vector<std::future<int>> futures;
    size_t perThread = baseImage.size() / threadCount;
    for (size_t i = 0; i < threadCount; ++i) {
        size_t start = i * perThread;
        size_t end = (i + 1) * perThread;
        if (i == threadCount - 1) {
            end = baseImage.size(); // Make sure the last thread covers all remaining work
        }

        // Ensure lambda captures only required variables and by value where appropriate
        futures.push_back(std::async(std::launch::async,
                                     [start, end, &baseImage, &newImage]() -> int {
                                         int delta = 0;
                                         for (size_t j = start; j < end; ++j) {
                                             delta += (baseImage[j] != newImage[j]); //TODO: integrate your function to calculate blocks.
                                         }
                                         return delta;
                                     }));
    }
    // Collect results
    int totalDelta = 0;
    for (auto& fut : futures) {
        totalDelta += fut.get(); // Accumulate the results
    }
}

double deltaManager::calculateDeltaParallelApple(char* baseImage, char* newImage) {
    return 0.0;
}

complexDeltaManager::complexDeltaManager(distanceFunction *magnitudeDistanceFunc,
                                         distanceFunction *orientationDistanceFunc, unsigned int memoryUSize,
                                         unsigned long long int captureSizeMega)
                                         :dist_func_magnitude(magnitudeDistanceFunc),
                                         dist_func_orientation(orientationDistanceFunc),
                                         memoryUnit(memoryUSize), cp() {

    full_delta = 0;
    captureSize = captureSizeMega << 20;

    memory_units_number = captureSize / memoryUSize;
}

complexDeltaManager::~complexDeltaManager(){
    delete dist_func_magnitude;
    delete dist_func_orientation;
}

void complexDeltaManager::calculateDelta(const vector<char> &baseImage, const vector<char> &newImage) {
    for (int i=0; i<memory_units_number; i++)
    {
        auto mag = (float)dist_func_magnitude->calculateMUDistanceBetweenPointsC(baseImage, newImage, memoryUnit,
                                                                            i*memoryUnit,
                                                                            i*memoryUnit);
        auto orient = (float)dist_func_orientation->calculateMUDistanceBetweenPointsC(baseImage, newImage, memoryUnit,
                                                                                i*memoryUnit,
                                                                                i*memoryUnit);

        std::complex<float> cd = std::polar(mag, orient);
        curr_delta_blocks.push_back(cd);
    }
}

vector<std::complex<float>> complexDeltaManager::calculateCepstrum() {
    return cepstrum::computeCepstrum(curr_delta_blocks);
}

