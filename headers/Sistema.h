#pragma once

#include <vector>
#include <string>
#include "Registro.h"
#include "Filtro.h"

class Sistema {
private:
    std::vector<Registro*> logs; 
    std::vector<Filtro*> filtros; 

    void mostrarMenu() const;
    void handleAdicionarFiltro(); 
    void handleVisualizarFiltros() const; 
    void handleVisualizarDados() const; 
    void handleLimparFiltros(); 
    void handleExportarDados() const;

    /**
     * @brief Obtém os resultados que passam por todos os filtros.
     */
    std::vector<Registro*> getResultadosFiltrados() const;

    /**
     * @brief Imprime o cabeçalho em um stream de saída (cout ou fstream).
     */
    void printHeader(std::ostream& out) const;

    /**
     * @brief Limpa a memória alocada para os filtros.
     */
    void clearFiltros();

public:
    /**
     * @brief Construtor. Recebe o nome do arquivo de log.
     * Abre e processa o arquivo, populando o vetor de logs.
     */
    Sistema(std::string arqLog);

    /**
     * @brief Destrutor. Libera toda a memória alocada dinamicamente.
     */
    ~Sistema();

    /**
     * @brief Inicia a execução do loop principal do menu.
     */
    void executar();
};