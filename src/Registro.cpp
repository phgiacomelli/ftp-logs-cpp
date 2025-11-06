#include "../headers/Registro.h"

#include <sstream>
#include <stdexcept>

#include "utils.h"

Registro::Registro(std::string linha)
    : dataHora("0"), origemPorta(0), fileSize(0), replyCode(0)  // Inicializa padrão
{
    std::vector<std::string> campos = utils::splitTSV(linha);

    // O arquivo de log deve ter 8 campos
    if (campos.size() >= 8) {
        dataHora = DataHora(campos[0]);
        origemIP = campos[1];
        origemPorta = utils::stringToInt(campos[2]);
        comando = campos[3];
        mimeType = campos[4];
        fileSize = utils::stringToInt(campos[5]);
        replyCode = utils::stringToInt(campos[6]);
        replyMsg = campos[7];
    }
    // Se não tiver 8 campos, o objeto será criado com valores padrão
}

std::string Registro::toTSVString() const {
    std::stringstream ss;
    ss << dataHora.toString() << "\t"
       << origemIP << "\t"
       << origemPorta << "\t"
       << comando << "\t"
       << mimeType << "\t"
       << fileSize << "\t"
       << replyCode << "\t"
       << replyMsg;
    return ss.str();
}