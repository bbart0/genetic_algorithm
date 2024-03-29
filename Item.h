#pragma once

class Item {
private:
    int weight;
    int value;

public:
    Item(int weight, int value);
    Item();

    int getWeight();

    void setWeight(int weight);

    int getValue();

    void setValue(int value);

};


