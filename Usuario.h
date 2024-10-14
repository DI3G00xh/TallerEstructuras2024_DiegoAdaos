#ifndef USUARIO_H
#define USUARIO_H
#include<string>
#include "MaterialBibliografico.h"
class Usuario
{
private:
    std::string nombre;
    int id;
    MaterialBibliografico* materialesPrestados[5];
    int contadorPrestados;

public:
    Usuario(const std::string& nombre, int id);
    ~Usuario();

    std::string getNombre() const { return nombre; }
    int getID() const { return id; }

    bool prestarMaterial(MaterialBibliografico* material);
    bool devolverMaterial(const std::string& isbn);
    void mostrarMaterialesPrestados() const;
    void mostrarInformación() const;
  
};
#endif