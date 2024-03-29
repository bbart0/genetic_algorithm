#pragma once
#include<vector>
#include <random>
#include "Item.h"

class CIndividual {
private:
    static const int SEED =1;
    static const int MAX = 100;

    static std::mt19937 gen;
    static std::uniform_int_distribution<> distr;
    std::vector<int> genotype;
    int currValue;



public:
     CIndividual(const std::vector<int> &genotype);
     CIndividual( int numOfItems);
     void fitness(const int &maxWeight, std::vector<Item> &items);
     void mutate(const float & mutProb);
     CIndividual *& crossWith(CIndividual & parent, CIndividual **children);

    const std::vector<int> &getGenotype();

    int getCurrValue();


    float getChance();
    void printGenes();
    int getChanceInt();



    static void initializeRandomGeneration();

    CIndividual();
};


