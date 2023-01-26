#ifndef GENOTYPE_H
#define GENOTYPE_H

#include "Matrix.h"

struct Point {int i = 0, j = 0; };

constexpr Point kM1Size = {16,26}; // first layer, count of inputs + baes 
constexpr Point kM2Size = {16,17}; // second layer, first layer + baes 
constexpr Point kM3Size = {16,17}; // third layer, second layer + baes
constexpr Point kM4Size = {12,17}; // output count (count of actions), third layer + baes
constexpr int kChance = 30;  // 1/30

Matrix ReLU(Matrix m);

void mutation(Matrix& m);

class Genotype 
{
    private:
    Matrix m1;
    Matrix m2;
    Matrix m3;
    Matrix m4;

    public:
    Genotype();
    Genotype(Genotype& parent);

    Matrix getMatrixByIndex(int index);

    int makeChoise(Matrix inputs, Point cellPosition);
};


#endif  GENOTYPE_H