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
#define SONIDO_QUACK "/Quack.mp3"
#define RUTA_WIN_SCREEN "/winscreen.png"
#define RUTA_LOSE_SCREEN "/losescreen.png"
#define RUTA_MAPA_1 "/mapa1.png"
#define RUTA_MAPA_2 "/mapa2.png"
#define ID_MAPA_OVERWORLD 1
#define ID_MAPA_INFIERNO 2
#define CUALQUIER_CANAL_LIBRE -1
#define CANTIDAD_DE_REPRODUCCIONES 0
#define SEGUIR_JUGANDO 253
#define FINAL_SLEEP 7
#define TAMANIO_FUENTE 24
#define ANCHO_VENTANA 960
#define ALTO_VENTANA 720
#define MAX_COORD_X 200
#define MAX_COORD_Y 160
#define OFFSET_MAPA_1 0.06
#define OFFSET_MAPA_2 0.03
#define OFFSET_Y_TABLERO 0.06
#define OFFSET_Y_ARMA 0.005
#define OFFSET_Y_SNIPER -0.02
#define OFFSET_Y_CASCO 0.023
#define OFFSET_X_CASCO_DER 0.005
#define OFFSET_X_CASCO_IZQ -0.005
#define OFFSET_Y_BALA 0.01
#define OFFSET_X_CASCO_AGACHADO_DER 0.025
#define OFFSET_X_CASCO_AGACHADO_IZQ -0.025
#define OFFSET_Y_CASCO_AGACHADO 0.018
#define OFFSET_Y_CAJA -0.005
#define OFFSET_ZOOM 100
#define ANGULO_NULO 0.0
#define ANGULO_90 90.0
#define ANGULO_270 270.0
#define ESCALA_SNIPER 1.0
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
#define POS_SPRITE_MUERTO 10
#define POS_SPRITE_SALTANDO 7
#define POS_SPRITE_ALETEANDO 11
#define POS_SPRITE_CAYENDO 8
#define OFFSET_SPRITES_PATO_CUACK 12
#define POS_ARMADURA 0
#define POS_CASCO 12
#define POS_ARMA 0
#define POS_BALA_UNICA 1
#define POS_CAJA_INTACTA 0
#define POS_CAJA_ROTA 2
#define POS_CAJA_MUY_ROTA 3
#define POS_CASCO 12
#define POS_INICIAL_PATO_TABLERO 10
#define GAP_PATO_TABLERO 0.1
#define X_INICIAL_PUNTAJE 100
#define Y_INICIAL_PUNTAJE 50
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
#define ID_GENERICO_ITEMS 9
#define ID_PEW_PEW_LASER 1
#define ID_AK 2
#define ID_MAGNUM 3
#define ID_SHOTGUN 4
#define ID_SNIPER 5

// Se decidio utilizar una variable global y no un atributo de la clase, porque
// conceptualmente este es un valor fijo, que solo oscila entre 2 valores y no
// depende del dibujador, sino del mapa actual.
float OFFSET_GENERAL_Y;  // '0.06' para el 'mapa 1' y '0.05' para el 'mapa 2'.

using namespace SDL2pp;

Dibujador::Dibujador(Renderer& renderer, const int id, Queue<EstadoJuego>& cola_recibidor):
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
        mapa1(renderer, DATA_PATH RUTA_MAPA_1),
        mapa2(renderer, DATA_PATH RUTA_MAPA_2),
        pantalla_victoria(renderer, DATA_PATH RUTA_WIN_SCREEN),
        pantalla_derrota(renderer, DATA_PATH RUTA_LOSE_SCREEN),
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
        sonido_sniper(Mix_LoadWAV((DATA_PATH SONIDO_SNIPER))),
        sonido_quack(Mix_LoadWAV((DATA_PATH SONIDO_QUACK))) {}

std::pair<float, float> Dibujador::convertir_a_relativo(float& x, float& y) {
    float x_convertido = static_cast<float>(x) / MAX_COORD_X;
    float y_convertido = static_cast<float>(y) / MAX_COORD_Y;
    return {x_convertido, y_convertido};
}

SDL2pp::Rect Dibujador::calcular_dst_rect(float& x, float& y, float& escala) {
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

void Dibujador::dibujar_pato_pintado(SDL2pp::Renderer& renderer, SDL2pp::Texture& sprite_sheet,
                                     const SDL_Rect& sprite, SDL2pp::Rect& dst_rect, const int& id,
                                     const double& angle, SDL_RendererFlip& flip) {
    SDL_Color color_mod;
    if (id == CERO) {  // ROJO
        color_mod = {MAX_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB,
                     MAX_INTENSIDAD_RGB};
    } else if (id == UNO) {  // VERDE
        color_mod = {MIN_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB,
                     MAX_INTENSIDAD_RGB};
    } else if (id == DOS) {  // AZUL
        color_mod = {MIN_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB,
                     MAX_INTENSIDAD_RGB};
    } else if (id == TRES) {  // AMARILLO
        color_mod = {MAX_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB,
                     MAX_INTENSIDAD_RGB};
    } else if (id == CUATRO) {  // NARANJA
        color_mod = {MAX_INTENSIDAD_RGB, MED_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB,
                     MAX_INTENSIDAD_RGB};
    } else if (id == CINCO) {  // VIOLETA
        color_mod = {MED_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB, MED_INTENSIDAD_RGB,
                     MAX_INTENSIDAD_RGB};
    } else if (id == SEIS) {  // MARRON
        color_mod = {MED_INTENSIDAD_RGB, RGB_AUX_MARRON_1, RGB_AUX_MARRON_2, MAX_INTENSIDAD_RGB};
    } else if (id == SIETE) {  // GRIS
        color_mod = {MED_INTENSIDAD_RGB, MED_INTENSIDAD_RGB, MED_INTENSIDAD_RGB,
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
                               const SDL_Rect& sprite, float x, float y, float& escala,
                               orientacion_e orientacion, const int& id) {
    SDL2pp::Rect dst_rect = calcular_dst_rect(x, y, escala);
    double angle = ANGULO_NULO;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (orientacion == IZQUIERDA) {
        flip = SDL_FLIP_HORIZONTAL;
    } else if (orientacion == ARRIBA) {
        angle = ANGULO_270;
    } else if (orientacion == ABAJO) {
        angle = ANGULO_90;
        flip = SDL_FLIP_HORIZONTAL;
    }

    if (id >= CERO && id < OCHO) {
        dibujar_pato_pintado(renderer, sprite_sheet, sprite, dst_rect, id, angle, flip);
        return;
    }

    renderer.Copy(sprite_sheet, SDL2pp::Optional<SDL2pp::Rect>(sprite),
                  SDL2pp::Optional<SDL2pp::Rect>(dst_rect), angle,
                  SDL2pp::Optional<SDL2pp::Point>(), flip);
}

void Dibujador::calcular_limites_camara(float& x_relativo, float& y_relativo) {
    this->x_min = std::min(this->x_min, static_cast<int>(x_relativo * ANCHO_VENTANA));
    this->y_min = std::min(this->y_min, static_cast<int>(y_relativo * ALTO_VENTANA));
    this->x_max = std::max(this->x_max, static_cast<int>(x_relativo * ANCHO_VENTANA));
    this->y_max = std::max(this->y_max, static_cast<int>(y_relativo * ALTO_VENTANA));
}

void Dibujador::dibujar_pato_vivo(SDL2pp::Renderer& renderer, float& escala, int& id,
                                  float& x_relativo, float& y_relativo, orientacion_e orientacion,
                                  estado_pato_e& estado, sonido_e& sonido) {
    calcular_limites_camara(x_relativo, y_relativo);
    if (orientacion == ARRIBA) {
        orientacion = DERECHA;  // Se corrige la orientacion del pato ya que lo que estara hacia
                                // arriba es el arma.
    }

    int offset_indice = CERO;
    if (sonido ==
        HACIENDO_CUAK) {  // Se suma un offset a la tira de sprites si esta haciendo 'quack'.
        offset_indice = OFFSET_SPRITES_PATO_CUACK;
    }

    if (estado == ESTADO_PARADO) {
        dibujar_sprite(renderer, this->sprite_sheet_pato,
                       this->sprites_pato[POS_SPRITE_PARADO + offset_indice], x_relativo,
                       y_relativo + (y_relativo * OFFSET_GENERAL_Y), escala, orientacion, id);
    } else if (estado == ESTADO_AGACHADO) {
        dibujar_sprite(renderer, this->sprite_sheet_pato,
                       this->sprites_pato[POS_SPRITE_AGACHADO + offset_indice], x_relativo,
                       y_relativo + (y_relativo * OFFSET_GENERAL_Y), escala, orientacion, id);
    } else if (estado == ESTADO_SALTANDO) {
        dibujar_sprite(renderer, this->sprite_sheet_pato,
                       this->sprites_pato[POS_SPRITE_SALTANDO + offset_indice], x_relativo,
                       y_relativo + (y_relativo * OFFSET_GENERAL_Y), escala, orientacion, id);
    } else if (estado == ESTADO_ALETEANDO) {
        dibujar_sprite(renderer, this->sprite_sheet_pato,
                       this->sprites_pato[POS_SPRITE_ALETEANDO + offset_indice], x_relativo,
                       y_relativo + (y_relativo * OFFSET_GENERAL_Y), escala, orientacion, id);
    } else if (estado == ESTADO_CAYENDO) {
        dibujar_sprite(renderer, this->sprite_sheet_pato,
                       this->sprites_pato[POS_SPRITE_CAYENDO + offset_indice], x_relativo,
                       y_relativo + (y_relativo * OFFSET_GENERAL_Y), escala, orientacion, id);
    } else if (estado == ESTADO_CAMINANDO) {
        unsigned int current_ticks = SDL_GetTicks();
        int sprite_index = UNO + (current_ticks / DIEZ) % CANTIDAD_SPRITES_CAMINAR;
        dibujar_sprite(renderer, this->sprite_sheet_pato,
                       this->sprites_pato[sprite_index + offset_indice], x_relativo,
                       y_relativo + (y_relativo * OFFSET_GENERAL_Y), escala, orientacion, id);
    }
}

void Dibujador::dibujar_armadura_pato(SDL2pp::Renderer& renderer, float& escala, float& x_relativo,
                                      float& y_relativo, orientacion_e orientacion,
                                      estado_pato_e& estado) {
    if (orientacion == ARRIBA) {
        orientacion = DERECHA;
    }

    if (estado == ESTADO_PARADO) {
        dibujar_sprite(renderer, this->sprite_sheet_equipamiento,
                       this->sprites_equipamiento[POS_SPRITE_PARADO], x_relativo,
                       y_relativo + (y_relativo * OFFSET_GENERAL_Y), escala, orientacion,
                       ID_GENERICO_ITEMS);
    } else if (estado == ESTADO_AGACHADO) {
        dibujar_sprite(renderer, this->sprite_sheet_equipamiento,
                       this->sprites_equipamiento[POS_SPRITE_AGACHADO], x_relativo,
                       y_relativo + (y_relativo * OFFSET_GENERAL_Y), escala, orientacion,
                       ID_GENERICO_ITEMS);
    } else if (estado == ESTADO_SALTANDO) {
        dibujar_sprite(renderer, this->sprite_sheet_equipamiento,
                       this->sprites_equipamiento[POS_SPRITE_SALTANDO], x_relativo,
                       y_relativo + (y_relativo * OFFSET_GENERAL_Y), escala, orientacion,
                       ID_GENERICO_ITEMS);
    } else if (estado == ESTADO_ALETEANDO) {
        dibujar_sprite(renderer, this->sprite_sheet_equipamiento,
                       this->sprites_equipamiento[POS_SPRITE_ALETEANDO], x_relativo,
                       y_relativo + (y_relativo * OFFSET_GENERAL_Y), escala, orientacion,
                       ID_GENERICO_ITEMS);
    } else if (estado == ESTADO_CAYENDO) {
        dibujar_sprite(renderer, this->sprite_sheet_equipamiento,
                       this->sprites_equipamiento[POS_SPRITE_CAYENDO], x_relativo,
                       y_relativo + (y_relativo * OFFSET_GENERAL_Y), escala, orientacion,
                       ID_GENERICO_ITEMS);
    } else if (estado == ESTADO_CAMINANDO) {
        unsigned int current_ticks = SDL_GetTicks();
        int sprite_index = UNO + (current_ticks / DIEZ) % CANTIDAD_SPRITES_CAMINAR;
        dibujar_sprite(renderer, this->sprite_sheet_equipamiento,
                       this->sprites_equipamiento[sprite_index], x_relativo,
                       y_relativo + (y_relativo * OFFSET_GENERAL_Y), escala, orientacion,
                       ID_GENERICO_ITEMS);
    }
}

void Dibujador::dibujar_sniper(SDL2pp::Renderer& renderer, float x, float y,
                               orientacion_e orientacion) {
    const int ancho_ventana = ANCHO_VENTANA;
    const int alto_ventana = ALTO_VENTANA;
    const SDL_Rect& sprite = this->sprites_sniper[POS_ARMA];
    int escala = ESCALA_SNIPER;
    int ancho_escalado = static_cast<int>(DOS * sprite.w * escala);
    int alto_escalado = static_cast<int>(DOS * sprite.h * escala);

    // Centramos el sprite en el eje 'X' y ponemos el '0' del eje 'Y' en la parte inferior del
    // sprite.
    int dst_x = static_cast<int>(ancho_ventana * x) - (ancho_escalado / DOS);
    int dst_y = static_cast<int>(alto_ventana * y) - alto_escalado;
    SDL2pp::Rect dst_rect(dst_x, dst_y, ancho_escalado, alto_escalado);
    double angle = ANGULO_NULO;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (orientacion == IZQUIERDA) {
        flip = SDL_FLIP_HORIZONTAL;
    } else if (orientacion == ARRIBA) {
        angle = ANGULO_270;
    } else if (orientacion == ABAJO) {
        angle = ANGULO_90;
        flip = SDL_FLIP_HORIZONTAL;
    }

    renderer.Copy(this->sprite_sheet_sniper, SDL2pp::Optional<SDL2pp::Rect>(sprite),
                  SDL2pp::Optional<SDL2pp::Rect>(dst_rect), angle,
                  SDL2pp::Optional<SDL2pp::Point>(), flip);
}

void Dibujador::renderizar_sniper(SDL2pp::Renderer& renderer, float& x_relativo, float& y_relativo,
                                  orientacion_e& orientacion, estado_pato_e& estado) {
    float offset_y = (y_relativo * OFFSET_GENERAL_Y) + OFFSET_Y_SNIPER;
    if (estado == ESTADO_AGACHADO) {
        if (orientacion == DERECHA) {
            dibujar_sniper(renderer, x_relativo, y_relativo + offset_y, ARRIBA);
        } else {
            dibujar_sniper(renderer, x_relativo, y_relativo + offset_y, ABAJO);
        }
    } else {
        dibujar_sniper(renderer, x_relativo, y_relativo + offset_y, orientacion);
    }
}

void Dibujador::dibujar_arma_pato(SDL2pp::Renderer& renderer, float& escala, float& x_relativo,
                                  float& y_relativo, orientacion_e& orientacion,
                                  estado_pato_e& estado, int& id_arma) {
    SDL2pp::Texture* sprite_sheet = nullptr;
    std::vector<SDL_Rect>* sprites = nullptr;
    if (id_arma == ID_PEW_PEW_LASER) {
        sprite_sheet = &this->sprite_sheet_laser;
        sprites = &this->sprites_laser;
    } else if (id_arma == ID_AK) {
        sprite_sheet = &this->sprite_sheet_ak;
        sprites = &this->sprites_ak;
    } else if (id_arma == ID_MAGNUM) {
        sprite_sheet = &this->sprite_sheet_pistola;
        sprites = &this->sprites_pistola;
    } else if (id_arma == ID_SHOTGUN) {
        sprite_sheet = &this->sprite_sheet_escopeta;
        sprites = &this->sprites_escopeta;
    } else if (id_arma == ID_SNIPER) {
        renderizar_sniper(renderer, x_relativo, y_relativo, orientacion, estado);
        return;
    }

    float offset_y = (y_relativo * OFFSET_GENERAL_Y) + OFFSET_Y_ARMA;
    if (estado == ESTADO_AGACHADO) {
        if (orientacion == DERECHA) {
            dibujar_sprite(renderer, *sprite_sheet, (*sprites)[POS_ARMA], x_relativo,
                           y_relativo + offset_y, escala, ARRIBA, ID_GENERICO_ITEMS);
        } else {
            dibujar_sprite(renderer, *sprite_sheet, (*sprites)[POS_ARMA], x_relativo,
                           y_relativo + offset_y, escala, ABAJO, ID_GENERICO_ITEMS);
        }
    } else {
        dibujar_sprite(renderer, *sprite_sheet, (*sprites)[POS_ARMA], x_relativo,
                       y_relativo + offset_y, escala, orientacion, ID_GENERICO_ITEMS);
    }
}

void Dibujador::dibujar_casco_pato(SDL2pp::Renderer& renderer, float& escala, float& x_relativo,
                                   float& y_relativo, orientacion_e orientacion,
                                   estado_pato_e& estado) {
    if (orientacion == ARRIBA) {
        orientacion = DERECHA;
    }

    float offset_x;
    float offset_y = (y_relativo * OFFSET_GENERAL_Y);
    if (orientacion == DERECHA) {
        offset_x = OFFSET_X_CASCO_DER;
    } else if (orientacion == IZQUIERDA) {
        offset_x = OFFSET_X_CASCO_IZQ;
    }

    if (estado == ESTADO_AGACHADO) {
        offset_y += OFFSET_Y_CASCO_AGACHADO;
        if (orientacion == DERECHA) {
            offset_x = OFFSET_X_CASCO_AGACHADO_DER;
            dibujar_sprite(renderer, this->sprite_sheet_equipamiento,
                           this->sprites_equipamiento[POS_CASCO], x_relativo - offset_x,
                           y_relativo + offset_y, escala, ARRIBA, ID_GENERICO_ITEMS);
        } else {
            offset_x = OFFSET_X_CASCO_AGACHADO_IZQ;
            dibujar_sprite(renderer, this->sprite_sheet_equipamiento,
                           this->sprites_equipamiento[POS_CASCO], x_relativo - offset_x,
                           y_relativo + offset_y, escala, ABAJO, ID_GENERICO_ITEMS);
        }
    } else {
        offset_y -= OFFSET_Y_CASCO;
        dibujar_sprite(renderer, this->sprite_sheet_equipamiento,
                       this->sprites_equipamiento[POS_CASCO], x_relativo - offset_x,
                       y_relativo + offset_y, escala, orientacion, ID_GENERICO_ITEMS);
    }
}

void Dibujador::reproducir_disparo_ak() {
    Mix_PlayChannel(CUALQUIER_CANAL_LIBRE, this->sonido_ak, CANTIDAD_DE_REPRODUCCIONES);
}

void Dibujador::reproducir_explosion() {
    Mix_PlayChannel(CUALQUIER_CANAL_LIBRE, this->sonido_explosion, CANTIDAD_DE_REPRODUCCIONES);
}

void Dibujador::reproducir_disparo_escopeta() {
    Mix_PlayChannel(CUALQUIER_CANAL_LIBRE, this->sonido_escopeta, CANTIDAD_DE_REPRODUCCIONES);
}

void Dibujador::reproducir_disparo_laser() {
    Mix_PlayChannel(CUALQUIER_CANAL_LIBRE, this->sonido_laser, CANTIDAD_DE_REPRODUCCIONES);
}

void Dibujador::reproducir_disparo_sniper() {
    Mix_PlayChannel(CUALQUIER_CANAL_LIBRE, this->sonido_sniper, CANTIDAD_DE_REPRODUCCIONES);
}

void Dibujador::reproducir_disparo_pistola() {
    Mix_PlayChannel(CUALQUIER_CANAL_LIBRE, this->sonido_pistola, CANTIDAD_DE_REPRODUCCIONES);
}

void Dibujador::reproducir_quack() {
    Mix_PlayChannel(CUALQUIER_CANAL_LIBRE, this->sonido_quack, CANTIDAD_DE_REPRODUCCIONES);
}

void Dibujador::reproducir_sonido_pato(const int& id_arma, const sonido_e& sonido) {
    if (sonido == HACIENDO_CUAK) {
        reproducir_quack();
    } else {
        if (id_arma == ID_MAGNUM) {
            reproducir_disparo_pistola();
        } else if (id_arma == ID_AK) {
            reproducir_disparo_ak();
        } else if (id_arma == ID_SHOTGUN) {
            reproducir_disparo_escopeta();
        } else if (id_arma == ID_PEW_PEW_LASER) {
            reproducir_disparo_laser();
        } else if (id_arma == ID_SNIPER) {
            reproducir_disparo_sniper();
        }
    }
}

void Dibujador::dibujar_patos(EstadoJuego& estado_actual, SDL2pp::Renderer& renderer) {
    for (auto& pato: estado_actual.info_patos) {
        float escala = ESCALA_SPRITES_GRANDES;
        int id = pato.id;
        float x = pato.posicion.coordenada_x;
        float y = pato.posicion.coordenada_y;
        bool esta_vivo = pato.vivo;
        bool tiene_arma = pato.arma;
        int id_arma = pato.id_arma_equipada;
        bool tiene_casco = pato.casco;
        bool tiene_armadura = pato.armadura;
        orientacion_e orientacion = pato.orientacion;
        estado_pato_e estado = pato.estado;
        sonido_e sonido = pato.sonido;
        auto [x_relativo, y_relativo] = convertir_a_relativo(x, y);
        if (esta_vivo == false) {
            dibujar_sprite(renderer, this->sprite_sheet_pato, this->sprites_pato[POS_SPRITE_MUERTO],
                           x_relativo, y_relativo + (y_relativo * OFFSET_GENERAL_Y), escala,
                           orientacion, id);
        } else {
            dibujar_pato_vivo(renderer, escala, id, x_relativo, y_relativo, orientacion, estado,
                              sonido);
            if (tiene_armadura) {
                dibujar_armadura_pato(renderer, escala, x_relativo, y_relativo, orientacion,
                                      estado);
            }

            if (tiene_casco) {
                dibujar_casco_pato(renderer, escala, x_relativo, y_relativo, orientacion, estado);
            }

            if (tiene_arma) {
                dibujar_arma_pato(renderer, escala, x_relativo, y_relativo, orientacion, estado,
                                  id_arma);
            }

            if (sonido != SILENCIO) {
                reproducir_sonido_pato(id_arma, sonido);
            }
        }
    }
}

SDL2pp::Texture* Dibujador::obtener_sprite_sheet_arma_bala(int& id_arma) {
    if (id_arma == ID_PEW_PEW_LASER) {
        return &this->sprite_sheet_laser;
    } else if (id_arma == ID_AK) {
        return &this->sprite_sheet_ak;
    } else if (id_arma == ID_MAGNUM) {
        return &this->sprite_sheet_pistola;
    } else if (id_arma == ID_SHOTGUN) {
        return &this->sprite_sheet_escopeta;
    } else if (id_arma == ID_SNIPER) {
        return &this->sprite_sheet_sniper;
    }

    return nullptr;
}

std::vector<SDL_Rect>* Dibujador::obtener_sprites_arma_bala(int& id_arma) {
    if (id_arma == ID_PEW_PEW_LASER) {
        return &this->sprites_laser;
    } else if (id_arma == ID_AK) {
        return &this->sprites_ak;
    } else if (id_arma == ID_MAGNUM) {
        return &this->sprites_pistola;
    } else if (id_arma == ID_SHOTGUN) {
        return &this->sprites_escopeta;
    } else if (id_arma == ID_SNIPER) {
        return &this->sprites_sniper;
    }

    return nullptr;
}

int Dibujador::obtener_indice_sprite(inclinacion_e& inclinacion) {
    if (inclinacion == NO_TIENE) {
        return UNO;
    } else if (inclinacion == PARA_ABAJO) {
        return DOS;
    } else {
        return TRES;
    }

    return CERO;
}

void Dibujador::dibujar_balas(EstadoJuego& estado_actual, SDL2pp::Renderer& renderer) {
    for (auto& bala: estado_actual.info_balas) {
        float escala = ESCALA_SPRITES_CHICOS;
        float x = bala.pos.coordenada_x;
        float y = bala.pos.coordenada_y;
        int id_bala = bala.id_arma;
        SDL2pp::Texture* sprite_sheet = obtener_sprite_sheet_arma_bala(id_bala);
        std::vector<SDL_Rect>* sprites = obtener_sprites_arma_bala(id_bala);
        inclinacion_e inclinacion = bala.inclinacion;
        orientacion_e orientacion = bala.direccion;
        int indice;
        if (id_bala == ID_MAGNUM || id_bala == ID_SHOTGUN) {
            indice = obtener_indice_sprite(inclinacion);
            escala = ESCALA_SPRITES_MEDIANOS;
        } else {
            indice = POS_BALA_UNICA;
        }

        auto [x_relativo, y_relativo] = convertir_a_relativo(x, y);
        float offset_y = (y_relativo * OFFSET_GENERAL_Y) + OFFSET_Y_BALA;
        dibujar_sprite(renderer, *sprite_sheet, (*sprites)[indice], x_relativo,
                       y_relativo + offset_y, escala, orientacion, ID_GENERICO_ITEMS);
    }
}

void Dibujador::dibujar_armas(EstadoJuego& estado_actual, SDL2pp::Renderer& renderer) {
    for (auto& arma: estado_actual.info_armas) {
        float escala = ESCALA_SPRITES_GRANDES;
        float x = arma.posicion.coordenada_x;
        float y = arma.posicion.coordenada_y;
        int id_arma = arma.id_arma;
        SDL2pp::Texture* sprite_sheet = obtener_sprite_sheet_arma_bala(id_arma);
        std::vector<SDL_Rect>* sprites = obtener_sprites_arma_bala(id_arma);
        orientacion_e orientacion = DERECHA;
        auto [x_relativo, y_relativo] = convertir_a_relativo(x, y);
        float offset_y = (y_relativo * OFFSET_GENERAL_Y);
        if (id_arma == ID_SNIPER) {
            offset_y += OFFSET_Y_SNIPER;
            dibujar_sniper(renderer, x_relativo, y_relativo + offset_y, orientacion);
            return;
        }
        dibujar_sprite(renderer, *sprite_sheet, (*sprites)[POS_ARMA], x_relativo,
                       y_relativo + offset_y, escala, orientacion, ID_GENERICO_ITEMS);
    }
}

void Dibujador::dibujar_cascos(EstadoJuego& estado_actual, SDL2pp::Renderer& renderer) {
    for (auto& casco: estado_actual.info_cascos) {
        float escala = ESCALA_SPRITES_GRANDES;
        float x = casco.coordenada_x;
        float y = casco.coordenada_y;
        orientacion_e orientacion = DERECHA;
        auto [x_relativo, y_relativo] = convertir_a_relativo(x, y);
        float offset_y = (y_relativo * OFFSET_GENERAL_Y);
        dibujar_sprite(renderer, this->sprite_sheet_equipamiento,
                       this->sprites_equipamiento[POS_CASCO], x_relativo, y_relativo + offset_y,
                       escala, orientacion, ID_GENERICO_ITEMS);
    }
}

void Dibujador::dibujar_armaduras(EstadoJuego& estado_actual, SDL2pp::Renderer& renderer) {
    for (auto& armadura: estado_actual.info_armaduras) {
        float escala = ESCALA_SPRITES_GRANDES;
        float x = armadura.coordenada_x;
        float y = armadura.coordenada_y;
        orientacion_e orientacion = DERECHA;
        auto [x_relativo, y_relativo] = convertir_a_relativo(x, y);
        float offset_y = (y_relativo * OFFSET_GENERAL_Y);
        dibujar_sprite(renderer, this->sprite_sheet_equipamiento,
                       this->sprites_equipamiento[POS_ARMADURA], x_relativo, y_relativo + offset_y,
                       escala, orientacion, ID_GENERICO_ITEMS);
    }
}

void Dibujador::dibujar_cajas(EstadoJuego& estado_actual, SDL2pp::Renderer& renderer) {
    for (auto& caja: estado_actual.info_cajas) {
        float escala = ESCALA_SPRITES_GRANDES;
        float x = caja.posicion.coordenada_x;
        float y = caja.posicion.coordenada_y;
        damage_e estado_caja = caja.estado;
        orientacion_e orientacion = DERECHA;
        int indice;
        if (estado_caja == INTACTA) {
            indice = POS_CAJA_INTACTA;
        } else if (estado_caja == ROTA) {
            indice = POS_CAJA_ROTA;
        } else {
            indice = POS_CAJA_MUY_ROTA;
        }

        auto [x_relativo, y_relativo] = convertir_a_relativo(x, y);
        float offset_y = (y_relativo * OFFSET_GENERAL_Y) + OFFSET_Y_CAJA;
        dibujar_sprite(renderer, this->sprite_sheet_caja, this->sprites_caja[indice], x_relativo,
                       y_relativo + offset_y, escala, orientacion, ID_GENERICO_ITEMS);
    }
}

void Dibujador::dibujar_estado_juego(EstadoJuego& estado_actual, SDL2pp::Renderer& renderer) {
    if (estado_actual.id_mapa == ID_MAPA_OVERWORLD) {
        renderer.Copy(this->mapa1);
        OFFSET_GENERAL_Y = OFFSET_MAPA_1;
    } else if (estado_actual.id_mapa == ID_MAPA_INFIERNO) {
        renderer.Copy(this->mapa2);
        OFFSET_GENERAL_Y = OFFSET_MAPA_2;
    }

    dibujar_cajas(estado_actual, renderer);
    dibujar_armas(estado_actual, renderer);
    dibujar_cascos(estado_actual, renderer);
    dibujar_armaduras(estado_actual, renderer);
    dibujar_patos(estado_actual, renderer);
    dibujar_balas(estado_actual, renderer);
}

void Dibujador::dibujar_patos_tablero(SDL2pp::Renderer& renderer) {
    float escala = ESCALA_SPRITES_GRANDES;
    float x = POS_INICIAL_PATO_TABLERO;
    float y = POS_INICIAL_PATO_TABLERO;
    orientacion_e orientacion = DERECHA;
    auto [x_relativo, y_relativo] = convertir_a_relativo(x, y);
    for (int i = CERO; i < OCHO; ++i) {
        dibujar_sprite(renderer, this->sprite_sheet_pato, this->sprites_pato[POS_SPRITE_PARADO],
                       x_relativo, y_relativo + (i * GAP_PATO_TABLERO) + OFFSET_Y_TABLERO, escala,
                       orientacion, i);
    }
}

void Dibujador::reiniciar_valores_zoom() {
    this->x_min = ANCHO_VENTANA;
    this->y_min = ALTO_VENTANA;
    this->x_max = CERO;
    this->y_max = CERO;
}

void Dibujador::verificar_valores_zoom() {
    this->x_min -= OFFSET_ZOOM;
    this->y_min -= OFFSET_ZOOM;
    this->x_max += OFFSET_ZOOM;
    this->y_max += OFFSET_ZOOM;
    if (this->x_min < CERO) this->x_min = CERO;
    if (this->y_min < CERO) this->y_min = CERO;
    if (this->x_max > ANCHO_VENTANA) this->x_max = ANCHO_VENTANA;
    if (this->y_max > ALTO_VENTANA) this->y_max = ALTO_VENTANA;
    int ancho_actual = this->x_max - this->x_min;
    int alto_actual = this->y_max - this->y_min;

    // Calcula la relacion de aspecto de la ventana (La que buscamos es 4:3).
    const float relacion_aspecto = static_cast<float>(ANCHO_VENTANA) / ALTO_VENTANA;

    // Ajustar el rectangulo visible para mantener la relacion de aspecto
    float ancho_deseado = alto_actual * relacion_aspecto;
    float alto_deseado = ancho_actual / relacion_aspecto;

    // Si el ancho actual es mayor al deseado, ajustamos el alto.
    if (ancho_actual > ancho_deseado) {
        int ajuste = (alto_actual - static_cast<int>(ancho_actual / relacion_aspecto)) / DOS;
        this->y_min += ajuste;
        this->y_max -= ajuste;
    }

    // Si el alto actual es mayor al deseado, ajustamos el ancho.
    else if (alto_actual > alto_deseado) {
        int ajuste = (ancho_actual - static_cast<int>(alto_actual * relacion_aspecto)) / DOS;
        this->x_min += ajuste;
        this->x_max -= ajuste;
    }
}

void Dibujador::mostrar_estado_juego(SDL2pp::Renderer& renderer) {
    SDL2pp::Texture textura_escena(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                   ANCHO_VENTANA, ALTO_VENTANA);
    renderer.SetTarget(textura_escena);
    renderer.Clear();
    reiniciar_valores_zoom();
    dibujar_estado_juego(this->ultimo_estado_recibido, renderer);
    verificar_valores_zoom();
    renderer.SetTarget();
    SDL_Rect area_visible = {this->x_min, this->y_min, (this->x_max - this->x_min),
                             (this->y_max - this->y_min)};
    renderer.Copy(textura_escena, area_visible, SDL2pp::NullOpt);
    renderer.Present();
}

void Dibujador::dibujar_puntos_tablero(SDL2pp::Renderer& renderer,
                                       const std::vector<int>& puntajes) {
    if (TTF_Init() == MENOS_UNO) {
        std::cerr << MSJ_ERROR_TFF << TTF_GetError() << std::endl;
        return;
    }

    TTF_Font* fuente = TTF_OpenFont(DATA_PATH RUTA_FUENTE, TAMANIO_FUENTE);
    int pos_x = X_INICIAL_PUNTAJE;
    int pos_y = Y_INICIAL_PUNTAJE;
    int separacion_y = GAP_PUNTAJE_TABLERO;
    for (size_t i = CERO; i < puntajes.size(); ++i) {
        std::string texto_puntaje = PUNTAJE_STR + std::to_string(puntajes[i]);
        SDL_Color color_texto = {MAX_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB,
                                 MAX_INTENSIDAD_RGB};  // COLOR BLANCO.
        SDL_Surface* temp_surface =
                TTF_RenderText_Solid(fuente, texto_puntaje.c_str(), color_texto);
        if (!temp_surface) {
            throw std::runtime_error(MSJ_ERROR_RENDER_TXT + std::string(TTF_GetError()));
        }

        SDL2pp::Surface superficie_texto(temp_surface);
        SDL2pp::Texture textura_texto(renderer, superficie_texto);
        renderer.Copy(
                textura_texto, SDL2pp::NullOpt,
                SDL2pp::Rect(pos_x, pos_y, textura_texto.GetWidth(), textura_texto.GetHeight()));
        pos_y += separacion_y;
    }

    TTF_CloseFont(fuente);
    TTF_Quit();
}

void Dibujador::dibujar_tablero(SDL2pp::Renderer& renderer) {
    std::vector<int> puntajes(OCHO, CERO);
    for (const auto& pato: this->ultimo_estado_recibido.info_patos) {
        int id = pato.id;
        puntajes[id] = pato.rondas_ganadas;
    }

    dibujar_patos_tablero(renderer);
    dibujar_puntos_tablero(renderer, puntajes);
    renderer.Present();
}

void Dibujador::renderizar(SDL2pp::Renderer& renderer, bool& jugador_activo) {
    EstadoJuego estado_actual;
    while (cola_estados.try_pop(estado_actual)) {
        this->ultimo_estado_recibido = estado_actual;
    }

    renderer.Clear();
    if (estado_actual.id_ganador == SEGUIR_JUGANDO) {
        if (estado_actual.ingame == false) {
            if ((estado_actual.rondas_jugadas % CINCO) == CERO &&
                estado_actual.rondas_jugadas != CERO) {
                dibujar_tablero(renderer);
                return;
            }
        }

        mostrar_estado_juego(renderer);
    } else {
        jugador_activo = false;
        if (estado_actual.id_ganador == this->id_jugador) {
            renderer.Copy(this->pantalla_victoria);
        } else {
            renderer.Copy(this->pantalla_derrota);
        }

        renderer.Present();
        std::this_thread::sleep_for(std::chrono::seconds(FINAL_SLEEP));
    }
}
