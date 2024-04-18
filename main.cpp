#include <iostream>
#include "FP754.h"
#include <string> // For std::stof
#include "deltaManager.h"
#include "distanceFunction.h"
#include <fstream>
#include <vector>
#include <iomanip> // For std::setw and std::setfill
#include <sstream> // For std::stringstream


int test_754(float num, float othernum) {
    FP754 number(5.5f);
    FP754 otherNumber(2.5f);

    number.printIEEE754Representation(); // Print the IEEE 754 representation

    // Example usage of add and subtract
    number.add(otherNumber); // Add otherNumber to number
    number.printIEEE754Representation(); // Print the new IEEE 754 representation

    number.subtract(FP754(1.5f)); // Subtract 1.5 from number
    number.printIEEE754Representation(); // Print the new IEEE 754 representation

    return 0;
}


std::vector<char> fileToHexVector(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    std::vector<char> hexData;
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return hexData;
    }

    // Read bytes from the file and convert to hex
    char byte;
    while (file.read(&byte, 1)) {
        std::stringstream ss;
        ss << std::hex << std::setw(2) << std::setfill('0') << (0xFF & static_cast<unsigned char>(byte));
        // Insert each hex digit as a separate char
        std::string hex = ss.str();
        for (auto& ch : hex) {
            hexData.push_back(ch);
        }
    }
    return hexData;
}



int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " image1 image2" << std::endl;
        return 1; // Return an error code if not enough arguments are provided
    }

    auto* df = new GrayDistance();
    deltaManager dm(df, 4096, 12);

    std::vector<char> file1Hex = fileToHexVector("/Users/jeries/CLionProjects/memoryCapture/mempartial_20240417151929.hex");
    std::vector<char> file2Hex = fileToHexVector("/Users/jeries/CLionProjects/memoryCapture/mempartial_20240417151958.hex");

    if (file1Hex.empty() || file2Hex.empty()) {
        delete df; // Clean up GrayDistance object
        return 2; // Return an error code if files could not be read
    }

    dm.calculateDelta(file1Hex, file2Hex);

    vector<double> res = dm.getDeltaBlocks();

    // Write the results to a file
    std::ofstream outFile("/Users/jeries/CLionProjects/memoryCapture/output.csv");
    if (!outFile) {
        std::cerr << "Failed to open the output file." << std::endl;
        delete df;
        return 3; // Return an error code if file could not be opened
    }

    outFile << "index,value\n";
    for (size_t i = 0; i < res.size(); ++i) {
        outFile << i << "," << res[i] << "\n";
    }

    outFile.close();
    //delete dm; // Clean up GrayDistance object
    return 0;
    
}
