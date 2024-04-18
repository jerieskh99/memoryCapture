//
// Created by Jeries Khoury on 08/04/2024.
//

#include "distanceFunction.h"
#include <bitset>


// Euclidean
double EuclideanDistance::calculateDistanceBetweenPoints(vector<double> x, vector<double> y) const {
    unsigned long dist_size = (x.size() < y.size()) ? (y.size()) : (x.size());
    vector<double> powers;
    for(int i=0; i<dist_size; i++){
        powers.push_back(pow((y[i] - x[i]), 2));
    }
    double sum = 0;
    for(double n: powers)   sum += n;
    return sqrt(sum);
}


double EuclideanDistance::calculateSumDistanceBetweenVectors(const std::vector<vector<double>> &vec1,
                                                          const std::vector<vector<double>> &vec2) const {
    double sum = 0.0;
    for(size_t i = 0; i < vec1.size(); ++i) {
        sum += calculateDistanceBetweenPoints(vec1[i], vec2[i]);
    }
    return sqrt(sum);
}


std::vector<double>
EuclideanDistance::vectorOfDistances(const std::vector<vector<double>> &vec1,
                                     const std::vector<vector<double>> &vec2) const {
    {
        std::vector<double> distances;
        // Example implementation could be calculating distances between corresponding elements
        for(size_t i = 0; i < vec1.size(); ++i) {
            distances.push_back(calculateDistanceBetweenPoints(vec1[i], vec2[i]));
        }
        return distances;
    }
}


// Calculate Hamming distance between two bytes
// Beware of the conversion
static inline int hammingDistanceByte(char a, char b) {
    return std::bitset<8>(a ^ b).count();
}


double GrayDistance::calculateDistanceBetweenPointsC(vector<char> x, vector<char> y) const {
    size_t minLength = std::min(x.size(), y.size());
    int totalDistance = 0;
    for (size_t i = 0; i < minLength; ++i) {
        totalDistance += hammingDistanceByte(x[i], y[i]);
    }
    return static_cast<double>(totalDistance);
}


double GrayDistance::calculateSumDistanceBetweenVectors(const vector<vector<char>> &vec1,
                                                        const vector<vector<char>> &vec2) const {
    size_t minLength = std::min(vec1.size(), vec2.size());
    double sumDistance = 0.0;
    for (size_t i = 0; i < minLength; ++i) {
        // Calculate and sum distances between corresponding vectors
        sumDistance += calculateDistanceBetweenPointsC(vec1[i], vec2[i]);
    }
    return sumDistance;
}


std::vector<double>
GrayDistance::vectorOfDistances(const vector<vector<char>> &vec1, const vector<vector<char>> &vec2) const {
    std::vector<double> distances;
    size_t minLength = std::min(vec1.size(), vec2.size());
    for (size_t i = 0; i < minLength; ++i) {
        // Calculate distance for each pair of vectors and add to distances vector
        distances.push_back(calculateDistanceBetweenPointsC(vec1[i], vec2[i]));
    }
    return distances;
}


// Calculates the distance between two memory units of the images.
// Increments i equally for both images and sums the total distance.
double distanceFunction::calculateMUDistanceBetweenPointsC(const vector<char>& baseImage, const vector<char>& newImage,
                                                           unsigned int memoryUnit, unsigned int base_index,
                                                           unsigned int new_index) {
    int totalDistance = 0;
    for (size_t i = 0; i < memoryUnit; ++i) {
        totalDistance += hammingDistanceByte(baseImage[base_index + i], newImage[new_index + i]);
    }
    return static_cast<double>(totalDistance);
}

