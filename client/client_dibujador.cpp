#include "client_dibujador.h"

#include <iostream>

#define RUTA_SPR_PATO "/sprites-pato-blanco.png"
#define RUTA_SPR_AK "/sprites-ak47.png"
#define RUTA_SPR_CAJAS "/sprites-cajas.png"
#define RUTA_SPR_ARMADURAS "/sprites-armaduras.png"
#define MAPA_1_STR "mapa 1"

using namespace SDL2pp;

Dibujador::Dibujador(Renderer& renderer, const std::string& ruta_mapa) : parseador(),
    spriteSheetPato(renderer, DATA_PATH RUTA_SPR_PATO),
    spriteSheetAK(renderer, DATA_PATH RUTA_SPR_AK),
    spriteSheetCaja(renderer, DATA_PATH RUTA_SPR_CAJAS),
    spriteSheetArmadura(renderer, DATA_PATH RUTA_SPR_ARMADURAS),
    mapa(renderer, (DATA_PATH + ruta_mapa).c_str()) {}

void Dibujador::dibujar_sprites_fila(SDL2pp::Renderer& renderer, SDL2pp::Texture& spriteSheet, 
                          const std::vector<SDL_Rect>& sprites, 
                          int anchoVentana, int altoVentana, float x, float y, float escala, float separacion) {
    int startX = static_cast<int>(anchoVentana * x);
    int startY = static_cast<int>(altoVentana * y);
    int scaledWidth = static_cast<int>(anchoVentana * escala);
    int scaledHeight = static_cast<int>(altoVentana * escala);
    int gap = static_cast<int>(anchoVentana * separacion);
    int contador = 0;

    for (size_t i = 0; i < sprites.size(); ++i){
        if (contador >= 12){
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
    if (estado == 0){
        int anchoVentana, altoVentana;
        SDL_GetWindowSize(window.Get(), &anchoVentana, &altoVentana);
        renderer.Clear();
        renderer.Copy(mapa);
        std::vector<SDL_Rect> spritesPato = parseador.obtener_sprites_pato();
        float x = 0.01;
        float y = 0.2;
        float escala = 0.07;
        float separacion = 0.01;
        dibujar_sprites_fila(renderer, spriteSheetPato, spritesPato, anchoVentana, altoVentana, x, y, escala, separacion);
        renderer.Present();
    } else if (estado == 1) {
        renderer.Clear();
        renderer.Copy(mapa);
        renderer.Present();
    } else if (estado == 2) {
        int anchoVentana, altoVentana;
        SDL_GetWindowSize(window.Get(), &anchoVentana, &altoVentana);
        renderer.Clear();
        renderer.Copy(mapa);
        std::vector<SDL_Rect> spritesAK = parseador.obtener_sprites_ak();
        float x = 0.01;
        float y = 0.2;
        float escala = 0.07;
        float separacion = 0.01;
        dibujar_sprites_fila(renderer, spriteSheetAK, spritesAK, anchoVentana, altoVentana, x, y, escala, separacion);
        y += 0.2;
        escala = 0.04;
        std::vector<SDL_Rect> spritesCaja = parseador.obtener_sprites_caja();
        dibujar_sprites_fila(renderer, spriteSheetCaja, spritesCaja, anchoVentana, altoVentana, x, y, escala, separacion);
        renderer.Present();
    } else if (estado == 3){
        int anchoVentana, altoVentana;
        SDL_GetWindowSize(window.Get(), &anchoVentana, &altoVentana);
        renderer.Clear();
        renderer.Copy(mapa);
        std::vector<SDL_Rect> spritesArmadura = parseador.obtener_sprites_armadura();
        float x = 0.01;
        float y = 0.2;
        float escala = 0.07;
        float separacion = 0.01;
        dibujar_sprites_fila(renderer, spriteSheetArmadura, spritesArmadura, anchoVentana, altoVentana, x, y, escala, separacion);
        renderer.Present();
    } else if (estado == 4) {
        int anchoVentana, altoVentana;
        SDL_GetWindowSize(window.Get(), &anchoVentana, &altoVentana);
        renderer.Clear();
        renderer.Copy(mapa);
        std::vector<SDL_Rect> spritesPato = parseador.obtener_sprites_pato();
        float x = 0.01;
        float y = 0.2;
        float escala = 0.07;
        float separacion = 0.01;
        dibujar_sprites_fila(renderer, spriteSheetPato, spritesPato, anchoVentana, altoVentana, x, y, escala, separacion);
        std::vector<SDL_Rect> spritesArmadura = parseador.obtener_sprites_armadura();
        dibujar_sprites_fila(renderer, spriteSheetArmadura, spritesArmadura, anchoVentana, altoVentana, x, y, escala, separacion);
        std::vector<SDL_Rect> spritesAK = parseador.obtener_sprites_ak();
        y += 0.01;
        dibujar_sprites_fila(renderer, spriteSheetAK, spritesAK, anchoVentana, altoVentana, x, y, escala, separacion);
        renderer.Present();
    }
}
