//
// Created by Jeries Khoury on 19/04/2024.
//

#ifndef MEMORYCAPTURE_CONVERSIONTOPROBABILITYDISTRIBUTION_H
#define MEMORYCAPTURE_CONVERSIONTOPROBABILITYDISTRIBUTION_H

#include "ByteFrequencyDB.h"
#include <vector>


class ConversionToProbabilityDistribution {
public:
    static std::vector<double> convert(const ByteFrequencyDB& db, int totalByteCount) {
        const auto& frequencies = db.getFrequencies();
        std::vector<double> probabilities(256, 0.0);

        // Convert frequencies to probabilities
        if (totalByteCount > 0) {
            for (int i = 0; i < 256; ++i) {
                probabilities[i] = static_cast<double>(frequencies[i]) / (totalByteCount);
            }
        }

        return probabilities;
    }
};


#endif //MEMORYCAPTURE_CONVERSIONTOPROBABILITYDISTRIBUTION_H
