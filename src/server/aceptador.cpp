#include "aceptador.h"

#include <utility>
#include <vector>

#include <syslog.h>
#include <netinet/in.h>
#include "../common/liberror.h"

#define EXCEPCION_ESPERADA "Se produjo una excepcion esperada: "
#define EXCEPCION_INESPERADA "Se produjo una excepcion inesperada: "
#define EXCEPCION_DESCONOCIDA "Se produjo una excepcion desconocida. "
#define CERO 0
#define MAX_CLIENTES_POR_PARTIDA 8
#define RW_CLOSE 2
#define VALOR_DUMMY 0xCC
#define MENSAJE_INICIAL "Bienvenido a una nueva partida de DuckGame. Desea crear una nueva partida (1) o ingresar a una ya existente (2)?"
#define NUEVA_PARTIDA 0x01
#define UNIRSE_A_PARTIDA 0x02
#define ID_INGRESO_INVALIDO 9 // 'ID' invalido, que le avisa al cliente que no existe la partida a la que quiere ingresar.

Aceptador::Aceptador(const char* servname, std::vector<Partida*>& partidas_en_juego):
        skt(servname), aceptando_jugadores(true), partidas(partidas_en_juego) {}

void Aceptador::crear_nueva_partida(Socket& peer){
    bool codigo_valido;
    std::string codigo;
    do {
        codigo = Partida::generar_codigo();
        size_t i = 0;
        codigo_valido = true;
        while (i < partidas.size()){
            if (codigo == partidas[i]->get_codigo()){
                codigo_valido = false;
                break;
            }
            i++;
        }
    } while (!codigo_valido);

    enviar_mensaje_inicial(peer, codigo);
    Partida* nueva_partida = new Partida(codigo);
    nueva_partida->agregar_jugador(std::move(peer));
    partidas.push_back(nueva_partida);
}

bool Aceptador::loop_ingreso_partida_usuario(Socket& peer){
    while (true){
        std::string codigo;
        std::vector<uint8_t> bytes(6);
        bool was_closed = false;
        peer.recvall(bytes.data(), bytes.size(), &was_closed);
        if (was_closed){
            aceptando_jugadores = false;
            return false;
        }

        for (uint8_t c: bytes){
            codigo += std::to_string(c - 0x30);
        }

        bool partida_existente = false;
        size_t i = 0;
        while (i < partidas.size() && !partida_existente){
            if (partidas[i]->get_codigo() == codigo){
                partidas[i]->agregar_jugador(std::move(peer));
                partida_existente = true;
                return true;
            }

            i++;
        }

        if (!partida_existente){
            bool was_closed = false;
            int valor_dummy = ID_INGRESO_INVALIDO;
            peer.sendall(&valor_dummy, sizeof(valor_dummy), &was_closed);
            if (was_closed){
                aceptando_jugadores = false;
                return false;
            }
        }
    }
}

void Aceptador::run() {
    while (aceptando_jugadores) {
        try {
            Socket peer = skt.accept();
            enviar_mensaje_inicial(peer, MENSAJE_INICIAL);
            uint8_t respuesta_cliente;
            recibir_respuesta_cliente(respuesta_cliente, peer);
            if (respuesta_cliente == NUEVA_PARTIDA){
                crear_nueva_partida(peer);
            } else {
                if (!loop_ingreso_partida_usuario(peer)){
                    break;
                }
            }
            // recolectar();
        } catch (const LibError& e) {
            if (!aceptando_jugadores) {
                // syslog(LOG_INFO, "%s%s. No hay clientes esperando a ser aceptados\n",
                //        EXCEPCION_ESPERADA, e.what());
            } else {
                syslog(LOG_ERR, "%s%s\n", EXCEPCION_INESPERADA, e.what());
            }

            break;
        } catch (...) {
            syslog(LOG_ERR, "%s\n", EXCEPCION_DESCONOCIDA);
            break;
        }
    }
}

bool Aceptador::recibir_respuesta_cliente(uint8_t& rta, Socket& s){
    bool was_closed = false;
    s.recvall(&rta, sizeof(rta), &was_closed);
    if (was_closed || (rta != NUEVA_PARTIDA && rta != UNIRSE_A_PARTIDA)) return false;
    return true;
}

bool Aceptador::enviar_mensaje_inicial(Socket& s, const std::string& mensaje){
    uint16_t size = mensaje.size();
    size = htons(size);
    bool was_closed = false;
    s.sendall(&size, sizeof(size), &was_closed);
    if (was_closed) return false;
    std::vector<uint8_t> bytes;
    for(size_t i = 0; i < mensaje.size(); i++){
        bytes.push_back(toascii(mensaje[i]));
    }

    s.sendall(bytes.data(), bytes.size(), &was_closed);
    return !was_closed;
}

void Aceptador::dejar_de_aceptar(){
    this->aceptando_jugadores = false;
    try {
        this->skt.shutdown(RW_CLOSE);
        this->skt.close();
    } catch (const LibError& e){}
}

// void Aceptador::eliminar_cliente(ThreadUsuario* jugador) {
//     jugador->cortar_conexion();
//     int id = jugador->get_id();
//     queues_clientes.eliminar_queue(id);
//     delete jugador;
// }

// void Aceptador::recolectar() {
//     for (size_t i = 0; i < partidas.size(); i++){
//         partidas[i]->buscar_jugadores_desconectados();
//         if (!partidas[i]->en_curso())
//             partidas[i]->terminar_partida();
//     }
// }

Aceptador::~Aceptador() {
    try {
        skt.shutdown(RW_CLOSE);
        skt.close();
    } catch (const LibError& e){}
    // this->join();
}
