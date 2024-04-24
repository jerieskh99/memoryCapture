//
// Created by Jeries Khoury on 24/04/2024.
//

#ifndef MEMORYCAPTURE_PROBDISTFUNCS_H
#define MEMORYCAPTURE_PROBDISTFUNCS_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric> // for transform


class HausdorffDistance {
public:
    static double maxDistance(const std::vector<double>& from, const std::vector<double>& to);

    static double calculate(const std::vector<double>& dist1, const std::vector<double>& dist2);


};


class BhattacharyyaDistance {
public:
    static double calculate(const std::vector<double>& P, const std::vector<double>& Q);
};


class KullbackLeiblerDivergence {
public:
    static double calculate(const std::vector<double>& P, const std::vector<double>& Q);
};

#endif //MEMORYCAPTURE_PROBDISTFUNCS_H
