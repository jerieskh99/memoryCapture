//
// Created by Jeries Khoury on 16/05/2024.
//

#ifndef MEMORYCAPTURE_COMPLEXDISTANCE_H
#define MEMORYCAPTURE_COMPLEXDISTANCE_H

#include <cmath>
#include <vector>
#include <tuple>
#include <complex>


class complexDistance {
    float magnitude;
    float orientation;

    float real;
    float image;


public:
    complexDistance(float mag, float orient);
    explicit complexDistance(std::complex<float> c_num);

    [[nodiscard]] float getMag() const { return magnitude; }
    [[nodiscard]] float getOrient() const { return orientation; }
    [[nodiscard]] float getReal() const { return real; }
    [[nodiscard]] float getImg() const { return image; }

    [[nodiscard]] std::complex<float> getStdComplex() const { return {real, image}; }

    // Friend functions overloads
    friend complexDistance sumComplexDist(const complexDistance& d1, const complexDistance& d2);
    friend complexDistance subtractComplexDist(const complexDistance& d1, const complexDistance& d2);
    friend complexDistance multiplyComplexDist(const complexDistance& d1, const complexDistance& d2);
    friend complexDistance divComplexDist(const complexDistance& d1, const complexDistance& d2);

    // Friend operator overloads
    friend complexDistance operator+(const complexDistance& d1, const complexDistance& d2);
    friend complexDistance operator-(const complexDistance& d1, const complexDistance& d2);
    friend complexDistance operator*(const complexDistance& d1, const complexDistance& d2);
    friend complexDistance operator/(const complexDistance& d1, const complexDistance& d2);


};


complexDistance operator+(const complexDistance& d1, const complexDistance& d2);

complexDistance operator-(const complexDistance& d1, const complexDistance& d2);

complexDistance operator*(const complexDistance& d1, const complexDistance& d2);

complexDistance operator/(const complexDistance& d1, const complexDistance& d2);


complexDistance sumComplexDist(const complexDistance& d1, const complexDistance& d2); // d1+d2

complexDistance subtractComplexDist(const complexDistance& d1, const complexDistance& d2); // d1-d2

complexDistance multiplyComplexDist(const complexDistance& d1, const complexDistance& d2); // d1*d2

complexDistance divComplexDist(const complexDistance& d1, const complexDistance& d2); // d1/d2

#endif //MEMORYCAPTURE_COMPLEXDISTANCE_H
