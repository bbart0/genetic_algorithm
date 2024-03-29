#include "CKnapsackProblem.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "InvalidItem.h"

using namespace std;

CKnapsackProblem::CKnapsackProblem() {
    itemNumber =0;
    items = vector<Item>();
}

CKnapsackProblem::CKnapsackProblem(int numOfItems, int sackWeight, vector<Item> &itemsP) {
    try{
        setItemNumberPriv(numOfItems);
        setItemsPriv(itemsP);
        setBackpackWeightPriv(sackWeight);
    }catch(InvalidItem &ex){
        cout<<"Invalid Item exception in CKnapsackProblem: "<< ex.what()<<endl;
        cout<<"Both arguments are initialized as 0 and an empty vector. Try again with setters"<<endl;
        itemNumber =0;
        cap =0;
        items = vector<Item>();
    }

    }


void CKnapsackProblem::printTest() {
    cout<<"weight  ->  value"<<endl;
        for(int i = 0 ;i<items.size(); i++){
            cout<<i<<": "<<items.at(i).getWeight()<<" -> "<<items.at(i).getValue()<<endl;
        }
        cout<<"Number of items: "<<itemNumber<<endl;
        cout<<"Backpack capacity: "<<cap<<endl;
}

CKnapsackProblem::~CKnapsackProblem() {

}





void CKnapsackProblem::setItemNumber(int itemNumber) {
    try{
        setItemNumberPriv(itemNumber);
    }catch(InvalidItem &ex){
        cout<<"Invalid Item exception: "<< ex.what()<<endl;
    }

}

void CKnapsackProblem::setItems( vector<Item> &items) {
    try{
        setItemsPriv(items);
    }catch(InvalidItem &ex){
        cout<<"Invalid Item exception: "<< ex.what()<<endl;
    }
}


void CKnapsackProblem::setItemsPriv(vector<Item> &items) throw(InvalidItem) {

    if(items.size() != itemNumber){
        throw InvalidItem("The number of items and the size of the given vector dont match");
    }

    for(int i=0; i< items.size(); i++){
      if(items.at(i).getWeight() <= 0 || items.at(i).getValue() <= 0){
        throw InvalidItem("Values and weights must be positive");
      }
    }

    CKnapsackProblem::items = items;

}
void CKnapsackProblem::setItemNumberPriv(int itemNumber) throw (InvalidItem){
    if(itemNumber<=0){
        throw InvalidItem("The number of items must be positive");
    }
    else{
        CKnapsackProblem::itemNumber = itemNumber;
    }
}

void CKnapsackProblem::readDataFrom(string txt) {

    string tmp;
    int weight;
    int val;



    ifstream ReadFile;
    ReadFile.open(txt,ios_base::in);

    if(!ReadFile){
        cout<<"File not found"<<endl;
    }
    else {
        if(getline(ReadFile,tmp)){
            stringstream ss(tmp);
            ss >>itemNumber>>cap;
            ss.clear();
        }


        while(getline(ReadFile,tmp)){
            stringstream linestream(tmp);


            linestream >>val>>weight;

            items.emplace_back(weight,val);
            if(ReadFile.eof()){
                linestream.clear();
            }
        }


    }

    ReadFile.close();
}

void CKnapsackProblem::setBackpackWeightPriv(int weight) throw(InvalidItem) {
    if(weight<= 0) throw InvalidItem("The capacity of the backpack must be positive");
    else{
        cap = weight;
    }
}

void CKnapsackProblem::setBackpackWeight(int weight) {
    try{
        setBackpackWeightPriv(weight);
    }catch(InvalidItem &ex){
        cout<<"Invalid Item exception: "<< ex.what()<<endl;
    }
}

int CKnapsackProblem::calc(int w[], int v[]) {

    int i, wt;
    int K[itemNumber + 1][cap + 1];
    for (i = 0; i <= itemNumber; i++) {
        for (wt = 0; wt <= cap; wt++) {
            if (i == 0 || wt == 0)
                K[i][wt] = 0;
            else if (w[i - 1] <= wt)
                K[i][wt] = max(v[i - 1] + K[i - 1][wt - w[i - 1]], K[i - 1][wt]);
            else
                K[i][wt] = K[i - 1][wt];
        }
    }

    return K[itemNumber][cap];
}

int CKnapsackProblem::calc() {
    int weights[itemNumber];
    int values[itemNumber];

    for(int i =0; i< itemNumber;i++){
        weights[i] = items.at(i).getWeight();
        values[i] = items.at(i).getValue();
    }


    return calc(weights,values);
}

int CKnapsackProblem::getItemNumber() const {
    return itemNumber;
}

const vector<Item> &CKnapsackProblem::getItems() const {
    return items;
}

int CKnapsackProblem::getCap() const {
    return cap;
}






