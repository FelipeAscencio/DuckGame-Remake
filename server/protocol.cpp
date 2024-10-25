#include "protocol.h"

using namespace ServerProtocol;

#define CODIGO_PATO 0x05
#define FIN_MENSAJE 0xFF

#define MOVER_DERECHA 1
#define MOVER_IZQUIERDA 2
#define AGACHARSE 3
#define SALTAR_O_ALETEAR 4
#define DISPARAR_O_AGARRAR 5

Protocol::Protocol(Socket& skt): s(skt) {}

std::vector<uint8_t> Protocol::serializar(Pato& pato) {
    std::vector<uint8_t> informacion_pato;
    informacion_pato.push_back(CODIGO_PATO);
    informacion_pato.push_back(pato.id_jugador);
    informacion_pato.push_back(pato.posicion.coordenada_x);
    informacion_pato.push_back(pato.posicion.coordenada_y);
    informacion_pato.push_back(pato.posee_arma ? 0x01 : 0x00);
    informacion_pato.push_back(pato.arma_equipada ? pato.arma_equipada->id_arma : 0x00);
    informacion_pato.push_back(pato.posee_casco ? 0x01 : 0x00);
    informacion_pato.push_back(pato.posee_armadura ? 0x01 : 0x00);
    informacion_pato.push_back(pato.orientacion);
    informacion_pato.push_back(pato.estado_actual);
    informacion_pato.push_back(FIN_MENSAJE);
    return informacion_pato;
}

bool Protocol::enviar(std::list<Pato>& patos) {
    bool was_closed = false;
    for (Pato p: patos) {
        std::vector<uint8_t> informacion_pato = serializar(p);
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
    uint8_t id_player;
    s.recvall(&id_player, sizeof(id_player), &was_closed);
    if (was_closed)
        return false;
    uint8_t accion_leida;
    s.recvall(&accion_leida, sizeof(accion_leida), &was_closed);
    if (was_closed)
        return false;
    cmd.id_cliente = id_player;
    cmd.accion = accion_leida;
    return true;
}