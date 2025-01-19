#include "finishedProduct.hh"
#pragma once

/**
* Potion ensorcelante is a Basic finished product
 */


class Potion : public FinishedProduct {
    public:
    Potion();

    protected:
    int _productionTime = 1;
    str _type : "Basic";
}