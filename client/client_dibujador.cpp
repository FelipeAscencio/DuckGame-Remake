#include "client_dibujador.h"

#define RUTA_SPR_PATO "/sprites-pato-blanco.png"
#define RUTA_SPR_AK "/sprites-ak47.png"
#define RUTA_SPR_CAJAS "/sprites-cajas.png"
#define RUTA_SPR_ARMADURAS "/sprites-armaduras.png"
#define ANCHO_VENTANA 960
#define ALTO_VENTANA 720
#define MAX_COORD_X 250
#define MAX_COORD_Y 160
#define DOS 2
#define ANGULO_NULO 0.0
#define ANGULO_270 270.0
#define ESCALA_SPRITES_GRANDES 0.07

using namespace SDL2pp;

Dibujador::Dibujador(Renderer& renderer, const std::string& ruta_mapa):
        parseador(),
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

SDL2pp::Rect Dibujador::calcularDstRect(float x, float y, float escala) {
    int anchoVentana = ANCHO_VENTANA;
    int altoVentana = ALTO_VENTANA;
    int scaledWidth = static_cast<int>(anchoVentana * escala);
    int scaledHeight = static_cast<int>(altoVentana * escala);

    // Centramos el sprite en el eje 'X' y ponemos el '0' del eje 'Y' en la parte inferior del sprite.
    int dstX = static_cast<int>(anchoVentana * x) - (scaledWidth / DOS);
    int dstY = static_cast<int>(altoVentana * y) - scaledHeight;
    return SDL2pp::Rect(dstX, dstY, scaledWidth, scaledHeight);
}

void Dibujador::dibujar_sprite(SDL2pp::Renderer& renderer, SDL2pp::Texture& spriteSheet,
                               const SDL_Rect& sprite, float x, float y, float escala,
                               orientacion_e orientacion) {
    SDL2pp::Rect dstRect = calcularDstRect(x, y, escala);
    double angle = ANGULO_NULO;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (orientacion == IZQUIERDA) {
        flip = SDL_FLIP_HORIZONTAL;
    } else if (orientacion == ARRIBA) {
        angle = ANGULO_270;
    }

    renderer.Copy(spriteSheet, SDL2pp::Optional<SDL2pp::Rect>(sprite), SDL2pp::Optional<SDL2pp::Rect>(dstRect), angle, SDL2pp::Optional<SDL2pp::Point>(), flip);
}

void Dibujador::renderizar(SDL2pp::Renderer& renderer, const int estado) {
    renderer.Clear();
    renderer.Copy(this->mapa);
    float escala = ESCALA_SPRITES_GRANDES;

    if (estado == 0) {
        int x = 100;
        int y = 100;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_rel, y_rel, escala, DERECHA);
    } else if (estado == 1) {
        int x = 100;
        int y = 100;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_rel, y_rel, escala, DERECHA);
    } else if (estado == 2) {
        int x = 100;
        int y = 100;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_rel, y_rel, escala, IZQUIERDA);
    } else if (estado == 3) {
        int x = 100;
        int y = 100;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_rel, y_rel, escala, ARRIBA);
    } else if (estado == 4){
        int x = 100;
        int y = 100;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[1], x_rel, y_rel, escala, DERECHA);
    } else if (estado == 5) {
        int x = 100;
        int y = 100;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[1], x_rel, y_rel, escala, IZQUIERDA);
    } else if (estado == 6) {
        int x = 100;
        int y = 100;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[1], x_rel, y_rel, escala, ARRIBA);
    } else if (estado == 7) {
        int x = 100;
        int y = 100;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_rel, y_rel, escala, DERECHA);
    }

    renderer.Present();
}
