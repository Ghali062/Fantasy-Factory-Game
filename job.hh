#include "finishedProduct.hh"
#include "rawMaterials.hh"
#include <vector>
#pragma once

enum class Jobs {
  CRAFT_POTION_ENSORCELANTE,
  CRAFT_BOULE_CRYSTAL,
  ASSEMBLE_RELIQUE_MAGIQUE,
  ASSEMBLE_BAGUETTE_MAGIQUE,
};

class Job {
public:
  Job(Jobs job);
  Jobs job;
  std::vector<RawMaterial> input;
  FinishedProduct output;
};
