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
#define CODIGO_ESTADO_JUEGO 0X0C
#define CODIGO_PUNTAJES 0x0D
#define CODIGO_POSICIONES 0x0E
#define FIN_MENSAJE 0xFE
#define FIN_COMUNICACION 0xFF

#define MOVER_DERECHA 1
#define MOVER_IZQUIERDA 2
#define AGACHARSE 3
#define MIRAR_HACIA_ARRIBA 4
#define SALTAR_O_ALETEAR 5
#define DISPARAR 6
#define AGARRAR 7

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
    info.push_back(FIN_MENSAJE);
    return info;
}

std::vector<uint8_t> ServerProtocol::Protocol::serializar_cantidades(
        const EstadoJuego& estado_actual) {
    std::vector<uint8_t> cantidades;
    cantidades.push_back(CODIGO_CANTIDADES);
    cantidades.push_back(estado_actual.cantidad_jugadores);
    //esto despues hay que sacar el + 1
    cantidades.push_back(estado_actual.cantidad_armas + 1);
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

std::vector<uint8_t> ServerProtocol::Protocol::serializar_estado_juego(const estado_actual_juego_e& estado){
    std::vector<uint8_t> estado_juego;
    estado_juego.push_back(CODIGO_ESTADO_JUEGO);
    estado_juego.push_back((uint8_t)estado);
    estado_juego.push_back(FIN_MENSAJE);
    return estado_juego;
}

std::vector<uint8_t> ServerProtocol::Protocol::serializar_puntajes(const std::vector<int>& puntajes){
    std::vector<uint8_t> puntajes_jugadores;
    puntajes_jugadores.push_back(CODIGO_PUNTAJES);
    for (auto& i : puntajes){
        puntajes_jugadores.push_back(i);
    }
    puntajes_jugadores.push_back(FIN_MENSAJE);
    return puntajes_jugadores;
}

std::vector<uint8_t> ServerProtocol::Protocol::serializar_rango_posiciones(const float& xmax, const float& xmin, const float& ymax, const float& ymin){
    std::vector<uint8_t> posiciones;
    posicion_t max(xmax, ymax);
    posicion_t min(xmin, ymin);
    std::vector<uint8_t> max_separada = separar_posicion_en_entero_y_decimal(max);
    std::vector<uint8_t> min_separada = separar_posicion_en_entero_y_decimal(min);
    posiciones.push_back(CODIGO_POSICIONES);
    posiciones.push_back(max_separada[0]);
    posiciones.push_back(max_separada[1]);
    posiciones.push_back(max_separada[2]);
    posiciones.push_back(max_separada[3]);
    posiciones.push_back(min_separada[0]);
    posiciones.push_back(min_separada[1]);
    posiciones.push_back(min_separada[2]);
    posiciones.push_back(min_separada[3]);
    posiciones.push_back(FIN_MENSAJE);
    return posiciones;
}

bool ServerProtocol::Protocol::_enviar(const std::vector<uint8_t>& bytes) {
    bool was_closed = false;
    s.sendall(bytes.data(), bytes.size(), &was_closed);
    return !was_closed;
}

bool ServerProtocol::Protocol::enviar(const EstadoJuego& estado_actual) {
    std::vector<uint8_t> cantidades = serializar_cantidades(estado_actual);
    bool envio_correcto = _enviar(cantidades);
    int i = 0;
    while (i < estado_actual.cantidad_jugadores && envio_correcto) {
        std::vector<uint8_t> pato_actual = serializar_pato(estado_actual.info_patos[i]);
        envio_correcto = _enviar(pato_actual);
        i++;
    }
    i = 0;
    while (i < estado_actual.cantidad_armas && envio_correcto) {
        std::vector<uint8_t> arma_actual = serializar_armas(estado_actual.info_armas[i]);
        envio_correcto = _enviar(arma_actual);
        i++;
    }
    //// aca hay que agregar la logica para enviar las armas, balas, armaduras, etc.
    
    std::vector<uint8_t> estado = serializar_estado_juego(estado_actual.estado_juego);
    envio_correcto = _enviar(estado);
    if (!envio_correcto) return false;
    if (estado_actual.estado_juego != INGAME){
        std::vector<uint8_t> puntajes = serializar_puntajes(estado_actual.puntajes);
        envio_correcto = _enviar(puntajes);    
    }

    std::vector<uint8_t> rango_posiciones = serializar_rango_posiciones(estado_actual.x_maximo, estado_actual.x_minimo, estado_actual.y_maximo, estado_actual.y_minimo);
    envio_correcto = _enviar(rango_posiciones);

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
    return (accion >= MOVER_DERECHA && accion <= AGARRAR);
}

bool ServerProtocol::Protocol::recibir(comando_t& cmd, const int& id_cliente) {
    bool was_closed = false;
    cmd.id_cliente = id_cliente;
    s.recvall(&(cmd.accion), sizeof(cmd.accion), &was_closed);
    return !was_closed;
}
