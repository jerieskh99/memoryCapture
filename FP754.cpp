//
// Created by Jeries Khoury on 08/04/2024.
//

#include "FP754.h"

FP754::FP754() : value(0.0f) {}

FP754::FP754(float val) : value(val) {}

[[nodiscard]] float FP754::getValue() const {
    return value;
}

void FP754::setValue(float val) {
    value = val;
}

void FP754::printIEEE754Representation() const {
    // Use a union to access the bits of the float as an integer
    union {
        float f;
        uint32_t i;
    } converter{};

    converter.f = value;

    std::cout << "IEEE 754 representation of " << value << ": ";
    std::cout << std::bitset<32>(converter.i) << std::endl;
}

void FP754::add(const FP754& other) {
    value += other.getValue();
}

void FP754::subtract(const FP754& other) {
    value -= other.getValue();
}











