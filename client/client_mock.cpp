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

ClientMock::ClientMock(const char* hostname, const char* servname) : s(hostname, servname), protocolo(s), id(protocolo.id_cliente), queue_enviador(), queue_recibidor(), e(protocolo, queue_enviador, id), r(protocolo, queue_recibidor) {}

char ClientMock::leer_entrada() {
    std::string linea = ".";
    while (std::none_of(acciones_validas.cbegin(), acciones_validas.cend(), MismaLetra(linea[0]))) {
        std::getline(std::cin, linea);
    }
    return linea[0];
}

bool ClientMock::realizar_accion(const char& accion) { return protocolo.enviar(accion); }

bool ClientMock::recibir_respuesta_juego(EstadoJuego& estado_actual) {
    return protocolo.recibir(estado_actual);
}

void ClientMock::loop_juego() {
    EstadoJuego estado_inicial;
    recibir_respuesta_juego(estado_inicial);
    // if (!primer_contacto) return;

    std::cout << estado_inicial.to_string() << std::endl;
    while (true) {
        EstadoJuego* estado_actual = new EstadoJuego;
        char accion = leer_entrada();
        if (!realizar_accion(accion))
            break;
        estado_actual->vaciar();
        recibir_respuesta_juego(*estado_actual);
        std::cout << estado_actual->to_string() << std::endl;
        delete estado_actual;
    }
}

void ClientMock::start() { 
    r.start();
    e.start();
    loop_juego(); 
}

ClientMock::~ClientMock(){
    e.dejar_de_enviar();
    r.dejar_de_recibir();
}
