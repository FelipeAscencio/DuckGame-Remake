#include "client_dibujador.h"

#define RUTA_SPR_PATO "/sprites-pato-blanco.png"
#define RUTA_SPR_AK "/sprites-ak47.png"
#define RUTA_SPR_CAJAS "/sprites-cajas.png"
#define RUTA_SPR_ARMADURAS "/sprites-armaduras.png"
#define RUTA_SPR_ESCOPETA "/sprites-escopeta.png"
#define RUTA_SPR_LASER "/sprites-laser.png"
#define RUTA_SPR_PISTOLA "/sprites-pistola.png"
#define RUTA_SPR_SNIPER "/sprites-sniper.png"
#define RUTA_FUENTE "/fuente_arcade.ttf"
#define MSJ_ERROR_TFF "Error al inicializar SDL_ttf: "
#define MSJ_ERROR_RENDER_TXT "Error al renderizar texto: "
#define PUNTAJE_STR "Puntaje: "
#define SONIDO_AK "/ak.mp3"
#define SONIDO_ESCOPETA "/escopeta.mp3"
#define SONIDO_EXPLOSION "/explosion.mp3"
#define SONIDO_LASER "/laser.mp3"
#define SONIDO_PISTOLA "/pistola.mp3"
#define SONIDO_SNIPER "/sniper.mp3"
#define CUALQUIER_CANAL_LIBRE -1
#define CANTIDAD_DE_REPRODUCCIONES 0
#define TAMANIO_FUENTE 24
#define ANCHO_VENTANA 960
#define ALTO_VENTANA 720
#define MAX_COORD_X 200
#define MAX_COORD_Y 160
#define OFFSET_Y 0.03
#define ANGULO_NULO 0.0
#define ANGULO_270 270.0
#define ESCALA_SPRITES_GRANDES 0.07
#define ESCALA_SPRITES_MEDIANOS 0.04
#define ESCALA_SPRITES_CHICOS 0.02
#define MIN_INTENSIDAD_RGB 0
#define MED_INTENSIDAD_RGB 128
#define MAX_INTENSIDAD_RGB 255
#define RGB_AUX_MARRON_1 69
#define RGB_AUX_MARRON_2 19
#define ESTADO_PARADO 0
#define ESTADO_AGACHADO 1
#define ESTADO_SALTANDO 2
#define ESTADO_ALETEANDO 3
#define ESTADO_CAYENDO 4
#define ESTADO_CAMINANDO 5
#define CANTIDAD_SPRITES_CAMINAR 6
#define POS_SPRITE_PARADO 0
#define POS_SPRITE_AGACHADO 9
#define POS_SPRITE_SALTANDO 7
#define POS_SPRITE_ALETEANDO 11
#define POS_SPRITE_CAYENDO 8
#define POS_INICIAL_PATO_TABLERO 10
#define GAP_PATO_TABLERO 0.1
#define X_INICIAL_PUNTAJE 100
#define Y_INICIAL_PUNTAJE 30
#define GAP_PUNTAJE_TABLERO 72
#define MENOS_UNO -1
#define CERO 0
#define UNO 1
#define DOS 2
#define TRES 3
#define CUATRO 4
#define CINCO 5
#define SEIS 6
#define SIETE 7
#define OCHO 8
#define DIEZ 10

using namespace SDL2pp;

Dibujador::Dibujador(Renderer& renderer, const std::string& ruta_mapa, const int id,
                     Queue<EstadoJuego>& cola_recibidor):
        id_jugador(id),
        cola_estados(cola_recibidor),
        ultimo_estado_recibido(),
        parseador(),
        sprite_sheet_pato(renderer, DATA_PATH RUTA_SPR_PATO),
        sprite_sheet_ak(renderer, DATA_PATH RUTA_SPR_AK),
        sprite_sheet_caja(renderer, DATA_PATH RUTA_SPR_CAJAS),
        sprite_sheet_equipamiento(renderer, DATA_PATH RUTA_SPR_ARMADURAS),
        sprite_sheet_escopeta(renderer, DATA_PATH RUTA_SPR_ESCOPETA),
        sprite_sheet_laser(renderer, DATA_PATH RUTA_SPR_LASER),
        sprite_sheet_pistola(renderer, DATA_PATH RUTA_SPR_PISTOLA),
        sprite_sheet_sniper(renderer, DATA_PATH RUTA_SPR_SNIPER),
        mapa(renderer, (DATA_PATH + ruta_mapa).c_str()),
        sprites_pato(parseador.obtener_sprites_pato()),
        sprites_ak(parseador.obtener_sprites_ak()),
        sprites_caja(parseador.obtener_sprites_caja()),
        sprites_equipamiento(parseador.obtener_sprites_equipamiento()),
        sprites_escopeta(parseador.obtener_sprites_escopeta()),
        sprites_laser(parseador.obtener_sprites_laser()),
        sprites_pistola(parseador.obtener_sprites_pistola()),
        sprites_sniper(parseador.obtener_sprites_sniper()),
        sprites_lootables(parseador.obtener_sprites_looteables()),
        sonido_ak(Mix_LoadWAV((DATA_PATH SONIDO_AK))),
        sonido_explosion(Mix_LoadWAV((DATA_PATH SONIDO_EXPLOSION))),
        sonido_laser(Mix_LoadWAV((DATA_PATH SONIDO_LASER))),
        sonido_pistola(Mix_LoadWAV((DATA_PATH SONIDO_PISTOLA))),
        sonido_escopeta(Mix_LoadWAV((DATA_PATH SONIDO_ESCOPETA))),
        sonido_sniper(Mix_LoadWAV((DATA_PATH SONIDO_SNIPER))) {}

std::pair<float, float> Dibujador::convertir_a_relativo(float x, float y) {
    float x_convertido = static_cast<float>(x) / MAX_COORD_X;
    float y_convertido = static_cast<float>(y) / MAX_COORD_Y;
    return {x_convertido, y_convertido};
}

SDL2pp::Rect Dibujador::calcular_dst_rect(float x, float y, float escala) {
    int ancho_ventana = ANCHO_VENTANA;
    int alto_ventana = ALTO_VENTANA;
    int ancho_escalado = static_cast<int>(ancho_ventana * escala);
    int alto_escalado = static_cast<int>(alto_ventana * escala);

    // Centramos el sprite en el eje 'X' y ponemos el '0' del eje 'Y' en la parte inferior del
    // sprite.
    int dst_x = static_cast<int>(ancho_ventana * x) - (ancho_escalado / DOS);
    int dst_y = static_cast<int>(alto_ventana * y) - alto_escalado;
    return SDL2pp::Rect(dst_x, dst_y, ancho_escalado, alto_escalado);
}

void Dibujador::dibujar_pato_enemigo(SDL2pp::Renderer& renderer, SDL2pp::Texture& sprite_sheet,
                                     const SDL_Rect& sprite, SDL2pp::Rect& dst_rect, const int id,
                                     const double angle, SDL_RendererFlip& flip) {
    SDL_Color color_mod;
    if (id == UNO) {  // ROJO
        color_mod = {MAX_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB,
                     MAX_INTENSIDAD_RGB};
    } else if (id == DOS) {  // VERDE
        color_mod = {MIN_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB,
                     MAX_INTENSIDAD_RGB};
    } else if (id == TRES) {  // AZUL
        color_mod = {MIN_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB,
                     MAX_INTENSIDAD_RGB};
    } else if (id == CUATRO) {  // AMARILLO
        color_mod = {MAX_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB,
                     MAX_INTENSIDAD_RGB};
    } else if (id == CINCO) {  // NARANJA
        color_mod = {MAX_INTENSIDAD_RGB, MED_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB,
                     MAX_INTENSIDAD_RGB};
    } else if (id == SEIS) {  // VIOLETA
        color_mod = {MED_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB, MED_INTENSIDAD_RGB,
                     MAX_INTENSIDAD_RGB};
    } else if (id == SIETE) {  // MARRON
        color_mod = {MED_INTENSIDAD_RGB, RGB_AUX_MARRON_1, RGB_AUX_MARRON_2, MAX_INTENSIDAD_RGB};
    } else if (id == OCHO) {  // NEGRO
        color_mod = {MIN_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB,
                     MAX_INTENSIDAD_RGB};
    }

    SDL_SetTextureColorMod(sprite_sheet.Get(), color_mod.r, color_mod.g, color_mod.b);
    renderer.Copy(sprite_sheet, SDL2pp::Optional<SDL2pp::Rect>(sprite),
                  SDL2pp::Optional<SDL2pp::Rect>(dst_rect), angle,
                  SDL2pp::Optional<SDL2pp::Point>(), flip);
    SDL_SetTextureColorMod(sprite_sheet.Get(), MAX_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB,
                           MAX_INTENSIDAD_RGB);
}

void Dibujador::dibujar_sprite(SDL2pp::Renderer& renderer, SDL2pp::Texture& sprite_sheet,
                               const SDL_Rect& sprite, float x, float y, float escala,
                               orientacion_e orientacion, const int id) {
    SDL2pp::Rect dst_rect = calcular_dst_rect(x, y, escala);
    double angle = ANGULO_NULO;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (orientacion == IZQUIERDA) {
        flip = SDL_FLIP_HORIZONTAL;
    } else if (orientacion == ARRIBA) {
        angle = ANGULO_270;
    }

    if (id > CERO && id <= OCHO) {
        if (id != this->id_jugador) {
            dibujar_pato_enemigo(renderer, sprite_sheet, sprite, dst_rect, id, angle, flip);
            return;
        }
    }

    renderer.Copy(sprite_sheet, SDL2pp::Optional<SDL2pp::Rect>(sprite),
                  SDL2pp::Optional<SDL2pp::Rect>(dst_rect), angle,
                  SDL2pp::Optional<SDL2pp::Point>(), flip);
}

void Dibujador::dibujar_patos(EstadoJuego& estado_actual, SDL2pp::Renderer& renderer) {
    float escala = ESCALA_SPRITES_GRANDES;
    int id;
    float x;
    float y;
    orientacion_e orientacion;
    estado_pato_e estado;
    for (auto& pato: estado_actual.info_patos) {
        id = pato.id;
        x = pato.posicion.coordenada_x;
        y = pato.posicion.coordenada_y;
        orientacion = pato.orientacion;
        estado = pato.estado;
        if (estado == ESTADO_PARADO) {
            auto [x_1, y_1] = convertir_a_relativo(x, y);
            dibujar_sprite(renderer, this->sprite_sheet_pato, this->sprites_pato[POS_SPRITE_PARADO],
                           x_1, y_1 + OFFSET_Y, escala, orientacion, id);
        } else if (estado == ESTADO_AGACHADO) {
            auto [x_1, y_1] = convertir_a_relativo(x, y);
            dibujar_sprite(renderer, this->sprite_sheet_pato,
                           this->sprites_pato[POS_SPRITE_AGACHADO], x_1, y_1 + OFFSET_Y, escala,
                           orientacion, id);
        } else if (estado == ESTADO_SALTANDO) {
            auto [x_1, y_1] = convertir_a_relativo(x, y);
            dibujar_sprite(renderer, this->sprite_sheet_pato,
                           this->sprites_pato[POS_SPRITE_SALTANDO], x_1, y_1 + OFFSET_Y, escala,
                           orientacion, id);
        } else if (estado == ESTADO_ALETEANDO) {
            auto [x_1, y_1] = convertir_a_relativo(x, y);
            dibujar_sprite(renderer, this->sprite_sheet_pato,
                           this->sprites_pato[POS_SPRITE_ALETEANDO], x_1, y_1 + OFFSET_Y, escala,
                           orientacion, id);
        } else if (estado == ESTADO_CAYENDO) {
            auto [x_1, y_1] = convertir_a_relativo(x, y);
            dibujar_sprite(renderer, this->sprite_sheet_pato,
                           this->sprites_pato[POS_SPRITE_CAYENDO], x_1, y_1 + OFFSET_Y, escala,
                           orientacion, id);
        } else if (estado == ESTADO_CAMINANDO) {
            unsigned int current_ticks = SDL_GetTicks();
            int sprite_index = UNO + (current_ticks / DIEZ) % CANTIDAD_SPRITES_CAMINAR;
            auto [x_1, y_1] = convertir_a_relativo(x, y);
            dibujar_sprite(renderer, this->sprite_sheet_pato, this->sprites_pato[sprite_index], x_1,
                           y_1 + OFFSET_Y, escala, orientacion, id);
        }
    }
}

void Dibujador::dibujar_estado_juego(EstadoJuego& estado_actual, SDL2pp::Renderer& renderer) {
    dibujar_patos(estado_actual, renderer);
}

void Dibujador::dibujar_patos_tablero(SDL2pp::Renderer& renderer){
    float escala = ESCALA_SPRITES_GRANDES;
    float x = POS_INICIAL_PATO_TABLERO;
    float y = POS_INICIAL_PATO_TABLERO;
    orientacion_e orientacion = DERECHA;
    auto [x_1, y_1] = convertir_a_relativo(x, y);
    for (int i = 0; i < OCHO; ++i){
        dibujar_sprite(renderer, this->sprite_sheet_pato, this->sprites_pato[POS_SPRITE_PARADO],
                           x_1, y_1 + (i * GAP_PATO_TABLERO) + OFFSET_Y, escala, orientacion, i + UNO);
    }
}

void Dibujador::dibujar_puntos_tablero(SDL2pp::Renderer& renderer, const std::vector<int>& puntajes){
    TTF_Font* fuente = TTF_OpenFont(DATA_PATH RUTA_FUENTE, TAMANIO_FUENTE);
    int pos_x = X_INICIAL_PUNTAJE;
    int pos_y = Y_INICIAL_PUNTAJE;
    int separacion_y = GAP_PUNTAJE_TABLERO;
    for (size_t i = 0; i < puntajes.size(); ++i) {
        std::string texto_puntaje = PUNTAJE_STR + std::to_string(puntajes[i]);
        SDL_Color color_texto = {MAX_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB}; // COLOR BLANCO.
        SDL_Surface* temp_surface = TTF_RenderText_Solid(fuente, texto_puntaje.c_str(), color_texto);
        if (!temp_surface) {
            throw std::runtime_error(MSJ_ERROR_RENDER_TXT + std::string(TTF_GetError()));
        }

        SDL2pp::Surface superficie_texto(temp_surface);
        SDL2pp::Texture textura_texto(renderer, superficie_texto);
        renderer.Copy(textura_texto, SDL2pp::NullOpt, SDL2pp::Rect(pos_x, pos_y, textura_texto.GetWidth(), textura_texto.GetHeight()));
        pos_y += separacion_y;
    }

    TTF_CloseFont(fuente);
}

void Dibujador::dibujar_tablero(SDL2pp::Renderer& renderer, const std::vector<int>& puntajes) {
    if (TTF_Init() == MENOS_UNO) {
        std::cerr << MSJ_ERROR_TFF << TTF_GetError() << std::endl;
        return;
    }

    dibujar_patos_tablero(renderer);
    dibujar_puntos_tablero(renderer, puntajes);
    
    TTF_Quit();
}

void Dibujador::reproducir_disparo_ak(){
    Mix_PlayChannel(CUALQUIER_CANAL_LIBRE, this->sonido_ak, CANTIDAD_DE_REPRODUCCIONES);
}

void Dibujador::reproducir_explosion(){
    Mix_PlayChannel(CUALQUIER_CANAL_LIBRE, this->sonido_explosion, CANTIDAD_DE_REPRODUCCIONES);
}

void Dibujador::reproducir_disparo_escopeta(){
    Mix_PlayChannel(CUALQUIER_CANAL_LIBRE, this->sonido_escopeta, CANTIDAD_DE_REPRODUCCIONES);
}

void Dibujador::reproducir_disparo_laser(){
    Mix_PlayChannel(CUALQUIER_CANAL_LIBRE, this->sonido_laser, CANTIDAD_DE_REPRODUCCIONES);
}

void Dibujador::reproducir_disparo_sniper(){
    Mix_PlayChannel(CUALQUIER_CANAL_LIBRE, this->sonido_sniper, CANTIDAD_DE_REPRODUCCIONES);
}

void Dibujador::reproducir_disparo_pistola(){
    Mix_PlayChannel(CUALQUIER_CANAL_LIBRE, this->sonido_pistola, CANTIDAD_DE_REPRODUCCIONES);
}

void Dibujador::renderizar(SDL2pp::Renderer& renderer) {
    EstadoJuego estado_actual;
    while (cola_estados.try_pop(estado_actual)) {
        this->ultimo_estado_recibido = estado_actual;
    }

    renderer.Clear();
    renderer.Copy(this->mapa);
    dibujar_estado_juego(this->ultimo_estado_recibido, renderer);
    renderer.Present();
}
