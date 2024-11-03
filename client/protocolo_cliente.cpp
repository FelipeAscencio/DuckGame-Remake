// Copyright 2024 Axel Zielonka y Felipe Ascensio
#include "client/protocolo_cliente.h"

#include <map>
#include <vector>

#define ACCION_DERECHA 0x01
#define ACCION_IZQUIERDA 0x02
#define ACCION_AGACHARSE 0x03
#define ACCION_ARRIBA 0x04
#define ACCION_SALTO 0x05
#define ACCION_DISPARAR 0x06

#define DERECHA 'D'
#define IZQUIERDA 'A'
#define ARRIBA 'W'
#define AGACHARSE 'S'
#define SALTO ' '
#define DISPARO 'C'

#define CODIGO_PATO 0x05
#define CODIGO_ARMA 0x06
#define CODIGO_BALA 0x07
#define CODIGO_ARMADURA 0x08
#define CODIGO_CASCO 0x09
#define CODIGO_CAJA 0x0A
#define CODIGO_CANTIDADES 0x0B
#define FIN_MENSAJE 0xFE
#define FIN_COMUNICACION 0xFF

static std::map<char, uint8_t> acciones = {
        {DERECHA, ACCION_DERECHA}, {IZQUIERDA, ACCION_IZQUIERDA}, {AGACHARSE, ACCION_AGACHARSE},
        {ARRIBA, ACCION_ARRIBA},   {SALTO, ACCION_SALTO},         {DISPARO, ACCION_DISPARAR}};

// ProtocoloCliente::ProtocoloCliente(const char* hostname, const char* servname):
//         s(hostname, servname) {
//     bool closed = false;
//     s.recvall(&id_cliente, sizeof(id_cliente), &closed);
//     if (closed)
//         throw ErrorConstructor();
// }

ProtocoloCliente::ProtocoloCliente(Socket& skt): s(skt) {
    bool closed = false;
    s.recvall(&id_cliente, sizeof(id_cliente), &closed);
    if (closed)
        throw ErrorConstructor();
}


uint8_t ProtocoloCliente::parsear_comando(char accion) {
    std::map<char, uint8_t>::iterator it = acciones.find(accion);
    if (it == acciones.end())
        return 0;
    else
        return acciones.at(accion);
}

bool ProtocoloCliente::enviar(const char& accion) {
    bool was_closed = false;
    uint8_t comando = parsear_comando(accion);
    if (comando == 0)
        return false;
    s.sendall(&comando, sizeof(comando), &was_closed);
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
        float x, y;
        x = info[1] + (info[2]/TILE_A_METRO);
        y = info[3] + (info[4]/TILE_A_METRO);
        posicion_t posicion(x,y);
        InformacionPato pato(info[0], posicion, static_cast<bool>(info[5]),
                             static_cast<bool>(info[6]), info[7], static_cast<bool>(info[8]),
                             static_cast<bool>(info[9]), static_cast<orientacion_e>(info[10]),
                             static_cast<estado_pato_e>(info[11]));
        estado_actual.agregar_info_pato(pato);
        return true;
    } else {
        return false;
    }
}

bool ProtocoloCliente::procesar_armas(EstadoJuego& estado_actual) {
    bool was_closed = false;
    uint8_t leido = 0x00;
    std::vector<uint8_t> info;
    while (leido != FIN_MENSAJE && !was_closed) {
        s.recvall(&leido, sizeof(leido), &was_closed);
        if (!was_closed)
            info.push_back(leido);
    }
    if (!was_closed) {
        float x, y;
        x = info[1] + (info[2]/TILE_A_METRO);
        y = info[3] + (info[4]/TILE_A_METRO);
        InformacionArma arma_nueva(info[0], x, y);
        estado_actual.agregar_arma(arma_nueva);
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
            resultado = procesar_armas(estado_actual);
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
