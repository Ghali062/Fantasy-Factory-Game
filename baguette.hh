#include "finishedProduct.hh"
#pragma once

/**
* Baguette magique is a Deluxe finished product
 */


class Baguette : public FinishedProduct {
    public:
    Baguette();

    protected:
    int _productionTime = 5;
    str _type : "Deluxe";
}