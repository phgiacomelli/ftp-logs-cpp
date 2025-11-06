#pragma once

#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

namespace utils {

/**
 * @brief Divide uma string com base em um delimitador (tab, no caso).
 * @param s String a ser dividida.
 * @return Um vetor de strings contendo os campos.
 */
inline std::vector<std::string> splitTSV(const std::string& s) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, '\t')) {
        result.push_back(item);
    }
    return result;
}

/**
 * @brief Converte uma string para inteiro, tratando o hífen "-" como 0.
 * @param s String a ser convertida.
 * @param defaultVal Valor a ser retornado se a string for "-" ou inválida.
 * @return O valor inteiro.
 */
inline int stringToInt(const std::string& s, int defaultVal = 0) {
    if (s == "-") {
        return defaultVal;
    }
    try {
        return std::stoi(s);
    } catch (...) {
        return defaultVal;
    }
}

/**
 * @brief Converte uma string para maiúsculas.
 */
inline std::string toUpper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return s;
}

/**
 * @brief Verifica se a string 'a' contém a string 'b' (case-insensitive).
 * @param a String principal.
 * @param b Substring a ser procurada.
 * @return true se 'a' contém 'b', false caso contrário.
 */
inline bool containsCaseInsensitive(const std::string& a, const std::string& b) {
    if (b.empty()) {
        return true;
    }
    return toUpper(a).find(toUpper(b)) != std::string::npos;
}

} 