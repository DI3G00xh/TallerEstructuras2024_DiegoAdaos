#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Libro.h"
#include "Revista.h"
#include "Usuario.h"
#include "MaterialBibliografico.h"

#define MAX_MATERIALES 100
#define MAX_USUARIOS 50

void guardarUsuarios(Usuario* usuarios[], int contadorUsuarios) {
    std::ofstream archivoUsuarios("usuarios.txt");

    if (archivoUsuarios.is_open()) {
        for (int i = 0; i < contadorUsuarios; ++i) {
            if (usuarios[i] != nullptr) {
                archivoUsuarios << usuarios[i]->getNombre() << "," 
                                << usuarios[i]->getID() << "\n";  // Usar getID()
            }
        }
        archivoUsuarios.close();
        std::cout << "Usuarios guardados exitosamente.\n";
    } else {
        std::cerr << "Error al abrir el archivo de usuarios para guardar.\n";
    }
}

void guardarMateriales(MaterialBibliografico* biblioteca[], int contadorMateriales) {
    std::ofstream archivoMateriales("materiales.txt");

    if (archivoMateriales.is_open()) {
        for (int i = 0; i < contadorMateriales; ++i) {
            if (biblioteca[i] != nullptr) {
                Libro* libro = dynamic_cast<Libro*>(biblioteca[i]);
                if (libro != nullptr) {
                    archivoMateriales << "Libro," 
                                      << libro->getNombre() << "," 
                                      << libro->getISBN() << ","
                                      << libro->getAutor() << ","
                                      << libro->getFecha() << ","  // Usar getFecha()
                                      << libro->getResumen() << ","  // Usar getResumen()
                                      << (libro->isPrestado() ? "1" : "0") << "\n";
                } else {
                    Revista* revista = dynamic_cast<Revista*>(biblioteca[i]);
                    if (revista != nullptr) {
                        archivoMateriales << "Revista," 
                                          << revista->getNombre() << ","
                                          << revista->getISBN() << ","
                                          << revista->getAutor() << ","
                                          << revista->getNumero() << ","  // Usar getNumero()
                                          << revista->getMes() << ","  // Usar getMes()
                                          << (revista->isPrestado() ? "1" : "0") << "\n";
                    }
                }
            }
        }
        archivoMateriales.close();
        std::cout << "Materiales guardados exitosamente.\n";
    } else {
        std::cerr << "Error al abrir el archivo de materiales para guardar.\n";
    }
}

int main() {
    MaterialBibliografico* biblioteca[MAX_MATERIALES];
    int contadorMateriales = 0;

    Usuario* usuarios[MAX_USUARIOS];
    int contadorUsuarios = 0;

    // Inicializar arrays
    for(int i = 0; i < MAX_MATERIALES; ++i) {
        biblioteca[i] = nullptr;
    }
    for(int i = 0; i < MAX_USUARIOS; ++i) {
        usuarios[i] = nullptr;
    }

    //Leer Archivo Usuarios
    std::ifstream archivoUsuarios("usuarios.txt");
    if(archivoUsuarios.is_open()) {
        std::string linea;
        while(std::getline(archivoUsuarios, linea) && contadorUsuarios < MAX_USUARIOS) {
            std::stringstream ss(linea);
            std::string nombre;
            std::string idStr;
            getline(ss, nombre, ',');
            getline(ss, idStr, ',');
            int id = std::stoi(idStr);
            std::cout << "Cargando usuario: Nombre: " << nombre << ", ID: " << id << "\n";
            usuarios[contadorUsuarios++] = new Usuario(nombre, id);
        }
        archivoUsuarios.close();
        std::cout << "Usuarios cargados exitosamente.\n";
    } else {
        std::cout << "No se encontró usuarios.\n";
    }
    //Leer Archivos Materiales
    std::ifstream archivoMateriales("materiales.txt");
    if(archivoMateriales.is_open()) {
        std::string linea;
        while(std::getline(archivoMateriales, linea) && contadorMateriales < MAX_MATERIALES) {
            std::stringstream ss(linea);
            std::string tipo, nombre, isbn, autor, fecha, resumen, prestadoStr;
            getline(ss, tipo, ',');
            getline(ss, nombre, ',');
            getline(ss, isbn, ',');
            getline(ss, autor, ',');
            if(tipo == "Libro") {
                getline(ss, fecha, ',');
                getline(ss, resumen, ',');
                getline(ss, prestadoStr, ',');
                Libro* libro = new Libro(nombre, isbn, autor, fecha, resumen);
                libro->setPrestado(prestadoStr == "1");
                biblioteca[contadorMateriales++] = libro;
            } else if(tipo == "Revista") {
                std::string numeroStr, mes;
                getline(ss, numeroStr, ',');
                getline(ss, mes, ',');
                getline(ss, prestadoStr, ',');
                int numero = std::stoi(numeroStr);
                Revista* revista = new Revista(nombre, isbn, autor, numero, mes);
                revista->setPrestado(prestadoStr == "1");
                biblioteca[contadorMateriales++] = revista;
            }
        }
        archivoMateriales.close();
        std::cout << "Materiales cargados exitosamente.\n";
    } else {
        std::cout << "No se encontró el archivo de materiales.\n";
    }

    int opcion;
    do {
        std::cout << "===== Simulador de Biblioteca Digital =====\n";
        std::cout << "1. Agregar Material\n";
        std::cout << "2. Mostrar Todos los Materiales\n";
        std::cout << "3. Buscar Material\n";
        std::cout << "4. Gestionar Usuario\n";
        std::cout << "5. Prestar Material\n";
        std::cout << "6. Devolver Material\n";
        std::cout << "7. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1: { // Agregar Libro o Revista
                if(contadorMateriales >= MAX_MATERIALES) {
                    std::cout << "Error: La biblioteca está llena.\n";
                    break;
                }

                int opcionLibro;
                std::cout << "Qué desea agregar?\n1. Libro\n2. Revista\nSeleccione una opción: ";
                std::cin >> opcionLibro;
                std::cin.ignore();

                if(opcionLibro == 1) {
                    std::string nombre, isbn, autor, fecha, resumen;
                    std::cout << "Ingrese el nombre del libro: ";
                    std::getline(std::cin, nombre);
                    std::cout << "Ingrese el ISBN: ";
                    std::getline(std::cin, isbn);
                    std::cout << "Ingrese el autor: ";
                    std::getline(std::cin, autor);
                    std::cout << "Ingrese la fecha de publicación: ";
                    std::getline(std::cin, fecha);
                    std::cout << "Ingrese el resumen: ";
                    std::getline(std::cin, resumen);

                    biblioteca[contadorMateriales++] = new Libro(nombre, isbn, autor, fecha, resumen);
                    std::cout << "Libro agregado exitosamente.\n";
                } else if(opcionLibro == 2) {
                    std::string nombre, isbn, autor, mes;
                    int numero;
                    std::cout << "Ingrese el nombre de la revista: ";
                    std::getline(std::cin, nombre);
                    std::cout << "Ingrese el ISBN: ";
                    std::getline(std::cin, isbn);
                    std::cout << "Ingrese el autor: ";
                    std::getline(std::cin, autor);
                    std::cout << "Ingrese el número de edición: ";
                    std::cin >> numero;
                    std::cin.ignore();
                    std::cout << "Ingrese el mes de publicación: ";
                    std::getline(std::cin, mes);

                    biblioteca[contadorMateriales++] = new Revista(nombre, isbn, autor, numero, mes);
                    std::cout << "Revista agregada exitosamente.\n";
                } else {
                    std::cout << "Opción inválida.\n";
                }
                break;
            }
             // Mostrar Todos los Materiales
            case 2: {
                if(contadorMateriales == 0) {
                    std::cout << "La biblioteca está vacía.\n";
                } else {
                    for(int i = 0; i < contadorMateriales; ++i) {
                        biblioteca[i]->mostrarInformación();
                    }
                }
                break;
            }
            case 3: { // Buscar Material
                int tipoBusqueda;
                std::cout << "Buscar por:\n1. Título\n2. Autor\nSeleccione una opción: ";
                std::cin >> tipoBusqueda;
                std::cin.ignore();

                std::string termino;
                if(tipoBusqueda == 1) {
                    std::cout << "Ingrese el título a buscar: ";
                } else if(tipoBusqueda == 2) {
                    std::cout << "Ingrese el autor a buscar: ";
                } else {
                    std::cout << "Opción inválida.\n";
                    break;
                }
                std::getline(std::cin, termino);

                bool encontrado = false;
                for(int i = 0; i < contadorMateriales; ++i) {
                    if((tipoBusqueda == 1 && biblioteca[i]->getNombre() == termino) ||
                       (tipoBusqueda == 2 && biblioteca[i]->getAutor() == termino)) {
                        biblioteca[i]->mostrarInformación();
                        encontrado = true;
                    }
                }
                if(!encontrado) {
                    std::cout << "No se encontraron materiales coincidentes.\n";
                }
                break;
            }
            // Gestionar Usuario
            case 4: { 
                int opcionUsuario;
                std::cout << "Qué desea hacer?\n1. Agregar Usuario\n2. Eliminar Usuario\n3. Buscar Usuario y ver Información\nSeleccione una opción: ";
                std::cin >> opcionUsuario;

                switch(opcionUsuario) {
                     // Agregar Usuario
                    case 1: {
                        if(contadorUsuarios >= MAX_USUARIOS) {
                            std::cout << "Error: Se ha alcanzado el límite de usuarios.\n";
                            break;
                        }
                        std::string nombre;
                        int id;
                        std::cout << "Ingrese el nombre del usuario: ";
                        std::cin.ignore();
                        std::getline(std::cin, nombre);
                        std::cout << "Ingrese el ID del usuario: ";
                        std::cin >> id;

                        // Verificar id
                        bool idUnico = true;
                        for(int i = 0; i < contadorUsuarios; ++i) {
                            if(usuarios[i]->getID() == id) {
                                idUnico = false;
                                break;
                            }
                        }
                        if(!idUnico) {
                            std::cout << "Error: Ya existe un usuario con ese ID.\n";
                            break;
                        }

                        usuarios[contadorUsuarios++] = new Usuario(nombre, id);
                        std::cout << "Usuario creado exitosamente.\n";
                        break;
                    }
                    //borrar usuario
                    case 2: { 
                        if(contadorUsuarios == 0) {
                            std::cout << "No hay usuarios para eliminar.\n";
                            break;
                        }

                        int id;
                        std::cout << "Ingrese el ID del usuario a eliminar: ";
                        std::cin >> id;

                        bool encontrado = false;
                        for(int i = 0; i < contadorUsuarios; ++i) {
                            if(usuarios[i]->getID() == id) {
                                delete usuarios[i];
                                for(int j = i; j < contadorUsuarios - 1; ++j) {
                                    usuarios[j] = usuarios[j + 1];
                                }
                                usuarios[--contadorUsuarios] = nullptr;
                                std::cout << "Usuario eliminado exitosamente.\n";
                                encontrado = true;
                                break;
                            }
                        }
                        if(!encontrado) {
                            std::cout << "Usuario no encontrado.\n";
                        }
                        break;
                    }
                    // Buscar Usuario y ver Información
                    case 3: { 
                        int idUsuario;
                        std::cout << "Ingrese el ID del usuario: ";
                        std::cin >> idUsuario;

                        Usuario* usuario = nullptr;
                        for(int i = 0; i < contadorUsuarios; ++i) {
                            if(usuarios[i]->getID() == idUsuario) {
                                usuario = usuarios[i];
                                break;
                            }
                        }
                        if(!usuario) {
                            std::cout << "Error: Usuario no encontrado.\n";
                            break;
                        }
                        usuario->mostrarInformación();
                        usuario->mostrarMaterialesPrestados();
                        break;
                    }
                }
                break;
            }
            //Prestar Libros
            case 5: { 
                int idUsuario;
                std::string isbn;
                std::cout << "Ingrese el ID del usuario: ";
                std::cin >> idUsuario;

                Usuario* usuario = nullptr;
                for(int i = 0; i < contadorUsuarios; ++i) {
                    if(usuarios[i]->getID() == idUsuario) {
                        usuario = usuarios[i];
                        break;
                    }
                }
                if(!usuario) {
                    std::cout << "Error: Usuario no encontrado.\n";
                    break;
                }
                std::cout << "Ingrese el ISBN del material a prestar: ";
                std::cin.ignore();
                std::getline(std::cin, isbn);

                MaterialBibliografico* material = nullptr;
                for(int i = 0; i < contadorMateriales; ++i) {
                    if(biblioteca[i]->getISBN() == isbn) {
                        material = biblioteca[i];
                        break;
                    }
                }
                if(!material) {
                    std::cout << "Error: Material no encontrado.\n";
                    break;
                }
                if(material->isPrestado()) {
                    std::cout << "Error: El material ya está prestado.\n";
                    break;
                }
                if(usuario->prestarMaterial(material)) {
                    material->setPrestado(true);
                    std::cout << "Material prestado exitosamente.\n";
                }
                break;
            }
            //Devolver libros
            case 6: {
                int idUsuario;
                std::string isbn;
                std::cout << "Ingrese el ID del usuario: ";
                std::cin >> idUsuario;

                Usuario* usuario = nullptr;
                for(int i = 0; i < contadorUsuarios; ++i) {
                    if(usuarios[i]->getID() == idUsuario) {
                        usuario = usuarios[i];
                        break;
                    }
                }
                if(!usuario) {
                    std::cout << "Error: Usuario no encontrado.\n";
                    break;
                }
                std::cout << "Ingrese el ISBN del material a devolver: ";
                std::cin.ignore();
                std::getline(std::cin, isbn);

                MaterialBibliografico* material = nullptr;
                for(int i = 0; i < contadorMateriales; ++i) {
                    if(biblioteca[i]->getISBN() == isbn) {
                        material = biblioteca[i];
                        break;
                    }
                }
                if(!material) {
                    std::cout << "Error: Material no encontrado.\n";
                    break;
                }
                if(usuario->devolverMaterial(isbn)) {
                    material->setPrestado(false);
                    std::cout << "Material devuelto exitosamente.\n";
                }
                break;
            }
            //Salir del programa
            case 7: { 
                guardarMateriales(biblioteca, contadorMateriales);
                guardarUsuarios(usuarios, contadorUsuarios);
                std::cout << "Saliendo del programa...\n";
                break;
            }
            default:
                std::cout << "Opción inválida. Intente de nuevo.\n";
        }
        std::cout << "\n";

    } while(opcion != 7);

    // Liberar la memoria
    for(int i = 0; i < contadorMateriales; ++i) {
        delete biblioteca[i];
    }
    for(int i = 0; i < contadorUsuarios; ++i) {
        delete usuarios[i];
    }

    return 0;
}