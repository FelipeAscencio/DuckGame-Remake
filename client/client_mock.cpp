#include "client_mock.h"

#include <algorithm>
#include <string>
#include <vector>

static std::vector<char> acciones_validas = {'A', 'D', 'S', 'W', ' ', 'C'};

struct MismaLetra {
    char letra;
    explicit MismaLetra(char c): letra(c) {}
    bool operator()(const char& c) { return letra == c; }
};

ClientMock::ClientMock(const char* hostname, const char* servname): protocolo(hostname, servname) {}

char ClientMock::leer_entrada() {
    char leido = '.';
    std::cin >> leido;
    while (std::none_of(acciones_validas.cbegin(), acciones_validas.cend(), MismaLetra(leido))) {
        std::cin >> leido;
    }
    return leido;
}

bool ClientMock::realizar_accion(const char& accion) { return protocolo.enviar(accion); }

bool ClientMock::recibir_respuesta_juego(EstadoJuego& estado_actual) {
    return protocolo.recibir(estado_actual);
}

void ClientMock::loop_juego() {
    bool loop = true;
    EstadoJuego estado;
    recibir_respuesta_juego(estado);
    std::cout << estado.to_string() << std::endl;
    while (loop) {
        char accion = leer_entrada();
        loop = realizar_accion(accion);
        if (loop) {
            recibir_respuesta_juego(estado);
            std::cout << estado.to_string() << std::endl;
        }
    }
}

void ClientMock::start() { loop_juego(); }
