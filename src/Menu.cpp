#include "Menu.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

void Menu::agregarReceta() {
    try {
        std::string nombre, categoria, autor, procedimiento;
        int tiempo, nIng;

        std::cin.ignore();
        std::cout << "Nombre: ";
        std::getline(std::cin, nombre);

        std::cout << "Categoria: ";
        std::getline(std::cin, categoria);

        std::cout << "Autor: ";
        std::getline(std::cin, autor);

        std::cout << "Tiempo (min): ";
        std::cin >> tiempo;
        std::cin.ignore();

        std::cout << "Procedimiento: ";
        std::getline(std::cin, procedimiento);

        Receta r(nombre, categoria, autor, tiempo, procedimiento);

        std::cout << "Numero de ingredientes: ";
        std::cin >> nIng;
        std::cin.ignore();

        for (int i = 0; i < nIng; i++) {
            std::string n, u;
            float c;

            std::cout << "Ingrediente " << i + 1 << " nombre: ";
            std::getline(std::cin, n);

            std::cout << "Unidad: ";
            std::getline(std::cin, u);

            std::cout << "Cantidad: ";
            std::cin >> c;
            std::cin.ignore();

            r.agregarIngrediente(Ingrediente(n, u, c));
        }

        recetario.mostrarTodas();
        std::cout << "Posicion a insertar (0 principio): ";
        int pos;
        std::cin >> pos;
        std::cin.ignore();

        recetario.agregarRecetaEnPosicion(r, pos);

        std::cout << "Receta agregada correctamente.\n";

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}


void Menu::mostrarRecetas() {
    recetario.mostrarTodas();
}

void Menu::buscarReceta() {
    try {
        std::string opcion, valor;
        std::cin.ignore();

        std::cout << "Buscar por (nombre/categoria): ";
        std::getline(std::cin, opcion);

        if (opcion == "nombre") {
            std::cout << "Nombre: ";
            std::getline(std::cin, valor);

            Receta* r = recetario.buscarRecetaPorNombre(valor);
            if (!r) std::cout << "No encontrada.\n";
            else std::cout << r->toString() << "\n";
        }
        else if (opcion == "categoria") {

            std::cout << "Categoria: ";
            std::getline(std::cin, valor);

            recetario.buscarPorCategoria(valor);  

        } else {
            std::cout << "Opcion invalida.\n";
        }

    } catch (...) {
        std::cout << "Error en busqueda.\n";
    }
}


void Menu::eliminarReceta() {
    std::string nombre;
    std::cin.ignore();
    std::cout << "Nombre a eliminar: ";
    std::getline(std::cin, nombre);

    try {
        recetario.eliminarRecetaPorNombre(nombre);
        std::cout << "Receta eliminada.\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void Menu::eliminarTodasRecetas() {
    recetario.eliminarTodasRecetas();
    std::cout << "Todas las recetas eliminadas.\n";
}

void Menu::ordenarRecetas() {
    std::string opcion;
    std::cin.ignore();
    std::cout << "Ordenar por (nombre/tiempo): ";
    std::getline(std::cin, opcion);

    if (opcion == "nombre") recetario.ordenarPorNombre();
    else if (opcion == "tiempo") recetario.ordenarPorTiempo();
    else std::cout << "Opcion invalida.\n";

    mostrarRecetas();
}

void Menu::editarReceta() {
    try {
        std::string nombre;
        std::cin.ignore();
        std::cout << "Nombre a editar: ";
        std::getline(std::cin, nombre);

        Receta* r = recetario.buscarRecetaPorNombre(nombre);
        if (!r) {
            std::cout << "No encontrada.\n";
            return;
        }

        int opc;
        do {
            std::cout << "\n1.Nombre\n2.Categoria\n3.Autor\n4.Tiempo\n5.Procedimiento\n"
                         "6.Reemplazar ingredientes\n0.Salir\n";

            std::cout << "Opcion: ";
            std::cin >> opc;
            std::cin.ignore();

            if (opc == 1) {
                std::string x; std::getline(std::cin, x); r->setNombre(x);
            }
            else if (opc == 2) {
                std::string x; std::getline(std::cin, x); r->setCategoria(x);
            }
            else if (opc == 3) {
                std::string x; std::getline(std::cin, x); r->setAutor(x);
            }
            else if (opc == 4) {
                int t; std::cin >> t; r->setTiempo(t); std::cin.ignore();
            }
            else if (opc == 5) {
                std::string x; std::getline(std::cin, x); r->setProcedimiento(x);
            }
            else if (opc == 6) {
                r->eliminarTodosIngredientes();
                int n;
                std::cout << "Num ingredientes: ";
                std::cin >> n;
                std::cin.ignore();

                for (int i = 0; i < n; i++) {
                    std::string n2, u;
                    float c;

                    std::cout << "Nombre: ";
                    std::getline(std::cin, n2);

                    std::cout << "Unidad: ";
                    std::getline(std::cin, u);

                    std::cout << "Cantidad: ";
                    std::cin >> c;
                    std::cin.ignore();

                    r->agregarIngrediente(Ingrediente(n2, u, c));
                }
            }

        } while (opc != 0);

    } catch (...) {
        std::cout << "Error editando.\n";
    }
}

void Menu::guardarRecetario() {
    std::string archivo;
    std::cin.ignore();
    std::cout << "Archivo: ";
    std::getline(std::cin, archivo);

    try {
        recetario.guardarADisco(archivo);
        std::cout << "Guardado.\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void Menu::leerRecetario() {
    std::string archivo;
    std::cin.ignore();
    std::cout << "Archivo: ";
    std::getline(std::cin, archivo);

    try {
        recetario.leerDeDisco(archivo);
        std::cout << "Cargado.\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void Menu::iniciar() {
    int opc;
    do {
        std::cout << "\n--- MENU ---\n"
                  << "1.Agregar\n2.Mostrar\n3.Buscar\n4.Eliminar\n"
                  << "5.Eliminar todas\n6.Ordenar\n7.Editar\n"
                  << "8.Guardar\n9.Cargar\n0.Salir\n";
        std::cout << "Opcion: ";
        std::cin >> opc;

        switch (opc) {
            case 1: agregarReceta(); break;
            case 2: mostrarRecetas(); break;
            case 3: buscarReceta(); break;
            case 4: eliminarReceta(); break;
            case 5: eliminarTodasRecetas(); break;
            case 6: ordenarRecetas(); break;
            case 7: editarReceta(); break;
            case 8: guardarRecetario(); break;
            case 9: leerRecetario(); break;
        }

    } while (opc != 0);
}
