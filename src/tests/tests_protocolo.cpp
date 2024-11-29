#include <cstdint>
#include <cstdlib>
#include <stdio.h>
#include <memory>
#include <thread>
#include <chrono>
#include <arpa/inet.h>
#include <gtest/gtest.h>

#include "../client/protocolo_cliente.h"
#include "../server/protocol.h"

#define SLEEP_DE_ACEPTACION 100

using namespace ServerProtocol;

// DEFINICION DE LAS VARIABLES GLOBALES.
const char* localhost = "127.0.0.1";
const char* server_port = "8085";

// Declaracion de la clase utilizada para los tests.
class SocketTest : public ::testing::Test {
};

// TESTS.
TEST_F(SocketTest, MoverseHaciaLaDerecha) {
    // Hilo del servidor.
    std::thread server_thread([&]() {
        Socket server_socket(server_port);
        Socket client_connection = server_socket.accept();
        Protocol protocolo_server(client_connection);
        comando_t cmd;
        int comando_cliente = 1;
        bool resultado_servidor = protocolo_server.recibir(cmd, 1);
        ASSERT_TRUE(resultado_servidor) << "Error: No se pudo recibir la accion en el servidor.";
        ASSERT_EQ(cmd.accion, comando_cliente) << "Error: El comando recibido no coincide con el esperado.";
    });

    // Sleep necesario para que este listo el server para aceptar al cliente.
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DE_ACEPTACION));

    // Hilo del cliente.
    std::thread client_thread([&]() {
        Socket client_socket(localhost, server_port);
        ProtocoloCliente protocolo_cliente(client_socket);
        const char accion = 'D'; // Accion a enviar.
        bool resultado_cliente = protocolo_cliente.enviar(accion);
        ASSERT_TRUE(resultado_cliente) << "Error: No se pudo enviar la accion desde el cliente.";
    });

    // Espera a que los hilos terminen.
    client_thread.join();
    server_thread.join();
}

// TESTS.
TEST_F(SocketTest, MoverseHaciaLaIzquierda) {
    // Hilo del servidor.
    std::thread server_thread([&]() {
        Socket server_socket(server_port);
        Socket client_connection = server_socket.accept();
        Protocol protocolo_server(client_connection);
        comando_t cmd;
        int comando_cliente = 2;
        bool resultado_servidor = protocolo_server.recibir(cmd, 1);
        ASSERT_TRUE(resultado_servidor) << "Error: No se pudo recibir la accion en el servidor.";
        ASSERT_EQ(cmd.accion, comando_cliente) << "Error: El comando recibido no coincide con el esperado.";
    });

    // Sleep necesario para que este listo el server para aceptar al cliente.
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DE_ACEPTACION));

    // Hilo del cliente.
    std::thread client_thread([&]() {
        Socket client_socket(localhost, server_port);
        ProtocoloCliente protocolo_cliente(client_socket);
        const char accion = 'A'; // Accion a enviar.
        bool resultado_cliente = protocolo_cliente.enviar(accion);
        ASSERT_TRUE(resultado_cliente) << "Error: No se pudo enviar la accion desde el cliente.";
    });

    // Espera a que los hilos terminen.
    client_thread.join();
    server_thread.join();
}

// TESTS.
TEST_F(SocketTest, MirarHaciaArriba) {
    // Hilo del servidor.
    std::thread server_thread([&]() {
        Socket server_socket(server_port);
        Socket client_connection = server_socket.accept();
        Protocol protocolo_server(client_connection);
        comando_t cmd;
        int comando_cliente = 4;
        bool resultado_servidor = protocolo_server.recibir(cmd, 1);
        ASSERT_TRUE(resultado_servidor) << "Error: No se pudo recibir la accion en el servidor.";
        ASSERT_EQ(cmd.accion, comando_cliente) << "Error: El comando recibido no coincide con el esperado.";
    });

    // Sleep necesario para que este listo el server para aceptar al cliente.
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DE_ACEPTACION));

    // Hilo del cliente.
    std::thread client_thread([&]() {
        Socket client_socket(localhost, server_port);
        ProtocoloCliente protocolo_cliente(client_socket);
        const char accion = 'W'; // Accion a enviar.
        bool resultado_cliente = protocolo_cliente.enviar(accion);
        ASSERT_TRUE(resultado_cliente) << "Error: No se pudo enviar la accion desde el cliente.";
    });

    // Espera a que los hilos terminen.
    client_thread.join();
    server_thread.join();
}

// TESTS.
TEST_F(SocketTest, Agacharse) {
    // Hilo del servidor.
    std::thread server_thread([&]() {
        Socket server_socket(server_port);
        Socket client_connection = server_socket.accept();
        Protocol protocolo_server(client_connection);
        comando_t cmd;
        int comando_cliente = 3;
        bool resultado_servidor = protocolo_server.recibir(cmd, 1);
        ASSERT_TRUE(resultado_servidor) << "Error: No se pudo recibir la accion en el servidor.";
        ASSERT_EQ(cmd.accion, comando_cliente) << "Error: El comando recibido no coincide con el esperado.";
    });

    // Sleep necesario para que este listo el server para aceptar al cliente.
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DE_ACEPTACION));

    // Hilo del cliente.
    std::thread client_thread([&]() {
        Socket client_socket(localhost, server_port);
        ProtocoloCliente protocolo_cliente(client_socket);
        const char accion = 'S'; // Accion a enviar.
        bool resultado_cliente = protocolo_cliente.enviar(accion);
        ASSERT_TRUE(resultado_cliente) << "Error: No se pudo enviar la accion desde el cliente.";
    });

    // Espera a que los hilos terminen.
    client_thread.join();
    server_thread.join();
}

// TESTS.
TEST_F(SocketTest, SaltarAletear) {
    // Hilo del servidor.
    std::thread server_thread([&]() {
        Socket server_socket(server_port);
        Socket client_connection = server_socket.accept();
        Protocol protocolo_server(client_connection);
        comando_t cmd;
        int comando_cliente = 5;
        bool resultado_servidor = protocolo_server.recibir(cmd, 1);
        ASSERT_TRUE(resultado_servidor) << "Error: No se pudo recibir la accion en el servidor.";
        ASSERT_EQ(cmd.accion, comando_cliente) << "Error: El comando recibido no coincide con el esperado.";
    });

    // Sleep necesario para que este listo el server para aceptar al cliente.
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DE_ACEPTACION));

    // Hilo del cliente.
    std::thread client_thread([&]() {
        Socket client_socket(localhost, server_port);
        ProtocoloCliente protocolo_cliente(client_socket);
        const char accion = ' '; // Accion a enviar.
        bool resultado_cliente = protocolo_cliente.enviar(accion);
        ASSERT_TRUE(resultado_cliente) << "Error: No se pudo enviar la accion desde el cliente.";
    });

    // Espera a que los hilos terminen.
    client_thread.join();
    server_thread.join();
}

// TESTS.
TEST_F(SocketTest, Agarrar) {
    // Hilo del servidor.
    std::thread server_thread([&]() {
        Socket server_socket(server_port);
        Socket client_connection = server_socket.accept();
        Protocol protocolo_server(client_connection);
        comando_t cmd;
        int comando_cliente = 7;
        bool resultado_servidor = protocolo_server.recibir(cmd, 1);
        ASSERT_TRUE(resultado_servidor) << "Error: No se pudo recibir la accion en el servidor.";
        ASSERT_EQ(cmd.accion, comando_cliente) << "Error: El comando recibido no coincide con el esperado.";
    });

    // Sleep necesario para que este listo el server para aceptar al cliente.
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DE_ACEPTACION));

    // Hilo del cliente.
    std::thread client_thread([&]() {
        Socket client_socket(localhost, server_port);
        ProtocoloCliente protocolo_cliente(client_socket);
        const char accion = 'K'; // Accion a enviar.
        bool resultado_cliente = protocolo_cliente.enviar(accion);
        ASSERT_TRUE(resultado_cliente) << "Error: No se pudo enviar la accion desde el cliente.";
    });

    // Espera a que los hilos terminen.
    client_thread.join();
    server_thread.join();
}

// TESTS.
TEST_F(SocketTest, Disparar) {
    // Hilo del servidor.
    std::thread server_thread([&]() {
        Socket server_socket(server_port);
        Socket client_connection = server_socket.accept();
        Protocol protocolo_server(client_connection);
        comando_t cmd;
        int comando_cliente = 6;
        bool resultado_servidor = protocolo_server.recibir(cmd, 1);
        ASSERT_TRUE(resultado_servidor) << "Error: No se pudo recibir la accion en el servidor.";
        ASSERT_EQ(cmd.accion, comando_cliente) << "Error: El comando recibido no coincide con el esperado.";
    });

    // Sleep necesario para que este listo el server para aceptar al cliente.
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DE_ACEPTACION));

    // Hilo del cliente.
    std::thread client_thread([&]() {
        Socket client_socket(localhost, server_port);
        ProtocoloCliente protocolo_cliente(client_socket);
        const char accion = 'J'; // Accion a enviar.
        bool resultado_cliente = protocolo_cliente.enviar(accion);
        ASSERT_TRUE(resultado_cliente) << "Error: No se pudo enviar la accion desde el cliente.";
    });

    // Espera a que los hilos terminen.
    client_thread.join();
    server_thread.join();
}

// TESTS.
TEST_F(SocketTest, Cuack) {
    // Hilo del servidor.
    std::thread server_thread([&]() {
        Socket server_socket(server_port);
        Socket client_connection = server_socket.accept();
        Protocol protocolo_server(client_connection);
        comando_t cmd;
        int comando_cliente = 8;
        bool resultado_servidor = protocolo_server.recibir(cmd, 1);
        ASSERT_TRUE(resultado_servidor) << "Error: No se pudo recibir la accion en el servidor.";
        ASSERT_EQ(cmd.accion, comando_cliente) << "Error: El comando recibido no coincide con el esperado.";
    });

    // Sleep necesario para que este listo el server para aceptar al cliente.
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DE_ACEPTACION));

    // Hilo del cliente.
    std::thread client_thread([&]() {
        Socket client_socket(localhost, server_port);
        ProtocoloCliente protocolo_cliente(client_socket);
        const char accion = 'C'; // Accion a enviar.
        bool resultado_cliente = protocolo_cliente.enviar(accion);
        ASSERT_TRUE(resultado_cliente) << "Error: No se pudo enviar la accion desde el cliente.";
    });

    // Espera a que los hilos terminen.
    client_thread.join();
    server_thread.join();
}

// TESTS.
TEST_F(SocketTest, CheatInmortalidad) {
    // Hilo del servidor.
    std::thread server_thread([&]() {
        Socket server_socket(server_port);
        Socket client_connection = server_socket.accept();
        Protocol protocolo_server(client_connection);
        comando_t cmd;
        int comando_cliente = 37;
        bool resultado_servidor = protocolo_server.recibir(cmd, 1);
        ASSERT_TRUE(resultado_servidor) << "Error: No se pudo recibir la accion en el servidor.";
        ASSERT_EQ(cmd.accion, comando_cliente) << "Error: El comando recibido no coincide con el esperado.";
    });

    // Sleep necesario para que este listo el server para aceptar al cliente.
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DE_ACEPTACION));

    // Hilo del cliente.
    std::thread client_thread([&]() {
        Socket client_socket(localhost, server_port);
        ProtocoloCliente protocolo_cliente(client_socket);
        const char accion = 'I'; // Accion a enviar.
        bool resultado_cliente = protocolo_cliente.enviar(accion);
        ASSERT_TRUE(resultado_cliente) << "Error: No se pudo enviar la accion desde el cliente.";
    });

    // Espera a que los hilos terminen.
    client_thread.join();
    server_thread.join();
}

// TESTS.
TEST_F(SocketTest, CheatRecargar) {
    // Hilo del servidor.
    std::thread server_thread([&]() {
        Socket server_socket(server_port);
        Socket client_connection = server_socket.accept();
        Protocol protocolo_server(client_connection);
        comando_t cmd;
        int comando_cliente = 38;
        bool resultado_servidor = protocolo_server.recibir(cmd, 1);
        ASSERT_TRUE(resultado_servidor) << "Error: No se pudo recibir la accion en el servidor.";
        ASSERT_EQ(cmd.accion, comando_cliente) << "Error: El comando recibido no coincide con el esperado.";
    });

    // Sleep necesario para que este listo el server para aceptar al cliente.
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DE_ACEPTACION));

    // Hilo del cliente.
    std::thread client_thread([&]() {
        Socket client_socket(localhost, server_port);
        ProtocoloCliente protocolo_cliente(client_socket);
        const char accion = 'R'; // Accion a enviar.
        bool resultado_cliente = protocolo_cliente.enviar(accion);
        ASSERT_TRUE(resultado_cliente) << "Error: No se pudo enviar la accion desde el cliente.";
    });

    // Espera a que los hilos terminen.
    client_thread.join();
    server_thread.join();
}

// TESTS.
TEST_F(SocketTest, CheatArmadura) {
    // Hilo del servidor.
    std::thread server_thread([&]() {
        Socket server_socket(server_port);
        Socket client_connection = server_socket.accept();
        Protocol protocolo_server(client_connection);
        comando_t cmd;
        int comando_cliente = 39;
        bool resultado_servidor = protocolo_server.recibir(cmd, 1);
        ASSERT_TRUE(resultado_servidor) << "Error: No se pudo recibir la accion en el servidor.";
        ASSERT_EQ(cmd.accion, comando_cliente) << "Error: El comando recibido no coincide con el esperado.";
    });

    // Sleep necesario para que este listo el server para aceptar al cliente.
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DE_ACEPTACION));

    // Hilo del cliente.
    std::thread client_thread([&]() {
        Socket client_socket(localhost, server_port);
        ProtocoloCliente protocolo_cliente(client_socket);
        const char accion = 'L'; // Accion a enviar.
        bool resultado_cliente = protocolo_cliente.enviar(accion);
        ASSERT_TRUE(resultado_cliente) << "Error: No se pudo enviar la accion desde el cliente.";
    });

    // Espera a que los hilos terminen.
    client_thread.join();
    server_thread.join();
}

// TESTS.
TEST_F(SocketTest, CheatCasco) {
    // Hilo del servidor.
    std::thread server_thread([&]() {
        Socket server_socket(server_port);
        Socket client_connection = server_socket.accept();
        Protocol protocolo_server(client_connection);
        comando_t cmd;
        int comando_cliente = 40;
        bool resultado_servidor = protocolo_server.recibir(cmd, 1);
        ASSERT_TRUE(resultado_servidor) << "Error: No se pudo recibir la accion en el servidor.";
        ASSERT_EQ(cmd.accion, comando_cliente) << "Error: El comando recibido no coincide con el esperado.";
    });

    // Sleep necesario para que este listo el server para aceptar al cliente.
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DE_ACEPTACION));

    // Hilo del cliente.
    std::thread client_thread([&]() {
        Socket client_socket(localhost, server_port);
        ProtocoloCliente protocolo_cliente(client_socket);
        const char accion = 'P'; // Accion a enviar.
        bool resultado_cliente = protocolo_cliente.enviar(accion);
        ASSERT_TRUE(resultado_cliente) << "Error: No se pudo enviar la accion desde el cliente.";
    });

    // Espera a que los hilos terminen.
    client_thread.join();
    server_thread.join();
}

// TESTS.
TEST_F(SocketTest, CheatRondas) {
    // Hilo del servidor.
    std::thread server_thread([&]() {
        Socket server_socket(server_port);
        Socket client_connection = server_socket.accept();
        Protocol protocolo_server(client_connection);
        comando_t cmd;
        int comando_cliente = 41;
        bool resultado_servidor = protocolo_server.recibir(cmd, 1);
        ASSERT_TRUE(resultado_servidor) << "Error: No se pudo recibir la accion en el servidor.";
        ASSERT_EQ(cmd.accion, comando_cliente) << "Error: El comando recibido no coincide con el esperado.";
    });

    // Sleep necesario para que este listo el server para aceptar al cliente.
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DE_ACEPTACION));

    // Hilo del cliente.
    std::thread client_thread([&]() {
        Socket client_socket(localhost, server_port);
        ProtocoloCliente protocolo_cliente(client_socket);
        const char accion = 'Z'; // Accion a enviar.
        bool resultado_cliente = protocolo_cliente.enviar(accion);
        ASSERT_TRUE(resultado_cliente) << "Error: No se pudo enviar la accion desde el cliente.";
    });

    // Espera a que los hilos terminen.
    client_thread.join();
    server_thread.join();
}

// TESTS.
TEST_F(SocketTest, CheatAK) {
    // Hilo del servidor.
    std::thread server_thread([&]() {
        Socket server_socket(server_port);
        Socket client_connection = server_socket.accept();
        Protocol protocolo_server(client_connection);
        comando_t cmd;
        int comando_cliente = 32;
        bool resultado_servidor = protocolo_server.recibir(cmd, 1);
        ASSERT_TRUE(resultado_servidor) << "Error: No se pudo recibir la accion en el servidor.";
        ASSERT_EQ(cmd.accion, comando_cliente) << "Error: El comando recibido no coincide con el esperado.";
    });

    // Sleep necesario para que este listo el server para aceptar al cliente.
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DE_ACEPTACION));

    // Hilo del cliente.
    std::thread client_thread([&]() {
        Socket client_socket(localhost, server_port);
        ProtocoloCliente protocolo_cliente(client_socket);
        const char accion = '1'; // Accion a enviar.
        bool resultado_cliente = protocolo_cliente.enviar(accion);
        ASSERT_TRUE(resultado_cliente) << "Error: No se pudo enviar la accion desde el cliente.";
    });

    // Espera a que los hilos terminen.
    client_thread.join();
    server_thread.join();
}

// TESTS.
TEST_F(SocketTest, CheatShotgun) {
    // Hilo del servidor.
    std::thread server_thread([&]() {
        Socket server_socket(server_port);
        Socket client_connection = server_socket.accept();
        Protocol protocolo_server(client_connection);
        comando_t cmd;
        int comando_cliente = 33;
        bool resultado_servidor = protocolo_server.recibir(cmd, 1);
        ASSERT_TRUE(resultado_servidor) << "Error: No se pudo recibir la accion en el servidor.";
        ASSERT_EQ(cmd.accion, comando_cliente) << "Error: El comando recibido no coincide con el esperado.";
    });

    // Sleep necesario para que este listo el server para aceptar al cliente.
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DE_ACEPTACION));

    // Hilo del cliente.
    std::thread client_thread([&]() {
        Socket client_socket(localhost, server_port);
        ProtocoloCliente protocolo_cliente(client_socket);
        const char accion = '2'; // Accion a enviar.
        bool resultado_cliente = protocolo_cliente.enviar(accion);
        ASSERT_TRUE(resultado_cliente) << "Error: No se pudo enviar la accion desde el cliente.";
    });

    // Espera a que los hilos terminen.
    client_thread.join();
    server_thread.join();
}

// TESTS.
TEST_F(SocketTest, CheatMagnum) {
    // Hilo del servidor.
    std::thread server_thread([&]() {
        Socket server_socket(server_port);
        Socket client_connection = server_socket.accept();
        Protocol protocolo_server(client_connection);
        comando_t cmd;
        int comando_cliente = 34;
        bool resultado_servidor = protocolo_server.recibir(cmd, 1);
        ASSERT_TRUE(resultado_servidor) << "Error: No se pudo recibir la accion en el servidor.";
        ASSERT_EQ(cmd.accion, comando_cliente) << "Error: El comando recibido no coincide con el esperado.";
    });

    // Sleep necesario para que este listo el server para aceptar al cliente.
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DE_ACEPTACION));

    // Hilo del cliente.
    std::thread client_thread([&]() {
        Socket client_socket(localhost, server_port);
        ProtocoloCliente protocolo_cliente(client_socket);
        const char accion = '3'; // Accion a enviar.
        bool resultado_cliente = protocolo_cliente.enviar(accion);
        ASSERT_TRUE(resultado_cliente) << "Error: No se pudo enviar la accion desde el cliente.";
    });

    // Espera a que los hilos terminen.
    client_thread.join();
    server_thread.join();
}

// TESTS.
TEST_F(SocketTest, CheatLaser) {
    // Hilo del servidor.
    std::thread server_thread([&]() {
        Socket server_socket(server_port);
        Socket client_connection = server_socket.accept();
        Protocol protocolo_server(client_connection);
        comando_t cmd;
        int comando_cliente = 35;
        bool resultado_servidor = protocolo_server.recibir(cmd, 1);
        ASSERT_TRUE(resultado_servidor) << "Error: No se pudo recibir la accion en el servidor.";
        ASSERT_EQ(cmd.accion, comando_cliente) << "Error: El comando recibido no coincide con el esperado.";
    });

    // Sleep necesario para que este listo el server para aceptar al cliente.
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DE_ACEPTACION));

    // Hilo del cliente.
    std::thread client_thread([&]() {
        Socket client_socket(localhost, server_port);
        ProtocoloCliente protocolo_cliente(client_socket);
        const char accion = '4'; // Accion a enviar.
        bool resultado_cliente = protocolo_cliente.enviar(accion);
        ASSERT_TRUE(resultado_cliente) << "Error: No se pudo enviar la accion desde el cliente.";
    });

    // Espera a que los hilos terminen.
    client_thread.join();
    server_thread.join();
}

// TESTS.
TEST_F(SocketTest, CheatSniper) {
    // Hilo del servidor.
    std::thread server_thread([&]() {
        Socket server_socket(server_port);
        Socket client_connection = server_socket.accept();
        Protocol protocolo_server(client_connection);
        comando_t cmd;
        int comando_cliente = 36;
        bool resultado_servidor = protocolo_server.recibir(cmd, 1);
        ASSERT_TRUE(resultado_servidor) << "Error: No se pudo recibir la accion en el servidor.";
        ASSERT_EQ(cmd.accion, comando_cliente) << "Error: El comando recibido no coincide con el esperado.";
    });

    // Sleep necesario para que este listo el server para aceptar al cliente.
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DE_ACEPTACION));

    // Hilo del cliente.
    std::thread client_thread([&]() {
        Socket client_socket(localhost, server_port);
        ProtocoloCliente protocolo_cliente(client_socket);
        const char accion = '5'; // Accion a enviar.
        bool resultado_cliente = protocolo_cliente.enviar(accion);
        ASSERT_TRUE(resultado_cliente) << "Error: No se pudo enviar la accion desde el cliente.";
    });

    // Espera a que los hilos terminen.
    client_thread.join();
    server_thread.join();
}

// TESTS.
TEST_F(SocketTest, EnviarEstadoDelJuego) {
    // Inicializacion de un estado de juego generico a enviar.
    EstadoJuego estado_enviado;
    estado_enviado.cantidad_jugadores = 2;
    estado_enviado.cantidad_armas = 3;
    estado_enviado.cantidad_balas = 4;
    estado_enviado.cantidad_armaduras = 1;
    estado_enviado.cantidad_cascos = 2;
    estado_enviado.cantidad_cajas = 2;
    estado_enviado.id_ganador = 1;
    estado_enviado.id_mapa = 2;
    estado_enviado.rondas_jugadas = 2;
    estado_enviado.ingame = true;

    // Informacion de patos.
    estado_enviado.info_patos.emplace_back(
        InformacionPato(1, posicion_t(15, 25), true, false, 0, true, false,  
                        orientacion_e::DERECHA, estado_pato_e::PARADO, 
                        sonido_e::DISPARANDO, 1));

    // Informacion de armas.
    estado_enviado.info_armas.emplace_back(InformacionArma(1, posicion_t(32, 41)));

    // Informacion de balas.
    estado_enviado.info_balas.emplace_back(
        InformacionBala(1, posicion_t(65, 78), inclinacion_e::NO_TIENE, 
                        orientacion_e::DERECHA));

    // Informacion de armaduras.
    estado_enviado.info_armaduras.emplace_back(posicion_t(23, 46));

    // Informacion de cascos.
    estado_enviado.info_cascos.emplace_back(posicion_t(51, 33));

    // Informacion de cajas.
    estado_enviado.info_cajas.emplace_back(InformacionCaja(
        posicion_t(72, 83), damage_e::INTACTA));

    // Hilo del servidor.
    std::thread server_thread([&]() {
        Socket server_socket(server_port);
        Socket client_connection = server_socket.accept();
        Protocol protocolo_server(client_connection);
        bool resultado_envio = protocolo_server.enviar(estado_enviado);
        ASSERT_TRUE(resultado_envio) << "Error: No se pudo enviar el estado del juego al cliente.";
    });

    // Sleep necesario para que este listo el server para aceptar al cliente.
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DE_ACEPTACION));

    // Hilo del cliente.
    std::thread client_thread([&]() {
        Socket client_socket(localhost, server_port);
        ProtocoloCliente protocolo_cliente(client_socket);
        EstadoJuego estado_recibido;
        bool resultado_recepcion = protocolo_cliente.recibir(estado_recibido);
        ASSERT_TRUE(resultado_recepcion) << "Error: No se pudo recibir el estado del juego desde el servidor.";

        // Comprueba que todos los campos del 'EstadoJuego' sean iguales.
        ASSERT_EQ(estado_recibido.cantidad_jugadores, estado_enviado.cantidad_jugadores);
        ASSERT_EQ(estado_recibido.cantidad_armas, estado_enviado.cantidad_armas);
        ASSERT_EQ(estado_recibido.cantidad_balas, estado_enviado.cantidad_balas);
        ASSERT_EQ(estado_recibido.cantidad_armaduras, estado_enviado.cantidad_armaduras);
        ASSERT_EQ(estado_recibido.cantidad_cascos, estado_enviado.cantidad_cascos);
        ASSERT_EQ(estado_recibido.cantidad_cajas, estado_enviado.cantidad_cajas);
        ASSERT_EQ(estado_recibido.id_ganador, estado_enviado.id_ganador);
        ASSERT_EQ(estado_recibido.id_mapa, estado_enviado.id_mapa);
        ASSERT_EQ(estado_recibido.rondas_jugadas, estado_enviado.rondas_jugadas);
        ASSERT_EQ(estado_recibido.ingame, estado_enviado.ingame);
        
        // Verifica que todos los campos de los vectores sean iguales.
        const auto& pato_enviado = estado_enviado.info_patos[0];
        const auto& pato_recibido = estado_recibido.info_patos[0];
        ASSERT_EQ(pato_recibido.id, pato_enviado.id);
        ASSERT_EQ(pato_recibido.posicion.coordenada_x, pato_enviado.posicion.coordenada_x);
        ASSERT_EQ(pato_recibido.posicion.coordenada_y, pato_enviado.posicion.coordenada_y);
        ASSERT_EQ(pato_recibido.vivo, pato_enviado.vivo);
        ASSERT_EQ(pato_recibido.arma, pato_enviado.arma);
        ASSERT_EQ(pato_recibido.id_arma_equipada, pato_enviado.id_arma_equipada);
        ASSERT_EQ(pato_recibido.casco, pato_enviado.casco);
        ASSERT_EQ(pato_recibido.armadura, pato_enviado.armadura);
        ASSERT_EQ(pato_recibido.orientacion, pato_enviado.orientacion);
        ASSERT_EQ(pato_recibido.estado, pato_enviado.estado);
        ASSERT_EQ(pato_recibido.sonido, pato_enviado.sonido);
        ASSERT_EQ(pato_recibido.rondas_ganadas, pato_enviado.rondas_ganadas);

        const auto& arma_recibida = estado_recibido.info_armas[0];
        const auto& arma_enviada = estado_enviado.info_armas[0];
        ASSERT_EQ(arma_enviada.posicion.coordenada_x, arma_recibida.posicion.coordenada_x);
        ASSERT_EQ(arma_enviada.posicion.coordenada_y, arma_recibida.posicion.coordenada_y);
        ASSERT_EQ(arma_enviada.id_arma, arma_recibida.id_arma);

        const auto& bala_enviada = estado_enviado.info_balas[0];
        const auto& bala_recibida = estado_recibido.info_balas[0];
        ASSERT_EQ(bala_enviada.id_arma, bala_recibida.id_arma);
        ASSERT_EQ(bala_enviada.pos.coordenada_x, bala_recibida.pos.coordenada_x);
        ASSERT_EQ(bala_enviada.pos.coordenada_y, bala_recibida.pos.coordenada_y);
        ASSERT_EQ(bala_enviada.inclinacion, bala_recibida.inclinacion);
        ASSERT_EQ(bala_enviada.direccion, bala_recibida.direccion);

        const auto& caja_enviada = estado_enviado.info_cajas[0];
        const auto& caja_recibida = estado_recibido.info_cajas[0];
        ASSERT_EQ(caja_enviada.posicion.coordenada_x, caja_recibida.posicion.coordenada_x);
        ASSERT_EQ(caja_enviada.posicion.coordenada_y, caja_recibida.posicion.coordenada_y);
        ASSERT_EQ(caja_enviada.estado, caja_recibida.estado);

        ASSERT_EQ(estado_recibido.info_cascos[0].coordenada_x, estado_enviado.info_cascos[0].coordenada_x);
        ASSERT_EQ(estado_recibido.info_cascos[0].coordenada_y, estado_enviado.info_cascos[0].coordenada_y);
        
        ASSERT_EQ(estado_recibido.info_armaduras[0].coordenada_x, estado_enviado.info_armaduras[0].coordenada_x);
        ASSERT_EQ(estado_recibido.info_armaduras[0].coordenada_y, estado_enviado.info_armaduras[0].coordenada_y);
    });

    // Espera a que los hilos terminen.
    client_thread.join();
    server_thread.join();
}
