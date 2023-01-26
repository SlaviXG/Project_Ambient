#include "Genotype.h"
#include <random>

void mutation(Matrix& m)
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_real_distribution<double> distr(-1, 1);

    for(int i = 0; i < m.getY(); i++)
    {
        for(int j = 0; j < m.getY(); j++)
        {
            if(rand() % kChance == 0)
            {
                m[i][j] = distr(eng);
            }
        }
    }
}

Matrix ReLU(Matrix m)
{
    for(int i = 0; i < m.getY(); i++)
    {
        for(int j = 0; j < m.getX(); j++)
        {
            if(m[i][j] <= 0)
                m[i][j] = 0;
        }
    }

    return m;
}

Genotype::Genotype()
{
    m1 = Matrix(kM1Size.j,kM1Size.i);
    m2 = Matrix(kM2Size.j,kM2Size.i);
    m3 = Matrix(kM3Size.j,kM3Size.i);
    m4 = Matrix(kM4Size.j,kM4Size.i);

    m1.setRandomValues();
    m2.setRandomValues();
    m3.setRandomValues();
    m4.setRandomValues();
}

Genotype::Genotype(Genotype& parent)
{
    m1 = parent.getMatrixByIndex(1);
    m2 = parent.getMatrixByIndex(2);
    m3 = parent.getMatrixByIndex(3);
    m4 = parent.getMatrixByIndex(4);
}

Matrix Genotype::getMatrixByIndex(int index)
{
   switch (index)
   {
   case 1:
    return m1;
   case 2:
    return m2;
   case 3:
    return m3;
   case 4:
    return m4;
   default:
    return Matrix();
   }
}

int Genotype::makeChoise(Matrix inputs, Point cellPosition)
{
    Matrix firstLayer = ReLU(m1*inputs);
    Matrix secondLayer = ReLU(m2*firstLayer);
    Matrix thirdLayer = ReLU(m3*secondLayer);
    Matrix output = ReLU(m4*thirdLayer);


}