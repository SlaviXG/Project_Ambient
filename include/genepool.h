#ifndef GENEPOOL_H
#define GENEPOOL_H

#include <iostream>
#include <cassert>

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
            unsigned int pos = 0;
            bool is_fit = false;
            for(; pos < gene_pool.size(); pos++){
                if(score >= gene_pool[pos].second){
                    is_fit = true;
                    break;
                }
            }
            //DEBUG
//            std::cout << "\n" << cell->getTotalScore() << "\n";

            if(gene_pool.size() != pool_size){
                if(is_fit){
                    std::vector<std::pair<genotype::Genotype, int>>::iterator it = gene_pool.begin() + pos;
                    gene_pool.insert(it, {cell->getGenotype(), cell->getTotalScore()});
                }
                else{
                    gene_pool.push_back({cell->getGenotype(), cell->getTotalScore()});
                }
            }
            else{
                if(is_fit){
                    gene_pool.pop_back();
                    std::vector<std::pair<genotype::Genotype, int>>::iterator it = gene_pool.begin() + pos;
                    gene_pool.insert(it, {cell->getGenotype(), cell->getTotalScore()});
                }
            }

            //DEBUG
//            print();
        }

        //DEBUG ZONE

        inline void print(){
            std::cout << "\n" << gene_pool.size() << " -\\- " << pool_size << "\n";
            for(int i = 0; i < gene_pool.size(); i++){
                std::cout << gene_pool[i].second << "\n";
            }
        }

        inline unsigned int get_pool_cursize(){
            return gene_pool.size();
        }

        inline unsigned int get_pool_maxsize(){
            return pool_size;
        }

        inline genotype::Genotype* getGenotype(unsigned int pos){
            assert(pos < gene_pool.size());
            return &gene_pool[pos].first;
        }

        inline void clear_pool(){
            gene_pool.clear();
        }

    private:

        unsigned int pool_size;
        //const std::string pool_file_name = "genepool.dat";
        std::vector<std::pair<genotype::Genotype, int>> gene_pool;
    };

}


#endif // GENEPOOL_H
