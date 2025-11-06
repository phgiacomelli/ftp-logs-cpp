#pragma once

#include <ctime>
#include <string>

class DataHora {
   private:
    // Armazena o timestamp POSIX como um time_t (numérico)
    std::time_t timestamp;

   public:
    /**
     * @brief Construtor que recebe um timestamp POSIX no formato string.
     */
    DataHora(std::string timestampStr);

    /**
     * @brief Construtor padrão.
     */
    DataHora();

    /**
     * @brief Retorna a data/hora no formato ISO 8601 (YYYY-MM-DDThh:mm:ss).
     */
    std::string toString() const;

    /**
     * @brief Compara este objeto DataHora com outro[cite: 45].
     * @return 0 se igual, < 0 se this for menor, > 0 se this for maior.
     */
    int compare(const DataHora& dth) const;

    std::time_t getTimestamp() const { return timestamp; }
};
