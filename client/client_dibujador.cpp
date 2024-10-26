#include "client_dibujador.h"

#include <iostream>

#define RUTA_SPR_PATO "/sprites-pato-blanco.png"
#define RUTA_MAPA_1 "/mapa1.png"

using namespace SDL2pp;

Dibujador::Dibujador(): parseador() {}

void Dibujador::dibujar_sprites_fila(SDL2pp::Renderer& renderer, SDL2pp::Texture& spriteSheet, 
                          const std::vector<SDL_Rect>& sprites, 
                          int anchoVentana, int altoVentana, float x, float y, float escala, float separacion) {
    // Parámetros de posición y escala basados en el tamaño de la ventana
    int startX = static_cast<int>(anchoVentana * x);        // 1% de la ventana en X para el primer sprite
    int startY = static_cast<int>(altoVentana * y);        // 20% de la ventana en Y para mantenerlo fijo
    int scaledWidth = static_cast<int>(anchoVentana * escala);   // Escala del pato al 7% de la anchura de la ventana
    int scaledHeight = static_cast<int>(altoVentana * escala); // Escala del pato al 7% de la altura de la ventana
    int gap = static_cast<int>(anchoVentana * separacion);           // 1% de la ventana como espacio entre sprites
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

    //// Dibuja cada sprite uno al lado del otro en el eje X
    //for (size_t i = 0; i < spritesPato.size(); ++i) {
    //    if (i < 12){
    //        SDL_Rect dstRect;
    //        dstRect.x = startX + i * (scaledWidth + gap); // Posición X para cada sprite, uno al lado del otro
    //        dstRect.y = startY;                           // Posición Y fija en relación con el tamaño de la ventana
    //        dstRect.w = scaledWidth;                      // Ancho escalado del sprite
    //        dstRect.h = scaledHeight;                     // Alto escalado del sprite
    //        renderer.Copy(spriteSheetPato, spritesPato[i], dstRect);
    //    } else {
    //        SDL_Rect dstRect;
    //        dstRect.x = startX + (i - 12) * (scaledWidth + gap); // Posición X para cada sprite, uno al lado del otro
    //        dstRect.y = 50 + startY;                           // Posición Y fija en relación con el tamaño de la ventana
    //        dstRect.w = scaledWidth;                      // Ancho escalado del sprite
    //        dstRect.h = scaledHeight;                     // Alto escalado del sprite
    //        renderer.Copy(spriteSheetPato, spritesPato[i], dstRect);
    //    }
    //    
    //    // Copiar cada sprite de la hoja al renderer en la posición dstRect
    //    
    //}
}

void Dibujador::renderizar(Renderer& renderer, Window& window, const int estado) {
    Texture spriteSheetPato(renderer, DATA_PATH RUTA_SPR_PATO);
    Texture mapa(renderer, DATA_PATH RUTA_MAPA_1);
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
    }
}
