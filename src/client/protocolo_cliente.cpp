#include "client/protocolo_cliente.h"

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
#define ACCION_CUAK 0x08
#define ACCION_AK 0x20
#define ACCION_SG 0x21
#define ACCION_MAGNUM 0x22
#define ACCION_LASER 0x23
#define ACCION_SNIPER 0x24
#define ACCION_INMORTALIDAD 0x25
#define ACCION_RECARGAR 0x26
#define ACCION_ARMADUAR 0x27
#define ACCION_CASCO 0x28

#define DERECHA 'D'
#define IZQUIERDA 'A'
#define ARRIBA 'W'
#define AGACHARSE 'S'
#define SALTO ' '
#define DISPARO 'J'
#define AGARRAR 'K'
#define CUAK 'C'
#define CHEAT_AK '1'
#define CHEAT_SG '2'
#define CHEAT_MAGNUM '3'
#define CHEAT_LASER '4'
#define CHEAT_SNIPER '5'
#define CHEAT_INMORTALIDAD 'I'
#define CHEAT_RECARGAR 'R'
#define CHEAT_ARMADURA 'L'
#define CHEAT_CASCO 'P'

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
        {ARRIBA, ACCION_ARRIBA},   {SALTO, ACCION_SALTO},         {DISPARO, ACCION_DISPARAR},
        {AGARRAR, ACCION_AGARRAR}, {CUAK, ACCION_CUAK}, {CHEAT_AK, ACCION_AK}, {CHEAT_SG, ACCION_SG},
        {CHEAT_MAGNUM, ACCION_MAGNUM}, {CHEAT_LASER, ACCION_LASER}, {CHEAT_SNIPER, ACCION_SNIPER}, 
        {CHEAT_INMORTALIDAD, ACCION_INMORTALIDAD}, {CHEAT_RECARGAR, ACCION_RECARGAR}, {CHEAT_ARMADURA, ACCION_ARMADUAR},
        {CHEAT_CASCO, ACCION_CASCO}};

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
        if (!was_closed) {
            cantidades.push_back(leido);
        }
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
        x = info[SEGUNDA_POSICION] + (info[TERCERA_POSICION] / TILE_A_METRO);
        y = info[CUARTA_POSICION] + (info[QUINTA_POSICION] / TILE_A_METRO);
        posicion_t posicion(x, y);
        InformacionPato pato(
                info[PRIMERA_POSICION], posicion, static_cast<bool>(info[SEXTA_POSICION]),
                static_cast<bool>(info[SEPTIMA_POSICION]), info[OCTAVA_POSICION],
                static_cast<bool>(info[NOVENA_POSICION]), static_cast<bool>(info[DECIMA_POSICION]),
                static_cast<orientacion_e>(info[DECIMO_PRIMERA_POSICION]),
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
        x = info[SEGUNDA_POSICION] + (info[TERCERA_POSICION] / TILE_A_METRO);
        y = info[CUARTA_POSICION] + (info[QUINTA_POSICION] / TILE_A_METRO);
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

    return !resultado;
}

bool ProtocoloCliente::recibir(EstadoJuego& estado_actual) {
    uint8_t leido = BYTE_NULO;
    bool was_closed = false;
    std::vector<uint8_t> cantidades(SEIS);
    s.recvall(&leido, sizeof(leido), &was_closed);
    s.recvall(cantidades.data(), cantidades.size(), &was_closed);
    s.recvall(&leido, sizeof(leido), &was_closed);
    int i = 0;
    std::vector<uint8_t> info_pato(12);
    while (i < cantidades[PRIMERA_POSICION]) {
        s.recvall(&leido, sizeof(leido), &was_closed);  // Lee codigo del pato.
        s.recvall(info_pato.data(), info_pato.size(), &was_closed);
        s.recvall(&leido, sizeof(leido), &was_closed);  // Lee codigo fin mensaje.
        float x = info_pato[1] + (info_pato[2] / TILE_A_METRO);
        float y = info_pato[3] + (info_pato[4] / TILE_A_METRO);
        posicion_t pos(x, y);
        InformacionPato pato_actual(info_pato[0], pos, info_pato[5], info_pato[6], info_pato[7],
                                    info_pato[8], info_pato[9], (orientacion_e)info_pato[10],
                                    (estado_pato_e)info_pato[11]);
        estado_actual.agregar_info_pato(pato_actual);
        info_pato.clear();
        info_pato.resize(12);
        i++;
    }
    i = 0;
    std::vector<uint8_t> info_arma(5);
    while (i < cantidades[1]) {
        s.recvall(&leido, sizeof(leido), &was_closed);
        s.recvall(info_arma.data(), info_arma.size(), &was_closed);
        s.recvall(&leido, sizeof(leido), &was_closed);

        float x = info_arma[1] + (info_arma[2] / TILE_A_METRO);
        float y = info_arma[3] + (info_arma[4] / TILE_A_METRO);
        posicion_t pos(x, y);
        InformacionArma arma_actual(info_arma[0], pos);
        estado_actual.agregar_arma(arma_actual);
        info_arma.clear();
        info_arma.resize(5);
        i++;
    }

    s.recvall(&leido, sizeof(leido), &was_closed);  // Lee el fin de  la comunicacion.
    return !was_closed;
}