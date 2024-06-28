//
// Created by Jeries Khoury on 08/04/2024.
//

#ifndef MEMORYCAPTURE_DISTANCEFUNCTION_H
#define MEMORYCAPTURE_DISTANCEFUNCTION_H

#include<vector>
#include <algorithm> // For std::min and std::max
#include <cmath> // For std::abs
#include <stdexcept>
#include <string>
#include "ByteFrequencyDB.h"
#include "ConversionToProbabilityDistribution.h"
#include "ProbDistFuncs.h"

using std::vector;

class distanceFunction {
public:
    // Virtual destructor to ensure derived class destructors are called
    virtual ~distanceFunction() = default;


    // Calculate distance between two points
    [[nodiscard]] virtual double calculateDistanceBetweenPoints(vector<double> x, vector<double> y) const = 0;

    [[nodiscard]] virtual double calculateDistanceBetweenPointsC(vector<char> x, vector<char> y) const = 0;


    // Calculate distance between two vectors
    [[nodiscard]] virtual double calculateSumDistanceBetweenVectors(const std::vector<vector<double>>& vec1,
                                                                 const std::vector<vector<double>>& vec2) const = 0;

    [[nodiscard]] virtual double calculateSumDistanceBetweenVectors(const std::vector<vector<char>>& vec1,
                                                                    const std::vector<vector<char>>& vec2) const = 0;


    // Return a vector of distances
    virtual std::vector<double> vectorOfDistances(const std::vector<vector<double>>& vec1,
                                                  const std::vector<vector<double>>& vec2) const = 0;

    virtual std::vector<double> vectorOfDistances(const std::vector<vector<char>>& vec1,
                                                  const std::vector<vector<char>>& vec2) const = 0;

    virtual double calculateMUDistanceBetweenPointsC(const vector<char>& baseImage, const vector<char>& newImage
                                                     , unsigned int memoryUnit, unsigned int base_index
                                                     , unsigned int new_index) = 0;
};



class EuclideanDistance : public distanceFunction {
public:
    [[nodiscard]] double calculateDistanceBetweenPoints(vector<double> x, vector<double> y) const override;

    [[nodiscard]] double calculateSumDistanceBetweenVectors(const std::vector<vector<double>>& vec1,
                                                   const std::vector<vector<double>>& vec2) const override;

    [[nodiscard]] std::vector<double> vectorOfDistances(const std::vector<vector<double>>& vec1,
                                                        const std::vector<vector<double>>& vec2) const override;

};


class GrayDistance : public distanceFunction {
public:
    [[nodiscard]] double calculateDistanceBetweenPointsC(vector<char> x, vector<char> y) const override;

    [[nodiscard]] double calculateSumDistanceBetweenVectors(const std::vector<vector<char>>& vec1,
                                                                    const std::vector<vector<char>>& vec2)
                                                                    const override;

    [[nodiscard]] std::vector<double> vectorOfDistances(const std::vector<vector<char>>& vec1,
                                                  const std::vector<vector<char>>& vec2) const override;

    [[nodiscard]] double calculateDistanceBetweenPoints(vector<double> x, vector<double> y) const override{ return 0.0;}

    [[nodiscard]] double calculateSumDistanceBetweenVectors(const std::vector<vector<double>>& vec1,
                                                            const std::vector<vector<double>>& vec2) const override
                                                            {return 0.0;}

    [[nodiscard]] std::vector<double> vectorOfDistances(const std::vector<vector<double>>& vec1,
                                                        const std::vector<vector<double>>& vec2) const override
                                                        {return vector<double>(0.0);}

     double calculateMUDistanceBetweenPointsC(const vector<char>& baseImage, const vector<char>& newImage
            , unsigned int memoryUnit, unsigned int base_index
            , unsigned int new_index) override;
};

class cosineDistance : public distanceFunction{
public:
    [[nodiscard]] double calculateDistanceBetweenPointsC(vector<char> v1, vector<char> v2) const override;

    [[nodiscard]] double calculateSumDistanceBetweenVectors(const std::vector<vector<char>>& vec1,
                                                            const std::vector<vector<char>>& vec2)
    const override { return 0.0; }

    [[nodiscard]] std::vector<double> vectorOfDistances(const std::vector<vector<char>>& vec1,
                                                        const std::vector<vector<char>>& vec2) const override{
        return vector<double>(0.0);
    }

    [[nodiscard]] double calculateDistanceBetweenPoints(vector<double> x, vector<double> y) const override{
        return 0.0;
    }

    [[nodiscard]] double calculateSumDistanceBetweenVectors(const std::vector<vector<double>>& vec1,
                                                            const std::vector<vector<double>>& vec2) const override
    {return 0.0;}

    [[nodiscard]] std::vector<double> vectorOfDistances(const std::vector<vector<double>>& vec1,
                                                        const std::vector<vector<double>>& vec2) const override
    {return vector<double>(0.0);}

    double calculateMUDistanceBetweenPointsC(const vector<char>& baseImage, const vector<char>& newImage
            , unsigned int memoryUnit, unsigned int base_index
            , unsigned int new_index) override;

};


class hausdorffDistance : public distanceFunction{
private:
    int byteCount;
public:
    explicit hausdorffDistance(int count): distanceFunction(), byteCount(count){}

    [[nodiscard]] double calculateDistanceBetweenPointsC(vector<char> v1, vector<char> v2) const override;

    [[nodiscard]] double calculateSumDistanceBetweenVectors(const std::vector<vector<char>>& vec1,
                                                            const std::vector<vector<char>>& vec2)
    const override { return 0.0; }

    [[nodiscard]] std::vector<double> vectorOfDistances(const std::vector<vector<char>>& vec1,
                                                        const std::vector<vector<char>>& vec2) const override{
        return vector<double>(0.0);
    }

    [[nodiscard]] double calculateDistanceBetweenPoints(vector<double> x, vector<double> y) const override{
        return 0.0;
    }

    [[nodiscard]] double calculateSumDistanceBetweenVectors(const std::vector<vector<double>>& vec1,
                                                            const std::vector<vector<double>>& vec2) const override
    {return 0.0;}

    [[nodiscard]] std::vector<double> vectorOfDistances(const std::vector<vector<double>>& vec1,
                                                        const std::vector<vector<double>>& vec2) const override
    {return vector<double>(0.0);}

    double calculateMUDistanceBetweenPointsC(const vector<char>& baseImage, const vector<char>& newImage
            , unsigned int memoryUnit, unsigned int base_index
            , unsigned int new_index) override;
};


class bhattacharyyaDistance : public distanceFunction{
private:
    int byteCount;
public:
    explicit bhattacharyyaDistance(int count): distanceFunction(), byteCount(count){}

    [[nodiscard]] double calculateDistanceBetweenPointsC(vector<char> v1, vector<char> v2) const override;

    [[nodiscard]] double calculateSumDistanceBetweenVectors(const std::vector<vector<char>>& vec1,
                                                            const std::vector<vector<char>>& vec2)
    const override { return 0.0; }

    [[nodiscard]] std::vector<double> vectorOfDistances(const std::vector<vector<char>>& vec1,
                                                        const std::vector<vector<char>>& vec2) const override{
        return vector<double>(0.0);
    }

    [[nodiscard]] double calculateDistanceBetweenPoints(vector<double> x, vector<double> y) const override{
        return 0.0;
    }

    [[nodiscard]] double calculateSumDistanceBetweenVectors(const std::vector<vector<double>>& vec1,
                                                            const std::vector<vector<double>>& vec2) const override
    {return 0.0;}

    [[nodiscard]] std::vector<double> vectorOfDistances(const std::vector<vector<double>>& vec1,
                                                        const std::vector<vector<double>>& vec2) const override
    {return vector<double>(0.0);}

    double calculateMUDistanceBetweenPointsC(const vector<char>& baseImage, const vector<char>& newImage
            , unsigned int memoryUnit, unsigned int base_index
            , unsigned int new_index) override;
};


class kullbackLeibler : public distanceFunction{
private:
    int byteCount;
public:
    explicit kullbackLeibler(int count): distanceFunction(), byteCount(count){}

    [[nodiscard]] double calculateDistanceBetweenPointsC(vector<char> v1, vector<char> v2) const override;

    [[nodiscard]] double calculateSumDistanceBetweenVectors(const std::vector<vector<char>>& vec1,
                                                            const std::vector<vector<char>>& vec2)
    const override { return 0.0; }

    [[nodiscard]] std::vector<double> vectorOfDistances(const std::vector<vector<char>>& vec1,
                                                        const std::vector<vector<char>>& vec2) const override{
        return vector<double>(0.0);
    }

    [[nodiscard]] double calculateDistanceBetweenPoints(vector<double> x, vector<double> y) const override{
        return 0.0;
    }

    [[nodiscard]] double calculateSumDistanceBetweenVectors(const std::vector<vector<double>>& vec1,
                                                            const std::vector<vector<double>>& vec2) const override
    {return 0.0;}

    [[nodiscard]] std::vector<double> vectorOfDistances(const std::vector<vector<double>>& vec1,
                                                        const std::vector<vector<double>>& vec2) const override
    {return vector<double>(0.0);}

    double calculateMUDistanceBetweenPointsC(const vector<char>& baseImage, const vector<char>& newImage
            , unsigned int memoryUnit, unsigned int base_index
            , unsigned int new_index) override;
};




#endif //MEMORYCAPTURE_DISTANCEFUNCTION_H
