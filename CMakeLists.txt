cmake_minimum_required(VERSION 3.25)
project(ProyectoAED)
set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(estructuras)
include_directories(hash_funcion)
include_directories(blockchain)
include_directories(sfml)

add_executable(ProyectoAED
        main.cpp estructuras/double_list.h estructuras/hash.h estructuras/heap.h blockchain/block.h estructuras/trie.h blockchain/transaccion.h estructuras/b+tree.h blockchain/blockchain.h)

# Encontrar SFML
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

target_link_libraries(ProyectoAED
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
        )