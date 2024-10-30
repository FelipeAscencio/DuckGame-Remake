#include "client_dibujador.h"

#define RUTA_SPR_PATO "/sprites-pato-blanco.png"
#define RUTA_SPR_AK "/sprites-ak47.png"
#define RUTA_SPR_CAJAS "/sprites-cajas.png"
#define RUTA_SPR_ARMADURAS "/sprites-armaduras.png"
#define ANCHO_VENTANA 960
#define ALTO_VENTANA 720
#define MAX_COORD_X 250
#define MAX_COORD_Y 160
#define ANGULO_NULO 0.0
#define ANGULO_270 270.0
#define ESCALA_SPRITES_GRANDES 0.07
#define MAX_INTENSIDAD_RGB 255
#define CERO 0
#define UNO 1
#define DOS 2
#define TRES 3
#define CUATRO 4

using namespace SDL2pp;

Dibujador::Dibujador(Renderer& renderer, const std::string& ruta_mapa, const int id):
        id_jugador(id), parseador(),
        spriteSheetPato(renderer, DATA_PATH RUTA_SPR_PATO),
        spriteSheetAK(renderer, DATA_PATH RUTA_SPR_AK),
        spriteSheetCaja(renderer, DATA_PATH RUTA_SPR_CAJAS),
        spriteSheetArmadura(renderer, DATA_PATH RUTA_SPR_ARMADURAS),
        mapa(renderer, (DATA_PATH + ruta_mapa).c_str()),
        spritesPato(parseador.obtener_sprites_pato()),
        spritesAK(parseador.obtener_sprites_ak()),
        spritesCaja(parseador.obtener_sprites_caja()),
        spritesArmadura(parseador.obtener_sprites_armadura()) {}

std::pair<float, float> Dibujador::convertir_a_relativo(int x, int y) {
    float x_convertido = static_cast<float>(x) / MAX_COORD_X;
    float y_convertido = static_cast<float>(y) / MAX_COORD_Y;
    return {x_convertido, y_convertido};
}

SDL2pp::Rect Dibujador::calcular_dst_rect(float x, float y, float escala) {
    int anchoVentana = ANCHO_VENTANA;
    int altoVentana = ALTO_VENTANA;
    int scaledWidth = static_cast<int>(anchoVentana * escala);
    int scaledHeight = static_cast<int>(altoVentana * escala);

    // Centramos el sprite en el eje 'X' y ponemos el '0' del eje 'Y' en la parte inferior del sprite.
    int dstX = static_cast<int>(anchoVentana * x) - (scaledWidth / DOS);
    int dstY = static_cast<int>(altoVentana * y) - scaledHeight;
    return SDL2pp::Rect(dstX, dstY, scaledWidth, scaledHeight);
}

void Dibujador::dibujar_pato_enemigo(SDL2pp::Renderer& renderer, SDL2pp::Texture& spriteSheet,
                               const SDL_Rect& sprite, SDL2pp::Rect& dstRect, const int id, const double angle, SDL_RendererFlip& flip){
    SDL_Color colorMod;
    if (id == UNO) { // ROJO
        colorMod = {255, 0, 0, 255};
    } else if (id == DOS) { // VERDE
        colorMod = {0, 255, 0, 255};
    } else if (id == TRES) { // AZUL
        colorMod = {0, 0, 255, 255};
    } else { // AMARILLO
        colorMod = {255, 255, 0, 255};
    }

    SDL_SetTextureColorMod(spriteSheet.Get(), colorMod.r, colorMod.g, colorMod.b);
    renderer.Copy(spriteSheet, SDL2pp::Optional<SDL2pp::Rect>(sprite), SDL2pp::Optional<SDL2pp::Rect>(dstRect), angle, SDL2pp::Optional<SDL2pp::Point>(), flip);
    SDL_SetTextureColorMod(spriteSheet.Get(), MAX_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB);
}

void Dibujador::dibujar_sprite(SDL2pp::Renderer& renderer, SDL2pp::Texture& spriteSheet,
                               const SDL_Rect& sprite, float x, float y, float escala,
                               orientacion_e orientacion, const int id) {
    SDL2pp::Rect dstRect = calcular_dst_rect(x, y, escala);
    double angle = ANGULO_NULO;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (orientacion == IZQUIERDA) {
        flip = SDL_FLIP_HORIZONTAL;
    } else if (orientacion == ARRIBA) {
        angle = ANGULO_270;
    }

    if (id > CERO && id <= CUATRO){
        if (id != this->id_jugador){
            dibujar_pato_enemigo(renderer, spriteSheet, sprite, dstRect, id, angle, flip);
            return;
        }
    }
    
    renderer.Copy(spriteSheet, SDL2pp::Optional<SDL2pp::Rect>(sprite), SDL2pp::Optional<SDL2pp::Rect>(dstRect), angle, SDL2pp::Optional<SDL2pp::Point>(), flip);
}

void Dibujador::renderizar(SDL2pp::Renderer& renderer, const int estado) {
    renderer.Clear();
    renderer.Copy(this->mapa);
    float escala = ESCALA_SPRITES_GRANDES;
    unsigned int current_ticks = SDL_GetTicks();

    if (estado == 0) {
        int x = 100;
        int y = 100;
        auto [x_1, y_1] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_1, y_1, escala, DERECHA, 1);
        x = 150;
        y = 100;
        auto [x_2, y_2] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_2, y_2, escala, DERECHA, 2);
        x = 50;
        y = 100;
        auto [x_3, y_3] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_3, y_3, escala, DERECHA, 3);
        x = 200;
        y = 100;
        auto [x_4, y_4] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_4, y_4, escala, DERECHA, 4);
    } else if (estado == 1) {
        int x = 100;
        int y = 100;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_rel, y_rel, escala, DERECHA, 1);
    } if (estado == 2) {
        int x = 100;
        int y = 100;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        int spriteIndex = 1 + (current_ticks / 10) % 6;
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[spriteIndex], x_rel, y_rel, escala, DERECHA, 1);
    } else if (estado == 3) {
        int x = 100;
        int y = 100;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_rel, y_rel, escala, ARRIBA, 1);
    } else if (estado == 4){
        int x = 100;
        int y = 100;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[1], x_rel, y_rel, escala, DERECHA, 1);
    } else if (estado == 5) {
        int x = 100;
        int y = 100;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[1], x_rel, y_rel, escala, IZQUIERDA, 1);
    } else if (estado == 6) {
        int x = 100;
        int y = 100;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[1], x_rel, y_rel, escala, ARRIBA, 1);
    } else if (estado == 7) {
        int x = 100;
        int y = 100;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_rel, y_rel, escala, DERECHA, 1);
    }

    renderer.Present();
}
