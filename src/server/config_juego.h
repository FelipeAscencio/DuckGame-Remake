#ifndef CONFIG_JUEGO_H
#define CONFIG_JUEGO_H

#pragma once
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <string>

class ConfigJuego{
    public:
        static void cargar_configuracion(const std::string& archivo);
        static int ALCANCE_SNIPER;
        static int MUNICIONES_SNIPER;
        static int ALCANCE_AK47;
        static int MUNICIONES_AK47;
        static int FPS;
        static int ALCANCE_MAGNUM;
        static int MUNICIONES_MAGNUM;
        static int ALCANCE_MINIMO_PP_LASER;
        static int ALCANCE_MAXIMO_PP_LASER;
        static int MUNICIONES_PP_LASER;
        static int ALCANCE_MINIMO_SHOTGUN;
        static int ALCANCE_MAXIMO_SHOTGUN;
        static int MUNICIONES_SHOTGUN;
        static int PERDIGONES_POR_DISPARO_SG;
        static int LASERS_POR_DISPARO_PP;

    private:
        ConfigJuego() = default;
};



#endif