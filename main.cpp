#include <iostream>
#include <vector>
#include "CKnapsackProblem.h"
#include "CIndividual.h"
#include "CGeneticAlgorithm.h"
#include "Item.h"
#include <string>
using namespace std;

void testReading();
void knapsackCons();
void testRandomGen();
void individualTesting();
void printSolution(string mess, vector<int> sol, int value){
    cout<<mess<<endl;

    cout<<"[ ";
    for(int i=0; i<sol.size();i++){
        cout<<sol.at(i)<< ", ";
    }

    cout<<"]\n Value: "<<value<<endl;
}
void geneticValNormal(){
    vector<Item> items;
    items.reserve(4);

    items.push_back(Item(4,5));
    items.push_back(Item(1,1));
    items.push_back(Item(3,4));
    items.push_back(Item(2,3));
    CGeneticAlgorithm alg(10,0.5,0.1,20,items,5);
    alg.run();
    vector<int> solution = alg.getBestSolution();
    printSolution("\ntest - normalne parametry\n", solution, alg.getValueOfSolution(solution));

    cout<<"Optymalne roziwazanie to 0011 value: "<<endl;

    CKnapsackProblem sack(4,5,items);
    cout<<sack.calc()<<endl;


}

void geneticValTooBigCross(){
    vector<Item> items;
    items.reserve(4);

    items.push_back(Item(4,5));
    items.push_back(Item(1,1));
    items.push_back(Item(3,4));
    items.push_back(Item(2,3));
    CGeneticAlgorithm alg(10,0.7,0.1,20,items,5);
    alg.run();
    vector<int> solution = alg.getBestSolution();
    printSolution("\ntest - duzy wspolczynnik krzyzowania\n", solution, alg.getValueOfSolution(solution));

    cout<<"Optymalne roziwazanie to 0011 value: "<<endl;

    CKnapsackProblem sack(4,5,items);
    cout<<sack.calc()<<endl;


}
void geneticValTooBigMutation(){
    vector<Item> items;
    items.reserve(4);

    items.push_back(Item(4,5));
    items.push_back(Item(1,1));
    items.push_back(Item(3,4));
    items.push_back(Item(2,3));
    CGeneticAlgorithm alg(10,0.5,0.7,20,items,5);
    alg.run();
    vector<int> solution = alg.getBestSolution();
    printSolution("\ntest - duzy wspolczynnik mutowania\n", solution, alg.getValueOfSolution(solution));

    cout<<"Optymalne rozwiazanie to 0011 value: "<<endl;

    CKnapsackProblem sack(4,5,items);
    cout<<sack.calc()<<endl;


}
void geneticValNoCross(){
    vector<Item> items;
    items.reserve(4);

    items.push_back(Item(4,5));
    items.push_back(Item(1,1));
    items.push_back(Item(3,4));
    items.push_back(Item(2,3));
    CGeneticAlgorithm alg(10,0.0,0.1,20,items,5);
    alg.run();
    vector<int> solution = alg.getBestSolution();
    printSolution("\ntest - wspolczynnik krzyzowania = 0\n", solution, alg.getValueOfSolution(solution));

    cout<<"Optymalne rozwiazanie to 0011 value: "<<endl;

    CKnapsackProblem sack(4,5,items);
    cout<<sack.calc()<<endl;


}

void geneticValBiggerPop(){
    vector<Item> items;
    items.reserve(4);

    items.push_back(Item(4,5));
    items.push_back(Item(1,1));
    items.push_back(Item(3,4));
    items.push_back(Item(2,3));
    CGeneticAlgorithm alg(40,0.5,0.1,20,items,5);
    alg.run();
    vector<int> solution = alg.getBestSolution();
    printSolution("\nwieszka populacja : 40\n", solution, alg.getValueOfSolution(solution));

    cout<<"Optymalne roziwazanie to 0011 value: "<<endl;

    CKnapsackProblem sack(4,5,items);
    cout<<sack.calc()<<endl;


}

int main() {

//    Item* items = new Item[3];
//    items[0] = Item(2,3);
//    items[1] = Item(4,5);
//    items[2] = Item(5,6);
//    testReading();
    CIndividual::initializeRandomGeneration();
    CGeneticAlgorithm:: initializeRandomGeneration();

    testRandomGen();
    individualTesting();
    geneticValNormal();
    geneticValTooBigCross();
    geneticValTooBigMutation();
    geneticValNoCross();
    testReading();

    return 0;
}

void individualTesting(){
    CIndividual tmp(4);
    tmp.printGenes();


}
void testRandomGen(){
    CIndividual tmp(4);

    cout<<tmp.getChance()<<endl;
    cout<<tmp.getChance()<<endl;
    cout<<tmp.getChance()<<endl;
    cout<<tmp.getChance()<<endl;
    cout<<tmp.getChanceInt()<<endl;
    cout<<tmp.getChanceInt()<<endl;
}
void knapsackCons(){
    vector<Item> items;

    items.emplace_back(2,3);
    items.emplace_back(4,5);
    items.emplace_back(6,7);

    CKnapsackProblem temp(3,17,items);

    temp.printTest();
}
void testReading(){
    CKnapsackProblem reading;
    reading.readDataFrom("..\\f1_l-d_kp_10_269");
    reading.printTest();
    int result = reading.calc();
    cout<<"Wynik: "<<result<<endl;

    CGeneticAlgorithm alg(20,0.5,0.2,40,reading.getItems(),reading.getCap());
    alg.run();

    vector<int> solution = alg.getBestSolution();
    printSolution("\nAlgorytm dla wiekszej ilosci (10 przedmiotow)\n", solution, alg.getValueOfSolution(solution));


    CGeneticAlgorithm alg1(80,0.6,0.2,100,reading.getItems(),reading.getCap());
    alg1.run();

    vector<int> solution1 = alg1.getBestSolution();
    printSolution("\nAlgorytm dla wiekszej ilosci (10 przedmiotow) - wieksza populacja\n", solution1, alg1.getValueOfSolution(solution1));
}
