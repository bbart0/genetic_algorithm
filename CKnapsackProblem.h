#pragma once
#include "Item.h"
#include <vector>
#include <string>
#include "InvalidItem.h"


class CKnapsackProblem {
public:
    CKnapsackProblem();

    CKnapsackProblem(int numOfItems, int capacity, std::vector<Item> & items);
    ~CKnapsackProblem();
    void setItemNumber(int itemNumber);
    void setItems( std::vector<Item> &items);
    void setBackpackWeight(int weight);
    void readDataFrom(std::string txt);
    int calc(int w[], int v[]);
    int calc();

    int getItemNumber() const;

    const std::vector<Item> &getItems() const;

    int getCap() const;


    void printTest();
private:
    int itemNumber;
    std::vector<Item> items;
    int cap;
    void setItemsPriv(std::vector<Item> & items) throw (InvalidItem);
    void setItemNumberPriv(int itemNumber) throw( InvalidItem);
    void setBackpackWeightPriv(int weight) throw (InvalidItem);



};

