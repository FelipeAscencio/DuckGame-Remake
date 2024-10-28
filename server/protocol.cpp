#include "protocol.h"

using namespace ServerProtocol;

#define CODIGO_PATO 0x05
#define FIN_MENSAJE 0xFF

#define MOVER_DERECHA 1
#define MOVER_IZQUIERDA 2
#define AGACHARSE 3
#define MIRAR_HACIA_ARRIBA 4
#define SALTAR_O_ALETEAR 5
#define DISPARAR_O_AGARRAR 6

Protocol::Protocol(Socket& skt): s(skt) {}

std::vector<uint8_t> Protocol::serializar(const EstadoJuego& estado_actual, int indice) {
    std::vector<uint8_t> informacion_pato;
    informacion_pato.push_back(CODIGO_PATO);
    informacion_pato.push_back(estado_actual.id_jugadores[indice]);
    informacion_pato.push_back(estado_actual.posiciones[indice].coordenada_x);
    informacion_pato.push_back(estado_actual.posiciones[indice].coordenada_y);
    informacion_pato.push_back((uint8_t)estado_actual.poseen_armas[indice]);
    if (estado_actual.armas_equipadas[indice]) {
        informacion_pato.push_back(estado_actual.armas_equipadas[indice]->obtener_id());
    } else {
        informacion_pato.push_back(0x00);
    }
    informacion_pato.push_back((uint8_t)estado_actual.cascos_equipados[indice]);
    informacion_pato.push_back((uint8_t)estado_actual.armaduras_equipadas[indice]);
    informacion_pato.push_back(estado_actual.orientaciones[indice]);
    informacion_pato.push_back(estado_actual.estados_patos[indice]);
    informacion_pato.push_back(FIN_MENSAJE);
    return informacion_pato;
}

bool Protocol::enviar(const EstadoJuego& estado_actual) {
    bool was_closed = false;
    for (int i = 0; i < estado_actual.cantidad_jugadores; i++) {
        std::vector<uint8_t> informacion_pato = serializar(estado_actual, i);
        s.sendall(informacion_pato.data(), informacion_pato.size(), &was_closed);
        if (was_closed)
            break;
    }
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