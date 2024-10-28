#include "protocol.h"

using namespace ServerProtocol;

#define CODIGO_PATO 0x05
#define CODIGO_ARMA 0x06
#define CODIGO_BALA 0x07
#define CODIGO_ARMADURA 0x08
#define CODIGO_CASCO 0x09
#define CODIGO_CAJA 0x0A
#define CODIGO_CANTIDADES 0x0B
#define FIN_MENSAJE 0xFE
#define FIN_ENVIO 0xFF

#define MOVER_DERECHA 1
#define MOVER_IZQUIERDA 2
#define AGACHARSE 3
#define MIRAR_HACIA_ARRIBA 4
#define SALTAR_O_ALETEAR 5
#define DISPARAR_O_AGARRAR 6

Protocol::Protocol(Socket& skt): s(skt) {}

std::vector<uint8_t> Protocol::serializar_pato(const informacion_pato_t& pato_actual) {
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

std::vector<uint8_t> Protocol::serializar_cantidades(const estado_juego_t& estado_actual){
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

bool Protocol::enviar(const estado_juego_t& estado_actual) {
    bool was_closed = false;

    std::vector<uint8_t> cantidades = serializar_cantidades(estado_actual);
    s.sendall(cantidades.data(), cantidades.size(), &was_closed);
    
    if (was_closed) return false;
    
    for (int i = 0; i < estado_actual.cantidad_jugadores; i++) {
        std::vector<uint8_t> informacion_pato = serializar_pato(estado_actual.info_patos[i]);
        s.sendall(informacion_pato.data(), informacion_pato.size(), &was_closed);
        if (was_closed)
            break;
    }
    if (was_closed) return false;

    uint8_t cierre = FIN_ENVIO;
    s.sendall(&cierre, sizeof(cierre), &was_closed);
    return !was_closed;
}

bool Protocol::accion_valida(const uint8_t& accion) {
    return (accion >= MOVER_DERECHA && accion <= DISPARAR_O_AGARRAR);
}

bool Protocol::recibir(comando_t& cmd) {
    bool was_closed = false;
    s.recvall(&(cmd.id_cliente), sizeof(cmd.id_cliente), &was_closed);
    if (was_closed)
        return false;
    s.recvall(&(cmd.accion), sizeof(cmd.accion), &was_closed);
    return !was_closed;
}