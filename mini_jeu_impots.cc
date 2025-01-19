#include "mini_jeu_impots.hh"
#include "text_box.hh"
#include <algorithm> // For std::shuffle
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <stdio.h>
#include <string>
#include <termios.h>
#include <thread>
#include <unistd.h>
#include <vector>

using namespace std;

const int N_REELS = 5;
const int MAX_N = 101;
const char ROOFCEIL = '-';
const char WALLS = '|';

void setTerminalMode() {
  struct termios new_settings;
  tcgetattr(STDIN_FILENO, &new_settings);
  new_settings.c_lflag &= ~ICANON;
  new_settings.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}

void resetTerminalMode() {
  struct termios original_settings;
  tcgetattr(STDIN_FILENO, &original_settings);
  original_settings.c_lflag |= ICANON;
  original_settings.c_lflag |= ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &original_settings);
}

void showProgressBar(int count, int total, std::ostream &out, bool carriage_return) {
  int progress = (count * 50) / total; 
  if (carriage_return)
    out << "\r";
  out << "[";
  for (int i = 0; i < 50; ++i) {
    if (i < progress)
      out << "=";
    else
      out << " ";
  }
  out << "] " << progress * 2 << "% (" << count << "/" << total << ")";
  out.flush();
}

bool readKeyPresses() {
  const int maxCount = 100;
  int count = 0;

  setTerminalMode();

  cout << "Spammez la touche espace pour pratiquer l'évasion fiscale (Q pour quitter) :\n";
  cout << "\"On dit souvent que l'argent ne fait pas le bonheur, mais il permet de négocier un délai de paiement d'impôts !\" 🤭\n\n";

  while (count < maxCount) {
    char ch = getchar();
    if (ch == 'q' || ch == 'Q') {
      cout << '\n';
      resetTerminalMode();
      return false;
    }

    count++;
    showProgressBar(count, maxCount, std::cout, true);
  }

  cout << endl;
  resetTerminalMode();
  return true;
}

class SlotItem {
public:
  int number;
  vector<int> worth;
  string color;
  bool isWild;
  
  SlotItem() : number(0), color("\033[0m"), isWild(false) {}

  SlotItem(int number, string color = "", bool isWild = false)
      : number(number), color(color), isWild(isWild) {}

  void print() {
    const auto max_n_digit = to_string(MAX_N - 1).size();
    auto n_digit = to_string(number).size();
    cout << std::string(
        (max_n_digit - n_digit) / 2 + (max_n_digit - n_digit) % 2, ' ');
    cout << std::string((max_n_digit - n_digit) / 2, ' ');
    cout << color << number << "\033[0m";
  }
};

class Reel {
public:
  vector<SlotItem> slots;
  int relativePos;

  Reel() : relativePos(0) {}

  void addSlotItem(const SlotItem &item) { slots.push_back(item); }

  void spin(int spinAmount) {
    int n = slots.size();
    if (n == 0)
      return;

    relativePos = (relativePos + spinAmount + n) % n;
  }

  SlotItem getSlot(int row) {
    int index = (relativePos + row) % slots.size();
    return slots[index];
  }
};

class SlotMachine {
public:
  vector<Reel> reels;
  map<int, SlotItem> items;
  int rows;

  SlotMachine(int rows) : rows(rows) {}

  void addItem(const SlotItem &item) { items[item.number] = item; }

  void setupReel(size_t reelIndex, vector<int> itemNumbers) {
    if (reelIndex >= reels.size()) {
      reels.resize(reelIndex + 1);
    }

    Reel &reel = reels[reelIndex];
    reel.slots.clear();

    for (const int &number : itemNumbers) {
      if (items.find(number) != items.end()) {
        reel.addSlotItem(items[number]);
      }
    }
  }

  void spinReel(size_t reelIndex, int spinAmount) {
    if (reelIndex < reels.size()) {
      reels[reelIndex].spin(spinAmount);
    }
  }

  void display() {
    cout << "\033[2J\033[H";
    printBoxedText(
        "Avant de passer au bilan, c'est l'heure de payer vos impôts! 🏦💸\n"
        "\"Heureusement que l'humour n'est pas encore imposable, sinon on passerait tous en déficit !\" 🤣",
        "\033[38;2;0;255;0m"
    );
    cout << "\n\033[1;36m====== LES IMPÔTS ======\033[0m\n\n";
    
    const int w = to_string(MAX_N - 1).size();
    for (int row = 0; row < rows; ++row) {
      for (size_t reelIndex = 0; reelIndex < reels.size() + 1; ++reelIndex) {
        cout << std::string(w + 2, ROOFCEIL);
      }
      cout << std::string(2, ROOFCEIL);
      cout << "\n";
      if (row == rows / 2) {
        cout << "\033[48;2;0;128;0m";
      }
      cout << "| ";
      for (size_t reelIndex = 0; reelIndex < reels.size(); ++reelIndex) {
        SlotItem slot = reels[reelIndex].getSlot(row);
        slot.print();
        if (row == rows / 2) {
          cout << "\033[48;2;0;128;0m";
        }
        cout << " | ";
      }
      cout << "\n";
      cout << "\033[0m";
    }
    for (size_t reelIndex = 0; reelIndex < reels.size() + 1; ++reelIndex) {
      cout << std::string(w + 2, ROOFCEIL);
    }
    cout << std::string(2, ROOFCEIL) << '\n';
  }

  void spinAnimation(int spins = 10, int delayMs = 100) {
    for (int i = 0; i < spins; ++i) {
      for (size_t reelIndex = 0; reelIndex < reels.size(); ++reelIndex) {
        spinReel(reelIndex, 1);
      }
      display();
      this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
  }

  int score() {
    int score = 0;
    int row = rows / 2;
    cout << "Votre taux d'imposition est : (";
    for (size_t reelIndex = 0; reelIndex < reels.size(); ++reelIndex) {
      SlotItem slot = reels[reelIndex].getSlot(row);
      score += slot.number;
      cout << slot.number;
      if (reelIndex != reels.size() - 1)
        cout << " + ";
    }
    score /= 10;
    cout << ") / 10 = " << score << "% 💸\n";

    if (score < 10) {
        cout << "Félicitations, vous êtes un véritable génie fiscal! 🧠💰\n";
        cout << "À ce niveau-là, même le fisc se demande si vous existez vraiment... 🤔\n";
    } else if (score < 30) {
        cout << "Pas mal, vous avez réussi à réduire vos impôts! 🤑\n";
        cout << "On raconte que vous vous faites livrer vos factures en colissimo pour avoir plus de temps à déduire ! 📦\n";
    } else if (score < 50) {
        cout << "C'est un taux assez élevé... Dommage !\n";
        cout << "Mais ne vous inquiétez pas, un jour peut-être le gouvernement vous enverra une carte de remerciement ! 😅\n";
    } else {
        cout << "Oups, il semble que vos impôts soient très élevés... 😔\n";
        cout << "Vous payez tellement que l'État songe à vous mettre sur la liste des donateurs officiels... 💸\n";
    }
    return score;
  }
};

vector<string> createGradient(int numColors) {
  vector<string> gradient;
  if (numColors <= 0)
    return gradient;

  int startR = 255, startG = 255, startB = 255;
  int endR = 255, endG = 0, endB = 0;

  for (int i = 0; i < numColors; ++i) {

    int r = startR + (endR - startR) * i / (numColors - 1);
    int g = startG + (endG - startG) * i / (numColors - 1);
    int b = startB + (endB - startB) * i / (numColors - 1);

    ostringstream colorCode;
    colorCode << "\033[38;2;" << r << ";" << g << ";" << b << "m";

    gradient.push_back(colorCode.str());
  }

  return gradient;
}

int mini_jeu_impots() {
  srand(time(0));

  SlotMachine machine(3);
  vector<int> numbers;
  auto gradient = createGradient(MAX_N);
  for (int i = 0; i < MAX_N; ++i) {
    machine.addItem(SlotItem(i, gradient[i]));
    numbers.push_back(i);
  }

  random_device rd;
  mt19937 gen(rd());
  for (int reel = 0; reel < N_REELS; ++reel) {
    shuffle(numbers.begin(), numbers.end(), gen);
    machine.setupReel(reel, numbers);
  }

  machine.display();
  bool wants_to_play = readKeyPresses();
  int score;
  if (wants_to_play) {
    machine.spinAnimation(30, 100);
    machine.display();
    score = machine.score();
  } else {
    score = 100;
    cout << "Dommage, vous payerez 100% d'impots 🤷" << endl;
    cout << "\"Au moins, vous n'aurez plus besoin de décider quoi faire de votre argent... Le fisc le fera pour vous !\" 😆\n\n";
  }

  return score;
}
