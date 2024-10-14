#ifndef LIBRO_H
#define LIBRO_H
#include "MaterialBibliografico.h"
#include <string>

class Libro : public MaterialBibliografico{
    private:
        std::string fechaPublicacion;
        std::string resumen;
    
    public:
        Libro(const std::string& nombre, const std::string& isbn, const std::string& autor, const std::string& fechaPublicacion,
        const std::string& resumen) : MaterialBibliografico(nombre, isbn, autor), fechaPublicacion(fechaPublicacion), resumen(resumen) {}

    std::string getFecha() const {
        return fechaPublicacion;
    }

    std::string getResumen() const {
        return resumen;
    }
    void mostrarInformación() const override;  

};
#endif