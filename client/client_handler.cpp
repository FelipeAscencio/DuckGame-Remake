#include "client_handler.h"

#define CERO 0
#define MENOS_UNO -1
#define ANCHO_MIN 960
#define ALTO_MIN 720
#define VOLUMEN_MUSICA 0
#define FRECUENCIA_HZ 44100
#define BUFFER_AUDIO 2048
#define AUDIO_ESTEREO 2
#define DUCK_GAME_STR "Duck Game"
#define RUTA_MAPA_1 "/mapa1.png"
#define MUSICA_FONDO "/arcade-song.mp3"
#define ERROR_INICIAR_MIX "Error al inicializar SDL_mixer: "
#define ERROR_CARGAR_MUSICA "Error al cargar la musica de fondo: "

using namespace SDL2pp;

Client::Client(const char* hostname, const char* servicio):
        queue_enviador(),
        queue_recibidor(), jugador_activo(true), controlador(queue_enviador), s(hostname, servicio),
        protocolo(s),
        id(protocolo.id_cliente),
        e(protocolo, queue_enviador, id),
        r(protocolo, queue_recibidor) {}

Mix_Music* Client::iniciar_musica(){
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

void Client::terminar_musica(Mix_Music* musica_fondo){
    Mix_FreeMusic(musica_fondo);
    Mix_CloseAudio();
}

void Client::controlar_loop_juego() {
    Mix_Music* musica_fondo = iniciar_musica();
    SDL sdl(SDL_INIT_VIDEO);
    Window window(DUCK_GAME_STR, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_MIN,
                  ALTO_MIN, SDL_WINDOW_SHOWN);
    Renderer renderer(window, MENOS_UNO, SDL_RENDERER_ACCELERATED);
    std::string ruta_mapa = RUTA_MAPA_1;
    dibujador.emplace(renderer, ruta_mapa, this->id, queue_recibidor);

    r.start();
    e.start();

    while (this->jugador_activo) {
        controlador.manejar_eventos(this->jugador_activo);
        if (dibujador) {
            dibujador->renderizar(renderer);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    terminar_musica(musica_fondo);
}

Client::~Client() {
    e.dejar_de_enviar();
    r.dejar_de_recibir();
}
