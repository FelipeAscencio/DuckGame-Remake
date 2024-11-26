#include "server/protocol.h"

#include <vector>

#include <netinet/in.h>

#define CODIGO_PATO 0x05
#define CODIGO_ARMA 0x06
#define CODIGO_BALA 0x07
#define CODIGO_ARMADURA 0x08
#define CODIGO_CASCO 0x09
#define CODIGO_CAJA 0x0A
#define CODIGO_CANTIDADES 0x0B
#define CODIGO_GANADOR 0x0C
#define CODIGO_MAPA 0x0D
#define CODIGO_RONDAS_JUGADAS 0x0E
#define CODIGO_BOOL_INGAME 0x0F
#define FIN_MENSAJE 0xFE
#define FIN_COMUNICACION 0xFF

#define MOVER_DERECHA 1
#define MOVER_IZQUIERDA 2
#define AGACHARSE 3
#define MIRAR_HACIA_ARRIBA 4
#define SALTAR_O_ALETEAR 5
#define DISPARAR 6
#define AGARRAR 7
#define CUAK 8
#define CHEAT_AK 32
#define CHEAT_SG 33
#define CHEAT_MAGNUM 34
#define CHEAT_LASER 35
#define CHEAT_SNIPER 36
#define CHEAT_INMORTALIDAD 37
#define CHEAT_RECARGAR 38
#define CHEAT_ARMADUAR 39
#define CHEAT_CASCO 40
#define CHEAT_RONDAS 41

#define PRIMERA_POSICION 0
#define SEGUNDA_POSICION 1
#define TERCERA_POSICION 2
#define CUARTA_POSICION 3

ServerProtocol::Protocol::Protocol(Socket& skt): s(skt) {}

std::vector<uint8_t> separar_posicion_en_entero_y_decimal(const posicion_t& posicion) {
    std::vector<uint8_t> posiciones;
    posiciones.push_back((uint8_t)posicion.coordenada_x);  // parte entera de x
    posiciones.push_back((uint8_t)((posicion.coordenada_x - posiciones[PRIMERA_POSICION]) *
                                   TILE_A_METRO));         // parte decimal de x
    posiciones.push_back((uint8_t)posicion.coordenada_y);  // parte entera de y
    posiciones.push_back((uint8_t)((posicion.coordenada_y - posiciones[TERCERA_POSICION]) *
                                   TILE_A_METRO));  // parte decimal de y
    return posiciones;
}

std::vector<uint8_t> ServerProtocol::Protocol::serializar_pato(const InformacionPato& pato_actual) {
    std::vector<uint8_t> info;
    info.push_back(CODIGO_PATO);
    info.push_back(pato_actual.id);
    std::vector<uint8_t> posiciones_separadas =
            separar_posicion_en_entero_y_decimal(pato_actual.posicion);
    info.push_back(posiciones_separadas[PRIMERA_POSICION]);
    info.push_back(posiciones_separadas[SEGUNDA_POSICION]);
    info.push_back(posiciones_separadas[TERCERA_POSICION]);
    info.push_back(posiciones_separadas[CUARTA_POSICION]);
    info.push_back(pato_actual.vivo);
    info.push_back(pato_actual.arma);
    info.push_back(pato_actual.id_arma_equipada);
    info.push_back(pato_actual.casco);
    info.push_back(pato_actual.armadura);
    info.push_back(pato_actual.orientacion);
    info.push_back(pato_actual.estado);
    info.push_back(pato_actual.sonido);
    info.push_back(pato_actual.rondas_ganadas);
    info.push_back(FIN_MENSAJE);
    return info;
}

std::vector<uint8_t> ServerProtocol::Protocol::serializar_cantidades(
        const EstadoJuego& estado_actual) {
    std::vector<uint8_t> cantidades;
    cantidades.push_back(CODIGO_CANTIDADES);
    cantidades.push_back(estado_actual.cantidad_jugadores);
    // esto despues hay que sacar el + 1
    cantidades.push_back(estado_actual.cantidad_armas);
    cantidades.push_back(estado_actual.cantidad_balas);
    cantidades.push_back(estado_actual.cantidad_armaduras);
    cantidades.push_back(estado_actual.cantidad_cascos);
    cantidades.push_back(estado_actual.cantidad_cajas);
    cantidades.push_back(FIN_MENSAJE);
    return cantidades;
}

std::vector<uint8_t> ServerProtocol::Protocol::serializar_armas(const InformacionArma& info_arma) {
    std::vector<uint8_t> arma;
    arma.push_back(CODIGO_ARMA);
    arma.push_back(info_arma.id_arma);
    std::vector<uint8_t> posiciones_separadas =
            separar_posicion_en_entero_y_decimal(info_arma.posicion);
    arma.push_back(posiciones_separadas[PRIMERA_POSICION]);
    arma.push_back(posiciones_separadas[SEGUNDA_POSICION]);
    arma.push_back(posiciones_separadas[TERCERA_POSICION]);
    arma.push_back(posiciones_separadas[CUARTA_POSICION]);
    arma.push_back(FIN_MENSAJE);
    return arma;
}

std::vector<uint8_t> ServerProtocol::Protocol::serializar_ganador(const int& id) {
    std::vector<uint8_t> ganador;
    ganador.push_back(CODIGO_GANADOR);
    ganador.push_back(id);
    ganador.push_back(FIN_MENSAJE);
    return ganador;
}

std::vector<uint8_t> ServerProtocol::Protocol::serializar_bala(const InformacionBala& info_bala) {
    std::vector<uint8_t> bala;
    bala.push_back(CODIGO_BALA);
    bala.push_back(info_bala.id_arma);
    std::vector<uint8_t> pos = separar_posicion_en_entero_y_decimal(info_bala.pos);
    bala.push_back(pos[0]);
    bala.push_back(pos[1]);
    bala.push_back(pos[2]);
    bala.push_back(pos[3]);
    bala.push_back((uint8_t)info_bala.inclinacion);
    bala.push_back((uint8_t)info_bala.direccion);
    bala.push_back(FIN_MENSAJE);
    return bala;
}

std::vector<uint8_t> ServerProtocol::Protocol::serializar_mapa(const int& mapa) {
    std::vector<uint8_t> bytes_mapa;
    bytes_mapa.push_back(CODIGO_MAPA);
    bytes_mapa.push_back(mapa);
    bytes_mapa.push_back(FIN_MENSAJE);
    return bytes_mapa;
}

std::vector<uint8_t> ServerProtocol::Protocol::serializar_casco_o_armadura(const posicion_t& pos, bool casco){
    std::vector<uint8_t> bytes;
    uint8_t codigo = casco ? CODIGO_CASCO : CODIGO_ARMADURA;
    bytes.push_back(codigo);
    std::vector<uint8_t> posicion_separada = separar_posicion_en_entero_y_decimal(pos);
    bytes.push_back(posicion_separada[0]);
    bytes.push_back(posicion_separada[1]);
    bytes.push_back(posicion_separada[2]);
    bytes.push_back(posicion_separada[3]);
    bytes.push_back(FIN_MENSAJE);
    return bytes;
}

std::vector<uint8_t> ServerProtocol::Protocol::serializar_caja(const InformacionCaja& c){
    std::vector<uint8_t> bytes;
    std::vector<uint8_t> pos = separar_posicion_en_entero_y_decimal(c.posicion);
    bytes.push_back(CODIGO_CAJA);
    bytes.push_back(pos[0]);
    bytes.push_back(pos[1]);
    bytes.push_back(pos[2]);
    bytes.push_back(pos[3]);
    bytes.push_back(c.estado);
    bytes.push_back(FIN_MENSAJE);
    return bytes;
}

bool ServerProtocol::Protocol::_enviar(const std::vector<uint8_t>& bytes) {
    bool was_closed = false;
    s.sendall(bytes.data(), bytes.size(), &was_closed);
    return !was_closed;
}

bool ServerProtocol::Protocol::enviar(const EstadoJuego& estado_actual) {
    bool envio_correcto = _enviar(serializar_ganador(estado_actual.id_ganador));
    envio_correcto = _enviar(serializar_cantidades(estado_actual));
    envio_correcto = _enviar(serializar_mapa(estado_actual.id_mapa));
    int i = 0;
    while (i < estado_actual.cantidad_jugadores && envio_correcto) {
        envio_correcto = _enviar(serializar_pato(estado_actual.info_patos[i]));
        i++;
    }
    i = 0;
    while (i < estado_actual.cantidad_armas && envio_correcto) {
        envio_correcto = _enviar(serializar_armas(estado_actual.info_armas[i]));
        i++;
    }
    i = 0;
    while (i < estado_actual.cantidad_balas && envio_correcto) {
        envio_correcto = _enviar(serializar_bala(estado_actual.info_balas[i]));
        i++;
    }
    i = 0;
    while(i < estado_actual.cantidad_armaduras && envio_correcto){
        envio_correcto = _enviar(serializar_casco_o_armadura(estado_actual.info_armaduras[i], false));
        i++;
    }
    i = 0;
    while (i < estado_actual.cantidad_cascos && envio_correcto){
        envio_correcto = _enviar(serializar_casco_o_armadura(estado_actual.info_cascos[i], true));
        i++;
    }
    i = 0;
    while (i < estado_actual.cantidad_cajas && envio_correcto){
        envio_correcto = _enviar(serializar_caja(estado_actual.info_cajas[i]));
        i++;
    }

    std::vector<uint8_t> bytes(3);
    bytes[0] = CODIGO_RONDAS_JUGADAS;
    bytes[1] = estado_actual.rondas_jugadas;
    bytes[2] = FIN_MENSAJE;
    envio_correcto = _enviar(bytes);
    if (envio_correcto){
        bytes[0] = CODIGO_BOOL_INGAME;
        bytes[1] = estado_actual.ingame;
        envio_correcto = _enviar(bytes);
    }

    if (envio_correcto) {
        uint8_t cierre = FIN_COMUNICACION;
        bool was_closed = false;
        s.sendall(&cierre, sizeof(cierre), &was_closed);
        return !was_closed;
    } else {
        return false;
    }
}

bool ServerProtocol::Protocol::accion_valida(const uint8_t& accion) {
    return ((accion >= MOVER_DERECHA && accion <= CUAK) ||
            (accion >= CHEAT_AK && accion <= CHEAT_RONDAS));
}

bool ServerProtocol::Protocol::recibir(comando_t& cmd, const int& id_cliente) {
    bool was_closed = false;
    cmd.id_cliente = id_cliente;
    s.recvall(&(cmd.accion), sizeof(cmd.accion), &was_closed);
    return !was_closed;
}