#include "finishedProduct.hh"
#pragma once

/**
* Relique magique is a Deluxe finished product
 */


class Relique : public FinishedProduct {
    public:
    Relique();

    protected:
    int _productionTime = 5;
    str _type : "Deluxe";
}