#include "rawMaterials.hh"

std::map<std::string, float> RawMaterial::_price_table = {
    {"elixir", 1.5},
    {"poudre", 3.2},
};

float RawMaterial :: getReduction(int nbRawMaterials) {
    if (nbRawMaterials < 0)
      throw "Impossible argument négatif 🤬";

    if (0 <= nbRawMaterials && nbRawMaterials < 10)
      return 0;
    if (10 <= nbRawMaterials && nbRawMaterials < 50)
      return 0.1;
    else
      return 0.2;
  }