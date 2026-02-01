#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "facturas.h"
using namespace std;

const int MAX_FACTURAS = 100;
const int CAMPOS_FACTURA = 9;
string Facturas[MAX_FACTURAS][CAMPOS_FACTURA];
int TotalFacturas = 0;

void CargarFacturas() {
    ifstream Archivo("data/facturas.csv");
    if (!Archivo.is_open()) return;
    string Linea;
    getline(Archivo, Linea);
    TotalFacturas = 0;
    while (getline(Archivo, Linea) && TotalFacturas < MAX_FACTURAS) {
        stringstream Ss(Linea);
        string Valor;
        int i = 0;
        while (getline(Ss, Valor, ',') && i < CAMPOS_FACTURA) {
            Facturas[TotalFacturas][i] = Valor;
            i++;
        }
        TotalFacturas++;
    }
    Archivo.close();
}

void MostrarFacturas() {
    cout << "\nIdFactura | IdCliente | IdLinea | Mes | Año | Plan | Monto | Estado | FechaPago\n";
    for (int i = 0; i < TotalFacturas; i++) {
        for (int j = 0; j < CAMPOS_FACTURA; j++) {
            cout << Facturas[i][j];
            if (j < CAMPOS_FACTURA-1) cout << " | ";
        }
        cout << endl;
    }
}

void InsertarFactura() {
    if (TotalFacturas >= MAX_FACTURAS) return;
    for (int i = 0; i < CAMPOS_FACTURA; i++) {
        cout << "Ingrese ";
        switch(i) {
            case 0: cout << "IdFactura: "; break;
            case 1: cout << "IdCliente: "; break;
            case 2: cout << "IdLinea: "; break;
            case 3: cout << "Mes: "; break;
            case 4: cout << "Año: "; break;
            case 5: cout << "Plan: "; break;
            case 6: cout << "Monto: "; break;
            case 7: cout << "Estado: "; break;
            case 8: cout << "FechaPago: "; break;
        }
        cin >> Facturas[TotalFacturas][i];
    }
    TotalFacturas++;
    ofstream Archivo("data/facturas.csv", ios::app);
    for (int i = 0; i < CAMPOS_FACTURA; i++) {
        Archivo << Facturas[TotalFacturas-1][i];
        if (i < CAMPOS_FACTURA-1) Archivo << ",";
    }
    Archivo << endl;
    Archivo.close();
}

void ActualizarFactura() {
    if (TotalFacturas == 0) return;
    string Id;
    cout << "Ingrese IdFactura a actualizar: ";
    cin >> Id;
    for (int i = 0; i < TotalFacturas; i++) {
        if (Facturas[i][0] == Id) {
            for (int j = 1; j < CAMPOS_FACTURA; j++) {
                cout << "Ingrese nuevo valor para ";
                switch(j) {
                    case 1: cout << "IdCliente"; break;
                    case 2: cout << "IdLinea"; break;
                    case 3: cout << "Mes"; break;
                    case 4: cout << "Año"; break;
                    case 5: cout << "Plan"; break;
                    case 6: cout << "Monto"; break;
                    case 7: cout << "Estado"; break;
                    case 8: cout << "FechaPago"; break;
                }
                cout << " (actual: " << Facturas[i][j] << "): ";
                cin >> Facturas[i][j];
            }
            break;
        }
    }
    ofstream Archivo("data/facturas.csv");
    Archivo << "IdFactura,IdCliente,IdLinea,Mes,Año,Plan,Monto,Estado,FechaPago\n";
    for (int i = 0; i < TotalFacturas; i++) {
        for (int j = 0; j < CAMPOS_FACTURA; j++) {
            Archivo << Facturas[i][j];
            if (j < CAMPOS_FACTURA-1) Archivo << ",";
        }
        Archivo << endl;
    }
    Archivo.close();
}

void EliminarFactura() {
    if (TotalFacturas == 0) return;
    string Id;
    cout << "Ingrese IdFactura a eliminar: ";
    cin >> Id;
    for (int i = 0; i < TotalFacturas; i++) {
        if (Facturas[i][0] == Id) {
            for (int j = i; j < TotalFacturas-1; j++) {
                for (int k = 0; k < CAMPOS_FACTURA; k++)
                    Facturas[j][k] = Facturas[j+1][k];
            }
            TotalFacturas--;
            break;
        }
    }
    ofstream Archivo("data/facturas.csv");
    Archivo << "IdFactura,IdCliente,IdLinea,Mes,Año,Plan,Monto,Estado,FechaPago\n";
    for (int i = 0; i < TotalFacturas; i++) {
        for (int j = 0; j < CAMPOS_FACTURA; j++) {
            Archivo << Facturas[i][j];
            if (j < CAMPOS_FACTURA-1) Archivo << ",";
        }
        Archivo << endl;
    }
    Archivo.close();
}

void BuscarFactura() {
    if (TotalFacturas == 0) return;
    int Campo;
    cout << "\nBuscar por campo:\n0.IdFactura\n1.IdCliente\n2.IdLinea\n3.Mes\n4.Año\n5.Plan\n6.Monto\n7.Estado\n8.FechaPago\n";
    cout << "Seleccione campo: ";
    cin >> Campo;
    string Valor;
    cout << "Ingrese valor a buscar: ";
    cin >> Valor;
    bool Encontrado = false;
    for (int i = 0; i < TotalFacturas; i++) {
        if (Facturas[i][Campo] == Valor) {
            Encontrado = true;
            for (int j = 0; j < CAMPOS_FACTURA; j++) {
                cout << Facturas[i][j];
                if (j < CAMPOS_FACTURA-1) cout << " | ";
            }
            cout << endl;
        }
    }
    if (!Encontrado) cout << "No se encontro ninguna factura\n";
}

void OrdenarFacturas() {
    if (TotalFacturas == 0) return;
    int Campo;
    cout << "\nOrdenar por:\n0.IdFactura\n1.IdCliente\n2.IdLinea\n3.Mes\n4.Monto\n";
    cout << "Seleccione campo: ";
    cin >> Campo;
    for (int i = 0; i < TotalFacturas-1; i++) {
        for (int j = i+1; j < TotalFacturas; j++) {
            if (Facturas[i][Campo] > Facturas[j][Campo]) {
                for (int k = 0; k < CAMPOS_FACTURA; k++)
                    swap(Facturas[i][k], Facturas[j][k]);
            }
        }
    }
    MostrarFacturas();
}

void MenuFacturas() {
    int Opcion;
    do {
        cout << "\nMenu Facturas\n1.Mostrar\n2.Insertar\n3.Actualizar\n4.Eliminar\n5.Buscar\n6.Ordenar\n7.Volver\nOpcion: ";
        cin >> Opcion;
        switch(Opcion) {
            case 1: MostrarFacturas(); break;
            case 2: InsertarFactura(); break;
            case 3: ActualizarFactura(); break;
            case 4: EliminarFactura(); break;
            case 5: BuscarFactura(); break;
            case 6: OrdenarFacturas(); break;
            case 7: break;
            default: cout << "Opcion invalida\n"; break;
        }
    } while(Opcion != 7);
}

