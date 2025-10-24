#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <sstream>

// Rutas de las carpetas de salida
const std::string RUTA_INSTANCIAS = "nodos/";
const std::string RUTA_USUARIOS = "usuarios/";

// Prototipos de las funciones
void generarArchivoDeInstancia(int n, int indice, std::mt19937& rng);
void generarArchivoDeUsuarios(int n, int indice, std::mt19937& rng);

int main() {
    int numeroDeNodos;
    int cantidadDeInstancias;

    std::cout << "Ingresa el número de nodos para las instancias: ";
    std::cin >> numeroDeNodos;
    if (numeroDeNodos <= 1) {
        std::cerr << "Error: El número de nodos debe ser mayor que 1." << std::endl;
        return 1;
    }

    std::cout << "Ingresa la cantidad de sets de instancias a generar: ";
    std::cin >> cantidadDeInstancias;
    if (cantidadDeInstancias < 1) {
        std::cerr << "Error: Debes generar al menos 1 set." << std::endl;
        return 1;
    }

    std::mt19937 rng(time(0));
    int indiceArchivoActual = 0;

    // Bucle principal para generar múltiples sets de instancias
    for (int i = 0; i < cantidadDeInstancias; ++i) {
        std::cout << "\n--- Generando Set de Instancia #" << i + 1 << " ---" << std::endl;
        
        // Bucle para encontrar el siguiente nombre de archivo disponible y no sobrescribir
        while (true) {
            std::stringstream ss;
            ss << numeroDeNodos << "_instancia";
            if (indiceArchivoActual > 0) {
                ss << "_" << indiceArchivoActual;
            }
            ss << ".txt";
            
            std::ifstream f((RUTA_INSTANCIAS + ss.str()).c_str());
            if (!f.good()) {
                break; // Encontramos un nombre disponible
            }
            indiceArchivoActual++;
        }

        try {
            generarArchivoDeInstancia(numeroDeNodos, indiceArchivoActual, rng);
            generarArchivoDeUsuarios(numeroDeNodos, indiceArchivoActual, rng);
        } catch (const std::exception& e) {
            std::cerr << "Ocurrió un error: " << e.what() << std::endl;
            return 1;
        }
        indiceArchivoActual++; // Nos preparamos para el siguiente set en la próxima iteración
    }

    std::cout << "\n¡Proceso completado! Se generaron " << cantidadDeInstancias << " sets de instancias." << std::endl;
    return 0;
}

void generarArchivoDeInstancia(int n, int indice, std::mt19937& rng) {
    std::stringstream ss;
    ss << n << "_instancia";
    if (indice >= 0) {
        ss << "_" << indice;
    }
    ss << ".txt";
    std::string nombreArchivo = ss.str();
    
    std::ofstream archivo(RUTA_INSTANCIAS + nombreArchivo);

    // Lógica de escalado proporcional para los parámetros
    std::uniform_int_distribution<> distTiempoServicio(5 , 20);
    std::uniform_int_distribution<> distTiempoViaje(n * 0.5, n * 2.0);
    std::uniform_int_distribution<> distOffsetVentana(5, n * 2.0);
    std::uniform_int_distribution<> distDuracionVentana(30, 20 + n * 3.5);
    
    archivo << n << std::endl;

    archivo << 0;
    for (int i = 1; i < n; ++i) {
        archivo << " " << distTiempoServicio(rng);
    }
    archivo << std::endl;

    std::vector<std::vector<int>> distancias(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            distancias[i][j] = (i == j) ? 0 : distTiempoViaje(rng);
        }
    }

    archivo << "0 999";
    for (int i = 1; i < n; ++i) {
        int e_i = distancias[0][i] + distOffsetVentana(rng);
        int l_i = e_i + distDuracionVentana(rng);
        archivo << "  " << e_i << " " << l_i;
    }
    archivo << std::endl;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            archivo << distancias[i][j] << (j == n - 1 ? "" : " ");
        }
        archivo << std::endl;
    }

    archivo.close();
    std::cout << "-> Archivo de instancia '" << nombreArchivo << "' creado." << std::endl;
}

void generarArchivoDeUsuarios(int n, int indice, std::mt19937& rng) {
    // Número de usuarios escalable
    int maxUsuarios = 2 + (n / 2);
    std::uniform_int_distribution<> distNumUsuarios(2, maxUsuarios);
    int m = distNumUsuarios(rng);

    std::stringstream ss;
    ss << n << "_instancia";
    if (indice > 0) {
        ss << "_" << indice;
    }
    ss << "_" << m << "us.txt";
    std::string nombreArchivo = ss.str();
    
    std::ofstream archivo(RUTA_USUARIOS + nombreArchivo);

    // Tiempo total del usuario también escala
    std::uniform_int_distribution<> distTiempoTotal(n * 10, n * 15);
    std::uniform_int_distribution<> distValoracion(5, 25);

    archivo << m << std::endl;

    for (int k = 0; k < m; ++k) {
        archivo << distTiempoTotal(rng) << std::endl;
        archivo << 0;
        for (int i = 1; i < n; ++i) {
            archivo << " " << distValoracion(rng);
        }
        archivo << std::endl;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int valor = (i == j) ? 0 : distValoracion(rng) / 2;
                archivo << valor << (j == n - 1 ? "" : " ");
            }
            archivo << std::endl;
        }
    }

    archivo.close();
    std::cout << "-> Archivo de usuarios '" << nombreArchivo << "' creado." << std::endl;
}