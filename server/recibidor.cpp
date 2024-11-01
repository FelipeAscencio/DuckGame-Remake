// Copyright 2024 Axel Zielonka y Felipe Ascensio
#include "server/recibidor.h"

#include <sstream>

#include <syslog.h>

#define EXCEPCION_INESPERADA "Se produjo una excepcion inesperada: "
#define EXCEPCION_DESCONOCIDA "Se produjo una excepcion desconocida. "

Recibidor::Recibidor(Socket& s, Queue<comando_t>& q, const int& id):
        protocol(s), queue_comandos(q), vivo(true), id_cliente(id) {}

void Recibidor::run() {
    while (vivo) {
        try {
            comando_t cmd;
            if (protocol.recibir(cmd, id_cliente)) {
                if (Protocol::accion_valida(cmd.accion)) {
                    queue_comandos.push(cmd);
                }
            }
        } catch (const ClosedQueue& e) {
            syslog(LOG_INFO, "%s\n", e.what());
            break;
        } catch (std::exception& e) {
            syslog(LOG_ERR, "%s%s\n", EXCEPCION_INESPERADA, e.what());
            break;
        } catch (...) {
            syslog(LOG_ERR, "%s\n", EXCEPCION_DESCONOCIDA);
            break;
        }
    }
}

Recibidor::~Recibidor() { this->join(); }
