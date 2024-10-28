#include "protocolo_cliente.h"

#define CODIGO_PATO 0x05
#define CODIGO_ARMA 0x06
#define CODIGO_BALAS 0x07
#define CODIGO_ARMADURA 0x08
#define CODIGO_CASCO 0x09
#define CODIGO_CAJA 0x0A
#define CODIGO_CANTIDADES 0x0B
#define FIN_MENSAJE 0xFE
#define FIN_COMUNICACION 0xFF

ProtocoloCliente::ProtocoloCliente(Socket& skt) : s(skt) {}

bool ProtocoloCliente::enviar(comando_t& cmd){
    bool was_closed;
    uint8_t id = cmd.id_cliente;
    s.sendall(&id, sizeof(id), &was_closed);
    if (was_closed) return false;

    uint8_t accion = cmd.accion;
    s.sendall(&accion, sizeof(accion), &was_closed);
    return !was_closed;    
}

bool ProtocoloCliente::procesar_cantidades(estado_juego_t& estado_actual){
    bool was_closed;
    uint8_t leido = 0x00;
    std::vector<uint8_t> cantidades;
    while (leido != FIN_MENSAJE){
        s.recvall(&leido, sizeof(leido), &was_closed);
        if (was_closed) break;
        cantidades.push_back(leido);
    }
    if (!was_closed){
        estado_actual.cantidad_jugadores = cantidades[0];
        estado_actual.cantidad_armas = cantidades[1];
        estado_actual.cantidad_balas = cantidades[2];
        estado_actual.cantidad_armaduras = cantidades[3];
        estado_actual.cantidad_cascos = cantidades[4];
        estado_actual.cantidad_cajas = cantidades[5];
        return true;
    } else return false;
}

bool ProtocoloCliente::procesar_patos(estado_juego_t& estado_actual){
    bool was_closed;
    uint8_t leido = 0;
    std::vector<int> info;
    while (leido != FIN_MENSAJE) {
        s.recvall(&leido, sizeof(leido), &was_closed);
        if (was_closed) break;
        info.push_back(leido);
    }
    if (!was_closed){
        posicion_t posicion(info[1], info[2]);
        informacion_pato_t pato_actual(info[0], posicion, (bool)info[3], (bool)info[4], info[5], (bool)info[6], (bool)info[7], (orientacion_e)info[8], (estado_pato_e)info[9]);
        estado_actual.agregar_info_pato(pato_actual);
        return true;
    } else return false;
}

bool ProtocoloCliente::procesar_leido(const uint8_t& leido, estado_juego_t& estado_actual){
    switch (leido)
        {
        case CODIGO_PATO:
            procesar_patos(estado_actual);
            break;
        
        case CODIGO_ARMA:
            break;
        
        case CODIGO_BALAS:
            break;
        
        case CODIGO_ARMADURA:
            break;
        
        case CODIGO_CASCO:
            break;
        
        case CODIGO_CAJA:
            break;

        case CODIGO_CANTIDADES:
            procesar_cantidades(estado_actual);
            break;
        }
}

bool ProtocoloCliente::recibir(estado_juego_t& estado_actual){
    uint8_t leido = 0x00;
    bool was_closed;
    while (leido != FIN_COMUNICACION){
        std::vector<uint8_t> datos_leidos;
        s.recvall(&leido, sizeof(leido), &was_closed);
        if (was_closed) break;
        procesar_leido(leido, estado_actual);
    }
    return !was_closed;
}


