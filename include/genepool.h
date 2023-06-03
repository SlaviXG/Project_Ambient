#ifndef GENEPOOL_H
#define GENEPOOL_H

#include <iostream>
#include <cassert>

#include "Genotype.h"
#include "cell.h"


namespace genepool {

    class GenePoolInteractor{
<<<<<<< HEAD
        /**
         * @class GenePoolInteractor
         * @brief Interactor wrap for Genepool class
         */

        /**
         * @brief virtual function for adding single Cell to Genepool
         * @param cell object reference
         */
        virtual void AddToPool(environment::Cell* cell) = 0;
    };

    /**
     * @class GenePool
    * @brief collects the best neural networks
    *
    * GenePool class is responsible for collecting the best neural networks and passing collected
    * data to next generation, thus ensuring the learning of cells in the environment
    */
    class GenePool : public GenePoolInteractor
    {

    public:
        /**
         * @brief Constructor for GenePool
         * @param pool_size - max number of nnets saved to pool (usually equals to the starting number of cells)
         */
=======
        virtual void AddToPool(environment::Cell* cell) = 0;
    };

    class GenePool : public GenePoolInteractor
    {
    public:
>>>>>>> parent of 5ca7e22 (deploy: 8fcaa0a45f0abf3482480a09ac1e2897f420d718)
        GenePool(unsigned int pool_size){
            this->pool_size = pool_size;
        };

<<<<<<< HEAD
        /**
         * @brief AddToPool - Adds a single cell to the genepool (if cell's performance is good enough)
         * @param cell - reference to Cell object
         */
=======
>>>>>>> parent of 5ca7e22 (deploy: 8fcaa0a45f0abf3482480a09ac1e2897f420d718)
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
<<<<<<< HEAD
=======
            //DEBUG
//            std::cout << "\n" << cell->getTotalScore() << "\n";
>>>>>>> parent of 5ca7e22 (deploy: 8fcaa0a45f0abf3482480a09ac1e2897f420d718)

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
<<<<<<< HEAD
        /**
         * @brief print - prints contents of genepool (used for DEBUG ONLY)
         *
         */
=======

>>>>>>> parent of 5ca7e22 (deploy: 8fcaa0a45f0abf3482480a09ac1e2897f420d718)
        inline void print(){
            std::cout << "\n" << gene_pool.size() << " -\\- " << pool_size << "\n";
            for(int i = 0; i < gene_pool.size(); i++){
                std::cout << gene_pool[i].second << "\n";
            }
        }

<<<<<<< HEAD
        /**
         * @brief get_pool_cursize
         * @return current number of nnets saved in the pool
         */
=======
>>>>>>> parent of 5ca7e22 (deploy: 8fcaa0a45f0abf3482480a09ac1e2897f420d718)
        inline unsigned int get_pool_cursize(){
            return gene_pool.size();
        }

<<<<<<< HEAD
        /**
         * @brief get_pool_maxsize
         * @return maximum pool capacity
         */
=======
>>>>>>> parent of 5ca7e22 (deploy: 8fcaa0a45f0abf3482480a09ac1e2897f420d718)
        inline unsigned int get_pool_maxsize(){
            return pool_size;
        }

<<<<<<< HEAD

        /**
         * @brief getGenotype
         * @param pos - genotype id in genepool
         * @return genotype saved at pos
         */
=======
>>>>>>> parent of 5ca7e22 (deploy: 8fcaa0a45f0abf3482480a09ac1e2897f420d718)
        inline genotype::Genotype* getGenotype(unsigned int pos){
            assert(pos < gene_pool.size());
            return &gene_pool[pos].first;
        }

<<<<<<< HEAD
        /**
         * @brief clear_pool - clears the genepool
         */
=======
>>>>>>> parent of 5ca7e22 (deploy: 8fcaa0a45f0abf3482480a09ac1e2897f420d718)
        inline void clear_pool(){
            gene_pool.clear();
        }

    private:

        unsigned int pool_size;
<<<<<<< HEAD
=======
        //const std::string pool_file_name = "genepool.dat";
>>>>>>> parent of 5ca7e22 (deploy: 8fcaa0a45f0abf3482480a09ac1e2897f420d718)
        std::vector<std::pair<genotype::Genotype, int>> gene_pool;
    };

}


#endif // GENEPOOL_H
