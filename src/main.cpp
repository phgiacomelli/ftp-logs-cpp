#include <iostream>
#include <string>

#include "../headers/Sistema.h"

int main() {
    std::string nomeArquivoLog;
    std::cout << "Digite o nome do arquivo de log (ex: log.tsv): ";
    std::getline(std::cin, nomeArquivoLog);

    try {
        Sistema sistema(nomeArquivoLog);
        sistema.executar();
    } catch (...) {
        std::cerr << "Um erro desconhecido ocorreu." << std::endl;
        return 1;
    }

    return 0;
}