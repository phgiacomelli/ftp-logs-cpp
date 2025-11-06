#pragma once

#include <string>
#include <vector>

#include "DataHora.h"

class Registro {
   private:
    DataHora dataHora;
    std::string origemIP;
    int origemPorta;
    std::string comando;
    std::string mimeType;
    int fileSize;
    int replyCode;
    std::string replyMsg;

   public:
    /**
     * @brief Construtor que recebe uma linha TSV do log e a interpreta.
     */
    Registro(std::string linha);

    /**
     * @brief Retorna uma string formatada (TSV) do registro.
     * Útil para visualização e exportação.
     */
    std::string toTSVString() const;

    const DataHora& getDataHora() const { return dataHora; }
    const std::string& getOrigemIP() const { return origemIP; }
    int getOrigemPorta() const { return origemPorta; }
    const std::string& getComando() const { return comando; }
    const std::string& getMimeType() const { return mimeType; }
    int getFileSize() const { return fileSize; }
    int getReplyCode() const { return replyCode; }
    const std::string& getReplyMsg() const { return replyMsg; }
};