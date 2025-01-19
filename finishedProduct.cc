#include "finishedProduct.hh"

const std::map<FinishedProductType, float> FinishedProduct::_price_table = {
    {FinishedProductType::POTION_ENSORCELANTE, 11.0},
    {FinishedProductType::BOULE_CRYSTAL, 25.0},
    {FinishedProductType::BAGUETTE_MAGIQUE, 50},
    {FinishedProductType::RELIQUE_MAGIQUE, 70},
};
