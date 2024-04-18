//
// Created by Jeries Khoury on 08/04/2024.
//

#ifndef MEMORYCAPTURE_DELTAMANAGER_H
#define MEMORYCAPTURE_DELTAMANAGER_H
#include <vector>
#include"distanceFunction.h"
#include <future>


using std::vector;

#define PAGE_SIZE 4096

class deltaManager {
// A class for calculating the deltas of memory pages.
public:
    explicit deltaManager(distanceFunction* distanceFunction, unsigned int memoryUSize = PAGE_SIZE,
                          unsigned long long captureSizeMega = 2000);
    ~deltaManager();

    // Function to calculate the delta between two memory images.
    // The implementation will be based on the mathematical description
    // provided in the Fourier_deltas.pdf, using the Fourier transform
    // approach for efficient computation.
    void calculateFullDelta(const vector<char>& baseImage,
                        const vector<char>& newImage);

    void calculateDelta(const vector<char>& baseImage,
                        const vector<char>& newImage);

    [[nodiscard]] double getFullDelta() const{ return full_delta; }

    distanceFunction* getDistFunction(){ return dist_func; }

    vector<double>& getDeltaBlocks(){ return curr_delta_blocks; }

    void calculateDeltaParallel(const vector<char>& baseImage, const vector<char>& newImage);

    // Additional functions related to the calculation can be added here.
    // For example, function to apply the inverse Fourier transform to estimate
    // the function f(t) based on the calculated deltas.

private:
    // Private members and helper functions to support delta calculation.
    distanceFunction* dist_func;
    std::vector<double> curr_delta_blocks;
    double full_delta;
    unsigned int memoryUnit;
    unsigned long long captureSize;
    unsigned long long memory_units_number;
    size_t threadCount;
};


#endif //MEMORYCAPTURE_DELTAMANAGER_H
