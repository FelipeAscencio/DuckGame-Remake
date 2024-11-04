#include "client/protocolo_cliente.h"

#include <map>
#include <vector>

#define CERO 0
#define SEIS 6
#define BYTE_NULO 0x00
#define PRIMERA_POSICION 0
#define SEGUNDA_POSICION 1
#define TERCERA_POSICION 2
#define CUARTA_POSICION 3
#define QUINTA_POSICION 4
#define SEXTA_POSICION 5
#define SEPTIMA_POSICION 6
#define OCTAVA_POSICION 7
#define NOVENA_POSICION 8
#define DECIMA_POSICION 9
#define DECIMO_PRIMERA_POSICION 11
#define DECIMO_SEGUNDA_POSICION 12
#define TAMANIO_INFO_PATOS 10

#define ACCION_DERECHA 0x01
#define ACCION_IZQUIERDA 0x02
#define ACCION_AGACHARSE 0x03
#define ACCION_ARRIBA 0x04
#define ACCION_SALTO 0x05
#define ACCION_DISPARAR 0x06
#define ACCION_AGARRAR 0x07

#define DERECHA 'D'
#define IZQUIERDA 'A'
#define ARRIBA 'W'
#define AGACHARSE 'S'
#define SALTO ' '
#define DISPARO 'J'
#define AGARRAR 'K'

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
        {ARRIBA, ACCION_ARRIBA},   {SALTO, ACCION_SALTO},         {DISPARO, ACCION_DISPARAR}, {AGARRAR, ACCION_AGARRAR}};

ProtocoloCliente::ProtocoloCliente(Socket& skt): s(skt) {
    bool closed = false;
    s.recvall(&id_cliente, sizeof(id_cliente), &closed);
    if (closed)
        throw ErrorConstructor();
}

uint8_t ProtocoloCliente::parsear_comando(char accion) {
    std::map<char, uint8_t>::iterator it = acciones.find(accion);
    if (it == acciones.end())
        return CERO;
    else
        return acciones.at(accion);
}

bool ProtocoloCliente::enviar(const char& accion) {
    bool was_closed = false;
    uint8_t comando = parsear_comando(accion);
    if (comando == CERO)
        return false;

    s.sendall(&comando, sizeof(comando), &was_closed);
    return !was_closed;
}

bool ProtocoloCliente::procesar_cantidades(EstadoJuego& estado_actual) {
    bool was_closed = false;
    uint8_t leido = BYTE_NULO;
    std::vector<uint8_t> cantidades;
    while (leido != FIN_MENSAJE && !was_closed) {
        s.recvall(&leido, sizeof(leido), &was_closed);
        if (!was_closed)
            cantidades.push_back(leido);
    }

    if (!was_closed) {
        estado_actual.cantidad_jugadores = cantidades[PRIMERA_POSICION];
        estado_actual.cantidad_armas = cantidades[SEGUNDA_POSICION];
        estado_actual.cantidad_balas = cantidades[TERCERA_POSICION];
        estado_actual.cantidad_armaduras = cantidades[CUARTA_POSICION];
        estado_actual.cantidad_cascos = cantidades[QUINTA_POSICION];
        estado_actual.cantidad_cajas = cantidades[SEXTA_POSICION];
        return true;
    } else {
        return false;
    }
}

bool ProtocoloCliente::procesar_patos(EstadoJuego& estado_actual) {
    bool was_closed = false;
    uint8_t leido = BYTE_NULO;
    std::vector<uint8_t> info;
    while (leido != FIN_MENSAJE && !was_closed) {
        s.recvall(&leido, sizeof(leido), &was_closed);
        if (!was_closed)
            info.push_back(leido);
    }

    if (!was_closed) {
        float x, y;
        x = info[SEGUNDA_POSICION] + (info[TERCERA_POSICION]/TILE_A_METRO);
        y = info[CUARTA_POSICION] + (info[QUINTA_POSICION]/TILE_A_METRO);
        posicion_t posicion(x,y);
        InformacionPato pato(info[PRIMERA_POSICION], posicion, static_cast<bool>(info[SEXTA_POSICION]),
                             static_cast<bool>(info[SEPTIMA_POSICION]), info[OCTAVA_POSICION], static_cast<bool>(info[NOVENA_POSICION]),
                             static_cast<bool>(info[DECIMA_POSICION]), static_cast<orientacion_e>(info[DECIMO_PRIMERA_POSICION]),
                             static_cast<estado_pato_e>(info[DECIMO_SEGUNDA_POSICION]));
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
        x = info[SEGUNDA_POSICION] + (info[TERCERA_POSICION]/TILE_A_METRO);
        y = info[CUARTA_POSICION] + (info[QUINTA_POSICION]/TILE_A_METRO);
        InformacionArma arma_nueva(info[PRIMERA_POSICION], x, y);
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
    uint8_t leido = BYTE_NULO;
    bool was_closed = false;

    while (leido != FIN_COMUNICACION && !was_closed) {
        s.recvall(&leido, sizeof(leido), &was_closed);
        if (!was_closed)
            was_closed = procesar_leido(leido, estado_actual);
    }
    return !was_closed;
}
