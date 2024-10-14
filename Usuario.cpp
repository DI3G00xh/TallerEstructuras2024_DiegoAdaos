#include "Usuario.h"
#include <iostream>

Usuario::Usuario(const std::string& nombre, int id)
    : nombre(nombre), id(id), contadorPrestados(0) {
    for(int i = 0; i < 5; ++i) {
        materialesPrestados[i] = nullptr;
    }
}

Usuario::~Usuario() {
    // No se elimina la memoria de los materiales aquí, ya que la biblioteca lo gestiona
}

bool Usuario::prestarMaterial(MaterialBibliografico* material) {
    if(contadorPrestados >= 5) {
        std::cout << "Error: No puedes prestar más de 5 materiales.\n";
        return false;
    }
    for(int i = 0; i < 5; ++i) {
        if(materialesPrestados[i] == nullptr) {
            materialesPrestados[i] = material;
            contadorPrestados++;
            return true;
        }
    }
    return false;
}

bool Usuario::devolverMaterial(const std::string& isbn) {
    for(int i = 0; i < 5; ++i) {
        if(materialesPrestados[i] && materialesPrestados[i]->getISBN() == isbn) {
            materialesPrestados[i] = nullptr;
            contadorPrestados--;
            return true;
        }
    }
    std::cout << "Error: Material no encontrado en los prestados.\n";
    return false;
}

void Usuario::mostrarMaterialesPrestados() const {
    std::cout << "Materiales prestados por " << nombre << " (ID: " << id << "):\n";
    bool tienePrestados = false;
    for(int i = 0; i < 5; ++i) {
        if(materialesPrestados[i]) {
            materialesPrestados[i]->mostrarInformación();
            tienePrestados = true;
        }
    }
    if(!tienePrestados) {
        std::cout << "No hay materiales prestados.\n";
    }
}
void Usuario::mostrarInformación() const {
    std::cout << "Nombre: " << nombre << "\n"
              << "id: " << id << "\n"
              << "Materiales Prestadps: " << contadorPrestados << "\n";

}
