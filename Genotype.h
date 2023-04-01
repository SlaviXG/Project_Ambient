#ifndef GENOTYPE_H
#define GENOTYPE_H

#include <cassert>

#include "Matrix.h"
#include "point.h"

// inputs 0 - 23 - vision, 24 - current count of energy, 25 -  aggressiveness

namespace genotype {
    bool opponentIsNearby(Matrix inputs);

    constexpr Point
    kM1Size = {16, 26}; // first layer, count of inputs
    constexpr Point
    kM2Size = {16, 16}; // second layer, first layer
    constexpr Point
    kM3Size = {16, 16}; // third layer, second layer
    constexpr Point
    kM4Size = {18, 16}; // output count (count of actions), third layer
    constexpr Point
    kB1Size = {16, 1}; // first baes
    constexpr Point
    kB2Size = {16, 1}; // second baes
    constexpr Point
    kB3Size = {16, 1}; // third baes
    constexpr Point
    kB4Size = {18, 1}; // last baes

    constexpr int kChance = 30;  // 1/30
    constexpr int kMapSize = 100;

    Matrix ReLU(Matrix m);

    void mutation(Matrix &m);

    class Genotype {
    private:
        Matrix m1;
        Matrix m2;
        Matrix m3;
        Matrix m4;

        Matrix b1;
        Matrix b2;
        Matrix b3;
        Matrix b4;

    public:
        void operator =(const Genotype &g)
        {
            m1 = g.m1;
            m2 = g.m2;
            m3 = g.m3;
            m4 = g.m4;

            b1 = g.b1;
            b2 = g.b2;
            b3 = g.b3;
            b4 = g.b4;
        }
        Genotype();

        Genotype(const Genotype &g);

        Genotype(Genotype &parent);

        Matrix getWeightsMatrixByIndex(int index) const;

        Matrix getBaesMatrixByIndex(int index) const;
    };

}

#endif  GENOTYPE_H
