#include "company.hh"
#include "poudre.hh"
#include "worker.hh"

Company::Company(int nb_employees, float money)
    : elixir(0), poudre(0), _age(0), _money(money), _accumulatedMoney(0),
      _workers{Worker()} {}

void Company::hireWorker() {
  _workers.push_back(Worker());
  _money -= 50;
}

int Company::priceRawMaterials(std::string material, int nb) {
  if (material == "poudre") {
    Poudre new_poudre(nb);
    return new_poudre.getPrice();
  }
  if (material == "elixir") {
    Elixir new_elixir(nb);
    return new_elixir.getPrice();
  }
  throw "material should be elixir or poudre";
}

void Company::buyRawMaterials(std::string material, int nb) {
  if (material == "poudre") {
    Poudre new_poudre(nb);
    _money -= new_poudre.getPrice();
    poudre += new_poudre;
  } else if (material == "elixir") {
    Elixir new_elixir(nb);
    _money -= new_elixir.getPrice();
    elixir += new_elixir;
  } else {
    throw "material should be elixir or poudre";
  }
}

void Company::produce() {
  for (auto worker : _workers) {
    if (worker.IsWorking()) {
      auto job = worker.currentJob().value();
      for (auto input : job.input) {
        if (input.getMaterialType() == "elixir") {
          if (elixir.getNbRawMaterials() >= input.getNbRawMaterials()) {
            elixir -= input;
          } else {
            throw "Not enough elixir";
          }
        } else if (input.getMaterialType() == "poudre") {
          if (poudre.getNbRawMaterials() >= input.getNbRawMaterials()) {
            poudre -= input;
          } else {
            throw "Not enough poudre";
          }
        } else {
          throw "Impossible";
        }
      }
      add_product(job.output);
    }
  }
}

void Company::add_product(FinishedProduct product) {
  storage.push_back(product);
}

float Company::sellStorage() {
  auto res = 0;
  for (auto product : storage) {
    res += product.price();
  }
  storage.clear();
  addMoney(res);
  return res;
}

void Company::addMoney(float newMoney) {
  _money += newMoney;
  _accumulatedMoney += newMoney;
}

int Company::getLevel() {
  switch ((int)_accumulatedMoney) {
  case 0 ... 199:
    return 1;
  case 200 ... 349:
    return 2;
  case 350 ... 799:
    return 3;
  case 800 ... 1099:
    return 4;
  case 1100 ... 1400:
    return 5;
  }
  return 0; // never reached
}

int Company::getNextLevelGoal() {
  switch ((int)_accumulatedMoney) {
  case 0 ... 199:
    return 200;
  case 200 ... 349:
    return 350;
  case 350 ... 799:
    return 800;
  case 800 ... 999:
    return 1000;
  default:
    return 0; // never reached
  }
}

float Company::payWorkers() {
  float sum = _workers.size() * Worker::salary;
  _money -= sum;
  return sum;
}

void Company::payImpots(float dollars) { _money -= dollars; }

