#pragma once
#include "CIndividual.h"
#include <vector>
#include "Item.h"

class CGeneticAlgorithm {
private:
    int popSize;
    int cap;
    float crossProb;
    float mutProb;
    int iterations;
    std::vector<CIndividual> population;
    std::vector<Item> items;

    static const int SEED =1;
    static const int MAX = 100;

    static std::mt19937 gen;
    static std::uniform_int_distribution<> distr;

public:
    CGeneticAlgorithm(int popSize, float crossProb, float mutProb, int iterations, const std::vector<Item> &items,int cap);
    static void initializeRandomGeneration();
    float getChance();
    int getChanceInt();
    int getParentIndex();
    std::vector<int> getBestSolution();
    void updateFitness();
    int getValueOfSolution(std::vector<int>& genes);

    void run();
};


