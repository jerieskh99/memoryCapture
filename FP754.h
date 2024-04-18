//
// Created by Jeries Khoury on 08/04/2024.
//

#ifndef MEMORYCAPTURE_FP754_H
#define MEMORYCAPTURE_FP754_H

#include <iostream>
#include <bitset>
#include <cstdint>

class FP754 {
private:
    float value;

public:
    // Default constructor
    FP754();

    // Constructor from float
    explicit FP754(float val);

    // Get the float value
    [[nodiscard]] float getValue() const;

    // Set the float value
    void setValue(float val);

    // Print the IEEE 754 representation of the number
    void printIEEE754Representation() const;

    // Add another FP754 number to this one
    void add(const FP754& other);

    // Subtract another FP754 number from this one
    void subtract(const FP754& other);

    // Additional operations (e.g., multiplication, division) can be added here

    // ... other methods as needed
};



#endif //MEMORYCAPTURE_FP754_H
