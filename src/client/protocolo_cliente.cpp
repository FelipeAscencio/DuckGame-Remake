#include "client/protocolo_cliente.h"

#define MENOS_UNO -1
#define CERO 0
#define UNO 1
#define DOS 2
#define TRES 3
#define CUATRO 4
#define CINCO 5
#define SEIS 6
#define SIETE 7
#define OCHO 8
#define NUEVE 9
#define DIEZ 10
#define ONCE 11
#define DOCE 12
#define TRECE 13
#define CATORCE 14

#define BYTE_NULO 0x00
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
#define ACCION_RONDAS 0x29

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
#define CHEAT_RONDAS 'Z'

// 'Mapa' que encapsula todas las acciones posibles del juego recibidas en el 'Protocolo'.
static std::map<char, uint8_t> acciones = {{DERECHA, ACCION_DERECHA},
                                           {IZQUIERDA, ACCION_IZQUIERDA},
                                           {AGACHARSE, ACCION_AGACHARSE},
                                           {ARRIBA, ACCION_ARRIBA},
                                           {SALTO, ACCION_SALTO},
                                           {DISPARO, ACCION_DISPARAR},
                                           {AGARRAR, ACCION_AGARRAR},
                                           {CUAK, ACCION_CUAK},
                                           {CHEAT_AK, ACCION_AK},
                                           {CHEAT_SG, ACCION_SG},
                                           {CHEAT_MAGNUM, ACCION_MAGNUM},
                                           {CHEAT_LASER, ACCION_LASER},
                                           {CHEAT_SNIPER, ACCION_SNIPER},
                                           {CHEAT_INMORTALIDAD, ACCION_INMORTALIDAD},
                                           {CHEAT_RECARGAR, ACCION_RECARGAR},
                                           {CHEAT_ARMADURA, ACCION_ARMADUAR},
                                           {CHEAT_CASCO, ACCION_CASCO},
                                           {CHEAT_RONDAS, ACCION_RONDAS}};

ProtocoloCliente::ProtocoloCliente(Socket& skt): s(skt), id_cliente(MENOS_UNO) {}

bool ProtocoloCliente::recibir_mensaje_bienvenida(std::string& msj){
    uint16_t size;
    bool was_closed = false;
    s.recvall(&size, sizeof(size), &was_closed);
    if (was_closed) return false;
    size = ntohs(size);
    std::vector<uint8_t> bytes(size);
    s.recvall(bytes.data(), bytes.size(), &was_closed);
    if (was_closed) return false;
    msj.clear();
    for (uint8_t b: bytes){
        msj += (char)b;
    }

    return true;
}

bool ProtocoloCliente::enviar_respuesta(const uint8_t& rta){
    bool was_closed = false;
    uint8_t aux = rta;
    s.sendall(&aux, sizeof(aux), &was_closed);
    return !was_closed;
}

bool ProtocoloCliente::recibir_id(){
    bool was_closed = false;
    s.recvall(&id_cliente, sizeof(id_cliente), &was_closed);
    return !was_closed;
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

bool ProtocoloCliente::enviar_codigo_partida(const std::string& codigo){
    std::vector<uint8_t> bytes;
    for(char c: codigo){
        bytes.push_back(toascii(c));
    }
    
    bool was_closed = false;
    s.sendall(bytes.data(), bytes.size(), &was_closed);
    return !was_closed;
}

bool ProtocoloCliente::recibir(EstadoJuego& estado_actual) {
    uint8_t leido = BYTE_NULO;
    bool was_closed = false;

    // Recibe el 'id_ganador' de la partida.
    s.recvall(&leido, sizeof(leido), &was_closed);
    s.recvall(&leido, sizeof(leido), &was_closed);
    estado_actual.id_ganador = leido;
    s.recvall(&leido, sizeof(leido), &was_closed);

    std::vector<uint8_t> cantidades(SEIS);
    s.recvall(&leido, sizeof(leido), &was_closed);
    s.recvall(cantidades.data(), cantidades.size(), &was_closed);
    s.recvall(&leido, sizeof(leido), &was_closed);

    // Recibe el 'id' del mapa de la partida.
    s.recvall(&leido, sizeof(leido), &was_closed);
    s.recvall(&leido, sizeof(leido), &was_closed);
    estado_actual.id_mapa = leido;
    s.recvall(&leido, sizeof(leido), &was_closed);

    // Recibe la 'informacion de los patos' de la partida.
    int i = CERO;
    std::vector<uint8_t> info_pato(CATORCE);
    while (i < cantidades[CERO]) {
        s.recvall(&leido, sizeof(leido), &was_closed);  // Lee codigo del pato.
        s.recvall(info_pato.data(), info_pato.size(), &was_closed);
        s.recvall(&leido, sizeof(leido), &was_closed);  // Lee codigo fin mensaje.
        float x = info_pato[UNO] + (info_pato[DOS] / TILE_A_METRO);
        float y = info_pato[TRES] + (info_pato[CUATRO] / TILE_A_METRO);
        posicion_t pos(x, y);
        InformacionPato pato_actual(info_pato[CERO], pos, info_pato[CINCO], info_pato[SEIS],
                                    info_pato[SIETE], info_pato[OCHO], info_pato[NUEVE],
                                    (orientacion_e)info_pato[DIEZ], (estado_pato_e)info_pato[ONCE],
                                    (sonido_e)info_pato[DOCE], info_pato[TRECE]);
        estado_actual.agregar_info_pato(pato_actual);
        info_pato.clear();
        info_pato.resize(CATORCE);
        i++;
    }

    // Recibe la 'informacion de las armas spawneadas' de la partida.
    i = CERO;
    std::vector<uint8_t> info_arma(CINCO);
    while (i < cantidades[UNO]) {
        s.recvall(&leido, sizeof(leido), &was_closed);
        s.recvall(info_arma.data(), info_arma.size(), &was_closed);
        s.recvall(&leido, sizeof(leido), &was_closed);
        float x = info_arma[UNO] + (info_arma[DOS] / TILE_A_METRO);
        float y = info_arma[TRES] + (info_arma[CUATRO] / TILE_A_METRO);
        posicion_t pos(x, y);
        InformacionArma arma_actual(info_arma[CERO], pos);
        estado_actual.agregar_arma(arma_actual);
        info_arma.clear();
        info_arma.resize(CINCO);
        i++;
    }

    // Recibe la 'informacion de las balas' de la partida.
    i = CERO;
    std::vector<uint8_t> bala(SIETE);
    while (i < cantidades[DOS]) {
        s.recvall(&leido, sizeof(leido), &was_closed);
        s.recvall(bala.data(), bala.size(), &was_closed);
        s.recvall(&leido, sizeof(leido), &was_closed);
        float x = bala[UNO] + (bala[DOS] / TILE_A_METRO);
        float y = bala[TRES] + (bala[CUATRO] / TILE_A_METRO);
        posicion_t pos(x, y);
        InformacionBala nueva(bala[CERO], pos, (inclinacion_e)bala[CINCO],
                              (orientacion_e)bala[SEIS]);
        estado_actual.agregar_bala(nueva);
        bala.clear();
        bala.resize(SIETE);
        i++;
    }

    // Recibe la 'informacion de las armaduras spawneadas' de la partida.
    i = CERO;
    std::vector<uint8_t> armadura(CUATRO);
    while (i < cantidades[TRES]) {
        s.recvall(&leido, sizeof(leido), &was_closed);
        s.recvall(armadura.data(), armadura.size(), &was_closed);
        s.recvall(&leido, sizeof(leido), &was_closed);
        float x = armadura[CERO] + (armadura[UNO] / TILE_A_METRO);
        float y = armadura[DOS] + (armadura[TRES] / TILE_A_METRO);
        estado_actual.agregar_armadura(posicion_t(x, y));
        armadura.clear();
        armadura.resize(CUATRO);
        i++;
    }

    // Recibe la 'informacion de los cascos spawneados' de la partida.
    i = CERO;
    std::vector<uint8_t> casco(CUATRO);
    while (i < cantidades[CUATRO]) {
        s.recvall(&leido, sizeof(leido), &was_closed);
        s.recvall(casco.data(), casco.size(), &was_closed);
        s.recvall(&leido, sizeof(leido), &was_closed);
        float x = casco[CERO] + (casco[UNO] / TILE_A_METRO);
        float y = casco[DOS] + (casco[TRES] / TILE_A_METRO);
        estado_actual.agregar_casco(posicion_t(x, y));
        casco.clear();
        casco.resize(CUATRO);
        i++;
    }

    // Recibe la 'informacion de las cajas' de la partida.
    i = CERO;
    std::vector<uint8_t> caja(CINCO);
    while (i < cantidades[CINCO]) {
        s.recvall(&leido, sizeof(leido), &was_closed);
        s.recvall(caja.data(), caja.size(), &was_closed);
        s.recvall(&leido, sizeof(leido), &was_closed);
        float x = caja[CERO] + (caja[UNO] / TILE_A_METRO);
        float y = caja[DOS] + (caja[TRES] / TILE_A_METRO);
        InformacionCaja c(posicion_t(x, y), (damage_e)caja[CUATRO]);
        estado_actual.agregar_caja(c);
        caja.clear();
        caja.resize(CINCO);
        i++;
    }

    // Recibe la 'cantidad de rondas jugadas' de la partida.
    s.recvall(&leido, sizeof(leido), &was_closed);
    s.recvall(&leido, sizeof(leido), &was_closed);
    estado_actual.rondas_jugadas = leido;
    s.recvall(&leido, sizeof(leido), &was_closed);

    // Recibe el 'estado' de la partida.
    s.recvall(&leido, sizeof(leido), &was_closed);
    s.recvall(&leido, sizeof(leido), &was_closed);
    estado_actual.ingame = (bool)leido;
    s.recvall(&leido, sizeof(leido), &was_closed);

    // Lee el fin de la comunicacion del protocolo.
    s.recvall(&leido, sizeof(leido), &was_closed);
    return !was_closed;
}
