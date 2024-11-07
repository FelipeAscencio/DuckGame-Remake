#include "client_dibujador.h"

#define RUTA_SPR_PATO "/sprites-pato-blanco.png"
#define RUTA_SPR_AK "/sprites-ak47.png"
#define RUTA_SPR_CAJAS "/sprites-cajas.png"
#define RUTA_SPR_ARMADURAS "/sprites-armaduras.png"
#define RUTA_SPR_ESCOPETA "/sprites-escopeta.png"
#define RUTA_SPR_LASER "/sprites-laser.png"
#define RUTA_SPR_PISTOLA "/sprites-pistola.png"
#define ANCHO_VENTANA 960
#define ALTO_VENTANA 720
#define MAX_COORD_X 200
#define MAX_COORD_Y 160
#define ANGULO_NULO 0.0
#define ANGULO_270 270.0
#define ESCALA_SPRITES_GRANDES 0.07
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

Dibujador::Dibujador(Renderer& renderer, const std::string& ruta_mapa, const int id, Queue<EstadoJuego>& cola_recibidor):
        id_jugador(id), cola_estados(cola_recibidor), ultimo_estado_recibido(), parseador(),
        sprite_sheet_pato(renderer, DATA_PATH RUTA_SPR_PATO),
        sprite_sheet_ak(renderer, DATA_PATH RUTA_SPR_AK),
        sprite_sheet_caja(renderer, DATA_PATH RUTA_SPR_CAJAS),
        sprite_sheet_armadura(renderer, DATA_PATH RUTA_SPR_ARMADURAS),
        sprite_sheet_escopeta(renderer, DATA_PATH RUTA_SPR_ESCOPETA),
        sprite_sheet_laser(renderer, DATA_PATH RUTA_SPR_LASER),
        sprite_sheet_pistola(renderer, DATA_PATH RUTA_SPR_PISTOLA),
        mapa(renderer, (DATA_PATH + ruta_mapa).c_str()),
        sprites_pato(parseador.obtener_sprites_pato()),
        sprites_ak(parseador.obtener_sprites_ak()),
        sprites_caja(parseador.obtener_sprites_caja()),
        sprites_armadura(parseador.obtener_sprites_armadura()),
        sprites_escopeta(parseador.obtener_sprites_escopeta()),
        sprites_laser(parseador.obtener_sprites_laser()),
        sprites_pistola(parseador.obtener_sprites_pistola()) {}

// PROVISORIA PARA TESTEAR LOS PARSEOS.
void Dibujador::dibujar_sprites_fila(SDL2pp::Renderer& renderer, SDL2pp::Texture& sprite_sheet,
                                     const std::vector<SDL_Rect>& sprites, int ancho_ventana,
                                     int alto_ventana, float x, float y, float escala,
                                     float separacion) {
    int startX = static_cast<int>(ancho_ventana * x);
    int startY = static_cast<int>(alto_ventana * y);
    int ancho_escalado = static_cast<int>(ancho_ventana * escala);
    int alto_escalado = static_cast<int>(alto_ventana * escala);
    int gap = static_cast<int>(ancho_ventana * separacion);
    int contador = 0;

    for (size_t i = 0; i < sprites.size(); ++i) {
        if (contador >= 12) {
            contador = 0;
            startY += 50;
        }
        SDL_Rect dst_rect;
        dst_rect.x = startX + contador * (ancho_escalado + gap);
        dst_rect.y = startY;
        dst_rect.w = ancho_escalado;
        dst_rect.h = alto_escalado;
        renderer.Copy(sprite_sheet, sprites[i], dst_rect);
        contador++;
    }
}

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

    // Centramos el sprite en el eje 'X' y ponemos el '0' del eje 'Y' en la parte inferior del sprite.
    int dst_x = static_cast<int>(ancho_ventana * x) - (ancho_escalado / DOS);
    int dst_y = static_cast<int>(alto_ventana * y) - alto_escalado;
    return SDL2pp::Rect(dst_x, dst_y, ancho_escalado, alto_escalado);
}

void Dibujador::dibujar_pato_enemigo(SDL2pp::Renderer& renderer, SDL2pp::Texture& sprite_sheet,
                               const SDL_Rect& sprite, SDL2pp::Rect& dst_rect, const int id, const double angle, SDL_RendererFlip& flip){
    SDL_Color color_mod;
    if (id == UNO) { // ROJO
        color_mod = {MAX_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB};
    } else if (id == DOS) { // VERDE
        color_mod = {MIN_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB};
    } else if (id == TRES) { // AZUL
        color_mod = {MIN_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB};
    } else if (id == CUATRO) { // AMARILLO
        color_mod = {MAX_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB};
    } else if (id == CINCO) { // NARANJA
        color_mod = {MAX_INTENSIDAD_RGB, MED_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB};
    } else if (id == SEIS) { // VIOLETA
        color_mod = {MED_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB, MED_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB};
    } else if (id == SIETE) { // MARRON
        color_mod = {MED_INTENSIDAD_RGB, RGB_AUX_MARRON_1, RGB_AUX_MARRON_2, MAX_INTENSIDAD_RGB};
    } else if (id == OCHO) { // NEGRO
        color_mod = {MIN_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB, MIN_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB};
    }

    SDL_SetTextureColorMod(sprite_sheet.Get(), color_mod.r, color_mod.g, color_mod.b);
    renderer.Copy(sprite_sheet, SDL2pp::Optional<SDL2pp::Rect>(sprite), SDL2pp::Optional<SDL2pp::Rect>(dst_rect), angle, SDL2pp::Optional<SDL2pp::Point>(), flip);
    SDL_SetTextureColorMod(sprite_sheet.Get(), MAX_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB);
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

    if (id > CERO && id <= OCHO){
        if (id != this->id_jugador){
            dibujar_pato_enemigo(renderer, sprite_sheet, sprite, dst_rect, id, angle, flip);
            return;
        }
    }
    
    renderer.Copy(sprite_sheet, SDL2pp::Optional<SDL2pp::Rect>(sprite), SDL2pp::Optional<SDL2pp::Rect>(dst_rect), angle, SDL2pp::Optional<SDL2pp::Point>(), flip);
}

void Dibujador::dibujar_patos(EstadoJuego& estado_actual, SDL2pp::Renderer& renderer){
    float escala = ESCALA_SPRITES_GRANDES;
    int id;
    float x;
    float y;
    orientacion_e orientacion;
    estado_pato_e estado;
    for (auto& pato: estado_actual.info_patos){
        id = pato.id;
        x = pato.posicion.coordenada_x;
        y = pato.posicion.coordenada_y;
        orientacion = pato.orientacion;
        estado = pato.estado;
        if (estado == ESTADO_PARADO){
            auto [x_1, y_1] = convertir_a_relativo(x, y);
            dibujar_sprite(renderer, this->sprite_sheet_pato, this->sprites_pato[POS_SPRITE_PARADO], x_1, y_1, escala, orientacion, id);
        } else if (estado == ESTADO_AGACHADO){
            auto [x_1, y_1] = convertir_a_relativo(x, y);
            dibujar_sprite(renderer, this->sprite_sheet_pato, this->sprites_pato[POS_SPRITE_AGACHADO], x_1, y_1, escala, orientacion, id);
        } else if (estado == ESTADO_SALTANDO){
            auto [x_1, y_1] = convertir_a_relativo(x, y);
            dibujar_sprite(renderer, this->sprite_sheet_pato, this->sprites_pato[POS_SPRITE_SALTANDO], x_1, y_1, escala, orientacion, id);
        } else if (estado == ESTADO_ALETEANDO){
            auto [x_1, y_1] = convertir_a_relativo(x, y);
            dibujar_sprite(renderer, this->sprite_sheet_pato, this->sprites_pato[POS_SPRITE_ALETEANDO], x_1, y_1, escala, orientacion, id);
        } else if (estado == ESTADO_CAYENDO){
            auto [x_1, y_1] = convertir_a_relativo(x, y);
            dibujar_sprite(renderer, this->sprite_sheet_pato, this->sprites_pato[POS_SPRITE_CAYENDO], x_1, y_1, escala, orientacion, id);
        } else if (estado == ESTADO_CAMINANDO) {
            unsigned int current_ticks = SDL_GetTicks();
            int sprite_index = UNO + (current_ticks / DIEZ) % CANTIDAD_SPRITES_CAMINAR;
            auto [x_1, y_1] = convertir_a_relativo(x, y);
            dibujar_sprite(renderer, this->sprite_sheet_pato, this->sprites_pato[sprite_index], x_1, y_1, escala, orientacion, id);
        }
    }
}

void Dibujador::dibujar_estado_juego(EstadoJuego& estado_actual, SDL2pp::Renderer& renderer){
    dibujar_patos(estado_actual, renderer);
}

void Dibujador::renderizar(SDL2pp::Renderer& renderer) {
    EstadoJuego estado_actual;
    while (cola_estados.try_pop(estado_actual)){
        this->ultimo_estado_recibido = estado_actual;
    }

    renderer.Clear();
    renderer.Copy(this->mapa);
    dibujar_estado_juego(this->ultimo_estado_recibido, renderer);
    renderer.Present();
}
