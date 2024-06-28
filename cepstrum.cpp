//
// Created by Jeries Khoury on 16/05/2024.
//

#include "cepstrum.h"

std::vector<std::complex<float>> cepstrum::fft(const vector<std::complex<float>> &input) {
    std::vector<std::complex<float>> data = input;
    fftHelper(data, false);
    return data;
}

std::vector<std::complex<float>> cepstrum::ifft(const vector<std::complex<float>> &input) {
    std::vector<std::complex<float>> data = input;
    fftHelper(data, true);
    float invN = 1.0f / (float)data.size();
    for (auto& c : data) {
        c *= invN;
    }
    return data;
}

vector<std::complex<float>> cepstrum::computeCepstrum(const vector<std::complex<float>> &input) {
    // Step 1: Perform FFT on the input
    std::vector<std::complex<float>> fftResult = fft(input);

    // Step 2: Take the logarithm of the magnitude of the FFT result
    std::vector<std::complex<float>> logMag(fftResult.size());
    for (size_t i = 0; i < fftResult.size(); ++i) {
        logMag[i] = std::log(std::abs(fftResult[i]));
    }

    // Step 3: Perform IFFT on the logarithm result
    std::vector<std::complex<float>> cepstrumResult = ifft(logMag);

    return cepstrumResult;
}

void cepstrum::fftHelper(vector<std::complex<float>> &data, bool inverse) {
    const size_t N = data.size();
    if (N <= 1) return;

    std::vector<std::complex<float>> even(N / 2);
    std::vector<std::complex<float>> odd(N / 2);
    for (size_t i = 0; i < N / 2; ++i) {
        even[i] = data[i * 2];
        odd[i] = data[i * 2 + 1];
    }

    fftHelper(even, inverse);
    fftHelper(odd, inverse);

    float angle = 2 * M_PI / N * (inverse ? 1 : -1);
    std::complex<float> w(1);
    std::complex<float> wn(std::cos(angle), std::sin(angle));

    for (size_t i = 0; i < N / 2; ++i) {
        data[i] = even[i] + w * odd[i];
        data[i + N / 2] = even[i] - w * odd[i];
        if (inverse) {
            data[i] /= 2;
            data[i + N / 2] /= 2;
        }
        w *= wn;
    }
}







