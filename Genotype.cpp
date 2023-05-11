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
10) attack
11) duplication
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
            for (int j = 0; j < m.getX(); j++) {
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

    Genotype::Genotype()
    {
        this->weights = std::vector<Matrix>(0);
        this->baeses = std::vector<Matrix>(0);
        this->countOfLayers = 0;
    }


    Genotype::Genotype(std::vector<int> countOfWeights)
    {
        this->countOfLayers = 1;
        std::vector<int> temp;

        temp.push_back(countOfInputs);
        for(int i = 0; i < countOfWeights.size(); i++)
        {
            if(countOfWeights[i] > 0)
            {
                temp.push_back(countOfWeights[i]);
                this->countOfLayers++;
            }
        }
        temp.push_back(countOfOutputs);

        std::vector<Matrix> weight;
        std::vector<Matrix> baes;

        for(int i = 0; i < this->countOfLayers; i++)
        {
            Matrix w(temp[i],temp[i+1]);
            Matrix b(1,temp[i+1]);

            w.setRandomValues();
            b.setRandomValues();

            weight.push_back(w);
            baes.push_back(b);
        }

        weights = weight;
        baeses = baes;
    }

    Genotype::Genotype(const Genotype& g)
    {
        this->countOfLayers = g.countOfLayers;

        std::vector<Matrix> w;
        std::vector<Matrix> b;

        for(int i = 0; i < this->countOfLayers; i++)
        {
            w.push_back(mutation(g.weights[i]));
            b.push_back(mutation(g.baeses[i]));
        }

        this->weights = w;
        this->baeses = b;
    }

    Matrix Genotype::getWeightsMatrixByIndex(int index) const{

        if(index >= this->countOfLayers || index < 0)
            return Matrix();
        return this->weights[index];
    }

    Matrix Genotype::getBaesMatrixByIndex(int index) const{
        if(index >= this->countOfLayers || index < 0)
            return Matrix();
        return this->baeses[index];
    }

    void Genotype::mutate()
    {

        for(int i = 0; i < this->countOfLayers; i++)
        {
            this->weights[i] = mutation(this->weights[i]);
            this->baeses[i] = mutation(this->baeses[i]);
        }
    }
}
