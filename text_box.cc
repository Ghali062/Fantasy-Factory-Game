#include "text_box.hh"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Fonction pour calculer la largeur d'affichage d'une chaîne (compatible UTF-8)
size_t getDisplayWidth(const std::string &line) {
  size_t width = 0;
  for (size_t i = 0; i < line.length();) {
    unsigned char ch = line[i];
    size_t charLen;

    // \033[38;2;0;255;0m

    // Déterminer le nombre d'octets dans le caractère actuel
    if ((ch & 0x80) == 0) {
      charLen = 1; // ASCII 1 octet
      width += 1;  // Largeur simple
    } else if ((ch & 0xE0) == 0xC0) {
      charLen = 2; // UTF-8 2 octets
      width += 1;  // Largeur simple
    } else if ((ch & 0xF0) == 0xE0) {
      charLen = 3; // UTF-8 3 octets
      width += 1;  // Largeur simple
    } else if ((ch & 0xF8) == 0xF0) {
      charLen = 4; // UTF-8 4 octets
      width += 2;  // Largeur double (par exemple, emoji, CJK)
    } else {
      throw std::runtime_error("Encodage UTF-8 invalide détecté");
    }
    if (ch == '\033' && line[i + 1] == '[' && line[i + 2] == '3' &&
        line[i + 3] == '8') {
      width -= 8;
    }
    if (ch == '\033' && line[i + 1] == '[' && line[i + 2] == '3' &&
        line[i + 3] == '2') {
      width += 1;
    }

    i += charLen; // Passer au caractère suivant
  }
  return width;
}

void printBoxedText(const std::string &text, const std::string &color,
                    std::size_t padding_x, std::size_t padding_y,
                    std::size_t margin_x, std::size_t margin_y) {

  std::cout << color;

  // Diviser le texte en lignes
  std::vector<std::string> lines;
  std::istringstream stream(text);
  std::string line;
  size_t maxLength = 0;

  while (std::getline(stream, line)) {
    lines.push_back(line);
    size_t displayWidth = getDisplayWidth(line);
    if (displayWidth > maxLength) {
      maxLength = displayWidth;
    }
  }

  // Déterminer la largeur de la boîte (y compris le padding)
  size_t boxWidth = maxLength + 4 + padding_x;

  for (std::size_t i = 0; i < margin_y; i++) {
    std::cout << std::endl;
  }
  std::string floor_ceil = "";
  for (std::size_t i = 0; i < boxWidth - 2; i++) {
    floor_ceil += "─";
  }

  for (std::size_t i = 0; i < margin_x; i++) {
    std::cout << " ";
  }
  // Imprimer la bordure supérieure
  std::cout << "╭" << floor_ceil << "╮" << std::endl;

  for (std::size_t i = 0; i < padding_y; i++) {
    for (std::size_t i = 0; i < margin_x; i++) {
      std::cout << " ";
    }
    std::cout << "│ " << std::string((maxLength + padding_x), ' ') << " │"
              << std::endl;
  }

  // Imprimer chaque ligne de texte
  for (const auto &l : lines) {
    for (std::size_t i = 0; i < margin_x; i++) {
      std::cout << " ";
    }
    size_t displayWidth = getDisplayWidth(l);
    auto a = maxLength - displayWidth + padding_x;
    for (auto c : l) {
      if (c == '\e')
        a += 6;
    }
    std::cout << "│ " << std::string(a / 2, ' ') << l;
    for (auto c : l) {
      if (c == '\e')
        a += 1;
    }

    if (a % 2 == 1)
      a++;
    // Ajouter des espaces de padding si la ligne est plus courte que la longueur maximale
    std::cout << std::string(a / 2, ' ') << " │" << std::endl;
  }
  for (std::size_t i = 0; i < padding_y; i++) {
    for (std::size_t i = 0; i < margin_x; i++) {
      std::cout << " ";
    }
    std::cout << "│ " << std::string((maxLength + padding_x), ' ') << " │"
              << std::endl;
  }

  for (std::size_t i = 0; i < margin_x; i++) {
    std::cout << " ";
  }
  // Imprimer la bordure inférieure
  std::cout << "╰" << floor_ceil << "╯" << std::endl;
  for (std::size_t i = 0; i < margin_y; i++) {
    std::cout << std::endl;
  }
  std::cout << "\e[0m";
}
