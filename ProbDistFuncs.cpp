//
// Created by Jeries Khoury on 24/04/2024.
//

#include "ProbDistFuncs.h"


double HausdorffDistance::calculate(const std::vector<double> &from, const std::vector<double> &to) {
    return std::max(maxDistance(from, to), maxDistance(to, from));
}


double HausdorffDistance::maxDistance(const std::vector<double> &dist1, const std::vector<double> &dist2) {
    double maxD = 0.0;
    for (double dFrom : dist1) {
        double minD = std::numeric_limits<double>::infinity();
        for (double dTo : dist2) {
            double dist = std::fabs(dFrom - dTo);
            if (dist < minD) {
                minD = dist;
            }
        }
        if (minD > maxD) {
            maxD = minD;
        }
    }
    return maxD;
}


double BhattacharyyaDistance::calculate(const std::vector<double> &P, const std::vector<double> &Q) {
    double coefficient = 0.0;
    for (size_t i = 0; i < P.size(); ++i) {
        coefficient += std::sqrt(P[i] * Q[i]);
    }
    return -std::log(coefficient);
}


double KullbackLeiblerDivergence::calculate(const std::vector<double> &P, const std::vector<double> &Q) {
    double divergence = 0.0;
    for (size_t i = 0; i < P.size(); ++i) {
        if (P[i] > 0 && Q[i] > 0) {
            divergence += P[i] * std::log(P[i] / Q[i]);
        }
    }
    return divergence;
}
