#include "CIndividual.h"
#include <random>
#include <iostream>
#include <cmath>

using namespace std;

mt19937 CIndividual::gen;
uniform_int_distribution<> CIndividual::distr;

float CIndividual::getChance() {
    return (float) distr(gen) / (float) distr.max();
}

void CIndividual::initializeRandomGeneration() {
    random_device rd;
    gen = mt19937(rd());
    distr = uniform_int_distribution<int>(0, CIndividual::MAX);
}

CIndividual::CIndividual(const vector<int> &genotypeP) {
    genotype = genotypeP;
    currValue=0;
}

CIndividual::CIndividual(const int numOfItems) {
    genotype.reserve(numOfItems);
    currValue=0;
    int rand = getChanceInt();

    for(int i =0; i< numOfItems; i++, rand=getChanceInt()){
        if(rand % 2 ==0 ){
            genotype.push_back(0);
        }
        else{
            genotype.push_back(1);
        }

    }
}

int CIndividual::getChanceInt() {
    return distr(gen);
}

void CIndividual::printGenes() {
    cout<<"[ ";
    for(int i=0;i<genotype.size();i++){
        cout<<genotype.at(i)<<", ";
    }
    cout<<" ]"<<endl;
}

void CIndividual::fitness(const int &maxWeight,  vector<Item> &items) {
        //weight of the items
        if(genotype.size() == items.size()){
            int weight =0;
            for(int i =0; i< genotype.size();i++){
                weight += genotype.at(i) * items.at(i).getWeight();
            }

            if(weight<= maxWeight){
                //value of items is stored
                for(int i=0;i<items.size();i++){
                    currValue +=items.at(i).getValue();
                }
            }
            else currValue =0;
        }
        else{
            cout<<"CIndividual fitness : items and genotype size dont match\n ";
        }

}

void CIndividual::mutate(const float &mutProb) {
    for(int i=0;i<genotype.size();i++){
        if(getChance() <= mutProb){
            genotype.at(i) = (int) pow((genotype.at(i) -1),2);
        }
    }
}

CIndividual *& CIndividual::crossWith(CIndividual &parent, CIndividual **children) {
    delete [] (*children);

    (*children) = new CIndividual[2];
    int cutIndex = getChanceInt() % (genotype.size() -2);

    (*children)[0] = CIndividual(genotype.size());
    (*children)[1] = CIndividual(genotype.size());

    for(int i=0 ; i<genotype.size();i++){
        if(i<=cutIndex){
            (*children)[0].genotype.at(i) = genotype.at(i);
            (*children)[1].genotype.at(i) = parent.genotype.at(i);
        }
        else{
            (*children)[0].genotype.at(i) = parent.genotype.at(i);
            (*children)[1].genotype.at(i) = genotype.at(i);
        }
    }

    return (*children);
}

int CIndividual::getCurrValue() {
    return currValue;
}

const vector<int> &CIndividual::getGenotype() {
    return genotype;
}

CIndividual::CIndividual() {
    currValue=0;
}


