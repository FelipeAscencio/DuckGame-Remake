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

ClientMock::ClientMock(const char* hostname, const char* servname):
        s(hostname, servname),
        protocolo(s),
        id(protocolo.id_cliente),
        queue_enviador(),
        queue_recibidor(),
        e(protocolo, queue_enviador, id),
        r(protocolo, queue_recibidor) {}

void ClientMock::loop_juego() {
    while (true) {
        EstadoJuego estado_actual;
        if (queue_recibidor.try_pop(estado_actual)) {
            std::cout << estado_actual.to_string();
        }
    }
}

void ClientMock::start() {
    r.start();
    e.start();
    loop_juego();
}

ClientMock::~ClientMock() {
    e.dejar_de_enviar();
    r.dejar_de_recibir();
}
