#include "../headers/Sistema.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

Sistema::Sistema(std::string arqLog) {
    std::ifstream arquivo(arqLog);

    if (!arquivo.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo de log: " << arqLog << std::endl;
        return;
    }

    std::string linha;
    // Pula a linha do cabeçalho
    std::getline(arquivo, linha);

    while (std::getline(arquivo, linha)) {
        if (!linha.empty()) {
            logs.push_back(new Registro(linha));
        }
    }

    arquivo.close();
    std::cout << "Log processado. " << logs.size() << " registros carregados." << std::endl;
}

Sistema::~Sistema() {
    // Libera a memória dos Registros
    for (Registro* r : logs) {
        delete r;
    }

    // Libera a memória dos Filtros
    clearFiltros();
}

void Sistema::executar() {
    int opcao = 0;
    do {
        mostrarMenu();
        std::cout << "Escolha uma opcao: ";

        while (!(std::cin >> opcao)) {
            std::cout << "Opcao invalida. Digite um numero: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Limpa o buffer do cin

        switch (opcao) {
            case 1:
                handleAdicionarFiltro();
                break;
            case 2:
                handleVisualizarFiltros();
                break;
            case 3:
                handleVisualizarDados();
                break;
            case 4:
                handleLimparFiltros();
                break;
            case 5:
                handleExportarDados();
                break;
            case 0:
                std::cout << "Saindo..." << std::endl;
                break;
            default:
                std::cout << "Opcao invalida! Tente novamente." << std::endl;
        }
    } while (opcao != 0);
}

void Sistema::mostrarMenu() const {
    std::cout << "\n--- MENU PRINCIPAL ---" << std::endl;
    std::cout << "1. Adicionar filtro" << std::endl;
    std::cout << "2. Visualizar filtros" << std::endl;
    std::cout << "3. Visualizar dados" << std::endl;
    std::cout << "4. Limpar filtros" << std::endl;
    std::cout << "5. Exportar dados" << std::endl;
    std::cout << "0. Sair" << std::endl;
}

void Sistema::handleAdicionarFiltro() {
    int tipoFiltro;
    std::cout << "\n--- Adicionar Filtro ---" << std::endl;
    std::cout << "1. Data e Hora (ISO 8601)" << std::endl;
    std::cout << "2. IP" << std::endl;
    std::cout << "3. Porta (intervalo)" << std::endl;
    std::cout << "4. Comando" << std::endl;
    std::cout << "5. Mime Type (substring)" << std::endl;
    std::cout << "6. File Size (intervalo)" << std::endl;
    std::cout << "7. Reply Code (exato)" << std::endl;
    std::cout << "8. Reply Message (substring)" << std::endl;
    std::cout << "0. Voltar" << std::endl;
    std::cout << "Selecione o tipo de filtro: ";

    while (!(std::cin >> tipoFiltro)) {
        std::cout << "Opcao invalida. Digite um numero: ";
        std::cin.clear(); // limpa flags do cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpa o buffer
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string sVal1, sVal2;
    int iVal1, iVal2;

    switch (tipoFiltro) {
        case 1:
            std::cout << "Data/Hora inicial (YYYY-MM-DDThh:mm:ss): ";
            std::getline(std::cin, sVal1);
            std::cout << "Data/Hora final (YYYY-MM-DDThh:mm:ss): ";
            std::getline(std::cin, sVal2);
            filtros.push_back(new FiltroDataHora(sVal1, sVal2));
            break;
        case 2:
            std::cout << "IP (exato): ";
            std::getline(std::cin, sVal1);
            filtros.push_back(new FiltroIP(sVal1));
            break;
        case 3:
            std::cout << "Porta inicial: ";
            std::cin >> iVal1;
            std::cout << "Porta final: ";
            std::cin >> iVal2;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            filtros.push_back(new FiltroPorta(iVal1, iVal2));
            break;
        case 4:
            std::cout << "Comando (exato): ";
            std::getline(std::cin, sVal1);
            filtros.push_back(new FiltroComando(sVal1));
            break;
        case 5:
            std::cout << "Mime Type (substring, case-insensitive): ";
            std::getline(std::cin, sVal1);
            filtros.push_back(new FiltroMimeType(sVal1));
            break;
        case 6:
            std::cout << "Tamanho inicial: ";
            std::cin >> iVal1;
            std::cout << "Tamanho final: ";
            std::cin >> iVal2;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            filtros.push_back(new FiltroFileSize(iVal1, iVal2));
            break;
        case 7:
            std::cout << "Reply Code (exato): ";
            std::cin >> iVal1;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            filtros.push_back(new FiltroReplyCode(iVal1));
            break;
        case 8:
            std::cout << "Reply Message (substring, case-insensitive): ";
            std::getline(std::cin, sVal1);
            filtros.push_back(new FiltroReplyMsg(sVal1));
            break;
        case 0:
            return;
        default:
            std::cout << "Tipo de filtro invalido." << std::endl;
            return;
    }
    std::cout << "Filtro adicionado!" << std::endl;
}

void Sistema::handleVisualizarFiltros() const {
    std::cout << "\n--- Filtros Ativos ---" << std::endl;
    if (filtros.empty()) {
        std::cout << "Nenhum filtro aplicado!" << std::endl;
    } else {
        for (const Filtro* f : filtros) {
            std::cout << "- " << f->toString() << std::endl;
        }
    }
}

void Sistema::handleVisualizarDados() const {
    std::vector<Registro*> resultados = getResultadosFiltrados();

    std::cout << "\n--- Visualizacao de Dados ---" << std::endl;
    printHeader(std::cout);

    for (const Registro* r : resultados) {
        std::cout << r->toTSVString() << std::endl;
    }

    std::cout << "---" << std::endl;
    std::cout << "Total de registros selecionados: " << resultados.size() << std::endl;
}

void Sistema::handleLimparFiltros() {
    clearFiltros();
    std::cout << "Filtros limpos." << std::endl;
}

void Sistema::handleExportarDados() const {
    std::string nomeArquivo;
    std::cout << "Digite o nome do arquivo para exportacao (ex: export.tsv): ";
    std::getline(std::cin, nomeArquivo);

    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro: Nao foi possivel criar o arquivo " << nomeArquivo << std::endl;
        return;
    }

    std::vector<Registro*> resultados = getResultadosFiltrados();

    printHeader(arquivo);
    for (const Registro* r : resultados) {
        arquivo << r->toTSVString() << std::endl;
    }

    arquivo.close();
    std::cout << resultados.size() << " registros exportados para " << nomeArquivo << std::endl;
}

std::vector<Registro*> Sistema::getResultadosFiltrados() const {
    std::vector<Registro*> resultados;

    // Itera sobre todos os logs
    for (Registro* r : logs) {
        bool passaEmTodos = true;

        // Testa contra todos os filtros
        for (const Filtro* f : filtros) {
            if (!f->test(r)) {
                passaEmTodos = false;
                break;  // Se falhar em um, não precisa testar os outros
            }
        }

        if (passaEmTodos) {
            resultados.push_back(r);
        }
    }
    return resultados;
}

void Sistema::printHeader(std::ostream& out) const {
    out << "timestamp_iso" << "\t"
        << "ip" << "\t"
        << "port" << "\t"
        << "command" << "\t"
        << "mime_type" << "\t"
        << "file_size" << "\t"
        << "reply_code" << "\t"
        << "reply_msg" << std::endl;
}

void Sistema::clearFiltros() {
    for (Filtro* f : filtros) {
        delete f;  // free em cada filtro
    }
    filtros.clear();  // free no vetor de ponteiros
}