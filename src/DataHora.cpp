#include "../headers/DataHora.h"

#include <iomanip>
#include <sstream>
#include <stdexcept>

DataHora::DataHora(std::string timestampStr) {
    try {
        timestamp = std::stol(timestampStr);  // Converte string para long
    } catch (...) {
        timestamp = 0;  // Valor padrão em caso de erro
    }
}

DataHora::DataHora() : timestamp(0) {}

std::string DataHora::toString() const {
    std::stringstream ss;
    // Converte time_t para struct tm (em UTC/GMT)
    ss << std::put_time(std::gmtime(&timestamp), "%Y-%m-%dT%H:%M:%S");
    return ss.str();
}

int DataHora::compare(const DataHora& dth) const {
    if (timestamp < dth.timestamp) return -1;
    if (timestamp > dth.timestamp) return 1;
    return 0;
}
