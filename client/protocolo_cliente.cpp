// Copyright 2024 Axel Zielonka y Felipe Ascensio
#include "client/protocolo_cliente.h"

#include <vector>

#define CODIGO_PATO 0x05
#define CODIGO_ARMA 0x06
#define CODIGO_BALA 0x07
#define CODIGO_ARMADURA 0x08
#define CODIGO_CASCO 0x09
#define CODIGO_CAJA 0x0A
#define CODIGO_CANTIDADES 0x0B
#define FIN_MENSAJE 0xFE
#define FIN_COMUNICACION 0xFF

ProtocoloCliente::ProtocoloCliente(Socket& skt): s(skt) {
    bool closed = false;
    s.recvall(&id_cliente, sizeof(id_cliente), &closed);
    if (closed)
        throw ErrorConstructor();
}

bool ProtocoloCliente::enviar(const uint8_t& accion) {
    bool was_closed = false;
    s.sendall(&accion, sizeof(accion), &was_closed);
    return !was_closed;
}

bool ProtocoloCliente::procesar_cantidades(EstadoJuego& estado_actual) {
    bool was_closed = false;
    uint8_t leido = 0x00;
    std::vector<uint8_t> cantidades;
    while (leido != FIN_MENSAJE && !was_closed) {
        s.recvall(&leido, sizeof(leido), &was_closed);
        if (!was_closed)
            cantidades.push_back(leido);
    }

    if (!was_closed) {
        estado_actual.cantidad_jugadores = cantidades[0];
        estado_actual.cantidad_armas = cantidades[1];
        estado_actual.cantidad_balas = cantidades[2];
        estado_actual.cantidad_armaduras = cantidades[3];
        estado_actual.cantidad_cascos = cantidades[4];
        estado_actual.cantidad_cajas = cantidades[5];
        return true;
    } else {
        return false;
    }
}

bool ProtocoloCliente::procesar_patos(EstadoJuego& estado_actual) {
    bool was_closed = false;
    uint8_t leido = 0x00;
    std::vector<uint8_t> info;
    while (leido != FIN_MENSAJE && !was_closed) {
        s.recvall(&leido, sizeof(leido), &was_closed);
        if (!was_closed)
            info.push_back(leido);
    }

    if (!was_closed) {
        posicion_t posicion(info[1], info[2]);
        InformacionPato pato(info[0], posicion, static_cast<bool>(info[3]),
                             static_cast<bool>(info[4]), info[5], static_cast<bool>(info[6]),
                             static_cast<bool>(info[7]), static_cast<orientacion_e>(info[8]),
                             static_cast<estado_pato_e>(info[9]));
        estado_actual.agregar_info_pato(pato);
        return true;
    } else {
        return false;
    }
}

bool ProtocoloCliente::procesar_leido(const uint8_t& leido, EstadoJuego& estado_actual) {
    bool resultado = false;
    switch (leido) {
        case CODIGO_PATO:
            resultado = procesar_patos(estado_actual);
            break;

        case CODIGO_ARMA:
            break;

        case CODIGO_BALA:
            break;

        case CODIGO_ARMADURA:
            break;

        case CODIGO_CASCO:
            break;

        case CODIGO_CAJA:
            break;

        case CODIGO_CANTIDADES:
            resultado = procesar_cantidades(estado_actual);
            break;

        default:
            resultado = false;
            break;
    }
    return resultado;
}

bool ProtocoloCliente::recibir(EstadoJuego& estado_actual) {
    uint8_t leido = 0x00;
    bool was_closed = false;
    while (leido != FIN_COMUNICACION && !was_closed) {
        s.recvall(&leido, sizeof(leido), &was_closed);
        if (!was_closed)
            was_closed = procesar_leido(leido, estado_actual);
    }
    return !was_closed;
}
