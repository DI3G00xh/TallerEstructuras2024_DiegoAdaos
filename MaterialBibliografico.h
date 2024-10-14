#ifndef MATERIALBIBLIOGRAFICO_H
#define MATERIALBIBLIOGRAFICO_H
#include <string>
#include <iostream>


class MaterialBibliografico
{
protected:
    /* data */
    std::string nombre;
    std::string isbn;
    std::string autor;
    bool prestado;
public:
    MaterialBibliografico(const std::string& nombre, const std::string& isbn, const std::string& autor): nombre(nombre), isbn(isbn), autor(autor), prestado(false){}
    
    virtual ~MaterialBibliografico(){}

    std::string getNombre() const {return nombre;}
    std::string getISBN() const {return isbn;}
    std::string getAutor() const {return autor;}
    bool isPrestado() const { return prestado; }
    void setPrestado(bool estado) { prestado = estado; }

    virtual void mostrarInformación() const = 0;
};
#endif