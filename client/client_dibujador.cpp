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

void Dibujador::dibujar_sprites_fila(SDL2pp::Renderer& renderer, SDL2pp::Texture& spriteSheet,
                                     const std::vector<SDL_Rect>& sprites, float x, float y, float escala,
                                     float separacion) {
    int anchoVentana = ANCHO_VENTANA;
    int altoVentana = ALTO_VENTANA;
    int startX = static_cast<int>(anchoVentana * x);
    int startY = static_cast<int>(altoVentana * y);
    int scaledWidth = static_cast<int>(anchoVentana * escala);
    int scaledHeight = static_cast<int>(altoVentana * escala);
    int gap = static_cast<int>(anchoVentana * separacion);
    int contador = 0;

    for (size_t i = 0; i < sprites.size(); ++i) {
        if (contador >= 12) {
            contador = 0;
            startY += 50;
        }
        SDL_Rect dstRect;
        dstRect.x = startX + contador * (scaledWidth + gap);
        dstRect.y = startY;
        dstRect.w = scaledWidth;
        dstRect.h = scaledHeight;
        renderer.Copy(spriteSheet, sprites[i], dstRect);
        contador++;
    }
}

void Dibujador::dibujar_sprite(SDL2pp::Renderer& renderer, SDL2pp::Texture& spriteSheet,
                               const SDL_Rect& sprite, float x, float y, float escala) {
    int anchoVentana = ANCHO_VENTANA;
    int altoVentana = ALTO_VENTANA;
    int scaledWidth = static_cast<int>(anchoVentana * escala);
    int scaledHeight = static_cast<int>(altoVentana * escala);
    
    // Centramos el 'sprite' en 'X', y establecemos el piso del sprite como el '0' en 'Y'.
    int dstX = static_cast<int>(anchoVentana * x) - (scaledWidth / DOS);
    int dstY = static_cast<int>(altoVentana * y) - scaledHeight;
    SDL_Rect dstRect;
    dstRect.x = dstX;
    dstRect.y = dstY;
    dstRect.w = scaledWidth;
    dstRect.h = scaledHeight;

    renderer.Copy(spriteSheet, sprite, dstRect);
}

void Dibujador::renderizar(SDL2pp::Renderer& renderer, const int estado) {
    renderer.Clear();
    renderer.Copy(this->mapa);
    
    float escala = 0.07;  // Ajustar escala como desees para cada sprite
    float x = 0.01;        // Coordenada X (entre 0.0 y 1.0)
    float y = 0.2;        // Coordenada Y (entre 0.0 y 1.0)

    if (estado == 0) {
        float separacion = 0.01;
        dibujar_sprites_fila(renderer, this->spriteSheetPato, this->spritesPato, x, y, escala, separacion);
    } else if (estado == 1) {
        int x = 0;
        int y = 0;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_rel, y_rel, escala);
    } else if (estado == 2) {
        int x = 10;
        int y = 0;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_rel, y_rel, escala);
    } else if (estado == 3) {
        int x = 0;
        int y = 10;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_rel, y_rel, escala);
    } else if (estado == 4){
        int x = 250;
        int y = 160;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_rel, y_rel, escala);
    } else if (estado == 5) {
        int x = 240;
        int y = 160;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_rel, y_rel, escala);
    } else if (estado == 6) {
        int x = 260;
        int y = 150;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_rel, y_rel, escala);
    } else if (estado == 7) {
        int x = 240;
        int y = 150;
        auto [x_rel, y_rel] = convertir_a_relativo(x, y);
        dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_rel, y_rel, escala);
    }

    renderer.Present();
}
