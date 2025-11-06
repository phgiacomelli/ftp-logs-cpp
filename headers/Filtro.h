#pragma once

#include <sstream>
#include <string>

#include "DataHora.h"
#include "Registro.h"
#include "utils.h"

/**
 * @brief Classe base abstrata para todos os filtros.
 */
class Filtro {
   public:
    virtual ~Filtro() {}
    /**
     * @brief Testa se um registro passa neste filtro.
     * @return true se o registro satisfaz o filtro, false caso contrário.
     */
    virtual bool test(const Registro* r) const = 0;

    /**
     * @brief Retorna uma descrição do filtro para visualização.
     */
    virtual std::string toString() const = 0;
};


class FiltroDataHora : public Filtro {
   private:
    std::string isoStart;
    std::string isoEnd;

   public:
    FiltroDataHora(const std::string& s, const std::string& e)
        : isoStart(s), isoEnd(e) {}

    bool test(const Registro* r) const override {
        std::string registroIso = r->getDataHora().toString();

        bool depoisDoInicio = (registroIso >= isoStart);
        bool antesDoFim = (registroIso <= isoEnd);

        return (depoisDoInicio && antesDoFim);
    }

    std::string toString() const override {
        return "Data/Hora entre [" + isoStart + "] e [" + isoEnd + "]";
    }
};

class FiltroIP : public Filtro {
   private:
    std::string ip;

   public:
    FiltroIP(const std::string& s) : ip(s) {}
    bool test(const Registro* r) const override {
        return r->getOrigemIP() == ip;
    }
    std::string toString() const override {
        return "IP Origem == [" + ip + "]";
    }
};

class FiltroPorta : public Filtro {
   private:
    int start, end;

   public:
    FiltroPorta(int s, int e) : start(s), end(e) {}
    bool test(const Registro* r) const override {
        return r->getOrigemPorta() >= start && r->getOrigemPorta() <= end;
    }
    std::string toString() const override {
        return "Porta Origem entre [" + std::to_string(start) + "] e [" + std::to_string(end) + "]";
    }
};

class FiltroComando : public Filtro {
   private:
    std::string comando;

   public:
    FiltroComando(const std::string& s) : comando(s) {}
    bool test(const Registro* r) const override {
        return r->getComando() == comando;
    }
    std::string toString() const override {
        return "Comando == [" + comando + "]";
    }
};

class FiltroMimeType : public Filtro {
   private:
    std::string substring;

   public:
    FiltroMimeType(const std::string& s) : substring(s) {}
    bool test(const Registro* r) const override {
        return utils::containsCaseInsensitive(r->getMimeType(), substring);
    }
    std::string toString() const override {
        return "Mime Type contém (i) [" + substring + "]";
    }
};

class FiltroFileSize : public Filtro {
   private:
    int start, end;

   public:
    FiltroFileSize(int s, int e) : start(s), end(e) {}
    bool test(const Registro* r) const override {
        return r->getFileSize() >= start && r->getFileSize() <= end;
    }
    std::string toString() const override {
        return "File Size entre [" + std::to_string(start) + "] e [" + std::to_string(end) + "]";
    }
};

class FiltroReplyCode : public Filtro {
   private:
    int code;

   public:
    FiltroReplyCode(int c) : code(c) {}
    bool test(const Registro* r) const override {
        return r->getReplyCode() == code;
    }
    std::string toString() const override {
        return "Reply Code == [" + std::to_string(code) + "]";
    }
};

class FiltroReplyMsg : public Filtro {
   private:
    std::string substring;

   public:
    FiltroReplyMsg(const std::string& s) : substring(s) {}
    bool test(const Registro* r) const override {
        return utils::containsCaseInsensitive(r->getReplyMsg(), substring);
    }
    std::string toString() const override {
        return "Reply Message contém (i) [" + substring + "]";
    }
};