#include "Revista.h"
#include <iostream>

void Revista::mostrarInformación() const {
    std::cout << "Revista: " << nombre << "\n"
              << "ISBN: " << isbn << "\n"
              << "Autor: " << autor << "\n"
              << "Número de Edición: " << numeroEdicion << "\n"
              << "Mes de Publicación: " << mesPublicacion << "\n"
              << "Estado: " << (prestado ? "Prestado" : "Disponible") << "\n\n";
}


