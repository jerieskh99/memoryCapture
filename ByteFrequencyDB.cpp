//
// Created by Jeries Khoury on 19/04/2024.
//

#include "ByteFrequencyDB.h"

void ByteFrequencyDB::update(const std::vector<char>& data) {
    if (data.size() % 2 != 0) throw std::invalid_argument("Hex data length must be even.");

    for (size_t i = 0; i < data.size(); i += 2) {
        unsigned char byte = hexCharsToByte(data[i], data[i+1]);
        frequencies[byte]++;
    }

    if (maxHeap.empty()){
        for (auto item : frequencies){
            maxHeap.push(item);
        }
    }
}

std::vector<size_t>& ByteFrequencyDB::getTopOrderedFrequencies() {
    while (!maxHeap.empty())
    {
        orderedFrequencies.push_back(maxHeap.top());
        maxHeap.pop();
    }

    return orderedFrequencies;
}

void ByteFrequencyDB::update(const std::vector<char>& data, size_t startIndex, size_t memoryUnitSize) {

    for (size_t i = startIndex; i < startIndex + memoryUnitSize; ++i) {
        unsigned char byte = hexCharsToByte(data[i], data[i+1]);
        frequencies[byte]++;
    }

    if (maxHeap.empty()){
        for (auto item : frequencies){
            maxHeap.push(item);
        }
    }
}

