#include "company.hh"
#include "jeu.hh"
#include "mini_jeu_impots.hh"
#include "text_box.hh"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

auto g = "\033[38;2;0;255;0m";
auto r = "\033[0m";

int load(std::string message, int time_secs) {
  std::cout << message;
  std::cout.flush();
  for (int j = 0; j < time_secs; j++) {
    for (int i = 0; i < 3; i++) {
      std::cout << ".";
      std::cout.flush();
      std::this_thread::sleep_for(std::chrono::milliseconds(333));
    }
    std::cout << "\b\b\b   \b\b\b";
  }
  std::cout << std::endl;

  return 0;
}

void loading_screen(bool dev_mode, bool bienvenue,
                    std::string message = "Loading...") {
  std::string original = message + "\n"
                                   "\n\n\n\n"
                                   "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀@@@@@@@@@@\n"
                                   "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀@@@@@@@@ \n"
                                   "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀@@@⠀@@⠀ \n"
                                   "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⢸⣿⠀ \n"
                                   "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⢸⣿⠀ \n"
                                   "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⢸⣿⠀ \n"
                                   "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⢸⣿⡇⠀⢸⣿⠀ \n"
                                   "⠀⠀⢠⣷⡀⠀⠀⠀⠀⣼⣦⠀⠀⠀⠀⢠⣷⣄⠀⠀⠀⠀⢸⣿⡇⠀⢸⣿⠀ \n"
                                   "⠀⠀⢸⣿⣿⣆⠀⠀⠀⣿⣿⣷⡀⠀⠀⢸⣿⣿⣧⠀⠀⠀⢸⣿⡇⠀⢸⣿⠀ \n"
                                   "⠀⠀⣾⣿⣿⣿⣷⡀⢠⣿⣿⣿⣿⣆⠀⣼⣿⣿⣿⣷⣄⠀⢸⣿⡇⠀⢸⣿⠀ \n"
                                   "⠀⠀⣿⣿⣿⣿⣿⣿⣾⣿⣿⣿⣿⣿⣷⣿⣿⣿⣿⣿⣿⣶⣼⣿⣧⣤⣾⣿⠀ \n"
                                   "⠀⠀⣿⡟⠉⠉⢹⣿⡏⠉⠉⢻⣿⠉⠉⠉⣿⣿⠉⠉⢹⣿⣿⣿⣿⣿⣿⣿⠀ \n"
                                   "⠀⠀⣿⣷⣶⣶⣾⣿⣷⣶⣶⣾⣿⣶⣶⣶⣿⣿⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⠀ \n"
                                   "⠀⠀⣿⡏⠉⠉⢹⣿⡏⠉⠉⢹⣿⠉⠉⠉⣿⣿⠉⠉⢹⣿⣿⣿⣿⣿⣿⣿⠀ \n"
                                   "⠀⠀⣿⣿⣶⣶⣾⣿⣷⣶⣶⣿⣿⣷⣶⣾⣿⣿⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⠀ \n"
                                   "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ \n";
  std::string text = original;

  std::srand(std::time(nullptr));

  const int duration = dev_mode ? 100 : 5000; 
  const int tickDuration = 100;               
  const int iterations = duration / tickDuration;

  for (int i = 0; i < iterations; ++i) {
    for (size_t j = 0; j < text.length(); ++j) {
      if (original[j] == '@') {
        text[j] = (std::rand() % 2 == 0) ? '@' : ' ';
      }
    }

    std::cout << "\x1B[2J\x1B[H"; 

    if (bienvenue)
      Bienvenue();
    printBoxedText(text, "\e[0;33m", 104);

    std::this_thread::sleep_for(std::chrono::milliseconds(tickDuration));
  }

  std::cout << "\x1B[2J\x1B[H"; 
                                
}
void Bienvenue() {
  const std::string text =
      "👋 Bienvenue dans le jeu Fantastic Factory\n"
      "📜 Règles du jeu : Vous etes propiétaire d'une usine de production "
      "Vous fournissez des supermarchés ayant une demande infinie !\n"
      " 🫡 Vous devez manufacturer des produits à partir de matières "
      "magiques et la vente de ces produits magiques est automatique 🤑\n"
      "⭐️A partir du niveau 3, vous accédez au méthodes de production 'assemble' "
      "qui permettent de fabriquer des objets surnaturels de haute valeur 🤓"
      "\n"

      "🛑 Attention vous ne devez pas trop vous endetter! SINON VOUS SEREZ MAUDIT"
      "Si vous allez à \033[38;2;0;255;0m-200 mana\033[32m, VOUS PERDEZ "
      "💀\n"
      "💡 Petit conseil : \"Ne perdez pas tout votre mana en impôts, sinon même les démons "
      "vous enverront leur déclaration !\" 😈\n";
  printBoxedText(text, "\e[3m\e[1;32m");
}

void game_over() {
  // clang-format off
  printBoxedText( 
" ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓██████████████▓▒░░▒▓████████▓▒░       ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓███████▓▒░ \n"
"░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░\n"
"░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░\n"
"░▒▓█▓▒▒▓███▓▒░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓██████▓▒░        ░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒▒▓█▓▒░░▒▓██████▓▒░ ░▒▓███████▓▒░ \n"
"░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░\n"
"░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░\n"
" ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░       ░▒▓██████▓▒░   ░▒▓██▓▒░  ░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░\n",
 "\e[0;31m");
  // clang-format on
}

void bankrupt() {
  std::cout << "\n\n\n\nBankrupt 💸" << std::endl;
  game_over();
}
int choice(const std::string Phrase) {
  int choix_utilisateur = -1;
  std::cout << Phrase << "\n> ";

  while (true) {
    if (!(std::cin >> choix_utilisateur)) {
      if (std::cin.eof()) {
        std::cout << "\n👋🤓 Au revoir\n";
        exit(1);
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else if (choix_utilisateur == 0 || choix_utilisateur == 1) {
      std::cout << std::endl;
      return choix_utilisateur;
    } else {
      std::cout << std::endl;
      std::cout << "Veuillez choisir une option valide (0 ou 1).\n"
                << Phrase << "\n> ";
    }
  }
}

void Jeu::Tour() {
  auto newLevel = _company.getLevel();
  if (newLevel == 5) {
    printBoxedText("Félicitations Grand Industriel !!! Vous avez atteint le niveau maximum ! 🫡 ", "\e[1;93m", 6, 3, 2, 1);
    exit(0);
  } else if (newLevel != level) {
    std::stringstream text;
    text << "🎉 Bravo! Vous avez atteint le niveau " << newLevel << "🎉\n";
    if (newLevel == 3) {
      text << "🫡 Vous avez débloqué la méthode de production Assembler, vous pouvez manufacturer des produits DELUXE' 🫡\n";
    }
    for (int i = 0; i < 5; i++) {    
      if (i < newLevel) text << "⬛️";
      else text << ".";
    }
    text << "\n";
    printBoxedText(text.str(), "\033[38;5;220m", 6, 3, 41, 1);
  }
  level = newLevel;
  const auto r = "\e[0;0m";
  const auto bb = "\e[1;34m";
  const auto p = "\e[1;35m";
  std::stringstream text;
  text << bb << "Tour " << _tour << r << "\n";
  text << "Vous etes actuellement au niveau: " << p << newLevel << r << "\n";
  text << "Vous avez actuellement " << g << _company.getBalance() << " mana" << r << "\n";
  text << "Vous avez actuellement " << _company.getNbEmployees() << " elf(s) employé(s)\n";
  text << "Vous avez actuellement " << _company.elixir.getNbRawMaterials() << " kg de elixir\n";
  text << "Vous avez actuellement " << _company.poudre.getNbRawMaterials() << " kg de poudre\n";
  text << "Progrès du niveau: ";
  showProgressBar(_company.getAccumulatedMoney(), _company.getNextLevelGoal(), text);
  text << "\n\nEt rappelez-vous : \"Mieux vaut réinvestir vos gains en potions magiques qu'en impôts,\n "
         << "au moins vos elfes seront heureux !\" ✨\n";
  text << "\n";
  printBoxedText(text.str(), "", 6, 3, 38, 1);
}

int input(std::string phrase) {
  int res = -1;
  std::cout << phrase << "\n> ";
  std::cin >> res;
  std::cout << std::endl;
  return res;
}

Jeu::Jeu(int initial_nb_employees, float initial_money, bool dev_mode)
    : _company(initial_nb_employees, initial_money), _start(true), _tour(0),
      _dev_mode(dev_mode), level(1) {}

void Jeu::ask_material(std::string material) {
  std::cout << "Combien de kg de " << material << " voulez-vous acheter ?";
  int _quantity = input("");
  int price = _company.priceRawMaterials(material, _quantity);
  if (price > _company.getBalance()) {
    std::cout << "Vous n'avez pas assez d'argent pour acheter autant "
                 "de "
              << material << " (" << price << " > " << _company.getBalance()
              << ")" << std::endl;
  } else {
    std::cout << "Confirmez-vous vouloir l'acheter pour " << g << price << " mana"
              << r << " ? (Vous avez bénéficié d'une réduction de "
              << int(RawMaterial::getReduction(_quantity) * 100) << "%)\n";
    int choix = choice("  1 (OUI) ou 0 (NON) ?");
    if (choix == 1) {
      _company.buyRawMaterials(material, _quantity);
    }
  }
}

void Jeu::run() {
  loading_screen(_dev_mode, true);
  if (_tour == 0) {
    Bienvenue();
  }
  while (_start) {
    Tour();
    handleRawMaterials();
    handleHiring();
    handleProduction();
    endOfDay();
    if (_company.getBalance() < -200) {
      bankrupt();
      break;
    }
    _start = choice("Voulez-vous continuer ? (1/0)");
  }
}

void Jeu::handleRawMaterials() {
  int choix = choice(
      "Souhaitez-vous acheter des matières magiques ?\n 1 (OUI) ou 0 (NON)");
  if (choix == 1) {
    while (choix == 1) {
      choix = choice("Quelles matières magiques voulez-vous acheter ?\n"
                     "0. Elixir     (\033[38;2;0;255;0m1.5 mana\033[0m l'unité)\n"
                     "1. Poudre (\033[38;2;0;255;0m3.2 mana\033[0m l'unité)");
      if (choix == 0) {
        ask_material("elixir");
      } else if (choix == 1) {
        ask_material("poudre");
      }
      choix = choice("Souhaitez-vous continuer d'acheter des matières "
                     "magiques ?\n 1 (OUI) ou 0 (NON)");
    }
  }
}

void Jeu::handleHiring() {
  std::cout << "2. Engager un elf\n";
  std::cout << "🛑 ATTENTION 🛑: le salaire quotidien de chaque elf est "
               "de "
            << g << "10 mana" << r << " + " << g << "50 mana" << r
            << " pour le débloquer\n";
  int choix = choice("Souhaitez-vous engager un elf pour "
                     "\033[38;2;0;255;0m50 mana\033[0m ?\n 1 (OUI) ou 0 (NON)");
  if (choix == 1) {
    _company.hireWorker();
  }
}

void Jeu::handleProduction() {
  std::cout << "3. Manufacturer des produits\n";
  int choix =
      choice("Souhaitez-vous changer la production?\n  1 (OUI) ou 0 (NON) ?");
  while (choix == 1) {
    reassignWorker();
    choix = choice("Souhaitez-vous continuer de changer la production?\n"
                   "1 (OUI) ou 0 (NON) ?");
  }
}

void Jeu::reassignWorker() {
  std::cout << "Quel elf voulez vous ré-affecter ? (";
  for (int i = 0; i < _company.getNbEmployees(); i++) {
    if (i != 0)
      std::cout << ", ";
    std::cout << "elf numéro " << i;
  }
  int employee_id = input(")");
  if (employee_id >= _company.getNbEmployees()) {
    std::cout << "L'employé doit être compris entre 0 et "
              << _company.getNbEmployees() - 1 << std::endl;
    return;
  }
  const std::string header =
      "| Titre                                   | Prix unitaire     | Entrée              | Sortie | Commande |";
  const std::string jobs[] = {
      "| Fabriquer une Potion ensorcelante       | \033[38;2;0;255;0m11  mana\033[0m          | 2 Poudre            | x2     | 0        |",
      "| Fabriquer une Boule de crystal          | \033[38;2;0;255;0m25  mana\033[0m          | 3 Elixir            | x1     | 1        |",
      "| Assembler une Baguette magique          | \033[38;2;0;255;0m50  mana\033[0m          | 4 Poudre, 9 Elixir  | x1     | 2        |",
      "| Assembler une Relique magique           | \033[38;2;0;255;0m70  mana\033[0m          | 2 Poudre, 13 Elixir | x1     | 3        |",
  };
  const Jobs jobs_list[] = {
      Jobs::CRAFT_POTION_ENSORCELANTE,
      Jobs::CRAFT_BOULE_CRYSTAL,
      Jobs::ASSEMBLE_BAGUETTE_MAGIQUE,
      Jobs::ASSEMBLE_RELIQUE_MAGIQUE,
  };
  std::size_t jobs_count = sizeof(jobs) / sizeof(jobs[0]);
  if (_company.getLevel() < 3) {
    jobs_count = 2;
  }
  std::cout << "Quel métier voulez vous lui donner ?" << std::endl;
  std::cout << header << "\n" << std::string(header.length(), '-') << "\n";
  for (std::size_t i = 0; i < jobs_count; i++) {
    std::cout << jobs[i] << std::endl;
  }
  int job_id = input("");
  if (job_id >= (int)jobs_count) {
    std::cout << "Le métier doit être compris entre 0 et " << jobs_count - 1
              << std::endl;
    return;
  }
  _company.getWorker()[employee_id].assignJob(jobs_list[job_id]);
}

void Jeu::endOfDay() {
  std::cout << "-------------------------------------------------------------"
               "------\n";
  _tour++;
  try {
    _company.produce();
  } catch (const char *e) {
    printBoxedText(e);
  }
  loading_screen(_dev_mode, false, "L'usine tourne à plein régime");
  int taux_impot = mini_jeu_impots();
  std::stringstream buf;
  buf << "4. Bilan du jour\n";
  buf << "\tItems produits\n";
  for (auto product : _company.getStorage()) {
    buf << "\t" << product.getQuantity() << " " << product.to_string()
        << "(s)"
        << " Prix total: " << g << product.price() << " mana" << r << std::endl;
  }
  auto revenue = _company.sellStorage();
  auto impots_dollars = revenue * taux_impot / 100;
  _company.payImpots(impots_dollars);
  auto salaries = _company.payWorkers();
  auto benefits = revenue - impots_dollars - salaries;
  buf << "Vos gains (bruts) d'aujourd'hui: " << g << revenue << " mana" << r
      << std::endl;
  buf << "Impôts = " << revenue << " * " << taux_impot << "% = " << g
      << impots_dollars << " mana" << r << "\n";
  buf << "Coût des salaire d'aujourd'hui: " << g << salaries << " mana" << r
      << std::endl;
  buf << "Vos gains (nets) d'aujourd'hui: " << g << benefits << " mana" << r
      << std::endl;
  std::cout << buf.str();
}
