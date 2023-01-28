#include "Genotype.h"
#include <random>

bool oponentIsNearby(Matrix inputs)
{
    if(inputs[6][0] != 1 && inputs[7][0] != 1 && inputs[8][0] != 1 && inputs[11][0] != 1 &&  // Check neighboring frames
       inputs[12][0] != 1 && inputs[15][0] != 1 && inputs[16][0] != 1 && inputs[17][0] != 1)
    {
        return false;
    }
    return true;      
}

int bestPosibleChoiseIndex(Matrix outputs, Matrix inputs, Point CellPosition)       // !!!!!!!!!!
{
    int maxValue = outputs[0][0];
    int index = 0;

    for(int i = 1; i < outputs.getY(); i++)
    {
        if(maxValue < outputs[i][0])
        {
            index = i;
            maxValue = outputs[i][0];
        }
    }

     // Cell Vision:
    /*
    00 01 02 03 04
    05 06 07 08 09
    10 11 😀 12 13
    14 15 16 17 18
    21 22 23 24 25
    */
   
   /*
 vector of actions:
0) Movement up
1) Move to the upper right corner
2) Movement to the right
3) Movement in the north corner
4) Movement down
5) movement in the left corner
6) movement to the left
7) movement in the LW corner
8) photosynthesis
9) sleep
10) attack

11) duplication
    */  
    switch (index)
    {
    case 0:
        if(CellPosition.i == 0)
        {
            outputs[index][0] = 0;
            return bestPosibleChoiseIndex(outputs,inputs, CellPosition);
        }
        
        if(inputs[7][0] == 1 )
        {
            outputs[index][0] = 0;
            return bestPosibleChoiseIndex(outputs,inputs, CellPosition);    
        }
    
        return index;

    case 1:
        if(CellPosition.i == 0 || CellPosition.j == 99)             // mapSIze == 100
        {
            outputs[index][0] = 0;
            return bestPosibleChoiseIndex(outputs,inputs, CellPosition);
        }
        
        if(inputs[8][0] == 1 )
        {
            outputs[index][0] = 0;
            return bestPosibleChoiseIndex(outputs,inputs, CellPosition);    
        }
    
        return index;
    case 2:

        if(CellPosition.j == 99)
        {
            outputs[index][0] = 0;
            return bestPosibleChoiseIndex(outputs,inputs, CellPosition);
        }
        
        if(inputs[12][0] == 1 )
        {
            outputs[index][0] = 0;
            return bestPosibleChoiseIndex(outputs,inputs, CellPosition);    
        }
    case 3:

        if(CellPosition.i == 99 || CellPosition.j == 99)
        {
            outputs[index][0] = 0;
            return bestPosibleChoiseIndex(outputs,inputs, CellPosition);
        }
        
        if(inputs[17][0] == 1 )
        {
            outputs[index][0] = 0;
            return bestPosibleChoiseIndex(outputs,inputs, CellPosition);    
        }
    
        return index;
    case 4:

        if(CellPosition.i == 99)
        {
            outputs[index][0] = 0;
            return bestPosibleChoiseIndex(outputs,inputs, CellPosition);
        }
        
        if(inputs[16][0] == 1 )
        {
            outputs[index][0] = 0;
            return bestPosibleChoiseIndex(outputs,inputs, CellPosition);    
        }
    
        return index;
    case 5:

        if(CellPosition.i == 99, CellPosition.j == 0)
        {
            outputs[index][0] = 0;
            return bestPosibleChoiseIndex(outputs,inputs, CellPosition);
        }
        
        if(inputs[15][0] == 1 )
        {
            outputs[index][0] = 0;
            return bestPosibleChoiseIndex(outputs,inputs, CellPosition);    
        }
    
        return index;
    case 6:

        if(CellPosition.j == 0)
        {
            outputs[index][0] = 0;
            return bestPosibleChoiseIndex(outputs,inputs, CellPosition);
        }
        
        if(inputs[11][0] == 1 )
        {
            outputs[index][0] = 0;
            return bestPosibleChoiseIndex(outputs,inputs, CellPosition);    
        }
    
        return index;
    case 7:

        if(CellPosition.i == 0 || CellPosition.j == 0)
        {
            outputs[index][0] = 0;
            return bestPosibleChoiseIndex(outputs,inputs, CellPosition);
        }
        
        if(inputs[6][0] == 1 )
        {
            outputs[index][0] = 0;
            return bestPosibleChoiseIndex(outputs,inputs, CellPosition);    
        }
    
        return index;
    case 10:
        if(oponentIsNearby(inputs))
            return index;
        else
            outputs[index][0] = 0;
            return bestPosibleChoiseIndex(outputs,inputs, CellPosition);
    default:
        return index;
    }
}

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

    return bestPosibleChoiseIndex(output, inputs, cellPosition);
}