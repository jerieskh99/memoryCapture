//
// Created by Jeries Khoury on 16/05/2024.
//

#include "complexDistance.h"

complexDistance::complexDistance(float mag, float orient):magnitude(mag), orientation(orient) {
    real = magnitude * std::cos(orient);
    image = magnitude * std::sin(orient);
}

complexDistance::complexDistance(std::complex<float> c_num) {
    this -> real = c_num.real();
    this -> image = c_num.imag();
    this -> magnitude = std::sqrtf(real*real + image*image);
    this -> orientation = std::atan(image/real);
}

complexDistance sumComplexDist(const complexDistance& d1, const complexDistance& d2){
    float re = d1.getReal() + d2.getReal();
    float im = d1.getImg()  + d2.getImg();
    std::complex<float> c(re, im);
    return complexDistance(c);
}

complexDistance subtractComplexDist(const complexDistance& d1, const complexDistance& d2){
    float re = d1.getReal() - d2.getReal();
    float im = d1.getImg()  - d2.getImg();
    std::complex<float> c(re, im);
    return complexDistance(c);
}

complexDistance multiplyComplexDist(const complexDistance& d1, const complexDistance& d2){
    return {d1.getMag()*d2.getMag(), d1.getOrient()+d2.getOrient()};
}

complexDistance divComplexDist(const complexDistance& d1, const complexDistance& d2){
    return {d1.getMag()/d2.getMag(), d1.getOrient()-d2.getOrient()};
}

complexDistance operator+(const complexDistance& d1, const complexDistance& d2){
    return sumComplexDist(d1, d2);
}

complexDistance operator-(const complexDistance& d1, const complexDistance& d2){
    return subtractComplexDist(d1, d2);
}

complexDistance operator*(const complexDistance& d1, const complexDistance& d2){
    return multiplyComplexDist(d1, d2);
}

complexDistance operator/(const complexDistance& d1, const complexDistance& d2){
    return divComplexDist(d1, d2);
}

