#include "client_handler.h"

#include "../common/liberror.h"

#define MENOS_UNO -1
#define CERO 0
#define CANT_NUMEROS_PARTIDA 6
#define ANCHO_MIN 960
#define ALTO_MIN 720
#define VOLUMEN_MUSICA 2  // '2' Recomendado.
#define FRECUENCIA_HZ 44100
#define BUFFER_AUDIO 2048
#define AUDIO_ESTEREO 2
#define SLEEP 100
#define DUCK_GAME_STR "Duck Game"
#define MUSICA_FONDO "/arcade-song.mp3"
#define ERROR_INICIAR_MIX "Error al inicializar SDL_mixer: "
#define ERROR_CARGAR_MUSICA "Error al cargar la musica de fondo: "
#define INGRESO_INVALIDO "0" // ID de partida invalido, para detectar que no se pudo conectar a una partida.
#define MSJ_PARTIDA_CREADA_EXITOSA "Partida creada con exito. El id de su partida es: "
#define MSJ_INGRESE_ID  "Ingrese por favor el ID de 6 numeros de la partida a la que se quiere conectar: "
#define MSJ_ID_INEXISTENTE "ID de partida inexistente."
#define RW_CLOSE 2
#define ID_DUMMY 0xCC
#define MIL 1000
#define FPS 30
#define NUEVA_PARTIDA 0x01
#define PARTIDA_EXISTENTE 0x02
#define MAX_ID_JUGADOR 7

using namespace SDL2pp;

Client::Client(const char* hostname, const char* servicio):
        cola_enviador(),
        cola_recibidor(),
        jugador_activo(true),
        controlador(cola_enviador),
        socket(hostname, servicio),
        protocolo(socket), id(-1),
        enviador(protocolo, cola_enviador, id),
        recibidor(protocolo, cola_recibidor) {}

Mix_Music* Client::iniciar_musica() {
    if (Mix_OpenAudio(FRECUENCIA_HZ, MIX_DEFAULT_FORMAT, AUDIO_ESTEREO, BUFFER_AUDIO) < CERO) {
        std::cerr << ERROR_INICIAR_MIX << Mix_GetError() << std::endl;
    }

    Mix_Music* musica_fondo = Mix_LoadMUS(DATA_PATH MUSICA_FONDO);
    if (!musica_fondo) {
        std::cerr << ERROR_CARGAR_MUSICA << Mix_GetError() << std::endl;
    } else {
        Mix_VolumeMusic(VOLUMEN_MUSICA);
        Mix_PlayMusic(musica_fondo, MENOS_UNO);
    }

    return musica_fondo;
}

void Client::terminar_musica(Mix_Music* musica_fondo) {
    Mix_FreeMusic(musica_fondo);
    Mix_CloseAudio();
}

void Client::iniciar_hilos() {
    recibidor.start();
    enviador.start();
}

void Client::finalizar_hilos() {
    enviador.stop();
    recibidor.stop();
    enviador.join();
    recibidor.join();
}

bool Client::ingresar_nueva_partida(){
    std::string codigo_partida;
    if (!protocolo.recibir_mensaje_bienvenida(codigo_partida)){
        return false;
    }

    std::cout << MSJ_PARTIDA_CREADA_EXITOSA << codigo_partida << std::endl;
    if (!protocolo.recibir_id()){
        return false;
    }

    this->id = protocolo.id_cliente;
    return true;
}

bool Client::loop_ingresar_partida_existente(){
    do {
        std::string linea;
        std::cout << MSJ_INGRESE_ID << std::endl;
        std::getline(std::cin, linea);
        if (linea.size() == CANT_NUMEROS_PARTIDA){
            if (!protocolo.enviar_codigo_partida(linea)){
                return false;
            }
        
            if (!protocolo.recibir_id()){
                return false;
            }

            this->id = protocolo.id_cliente;
            if (this->id <= MAX_ID_JUGADOR){
                return true;
            }

            std::cout << MSJ_ID_INEXISTENTE << std::endl;
        }
    } while (true);
}

bool Client::primer_contacto_con_servidor(){
    std::string bienvenida;
    if (!protocolo.recibir_mensaje_bienvenida(bienvenida)){
        return false;
    }

    std::cout << bienvenida << std::endl;
    std::string linea;
    int respuesta;
    do{
        std::getline(std::cin, linea);
        respuesta = (int)(linea[0] - 0x30);
    } while (respuesta != NUEVA_PARTIDA && respuesta != PARTIDA_EXISTENTE);

    if (!protocolo.enviar_respuesta(respuesta)){
        return false;
    }

    if (respuesta == NUEVA_PARTIDA){
        return ingresar_nueva_partida();
    } else {
        return loop_ingresar_partida_existente();
    }
}

void Client::controlar_loop_juego() {
    if (!primer_contacto_con_servidor()){
        return;
    }

    Mix_Music* musica_fondo = iniciar_musica();
    SDL sdl(SDL_INIT_VIDEO);
    Window window(DUCK_GAME_STR, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_MIN,
                  ALTO_MIN, SDL_WINDOW_SHOWN);
    Renderer renderer(window, MENOS_UNO, SDL_RENDERER_ACCELERATED);
    dibujador.emplace(renderer, this->id, cola_recibidor);
    iniciar_hilos();
    while (this->jugador_activo && this->recibidor.esta_vivo()) {
        auto t1 = std::chrono::steady_clock::now();
        unsigned long frame_count = CERO;
        int ms_per_frame = MIL/FPS;
        controlador.manejar_eventos(this->jugador_activo);
        if (dibujador) {
            dibujador->renderizar(renderer, this->jugador_activo);
        }

        auto t2 = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        if (elapsed < ms_per_frame) {
            std::this_thread::sleep_for(std::chrono::milliseconds(ms_per_frame - elapsed));
        }

        t1 += std::chrono::milliseconds(ms_per_frame);
        frame_count++;
    }

    renderer.Clear();
    terminar_musica(musica_fondo);
}

Client::~Client() {
    finalizar_hilos();
    try {
        this->socket.shutdown(RW_CLOSE);
        this->socket.close();
    } catch (const LibError& e) {
        std::cerr << e.what() << std::endl;
    }
}
