//
// Created by Jeries Khoury on 19/04/2024.
//

#ifndef MEMORYCAPTURE_BYTEFREQUENCYDB_H
#define MEMORYCAPTURE_BYTEFREQUENCYDB_H

#include <array>
#include <cstddef>  // for std::size_t
#include <queue>
#include <functional>
#include <sstream>

class ByteFrequencyDB {
private:
    std::array<std::size_t, 256> frequencies;
    std::priority_queue<size_t, std::vector<size_t>, std::less<>> maxHeap;
    std::vector<size_t> orderedFrequencies;

public:
    ByteFrequencyDB() : frequencies{} {}

    void update(const std::vector<char>& data);

    // Overloaded update method to handle a specific range
    void update(const std::vector<char>& data, size_t startIndex, size_t memoryUnitSize);

    std::vector<size_t>& getTopOrderedFrequencies();

    [[nodiscard]] const std::array<std::size_t, 256>& getFrequencies() const {
        return frequencies;
    }

    static int hexCharToInt(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        std::stringstream ss;
        ss << "Invalid hexadecimal character: " << c;
        throw std::invalid_argument(ss.str());
    }

    // Convert two hex chars to one byte
    static unsigned char hexCharsToByte(char high, char low) {
        return hexCharToInt(high) * 16 + hexCharToInt(low);
    }

    void reset() {
        frequencies.fill(0);
    }
};


#endif //MEMORYCAPTURE_BYTEFREQUENCYDB_H
