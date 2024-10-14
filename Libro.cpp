#include "Libro.h"
#include <iostream>

void Libro::mostrarInformación() const {
    std::cout << "Libro: " << nombre << "\n"
              << "ISBN: " << isbn << "\n"
              << "Autor: " << autor << "\n"
              << "Fecha de Publicación: " << fechaPublicacion << "\n"
              << "Resumen: " << resumen << "\n"
              << "Estado: " << (prestado ? "Prestado" : "Disponible") << "\n\n";
}

