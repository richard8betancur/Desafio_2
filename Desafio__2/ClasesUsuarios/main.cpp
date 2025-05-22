#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Usuario {
private:
    char* nombre;
    int edad;
    int id;
    int antiguedadMeses;
    int adminAloja;
    float puntuacion;
    bool sesion;

public:
    Usuario() {
        nombre = nullptr;
    }

    ~Usuario() {
        delete[] nombre;
    }

    // Versión completa para anfitriones
    void setDatos(const char* n, int e, int i, int antig, int adm, float p, bool s) {
        if (nombre != nullptr) delete[] nombre;
        nombre = new char[strlen(n) + 1];
        strcpy_s(nombre, strlen(n) + 1, n);

        edad = e;
        id = i;
        antiguedadMeses = antig;
        adminAloja = adm;
        puntuacion = p;
        sesion = s;
    }

    // Versión simplificada para huéspedes (sin adminAloja)
    void setDatos(const char* n, int e, int i, int antig, float p, bool s) {
        setDatos(n, e, i, antig, 0, p, s); // adminAloja = 0
    }

    void mostrarDatos() {
        cout << "Nombre: " << nombre << endl;
        cout << "Edad: " << edad << endl;
        cout << "ID: " << id << endl;
        cout << "Meses de antigüedad: " << antiguedadMeses << endl;
        cout << "Alojamientos que administra: " << adminAloja << endl;
        cout << "Puntuación: " << puntuacion << endl;
        cout << "Sesión activa: " << (sesion ? "Sí" : "No") << endl;
        cout << "-----------------------------" << endl;
    }

    const char* getNombre() {
        return nombre;
    }
};

class Anfitrion : public Usuario {
public:
    void mostrarMenu() {
        cout << "Menú del anfitrión para: " << getNombre() << endl;
    }
};

class Huesped : public Usuario {
public:
    void mostrarMenu() {
        cout << "Menú del huésped para: " << getNombre() << endl;
    }
};

int main() {
    {
        ifstream archivo("Anfitriones.txt");
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo de anfitriones." << endl;
            return 1;
        }

        char nombre[100];
        int edad, id, antig, adm;
        float puntuacion;
        bool sesion;

        while (archivo >> nombre >> edad >> id >> antig >> adm >> puntuacion >> sesion) {
            Anfitrion a;
            a.setDatos(nombre, edad, id, antig, adm, puntuacion, sesion);
            a.mostrarDatos();
        }

        archivo.close();
    }

    {
        ifstream archivo("Huespedes.txt");
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo de huéspedes." << endl;
            return 1;
        }

        char nombre[100];
        int edad, id, antig;
        float puntuacion;
        bool sesion;

        while (archivo >> nombre >> edad >> id >> antig >> puntuacion >> sesion) {
            Huesped h;
            h.setDatos(nombre, edad, id, antig, puntuacion, sesion);
            h.mostrarDatos();
        }

        archivo.close();
    }

    return 0;
}



