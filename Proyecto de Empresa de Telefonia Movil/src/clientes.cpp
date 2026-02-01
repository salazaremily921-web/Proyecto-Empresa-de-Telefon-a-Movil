#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "clientes.h"
using namespace std;

const int MAX_CLIENTES = 100;
const int CAMPOS = 9;
string Clientes[MAX_CLIENTES][CAMPOS];
int TotalClientes = 0;

// cargar clientes desde csv
void CargarClientes() {
    ifstream Archivo("data/clientes.csv");
    if (!Archivo.is_open()) return;
    string Linea;
    getline(Archivo, Linea);
    TotalClientes = 0;
    while (getline(Archivo, Linea) && TotalClientes < MAX_CLIENTES) {
        stringstream Ss(Linea);
        string Valor;
        int i = 0;
        while (getline(Ss, Valor, ',') && i < CAMPOS) {
            Clientes[TotalClientes][i] = Valor;
            i++;
        }
        TotalClientes++;
    }
    Archivo.close();
}

// mostrar todos los clientes
void MostrarClientes() {
    cout << "\nId | Nombre | Apellido | Direccion | Ciudad | Email | Telefono | FechaRegistro | Estado\n";
    for (int i = 0; i < TotalClientes; i++) {
        for (int j = 0; j < CAMPOS; j++) {
            cout << Clientes[i][j];
            if (j < CAMPOS-1) cout << " | ";
        }
        cout << endl;
    }
}

// insertar cliente
void InsertarCliente() {
    if (TotalClientes >= MAX_CLIENTES) return;
    for (int i = 0; i < CAMPOS; i++) {
        cout << "Ingrese ";
        switch(i) {
            case 0: cout << "Id: "; break;
            case 1: cout << "Nombre: "; break;
            case 2: cout << "Apellido: "; break;
            case 3: cout << "Direccion: "; break;
            case 4: cout << "Ciudad: "; break;
            case 5: cout << "Email: "; break;
            case 6: cout << "Telefono: "; break;
            case 7: cout << "FechaRegistro: "; break;
            case 8: cout << "Estado: "; break;
        }
        cin >> Clientes[TotalClientes][i];
    }
    TotalClientes++;
    ofstream Archivo("data/clientes.csv", ios::app);
    for (int i = 0; i < CAMPOS; i++) {
        Archivo << Clientes[TotalClientes-1][i];
        if (i < CAMPOS-1) Archivo << ",";
    }
    Archivo << endl;
    Archivo.close();
}

// actualizar cliente
void ActualizarCliente() {
    if (TotalClientes == 0) return;
    string Id;
    cout << "Ingrese Id del cliente a actualizar: ";
    cin >> Id;
    for (int i = 0; i < TotalClientes; i++) {
        if (Clientes[i][0] == Id) {
            for (int j = 1; j < CAMPOS; j++) {
                cout << "Ingrese nuevo valor para ";
                switch(j) {
                    case 1: cout << "Nombre"; break;
                    case 2: cout << "Apellido"; break;
                    case 3: cout << "Direccion"; break;
                    case 4: cout << "Ciudad"; break;
                    case 5: cout << "Email"; break;
                    case 6: cout << "Telefono"; break;
                    case 7: cout << "FechaRegistro"; break;
                    case 8: cout << "Estado"; break;
                }
                cout << " (actual: " << Clientes[i][j] << "): ";
                cin >> Clientes[i][j];
            }
            break;
        }
    }
    ofstream Archivo("data/clientes.csv");
    Archivo << "Id,Nombre,Apellido,Direccion,Ciudad,Email,Telefono,FechaRegistro,Estado\n";
    for (int i = 0; i < TotalClientes; i++) {
        for (int j = 0; j < CAMPOS; j++) {
            Archivo << Clientes[i][j];
            if (j < CAMPOS-1) Archivo << ",";
        }
        Archivo << endl;
    }
    Archivo.close();
}

// eliminar cliente
void EliminarCliente() {
    if (TotalClientes == 0) return;
    string Id;
    cout << "Ingrese Id del cliente a eliminar: ";
    cin >> Id;
    for (int i = 0; i < TotalClientes; i++) {
        if (Clientes[i][0] == Id) {
            for (int j = i; j < TotalClientes-1; j++) {
                for (int k = 0; k < CAMPOS; k++)
                    Clientes[j][k] = Clientes[j+1][k];
            }
            TotalClientes--;
            break;
        }
    }
    ofstream Archivo("data/clientes.csv");
    Archivo << "Id,Nombre,Apellido,Direccion,Ciudad,Email,Telefono,FechaRegistro,Estado\n";
    for (int i = 0; i < TotalClientes; i++) {
        for (int j = 0; j < CAMPOS; j++) {
            Archivo << Clientes[i][j];
            if (j < CAMPOS-1) Archivo << ",";
        }
        Archivo << endl;
    }
    Archivo.close();
}

// buscar cliente por cualquier campo (10 búsquedas)
void BuscarCliente() {
    if (TotalClientes == 0) return;
    int Campo;
    cout << "\nBuscar por campo:\n0.Id\n1.Nombre\n2.Apellido\n3.Direccion\n4.Ciudad\n5.Email\n6.Telefono\n7.FechaRegistro\n8.Estado\n";
    cout << "Seleccione campo: ";
    cin >> Campo;
    string Valor;
    cout << "Ingrese valor a buscar: ";
    cin >> Valor;
    bool Encontrado = false;
    for (int i = 0; i < TotalClientes; i++) {
        if (Clientes[i][Campo] == Valor) {
            Encontrado = true;
            for (int j = 0; j < CAMPOS; j++) {
                cout << Clientes[i][j];
                if (j < CAMPOS-1) cout << " | ";
            }
            cout << endl;
        }
    }
    if (!Encontrado) cout << "No se encontro ningun cliente\n";
}

// ordenar clientes (5 ordenamientos por diferentes campos)
void OrdenarClientes() {
    if (TotalClientes == 0) return;
    int Campo;
    cout << "\nOrdenar por:\n0.Id\n1.Nombre\n2.Apellido\n3.Ciudad\n4.FechaRegistro\n";
    cout << "Seleccione campo: ";
    cin >> Campo;
    for (int i = 0; i < TotalClientes-1; i++) {
        for (int j = i+1; j < TotalClientes; j++) {
            if (Clientes[i][Campo] > Clientes[j][Campo]) {
                for (int k = 0; k < CAMPOS; k++)
                    swap(Clientes[i][k], Clientes[j][k]);
            }
        }
    }
    MostrarClientes();
}

// menu clientes
void MenuClientes() {
    int Opcion;
    do {
        cout << "\nMenu Clientes\n1.Mostrar\n2.Insertar\n3.Actualizar\n4.Eliminar\n5.Buscar\n6.Ordenar\n7.Volver\nOpcion: ";
        cin >> Opcion;
        switch(Opcion) {
            case 1: MostrarClientes(); break;
            case 2: InsertarCliente(); break;
            case 3: ActualizarCliente(); break;
            case 4: EliminarCliente(); break;
            case 5: BuscarCliente(); break;
            case 6: OrdenarClientes(); break;
            case 7: break;
            default: cout << "Opcion invalida\n"; break;
        }
    } while(Opcion != 7);
}

