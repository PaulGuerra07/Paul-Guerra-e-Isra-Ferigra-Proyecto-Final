#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <vector> 

using namespace std;

// Estructura para representar un álbum (7 campos)
struct Album {
    string titulo;          
    string artista;         
    int anoLanzamiento;     
    string genero;          
    int duracionMinutos;    
    float calificacion;     
    double precio;          
    char formato;           // 'D'igital, 'F'isico, 'V'inilo
};

// Constantes
const int MAX_ALBUMES = 20;
const int NUM_GENEROS = 5;
const int NUM_DECADAS = 7;

string generos[NUM_GENEROS] = {"Rock", "Pop", "Salsa", "Electronica", "Otros"};
string decadas[NUM_DECADAS] = {"1960s", "1970s", "1980s", "1990s", "2000s", "2010s", "2020s"};

// Funciones Auxiliares 

bool es_Genero_Valido(string g) {
    for (int i = 0; i < NUM_GENEROS; ++i) {
        if (generos[i] == g) return true;
    }
    return false;
}

int obtener_Indice_Genero(const string& gen) {
    for (int i = 0; i < NUM_GENEROS; ++i) {
        if (generos[i] == gen) return i;
    }
    return NUM_GENEROS - 1; 
}

int obtener_Indice_Decada(int ano) {
    if (ano < 1960) return 0;
    int indice = (ano - 1960) / 10;
    if (indice >= NUM_DECADAS) return NUM_DECADAS - 1;
    return indice;
}

// Gestión de la Colección 
// Registrar un nuevo álbum
void registrar_Album(Album coleccion[], int& numAlbumes) {
    if (numAlbumes >= MAX_ALBUMES) {
        cout << "Coleccion llena. No se puede agregar mas albumes." << endl;
        return;
    }
    
    Album nuevo; 
    cout << "\n REGISTRAR NUEVO ALBUM " << endl;
    
    cout << "1. Titulo: ";
    getline(cin, nuevo.titulo);
    
    cout << "2. Artista: ";
    getline(cin, nuevo.artista);
    
    cout << "3. Ano de lanzamiento: ";
    while (!(cin >> nuevo.anoLanzamiento)) {
        cout << "Entrada invalida. Ingrese un numero: ";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(); 
    
    bool generoCorrecto = false;
    do {
        cout << "4. Genero (Rock, Pop, Salsa, Electronica, Otros): ";
        getline(cin, nuevo.genero);
        if (es_Genero_Valido(nuevo.genero)) generoCorrecto = true;
        else cout << "--> Genero no valido." << endl;
    } while (!generoCorrecto);

    cout << "5. Duracion (minutos): ";
    while (!(cin >> nuevo.duracionMinutos)) {
        cout << "Numero invalido: ";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cout << "6. Calificacion (1.0 - 5.0): ";
    while (!(cin >> nuevo.calificacion) || nuevo.calificacion < 0 || nuevo.calificacion > 5) {
        cout << "Ingrese un decimal entre 0 y 5: ";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "7. Precio (USD): ";
    while (!(cin >> nuevo.precio)) {
        cout << "Ingrese un valor decimal valido: ";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "8. Formato (D=Digital, F=Fisico, V=Vinilo): ";
    cin >> nuevo.formato;
    while (nuevo.formato != 'D' && nuevo.formato != 'F' && nuevo.formato != 'V' && 
           nuevo.formato != 'd' && nuevo.formato != 'f' && nuevo.formato != 'v') {
        cout << "Opcion invalida. Ingrese D, F o V: ";
        cin >> nuevo.formato;
    }
    cin.ignore(); 

    coleccion[numAlbumes] = nuevo; 
    ++numAlbumes; 
    cout << "--> Album registrado exitosamente." << endl;
}

// Mostrar colección en formato tabla
void mostrar_Coleccion(const Album coleccion[], int numAlbumes) {
    if (numAlbumes == 0) {
        cout << "No hay albumes en la coleccion." << endl;
        return;
    }
    
    cout << "\n" << endl;
    cout << left << setw(20) << "Titulo" << setw(15) << "Artista" << setw(6) << "Ano" 
         << setw(12) << "Genero" << setw(6) << "Min" << setw(6) << "Calif" 
         << setw(8) << "Precio" << setw(5) << "Fmt" << endl;
    cout << "" << endl;

    for (int i = 0; i < numAlbumes; ++i) {
        cout << left << setw(20) << coleccion[i].titulo 
             << setw(15) << coleccion[i].artista
             << setw(6)  << coleccion[i].anoLanzamiento 
             << setw(12) << coleccion[i].genero
             << setw(6)  << coleccion[i].duracionMinutos 
             << setw(6)  << coleccion[i].calificacion
             << "$" << setw(7) << coleccion[i].precio
             << setw(5)  << coleccion[i].formato << endl; 
    }
    cout << "" << endl;
}

// Modificar datos de un álbum existente
void modificar_Album(Album coleccion[], int numAlbumes) {
    string busqueda;
    cout << "Ingrese el TITULO exacto del album a modificar: ";
    getline(cin, busqueda);

    for(int i = 0; i < numAlbumes; i++) {
        if(coleccion[i].titulo == busqueda) {
            cout << "Album encontrado. Ingrese los nuevos datos:" << endl;
            cout << "Nueva Calificacion: "; cin >> coleccion[i].calificacion;
            cout << "Nuevo Precio: "; cin >> coleccion[i].precio;
            cout << "--> Registro actualizado." << endl;
            cin.ignore();
            return;
        }
    }
    cout << "Error: Album no encontrado." << endl;
}

// Eliminar un álbum y reorganizar el arreglo
void eliminar_Album(Album coleccion[], int& numAlbumes) {
    string busqueda;
    cout << "Ingrese el TITULO del album a eliminar: ";
    getline(cin, busqueda);

    for(int i = 0; i < numAlbumes; i++) {
        if(coleccion[i].titulo == busqueda) {
            // Desplazar elementos a la izquierda para cubrir el hueco
            for(int j = i; j < numAlbumes - 1; j++) {
                coleccion[j] = coleccion[j+1];
            }
            numAlbumes--; 
            cout << "--> Album eliminado correctamente." << endl;
            return;
        }
    }
    cout << "Error: Album no encontrado." << endl;
}

// Ordenar colección por año (Burbuja)
void ordenar_Coleccion(Album coleccion[], int numAlbumes) {
    int tipo;
    cout << "Ordenar por Ano de Lanzamiento: 1. Ascendente, 2. Descendente: ";
    cin >> tipo;

    for(int i = 0; i < numAlbumes - 1; i++) {
        for(int j = 0; j < numAlbumes - i - 1; j++) {
            bool intercambiar = false;
            if (tipo == 1) { // Ascendente
                if(coleccion[j].anoLanzamiento > coleccion[j+1].anoLanzamiento) intercambiar = true;
            } else { // Descendente
                if(coleccion[j].anoLanzamiento < coleccion[j+1].anoLanzamiento) intercambiar = true;
            }

            if(intercambiar) {
                Album temp = coleccion[j];
                coleccion[j] = coleccion[j+1];
                coleccion[j+1] = temp;
            }
        }
    }
    cout << "--> Coleccion ordenada." << endl;
    cin.ignore();
}

// Buscar álbum por coincidencia en título
void buscar_Por_Titulo(const Album coleccion[], int numAlbumes) {
    string busqueda;
    cout << "Ingrese titulo a buscar: ";
    getline(cin, busqueda);
    bool encontrado = false; 
    for (int i = 0; i < numAlbumes; ++i) {
        if (coleccion[i].titulo.find(busqueda) != string::npos) {
            cout << "ENCONTRADO: " << coleccion[i].titulo << " (" << coleccion[i].anoLanzamiento << ")" << endl;
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No coincidencias." << endl;
}

// Encontrar el álbum con la mayor calificación
void mostrar_Mejor_Calificado(const Album coleccion[], int numAlbumes) {
    if (numAlbumes == 0) return;
    int indexMax = 0;
    for(int i = 1; i < numAlbumes; i++) {
        if(coleccion[i].calificacion > coleccion[indexMax].calificacion) {
            indexMax = i;
        }
    }
    cout << "\n*** ALBUM MEJOR CALIFICADO ***" << endl;
    cout << "Titulo: " << coleccion[indexMax].titulo << " | Nota: " << coleccion[indexMax].calificacion << endl;
}

// Análisis estadístico con matriz y promedios
void analizar_Coleccion(const Album coleccion[], int numAlbumes) {
    // Matriz bidimensional para el conteo
    int matrizConteo[NUM_GENEROS][NUM_DECADAS] = {0}; 
    
    for (int i = 0; i < numAlbumes; ++i) {
        int idxGen = obtener_Indice_Genero(coleccion[i].genero);
        int idxDec = obtener_Indice_Decada(coleccion[i].anoLanzamiento);
        ++matrizConteo[idxGen][idxDec]; 
    }
    
    cout << "\n--- MATRIZ DE ANALISIS (Generos vs Decadas) ---" << endl;
    cout << setw(15) << "Genero";
    for (int j = 0; j < NUM_DECADAS; ++j) cout << setw(8) << decadas[j];
    cout << endl;
    
    for (int i = 0; i < NUM_GENEROS; ++i) {
        cout << setw(15) << generos[i];
        for (int j = 0; j < NUM_DECADAS; ++j) {
            cout << setw(8) << matrizConteo[i][j];
        }
        cout << endl;
    }
    
    // Cálculo de promedios por género
    float sumaCalif[NUM_GENEROS] = {0}; 
    int conteoGen[NUM_GENEROS] = {0};   
    for (int i = 0; i < numAlbumes; ++i) {
        int idxGen = obtener_Indice_Genero(coleccion[i].genero);
        sumaCalif[idxGen] += coleccion[i].calificacion; 
        ++conteoGen[idxGen]; 
    }
    
    cout << "\nPromedio de calificaciones por genero:" << endl;
    for (int i = 0; i < NUM_GENEROS; ++i) {
        if (conteoGen[i] > 0) { 
            cout << generos[i] << ": " << (sumaCalif[i] / conteoGen[i]) << endl;
        }
    }
}

int main() {
    Album coleccion[MAX_ALBUMES]; 
    int numAlbumes = 0;           
    int opcion;                   
    
    do {
        cout << "\n SISTEMA DE GESTION DE MUSICA " << endl;
        cout << "1. Registrar album" << endl;
        cout << "2. Mostrar coleccion" << endl;
        cout << "3. Modificar album" << endl;     
        cout << "4. Eliminar album" << endl;      
        cout << "5. Buscar por titulo" << endl;
        cout << "6. Ordenar coleccion" << endl; 
        cout << "7. Ver album mejor calificado" << endl; 
        cout << "8. Analisis Estadistico" << endl;
        cout << "9. Salir" << endl;
        cout << "Elija una opcion: ";
        
        while (!(cin >> opcion)) {
            cout << "Opcion invalida. Ingrese un numero: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(); 
        
        switch (opcion) {
            case 1: registrar_Album(coleccion, numAlbumes); break;
            case 2: mostrar_Coleccion(coleccion, numAlbumes); break;
            case 3: modificar_Album(coleccion, numAlbumes); break;
            case 4: eliminar_Album(coleccion, numAlbumes); break;
            case 5: buscar_Por_Titulo(coleccion, numAlbumes); break;
            case 6: ordenar_Coleccion(coleccion, numAlbumes); break;
            case 7: mostrar_Mejor_Calificado(coleccion, numAlbumes); break;
            case 8: analizar_Coleccion(coleccion, numAlbumes); break;
            case 9: cout << "Cerrando sistema..." << endl; break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (opcion != 9); 
    
    return 0; 
}