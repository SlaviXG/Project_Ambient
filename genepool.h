#ifndef GENEPOOL_H
#define GENEPOOL_H
#include <iostream>
#include "Genotype.h"
#include "cell.h"


namespace genepool {

    class GenePoolInteractor{
        virtual void AddToPool(environment::Cell* cell) = 0;
    };

    class GenePool : public GenePoolInteractor
    {
    public:
        GenePool(unsigned int pool_size){
            this->pool_size = pool_size;
        };

        inline void AddToPool(environment::Cell* cell){
            int score = cell->getTotalScore();
            unsigned int i = 0;
            bool is_fit = false;
            for(; i < gene_pool.size(); i++){
                if(score >= gene_pool[i].second){
                    is_fit = true;
                    break;
                }
            }
            if(gene_pool.size() != pool_size){
                if(is_fit){
                    std::vector<std::pair<genotype::Genotype, int>>::iterator it = gene_pool.begin() + i;
                    gene_pool.insert(it, {cell->getGenotype(), score});
                }
                else{
                    gene_pool.push_back({cell->getGenotype(), score});
                }
            }
            else{
                if(is_fit){
                    gene_pool[i] = {cell->getGenotype(), score};
                }
            }

            //DEBUG
            std::cout << "\n" << score << "\n";
            print();
        }

        //DEBUG ZONE

        inline void print(){
            std::cout << "\n" << gene_pool.size() << " -\\- " << pool_size << "\n";
            for(int i = 0; i < gene_pool.size(); i++){
                std::cout << gene_pool[i].second << "\n";
            }
        }

        inline unsigned int get_pool_maxsize(){
            return pool_size;
        }

    private:
        unsigned int pool_size;
        //const std::string pool_file_name = "genepool.dat";
        std::vector<std::pair<genotype::Genotype, int>> gene_pool;
    };

}


#endif // GENEPOOL_H
