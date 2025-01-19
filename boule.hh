#include "finishedProduct.hh"
#pragma once

/**
* Boule de Crystal is a Basic finished product
 */


class Boule : public FinishedProduct {
    public:
    Boule();

    protected:
    int _productionTime = 1;
    str _type : "Basic";
}