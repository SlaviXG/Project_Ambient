#ifndef GENOTYPE_H
#define GENOTYPE_H


#include "Matrix.h"

// inputs 0 - 23 - vision, 24 - current count of energy,
struct Point {int i = 0, j = 0; };

constexpr Point kM1Size = {16,26}; // first layer, count of inputs
constexpr Point kM2Size = {16,16}; // second layer, first layer
constexpr Point kM3Size = {16,16}; // third layer, second layer
constexpr Point kM4Size = {12,16}; // output count (count of actions), third layer
constexpr Point kB1Size = {16,1}; // first baes
constexpr Point kB2Size = {16,1}; // second baes
constexpr Point kB3Size = {16,1}; // third baes
constexpr Point kB4Size = {12,1}; // last baes

constexpr int kChance = 30;  // 1/30
constexpr int kMapSize = 100;

Matrix ReLU(Matrix m);

void mutation(Matrix& m);

class Genotype 
{
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
    Genotype();
    Genotype(Genotype& parent);

    Matrix getWeightsMatrixByIndex(int index);
    Matrix getBaesMatrixByIndex(int index);

    int makeChoise(Matrix inputs, Point cellPosition);
};


#endif  GENOTYPE_H