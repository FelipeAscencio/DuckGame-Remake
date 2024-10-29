// Copyright 2024 Axel Zielonka y Felipe Ascensio
#include "server/protocol.h"

#include <vector>

using namespace ServerProtocol;

#define CODIGO_PATO 0x05
#define CODIGO_ARMA 0x06
#define CODIGO_BALA 0x07
#define CODIGO_ARMADURA 0x08
#define CODIGO_CASCO 0x09
#define CODIGO_CAJA 0x0A
#define CODIGO_CANTIDADES 0x0B
#define FIN_MENSAJE 0xFE
#define FIN_COMUNICACION 0xFF

#define MOVER_DERECHA 1
#define MOVER_IZQUIERDA 2
#define AGACHARSE 3
#define MIRAR_HACIA_ARRIBA 4
#define SALTAR_O_ALETEAR 5
#define DISPARAR_O_AGARRAR 6

Protocol::Protocol(Socket& skt): s(skt) {}

std::vector<uint8_t> Protocol::serializar_pato(const InformacionPato& pato_actual) {
    std::vector<uint8_t> info;
    info.push_back(CODIGO_PATO);
    info.push_back(pato_actual.id);
    info.push_back(pato_actual.posicion.coordenada_x);
    info.push_back(pato_actual.posicion.coordenada_y);
    info.push_back(pato_actual.vivo);
    info.push_back(pato_actual.arma);
    info.push_back(pato_actual.id_arma_equipada);
    info.push_back(pato_actual.casco);
    info.push_back(pato_actual.armadura);
    info.push_back(pato_actual.orientacion);
    info.push_back(pato_actual.estado);
    info.push_back(FIN_MENSAJE);
    return info;
}

std::vector<uint8_t> Protocol::serializar_cantidades(const EstadoJuego& estado_actual) {
    std::vector<uint8_t> cantidades;
    cantidades.push_back(CODIGO_CANTIDADES);
    cantidades.push_back(estado_actual.cantidad_jugadores);
    cantidades.push_back(estado_actual.cantidad_armas);
    cantidades.push_back(estado_actual.cantidad_balas);
    cantidades.push_back(estado_actual.cantidad_armaduras);
    cantidades.push_back(estado_actual.cantidad_cascos);
    cantidades.push_back(estado_actual.cantidad_cajas);
    cantidades.push_back(FIN_MENSAJE);
    return cantidades;
}

bool Protocol::_enviar(const std::vector<uint8_t>& bytes) {
    bool was_closed = false;
    s.sendall(bytes.data(), bytes.size(), &was_closed);
    return !was_closed;
}

bool Protocol::enviar(const EstadoJuego& estado_actual) {
    std::vector<uint8_t> cantidades = serializar_cantidades(estado_actual);
    bool envio_correcto = _enviar(cantidades);
    int i = 0;
    while (i < estado_actual.cantidad_jugadores && envio_correcto) {
        std::vector<uint8_t> pato_actual = serializar_pato(estado_actual.info_patos[i]);
        envio_correcto = _enviar(pato_actual);
        i++;
    }
    // aca hay que agregar la logica para enviar las armas, balas, armaduras, etc.
    if (envio_correcto) {
        uint8_t cierre = FIN_COMUNICACION;
        bool was_closed = false;
        s.sendall(&cierre, sizeof(cierre), &was_closed);
        return !was_closed;
    } else {
        return false;
    }
}

bool Protocol::accion_valida(const uint8_t& accion) {
    return (accion >= MOVER_DERECHA && accion <= DISPARAR_O_AGARRAR);
}

bool Protocol::recibir(comando_t& cmd, const int& id_cliente) {
    bool was_closed = false;
    cmd.id_cliente = id_cliente;
    s.recvall(&(cmd.accion), sizeof(cmd.accion), &was_closed);
    return !was_closed;
}
