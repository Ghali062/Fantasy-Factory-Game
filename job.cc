#include "job.hh"
#include "elixir.hh"
#include "poudre.hh"

Job::Job(Jobs job) {
  this->job = job;
  switch (job) {
  case Jobs::CRAFT_POTION_ENSORCELANTE:
    input = {Poudre(2)};
    output = FinishedProduct(FinishedProductType::POTION_ENSORCELANTE, 2);
    break;
  case Jobs::CRAFT_BOULE_CRYSTAL:
    input = {Elixir(3)};
    output = FinishedProduct(FinishedProductType::BOULE_CRYSTAL, 1);
    break;
  case Jobs::ASSEMBLE_RELIQUE_MAGIQUE:
    input = {Poudre(4), Elixir(9)};
    output = FinishedProduct(FinishedProductType::RELIQUE_MAGIQUE, 1);
    break;
  case Jobs::ASSEMBLE_BAGUETTE_MAGIQUE:
    input = {Poudre(2), Elixir(13)};
    output = FinishedProduct(FinishedProductType::BAGUETTE_MAGIQUE, 1);
    break;
  default:
    throw "Impossible";
  };
}
