#include <iostream>
#include <fstream>
using namespace std;

const int cod_prod{5};

/* 1. Emita un listado donde para cada cliente liste los tipos de producto tal que la cantidad total de
kilos transportados es mayor a 13000.*/

void listadoKg(string nom_prod[], string nom_cliente[], float kg[][cod_prod], int cont[], int cant_cliente, int cant_prod) {
    cout << "Los elementos con más de 13000kg son: " << endl;
    for (int i{0}; i < cant_cliente; i++) {
        cout << i << ". " << nom_cliente[i] << '\t';
        for (int j{0}; j < cant_prod; j++) {
            // encontrando productos con mas de 13000
            if (kg[i][j] > 13000){
                cout << nom_prod[j] << '\t';
                cont[i] += 1;
            }
        }
        cout << endl;
    }
}

int posc_mayor(int cont_cliente[], int codCLiente){
    int mayor = cont_cliente[0];
    int pos{0}; 

    for (int i{0}; i < codCLiente; i++)
    {
        if (cont_cliente[i] > mayor)
        {
            mayor = cont_cliente[i];
            pos = i;
        }
    }
    return pos;
}

/*2. Para el cliente con mayor cantidad tipos de productos que hayan superado 13000 kg en el punto
anterior, emita un listado con nombre de tipo de producto y total de kilómetros recorridos,
ordenado por total de kilómetros en forma ascendente.
Nota: No alterar el vector de nombres.*/

void listadoClienteVar(string nom_prod[], string nom_cliente[], int codCLiente, int list_var[], int seg[], float km[][cod_prod]){
    int pos = posc_mayor(list_var, codCLiente);
    cout << "variedad de " << nom_cliente[pos] << " posicion "
         << pos << "..." << endl;

    int n, temp{0};
    do{
        n = 0;
        for (int i{1}; i < cod_prod; i++){
            if (km[pos][i - 1] < km[pos][i]) {
                temp = km[pos][i - 1];
                km[pos][i - 1] = km[pos][i];
                km[pos][i] = temp;
                n++;
                temp = seg[i - 1];
                seg[i - 1] = seg[i];
                seg[i] = temp;
            }
        }
    } while (n != 0);
    for (int i{0}; i < cod_prod; i++) {
        cout << nom_prod[seg[i]] << '\t' << km[pos][i] << "km" << endl;
    }
}

/*3. Del listado anterior, tome el tipo de producto con mayor cantidad de kilómetros recorridos e
informe cuantas entregas se hicieron para ese tipo de producto (sin importar para que cliente). */

void mayorCantEntrega(string nom_prod[], string nom_cliente[],int cant_entregas[][cod_prod], float cant_km[][cod_prod],int codCLiente, int seguimiento[], int cont_cliente[]) {
    cout << "Entregas de " << nom_prod[seguimiento[0]]  << endl;

    for (int i{0}; i < codCLiente; i++){
        if (i == posc_mayor(cont_cliente, codCLiente)) {
            cout << i << ". " << nom_cliente[i] << '\t' << cant_entregas[i][0] << endl;
        }
        else {
            cout << i << ". " << nom_cliente[i] << '\t' << cant_entregas[i][seguimiento[0]]
                 << endl;
        }
    }
}

int main(){
    
    const int codCLiente{8};
    string nom_cliente[codCLiente];
    string nom_prod[cod_prod];
    float cant_peso[codCLiente][cod_prod]{0}; // peso total de cada uno de los viajes
    int cont_cliente[codCLiente]{0};  // cantidad de tipos de elementos que superan los 13000
    int seguimiento[cod_prod]{0, 1, 2, 3, 4};
    float cant_km[codCLiente][cod_prod]{0};
    int cant_entregas[codCLiente][cod_prod]{0};   // la cantidad de entregas de cada producto.

    ifstream nombre;
    nombre.open("Nombres.txt");
    if (!nombre) {
        cout << "Error al intentar abrir el archivo de nombre.";
        return 1;
    }
    for (int i{0}; i < codCLiente; i++) {
        nombre >> nom_cliente[i];
    }
    for (int i{0}; i < cod_prod; i++) {
        nombre >> nom_prod[i];
    }
    nombre.close();

    ifstream datos;
    datos.open("Datos.txt");
    if (!datos){
        cout << "Error al intentar abrir el archivo de Datos";
        return 2;
    }
    int tcliente, tprod{0};
    float tkg, tkm{0};
    while (datos >> tcliente >> tprod >> tkg >> tkm) {
        cant_entregas[tcliente][tprod] += 1;
        cant_peso[tcliente][tprod] += tkg;
        cant_km[tcliente][tprod] += tkm;
    }
    datos.close();

    listadoKg(nom_prod, nom_cliente, cant_peso, cont_cliente, codCLiente, cod_prod);
    listadoClienteVar(nom_prod, nom_cliente, codCLiente, cont_cliente, seguimiento, cant_km);
    mayorCantEntrega(nom_prod, nom_cliente, cant_entregas, cant_km, codCLiente, seguimiento, cont_cliente);
    return 0;
}
