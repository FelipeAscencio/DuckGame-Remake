#include "client_dibujador.h"

#define RUTA_SPR_PATO "/sprites-pato-blanco.png"
#define RUTA_MAPA_1 "/mapa1.png"

using namespace SDL2pp;

Dibujador::Dibujador(): parseador() {}

void Dibujador::dibujar_sprites_fila(SDL2pp::Renderer& renderer, SDL2pp::Texture& spriteSheetPato, 
                          const std::vector<SDL_Rect>& spritesPato, 
                          int anchoVentana, int altoVentana) {
    // Parámetros de posición y escala basados en el tamaño de la ventana
    int startX = static_cast<int>(anchoVentana * 0.01);        // 1% de la ventana en X para el primer sprite
    int startY = static_cast<int>(altoVentana * 0.2);        // 20% de la ventana en Y para mantenerlo fijo
    int scaledWidth = static_cast<int>(anchoVentana * 0.07);   // Escala del pato al 7% de la anchura de la ventana
    int scaledHeight = static_cast<int>(altoVentana * 0.07); // Escala del pato al 7% de la altura de la ventana
    int gap = static_cast<int>(anchoVentana * 0.01);           // 1% de la ventana como espacio entre sprites

    // Dibuja cada sprite uno al lado del otro en el eje X
    for (size_t i = 0; i < spritesPato.size(); ++i) {
        if (i < 12){
            SDL_Rect dstRect;
            dstRect.x = startX + i * (scaledWidth + gap); // Posición X para cada sprite, uno al lado del otro
            dstRect.y = startY;                           // Posición Y fija en relación con el tamaño de la ventana
            dstRect.w = scaledWidth;                      // Ancho escalado del sprite
            dstRect.h = scaledHeight;                     // Alto escalado del sprite
            renderer.Copy(spriteSheetPato, spritesPato[i], dstRect);
        } else {
            SDL_Rect dstRect;
            dstRect.x = startX + (i - 12) * (scaledWidth + gap); // Posición X para cada sprite, uno al lado del otro
            dstRect.y = 50 + startY;                           // Posición Y fija en relación con el tamaño de la ventana
            dstRect.w = scaledWidth;                      // Ancho escalado del sprite
            dstRect.h = scaledHeight;                     // Alto escalado del sprite
            renderer.Copy(spriteSheetPato, spritesPato[i], dstRect);
        }
        
        // Copiar cada sprite de la hoja al renderer en la posición dstRect
        
    }
}

void Dibujador::renderizar(Renderer& renderer, Window& window) {
    Texture spriteSheetPato(renderer, DATA_PATH RUTA_SPR_PATO);
    Texture mapa(renderer, DATA_PATH RUTA_MAPA_1);
    int anchoVentana, altoVentana;
    SDL_GetWindowSize(window.Get(), &anchoVentana, &altoVentana);
    renderer.Clear();
    renderer.Copy(mapa);
    std::vector<SDL_Rect> spritesPato = parseador.obtener_sprites_pato();
    dibujar_sprites_fila(renderer, spriteSheetPato, spritesPato, anchoVentana, altoVentana);
    renderer.Present();
}
