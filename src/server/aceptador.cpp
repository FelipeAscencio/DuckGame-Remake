#include "aceptador.h"

#define EXCEPCION_INESPERADA "Se produjo una excepcion inesperada: "
#define EXCEPCION_DESCONOCIDA "Se produjo una excepcion desconocida. "
#define MENSAJE_INICIAL                                                                           \
    "Bienvenido a una nueva partida de DuckGame. Desea crear una nueva partida (1) o ingresar a " \
    "una ya existente (2)?"

#define CERO 0
#define RW_CLOSE 2
#define VALOR_DUMMY 0xCC
#define NUEVA_PARTIDA 0x01
#define UNIRSE_A_PARTIDA 0x02
#define ID_INGRESO_INVALIDO \
    9  // 'ID' invalido, que le avisa al cliente que no existe la partida a la que quiere ingresar.
#define TAMANIO_CODIGO_PARTIDA 6
#define CONSTANTE_CASTEO_CODIGO 0x30

Aceptador::Aceptador(const char* servname, std::vector<Partida*>& partidas_en_juego):
        skt(servname), aceptando_jugadores(true), partidas(partidas_en_juego) {}

void Aceptador::crear_nueva_partida(Socket& peer) {
    bool codigo_valido;
    std::string codigo;
    do {
        codigo = Partida::generar_codigo();
        size_t i = CERO;
        codigo_valido = true;
        while (i < partidas.size()) {
            if (codigo == partidas[i]->get_codigo()) {
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

bool Aceptador::loop_ingreso_partida_usuario(Socket& peer) {
    while (true) {
        std::string codigo;
        std::vector<uint8_t> bytes(TAMANIO_CODIGO_PARTIDA);
        bool was_closed = false;
        peer.recvall(bytes.data(), bytes.size(), &was_closed);
        if (was_closed) {
            aceptando_jugadores = false;
            return false;
        }

        codigo = std::accumulate(bytes.begin(), bytes.end(), std::string(),
                         [](const std::string& acc, uint8_t c) {
                             return acc + std::to_string(c - CONSTANTE_CASTEO_CODIGO);
                         });

        bool partida_existente = false;
        size_t i = CERO;
        while (i < partidas.size()) {
            if (partidas[i]->get_codigo() == codigo) {
                partidas[i]->agregar_jugador(std::move(peer));
                return true;
            }

            i++;
        }

        
        int valor_dummy = ID_INGRESO_INVALIDO;
        peer.sendall(&valor_dummy, sizeof(valor_dummy), &was_closed);
        if (was_closed) {
            aceptando_jugadores = false;
            return false;
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
            if (respuesta_cliente == NUEVA_PARTIDA) {
                crear_nueva_partida(peer);
            } else {
                if (!loop_ingreso_partida_usuario(peer)) {
                    break;
                }
            }
        } catch (const LibError& e) {
            if (aceptando_jugadores) {
                syslog(LOG_ERR, "%s%s\n", EXCEPCION_INESPERADA, e.what());
            }

            break;
        } catch (...) {
            syslog(LOG_ERR, "%s\n", EXCEPCION_DESCONOCIDA);
            break;
        }
    }
}

bool Aceptador::recibir_respuesta_cliente(uint8_t& rta, Socket& s) {
    bool was_closed = false;
    s.recvall(&rta, sizeof(rta), &was_closed);
    if (was_closed || (rta != NUEVA_PARTIDA && rta != UNIRSE_A_PARTIDA))
        return false;
    return true;
}

bool Aceptador::enviar_mensaje_inicial(Socket& s, const std::string& mensaje) {
    uint16_t size = mensaje.size();
    size = htons(size);
    bool was_closed = false;
    s.sendall(&size, sizeof(size), &was_closed);
    if (was_closed)
        return false;
    std::vector<uint8_t> bytes;
    for (size_t i = CERO; i < mensaje.size(); i++) {
        bytes.push_back(toascii(mensaje[i]));
    }

    s.sendall(bytes.data(), bytes.size(), &was_closed);
    return !was_closed;
}

void Aceptador::dejar_de_aceptar() {
    this->aceptando_jugadores = false;
    try {
        this->skt.shutdown(RW_CLOSE);
        this->skt.close();
    } catch (const LibError& e) {}
}

Aceptador::~Aceptador() {
    try {
        skt.shutdown(RW_CLOSE);
        skt.close();
    } catch (const LibError& e) {}
}
