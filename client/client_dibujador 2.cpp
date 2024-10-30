#include "client_dibujador.h"

#define RUTA_SPR_PATO "/sprites-pato-blanco.png"
#define RUTA_SPR_AK "/sprites-ak47.png"
#define RUTA_SPR_CAJAS "/sprites-cajas.png"
#define RUTA_SPR_ARMADURAS "/sprites-armaduras.png"

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

void Dibujador::dibujar_sprites_fila(SDL2pp::Renderer& renderer, SDL2pp::Texture& spriteSheet,
                                     const std::vector<SDL_Rect>& sprites, int anchoVentana,
                                     int altoVentana, float x, float y, float escala,
                                     float separacion) {
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

void Dibujador::renderizar(Renderer& renderer, Window& window, const int estado) {
    renderer.Clear();
    renderer.Copy(this->mapa);
    int anchoVentana, altoVentana;
    SDL_GetWindowSize(window.Get(), &anchoVentana, &altoVentana);

    if (estado == 0) {
        float x = 0.01;
        float y = 0.2;
        float escala = 0.07;
        float separacion = 0.01;
        dibujar_sprites_fila(renderer, this->spriteSheetPato, this->spritesPato, anchoVentana,
                             altoVentana, x, y, escala, separacion);
    } else if (estado == 1) {
        float x = 0.01;
        float y = 0.2;
        float escala = 0.07;
        float separacion = 0.01;
        dibujar_sprites_fila(renderer, this->spriteSheetAK, this->spritesAK, anchoVentana,
                             altoVentana, x, y, escala, separacion);
        y += 0.2;
        escala = 0.04;
        dibujar_sprites_fila(renderer, this->spriteSheetCaja, this->spritesCaja, anchoVentana,
                             altoVentana, x, y, escala, separacion);
    } else if (estado == 2) {
        float x = 0.01;
        float y = 0.2;
        float escala = 0.07;
        float separacion = 0.01;
        dibujar_sprites_fila(renderer, this->spriteSheetArmadura, this->spritesArmadura,
                             anchoVentana, altoVentana, x, y, escala, separacion);
    } else if (estado == 3) {
        float x = 0.01;
        float y = 0.2;
        float escala = 0.07;
        float separacion = 0.01;
        dibujar_sprites_fila(renderer, this->spriteSheetPato, this->spritesPato, anchoVentana,
                             altoVentana, x, y, escala, separacion);
        dibujar_sprites_fila(renderer, this->spriteSheetArmadura, this->spritesArmadura,
                             anchoVentana, altoVentana, x, y, escala, separacion);
        y += 0.01;
        dibujar_sprites_fila(renderer, this->spriteSheetAK, this->spritesAK, anchoVentana,
                             altoVentana, x, y, escala, separacion);
    }

    renderer.Present();
}
