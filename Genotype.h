#ifndef GENOTYPE_H
#define GENOTYPE_H

#include <cassert>

#include "Matrix.h"
#include "point.h"

// inputs 0 - 23 - vision, 24 - current count of energy, 25 -  aggressiveness

namespace genotype {
    bool opponentIsNearby(Matrix inputs);
    constexpr int countOfInputs = 26;
    constexpr int countOfOutputs = 18;

    //constexpr Point
    //kM1Size = {16, 26}; // first layer, count of inputs
    //constexpr Point
    //kM2Size = {16, 16}; // second layer, first layer
    //constexpr Point
    //kM3Size = {16, 16}; // third layer, second layer
    //constexpr Point
    //kM4Size = {18, 16}; // output count (count of actions), third layer
    //constexpr Point
    //kB1Size = {16, 1}; // first baes
    //constexpr Point
    //kB2Size = {16, 1}; // second baes
    //constexpr Point
    //kB3Size = {16, 1}; // third baes
    //constexpr Point
    //kB4Size = {18, 1}; // last baes

    constexpr int kChance = 30;  // 1/30
    constexpr int kMapSize = 100;

    Matrix ReLU(Matrix m);

    Matrix mutation(Matrix m, double chance = (double)kChance/100.0);


    class Genotype {
    private:


        std::vector<Matrix> weights;
        std::vector<Matrix> baeses;
        int countOfLayers;

        //Matrix m1;
        //Matrix m2;
        //Matrix m3;
        //Matrix m4;

       // Matrix b1;
        //Matrix b2;
        //Matrix b3;
        //Matrix b4;

    public:
        int getCountOfLayers()
        {
            return this->countOfLayers;
        }

        void operator =(const Genotype &g)
        {
            this->weights = g.weights;
            this->baeses = g.baeses;
            this->countOfLayers = g.countOfLayers;

            //m1 = g.m1;
           // m2 = g.m2;
            //m3 = g.m3;
            //m4 = g.m4;

           // b1 = g.b1;
           // b2 = g.b2;
            //b3 = g.b3;
            //b4 = g.b4;
        }
        Genotype();


        Genotype(std::vector<int> countOfWeights);

        Genotype(const Genotype &g);

        //Genotype(Genotype &parent);

        Matrix getWeightsMatrixByIndex(int index) const;

        Matrix getBaesMatrixByIndex(int index) const;

        void mutate(double chance = (double)kChance/100.0);
    };

}

#endif  GENOTYPE_H
