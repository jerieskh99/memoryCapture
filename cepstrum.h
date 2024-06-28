//
// Created by Jeries Khoury on 16/05/2024.
//

#ifndef MEMORYCAPTURE_CEPSTRUM_H
#define MEMORYCAPTURE_CEPSTRUM_H

#include "complexDistance.h"
#include <vector>
#include <complex>

using std::vector;

class cepstrum {
private:
    static void fftHelper(std::vector<std::complex<float>>& data, bool inverse);
public:
    static std::vector<std::complex<float>> fft(const vector<std::complex<float>>& input);
    static std::vector<std::complex<float>> ifft(const vector<std::complex<float>>& input);
    static vector<std::complex<float>> computeCepstrum(const std::vector<std::complex<float>>& signal);
};


#endif //MEMORYCAPTURE_CEPSTRUM_H
