#pragma once

/**
 * Represents the Company
 */
#include "finishedProduct.hh"
#include "elixir.hh"
#include "poudre.hh"
#include "worker.hh"
#include <vector>

class Company
{
public:
  Company(int nb_employees, float money);
  void hireWorker();
  int getLevel();
  float getBalance() { return _money; }
  int getNbEmployees() { return _workers.size(); }
  std::vector<Worker> &getWorker() { return _workers; }
  int priceRawMaterials(std::string material, int nb);
  void buyRawMaterials(std::string material, int nb);
  void produce();
  void add_product(FinishedProduct product);
  std::vector<FinishedProduct> getStorage() { return storage; }
  float sellStorage();
  void addMoney(float newMoney);
  float payWorkers();
  void payImpots(float dollars);
  float getAccumulatedMoney() { return _accumulatedMoney; }
  int getNextLevelGoal();
  Elixir elixir;
  Poudre poudre;

protected:
  int _age;
  float _money;
  float _accumulatedMoney;

  std::vector<Worker> _workers;
  std::vector<FinishedProduct> storage;
};
