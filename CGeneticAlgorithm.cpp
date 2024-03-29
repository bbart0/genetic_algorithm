#include "CGeneticAlgorithm.h"
#include<random>
#include<vector>
using namespace std;

mt19937 CGeneticAlgorithm::gen;
uniform_int_distribution<> CGeneticAlgorithm::distr;

CGeneticAlgorithm::CGeneticAlgorithm(int popSizeP, float crossProbP, float mutProbP, int iterationsP,
                                     const std::vector<Item> &itemsP,int capP) {

    popSize = popSizeP;
    crossProb = crossProbP;
    cap = capP;
    mutProb = mutProbP;
    iterations = iterationsP;
    items = itemsP;

    population.reserve(popSize);
    for(int j=0;j<popSize;j++){
        population.push_back(CIndividual(items.size()));
    }
}

void CGeneticAlgorithm::initializeRandomGeneration() {
    random_device rd;
    gen = mt19937(rd());
    distr = uniform_int_distribution<int>(0, CGeneticAlgorithm::MAX);
}

float CGeneticAlgorithm::getChance() {
    return (float) distr(gen) / (float) distr.max();
}

int CGeneticAlgorithm::getChanceInt() {
    return distr(gen);
}

int CGeneticAlgorithm::getParentIndex() {
    int index0 = getChanceInt()%popSize;
    int index1 = getChanceInt()%popSize;
    if(population.at(index0).getCurrValue() >= population.at(index1).getCurrValue()) return index0;
    else return index1;
}

std::vector<int> CGeneticAlgorithm::getBestSolution() {
    int max =0;
    for(int i =0 ; i<population.size();i++){
        if(population.at(i).getCurrValue() > population.at(max).getCurrValue()){
            max = i;
        }
    }

    return population.at(max).getGenotype();
}

void CGeneticAlgorithm::updateFitness() {
    for(int i =0 ; i< population.size();i++){
        population.at(i).fitness(cap,items);
    }

}

void CGeneticAlgorithm::run() {
    CIndividual * parents = new CIndividual[2];
    CIndividual *children = new CIndividual[2];

    updateFitness();
    vector<CIndividual> popTemp;
    popTemp.reserve(popSize);

    for(int j=0; j<iterations;j++){

        //tworzenie nowego pokolenia
        while(popTemp.size()<popSize){
            parents[0] = population.at(getParentIndex());
            parents[1] = population.at(getParentIndex());

            if(getChance() < crossProb){
                children = parents[0].crossWith(parents[1], &children);
                popTemp.push_back(children[0]);
                popTemp.push_back(children[1]);
            }
            else{
                popTemp.push_back(parents[0]);
                popTemp.push_back(parents[1]);
            }
        }

        //usuniecie niepotrzebnego osobnika w przypadku nieparzystej liczby populacji
        if(popSize +1 == popTemp.size()) popTemp.pop_back();
        population = std::move(popTemp);

        //mutacja
        for(int k=0; k< population.size();k++){
            population.at(k).mutate(mutProb);
        }

        //aktualizacja wartosci fitness dla kazdego osobnika

        updateFitness();

    }

    delete[] children;
    delete[] parents;



}

int CGeneticAlgorithm::getValueOfSolution(vector<int> & sol) {
    vector<int> genes = sol;
    int val =0;
    for(int i =0; i<genes.size();i++){
        val += genes.at(i) * items.at(i).getValue();
    }
    return val;
}


