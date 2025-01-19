#include "items.hh"
#include <map>
#include <string>

#pragma once

/**
 * a finished product can be selled
 */

enum class FinishedProductType {
  POTION_ENSORCELANTE,
  BOULE_CRYSTAL,
  BAGUETTE_MAGIQUE,
  RELIQUE_MAGIQUE,
};

class FinishedProduct : public Items {
public:
  FinishedProduct() = default;
  FinishedProduct(FinishedProductType type, int quantity)
      : type(type), quantity(quantity) {}

  float price() { return _price_table.at(type) * quantity; }

  FinishedProductType type;

  int getQuantity() const { return quantity; }
  std::string to_string() const {
    switch (type) {
    case FinishedProductType::POTION_ENSORCELANTE:
      return "Potion";
    case FinishedProductType::BOULE_CRYSTAL:
      return "Boule";
    case FinishedProductType::BAGUETTE_MAGIQUE:
      return "Baguette";
    case FinishedProductType::RELIQUE_MAGIQUE:
      return "Relique";
    default:
      throw "impossible";
    }
  }

protected:
  // map : product / price
  const static std::map<FinishedProductType, float> _price_table;
  int quantity;
};
