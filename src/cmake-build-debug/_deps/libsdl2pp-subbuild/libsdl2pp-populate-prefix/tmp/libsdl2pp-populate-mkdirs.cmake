# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/axelzielonka/Documents/Axel/FIUBA/2024/Taller/TPS/DuckGame-g2-20242c/cmake-build-debug/_deps/libsdl2pp-src"
  "/Users/axelzielonka/Documents/Axel/FIUBA/2024/Taller/TPS/DuckGame-g2-20242c/cmake-build-debug/_deps/libsdl2pp-build"
  "/Users/axelzielonka/Documents/Axel/FIUBA/2024/Taller/TPS/DuckGame-g2-20242c/cmake-build-debug/_deps/libsdl2pp-subbuild/libsdl2pp-populate-prefix"
  "/Users/axelzielonka/Documents/Axel/FIUBA/2024/Taller/TPS/DuckGame-g2-20242c/cmake-build-debug/_deps/libsdl2pp-subbuild/libsdl2pp-populate-prefix/tmp"
  "/Users/axelzielonka/Documents/Axel/FIUBA/2024/Taller/TPS/DuckGame-g2-20242c/cmake-build-debug/_deps/libsdl2pp-subbuild/libsdl2pp-populate-prefix/src/libsdl2pp-populate-stamp"
  "/Users/axelzielonka/Documents/Axel/FIUBA/2024/Taller/TPS/DuckGame-g2-20242c/cmake-build-debug/_deps/libsdl2pp-subbuild/libsdl2pp-populate-prefix/src"
  "/Users/axelzielonka/Documents/Axel/FIUBA/2024/Taller/TPS/DuckGame-g2-20242c/cmake-build-debug/_deps/libsdl2pp-subbuild/libsdl2pp-populate-prefix/src/libsdl2pp-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/axelzielonka/Documents/Axel/FIUBA/2024/Taller/TPS/DuckGame-g2-20242c/cmake-build-debug/_deps/libsdl2pp-subbuild/libsdl2pp-populate-prefix/src/libsdl2pp-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/axelzielonka/Documents/Axel/FIUBA/2024/Taller/TPS/DuckGame-g2-20242c/cmake-build-debug/_deps/libsdl2pp-subbuild/libsdl2pp-populate-prefix/src/libsdl2pp-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
