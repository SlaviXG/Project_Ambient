#include "Genotype.h"
#include <random>

/*  INPUTS
 0 - 23 - frames:
00 01 02 03 04
05 06 07 08 09
10 11 😀 12 13
14 15 16 17 18
19 20 21 22 23

 24 - countOfEnergy
 25 - aggressiveness
 */

/*  OUTPUTS
0) Move U
1) Move UR
2) Move R
3) Move RD
4) Move D
5) Move LD
6) Move L
7) Move LU
8) photosynthesis
9) sleep                            // skip
9) attack
10) duplication
 */
namespace genotype {
    bool opponentIsNearby(Matrix inputs) {
        if (inputs[6][0] != 1 && inputs[7][0] != 1 && inputs[8][0] != 1 && inputs[11][0] != 1 &&
            inputs[12][0] != 1 && inputs[15][0] != 1 && inputs[16][0] != 1 && inputs[17][0] != 1) {
            return false;
        }
        return true;
    }

    Matrix mutation(Matrix m) {
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_real_distribution<double> distr(-1, 1);

        for (int i = 0; i < m.getY(); i++) {
            for (int j = 0; j < m.getY(); j++) {
                if (rand() % kChance == 0) {
                    m[i][j] = distr(eng);
                }
            }
        }

        return m;
    }

    Matrix ReLU(Matrix m) {
        for (int i = 0; i < m.getY(); i++) {
            for (int j = 0; j < m.getX(); j++) {
                if (m[i][j] <= 0)
                    m[i][j] = 0;
            }
        }

        return m;
    }

    Genotype::Genotype() {
        m1 = Matrix(kM1Size.j, kM1Size.i);
        m2 = Matrix(kM2Size.j, kM2Size.i);
        m3 = Matrix(kM3Size.j, kM3Size.i);
        m4 = Matrix(kM4Size.j, kM4Size.i);

        b1 = Matrix(kB1Size.j, kB1Size.i);
        b2 = Matrix(kB1Size.j, kB1Size.i);
        b3 = Matrix(kB1Size.j, kB1Size.i);
        b4 = Matrix(kB1Size.j, kB1Size.i);

        b1.setRandomValues();
        b2.setRandomValues();
        b3.setRandomValues();
        b4.setRandomValues();

        m1.setRandomValues();
        m2.setRandomValues();
        m3.setRandomValues();
        m4.setRandomValues();
    }

    Genotype::Genotype(Genotype &parent) {
        m1 = mutation(parent.getWeightsMatrixByIndex(1));
        m2 = mutation(parent.getWeightsMatrixByIndex(2));
        m3 = mutation(parent.getWeightsMatrixByIndex(3));
        m4 = mutation(parent.getWeightsMatrixByIndex(4));

        b1 = mutation(parent.getBaesMatrixByIndex(1));
        b2 = mutation(parent.getBaesMatrixByIndex(2));
        b3 = mutation(parent.getBaesMatrixByIndex(3));
        b4 = mutation(parent.getBaesMatrixByIndex(4));
    }

    Matrix Genotype::getWeightsMatrixByIndex(int index) {
        switch (index) {
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

    Matrix Genotype::getBaesMatrixByIndex(int index) {
        switch (index) {
            case 1:
                return b1;
            case 2:
                return b2;
            case 3:
                return b3;
            case 4:
                return b4;
            default:
                return Matrix();
        }
    }
}