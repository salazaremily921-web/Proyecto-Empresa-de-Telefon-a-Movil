#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "lineas.h"
using namespace std;

const int MAX_LINEAS = 100;
const int CAMPOS_LINEA = 9;
string Lineas[MAX_LINEAS][CAMPOS_LINEA];
int TotalLineas = 0;

void CargarLineas() {
    ifstream Archivo("data/lineas.csv");
    if (!Archivo.is_open()) return;
    string Linea;
    getline(Archivo, Linea);
    TotalLineas = 0;
    while (getline(Archivo, Linea) && TotalLineas < MAX_LINEAS) {
        stringstream Ss(Linea);
        string Valor;
        int i = 0;
        while (getline(Ss, Valor, ',') && i < CAMPOS_LINEA) {
            Lineas[TotalLineas][i] = Valor;
            i++;
        }
        TotalLineas++;
    }
    Archivo.close();
}

void MostrarLineas() {
    cout << "\nIdLinea | IdCliente | Numero | Plan | Estado | FechaActivacion | Minutos | Datos | Observaciones\n";
    for (int i = 0; i < TotalLineas; i++) {
        for (int j = 0; j < CAMPOS_LINEA; j++) {
            cout << Lineas[i][j];
            if (j < CAMPOS_LINEA-1) cout << " | ";
        }
        cout << endl;
    }
}

void InsertarLinea() {
    if (TotalLineas >= MAX_LINEAS) return;
    for (int i = 0; i < CAMPOS_LINEA; i++) {
        cout << "Ingrese ";
        switch(i) {
            case 0: cout << "IdLinea: "; break;
            case 1: cout << "IdCliente: "; break;
            case 2: cout << "Numero: "; break;
            case 3: cout << "Plan: "; break;
            case 4: cout << "Estado: "; break;
            case 5: cout << "FechaActivacion: "; break;
            case 6: cout << "Minutos: "; break;
            case 7: cout << "Datos: "; break;
            case 8: cout << "Observaciones: "; break;
        }
        cin >> Lineas[TotalLineas][i];
    }
    TotalLineas++;
    ofstream Archivo("data/lineas.csv", ios::app);
    for (int i = 0; i < CAMPOS_LINEA; i++) {
        Archivo << Lineas[TotalLineas-1][i];
        if (i < CAMPOS_LINEA-1) Archivo << ",";
    }
    Archivo << endl;
    Archivo.close();
}

void ActualizarLinea() {
    if (TotalLineas == 0) return;
    string Id;
    cout << "Ingrese IdLinea a actualizar: ";
    cin >> Id;
    for (int i = 0; i < TotalLineas; i++) {
        if (Lineas[i][0] == Id) {
            for (int j = 1; j < CAMPOS_LINEA; j++) {
                cout << "Ingrese nuevo valor para ";
                switch(j) {
                    case 1: cout << "IdCliente"; break;
                    case 2: cout << "Numero"; break;
                    case 3: cout << "Plan"; break;
                    case 4: cout << "Estado"; break;
                    case 5: cout << "FechaActivacion"; break;
                    case 6: cout << "Minutos"; break;
                    case 7: cout << "Datos"; break;
                    case 8: cout << "Observaciones"; break;
                }
                cout << " (actual: " << Lineas[i][j] << "): ";
                cin >> Lineas[i][j];
            }
            break;
        }
    }
    ofstream Archivo("data/lineas.csv");
    Archivo << "IdLinea,IdCliente,Numero,Plan,Estado,FechaActivacion,Minutos,Datos,Observaciones\n";
    for (int i = 0; i < TotalLineas; i++) {
        for (int j = 0; j < CAMPOS_LINEA; j++) {
            Archivo << Lineas[i][j];
            if (j < CAMPOS_LINEA-1) Archivo << ",";
        }
        Archivo << endl;
    }
    Archivo.close();
}

void EliminarLinea() {
    if (TotalLineas == 0) return;
    string Id;
    cout << "Ingrese IdLinea a eliminar: ";
    cin >> Id;
    for (int i = 0; i < TotalLineas; i++) {
        if (Lineas[i][0] == Id) {
            for (int j = i; j < TotalLineas-1; j++) {
                for (int k = 0; k < CAMPOS_LINEA; k++)
                    Lineas[j][k] = Lineas[j+1][k];
            }
            TotalLineas--;
            break;
        }
    }
    ofstream Archivo("data/lineas.csv");
    Archivo << "IdLinea,IdCliente,Numero,Plan,Estado,FechaActivacion,Minutos,Datos,Observaciones\n";
    for (int i = 0; i < TotalLineas; i++) {
        for (int j = 0; j < CAMPOS_LINEA; j++) {
            Archivo << Lineas[i][j];
            if (j < CAMPOS_LINEA-1) Archivo << ",";
        }
        Archivo << endl;
    }
    Archivo.close();
}

void BuscarLinea() {
    if (TotalLineas == 0) return;
    int Campo;
    cout << "\nBuscar por campo:\n0.IdLinea\n1.IdCliente\n2.Numero\n3.Plan\n4.Estado\n5.FechaActivacion\n6.Minutos\n7.Datos\n8.Observaciones\n";
    cout << "Seleccione campo: ";
    cin >> Campo;
    string Valor;
    cout << "Ingrese valor a buscar: ";
    cin >> Valor;
    bool Encontrado = false;
    for (int i = 0; i < TotalLineas; i++) {
        if (Lineas[i][Campo] == Valor) {
            Encontrado = true;
            for (int j = 0; j < CAMPOS_LINEA; j++) {
                cout << Lineas[i][j];
                if (j < CAMPOS_LINEA-1) cout << " | ";
            }
            cout << endl;
        }
    }
    if (!Encontrado) cout << "No se encontro ninguna linea\n";
}

void OrdenarLineas() {
    if (TotalLineas == 0) return;
    int Campo;
    cout << "\nOrdenar por:\n0.IdLinea\n1.IdCliente\n2.Numero\n3.Plan\n4.FechaActivacion\n";
    cout << "Seleccione campo: ";
    cin >> Campo;
    for (int i = 0; i < TotalLineas-1; i++) {
        for (int j = i+1; j < TotalLineas; j++) {
            if (Lineas[i][Campo] > Lineas[j][Campo]) {
                for (int k = 0; k < CAMPOS_LINEA; k++)
                    swap(Lineas[i][k], Lineas[j][k]);
            }
        }
    }
    MostrarLineas();
}

void MenuLineas() {
    int Opcion;
    do {
        cout << "\nMenu Lineas\n1.Mostrar\n2.Insertar\n3.Actualizar\n4.Eliminar\n5.Buscar\n6.Ordenar\n7.Volver\nOpcion: ";
        cin >> Opcion;
        switch(Opcion) {
            case 1: MostrarLineas(); break;
            case 2: InsertarLinea(); break;
            case 3: ActualizarLinea(); break;
            case 4: EliminarLinea(); break;
            case 5: BuscarLinea(); break;
            case 6: OrdenarLineas(); break;
            case 7: break;
            default: cout << "Opcion invalida\n"; break;
        }
    } while(Opcion != 7);
}

