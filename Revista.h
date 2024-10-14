#ifndef REVISTA_H
#define REVISTA_H
#include "MaterialBibliografico.h"
#include <string>


class Revista : public MaterialBibliografico{
    private:
        int numeroEdicion;
        std::string mesPublicacion;
    
    public:
        Revista(const std::string& nombre, const std::string& isbn, const std::string& autor, int numeroEdicion, const std::string& mesPublicacion):
        MaterialBibliografico(nombre, isbn, autor), numeroEdicion(numeroEdicion), mesPublicacion(mesPublicacion) {}

    int getNumero() const {
        return numeroEdicion;
    }

    std::string getMes() const {
        return mesPublicacion;
    }

    void mostrarInformación() const override;
};       
#endif