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

    std::vector<uint8_t> cantidades(6);
    s.recvall(&leido, sizeof(leido), &was_closed);

    s.recvall(cantidades.data(), cantidades.size(), &was_closed);

    s.recvall(&leido, sizeof(leido), &was_closed);

    int i = 0;
    std::vector<uint8_t> info_pato(10);
    posicion_t pos;
    while (i < cantidades[0]) {
        s.recvall(&leido, sizeof(leido), &was_closed);  // leo codigo del pato
        s.recvall(info_pato.data(), info_pato.size(), &was_closed);
        s.recvall(&leido, sizeof(leido), &was_closed);  // leo codigo fin mensaje
        pos.set_posicion(info_pato[1], info_pato[2]);
        std::cout << pos.to_string();
        InformacionPato pato_actual(info_pato[0], pos, info_pato[3], info_pato[4], info_pato[5],
                                    info_pato[6], info_pato[7], (orientacion_e)info_pato[8],
                                    (estado_pato_e)info_pato[9]);
        estado_actual.agregar_info_pato(pato_actual);
        info_pato.clear();
        info_pato.resize(10);
        i++;
    }
    s.recvall(&leido, sizeof(leido), &was_closed);  // leo fin de comunicacion

    return !was_closed;
}
