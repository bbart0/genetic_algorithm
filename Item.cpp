#include "Item.h"

Item::Item(int weightP, int valueP)  {
    weight = weightP;
    value = valueP;
}

int Item::getWeight() {
    return weight;
}

void Item::setWeight(int weight) {
    Item::weight = weight;
}

int Item::getValue() {
    return value;
}

void Item::setValue(int value) {
    Item::value = value;
}

Item::Item() {
    weight =0;
    value =0;
}
