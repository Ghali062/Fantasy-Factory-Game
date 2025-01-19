#pragma once

/**
 * Represents all kinds of items
 */
class Items

{
public:
  Items() {};

protected:
  float _buyPrice;
  float _sellPrice;
  float _rawMaterials;      // kind of material
  float _amountRawMaterial; // in kg
};
