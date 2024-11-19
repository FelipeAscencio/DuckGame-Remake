#include "client_handler.h"

#define CERO 0
#define MENOS_UNO -1
#define ANCHO_MIN 960
#define ALTO_MIN 720
#define VOLUMEN_MUSICA 5  // '5' Recomendado.
#define FRECUENCIA_HZ 44100
#define BUFFER_AUDIO 2048
#define AUDIO_ESTEREO 2
#define SLEEP 100
#define DUCK_GAME_STR "Duck Game"
#define MUSICA_FONDO "/arcade-song.mp3"
#define ERROR_INICIAR_MIX "Error al inicializar SDL_mixer: "
#define ERROR_CARGAR_MUSICA "Error al cargar la musica de fondo: "
#define RW_CLOSE 2

using namespace SDL2pp;

Client::Client(const char* hostname, const char* servicio):
        cola_enviador(),
        cola_recibidor(),
        jugador_activo(true),
        controlador(cola_enviador),
        socket(hostname, servicio),
        protocolo(socket),
        id(protocolo.id_cliente),
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

void Client::controlar_loop_juego() {
    Mix_Music* musica_fondo = iniciar_musica();
    SDL sdl(SDL_INIT_VIDEO);
    Window window(DUCK_GAME_STR, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_MIN,
                  ALTO_MIN, SDL_WINDOW_SHOWN);
    Renderer renderer(window, MENOS_UNO, SDL_RENDERER_ACCELERATED);
    dibujador.emplace(renderer, this->id, cola_recibidor);
    iniciar_hilos();
    while (this->jugador_activo) {
        controlador.manejar_eventos(this->jugador_activo);
        if (dibujador) {
            dibujador->renderizar(renderer, this->jugador_activo);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
    }

    terminar_musica(musica_fondo);
}

Client::~Client() {
    finalizar_hilos();
    this->socket.shutdown(RW_CLOSE);
    this->socket.close();
}
