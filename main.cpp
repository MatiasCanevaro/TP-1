#include <iostream>
#include <fstream>
#include "rwstring.hpp"
#include "listasord.hpp"

using namespace std;

struct Orden {
	int id;
	string cliente;
	string producto;
	float valor;
};
const int lcli = 12;
const int lprod = 10;

struct Despacho {
    string cliente;
	int bultos;
	float valor;
};

fstream& operator >> (fstream &fs, Orden& ord)
{
	fs.read((char *) &ord.id, sizeof(ord.id));
    ord.cliente = readstring(fs, lcli);
	ord.producto = readstring(fs, lprod);
	fs.read((char *) &ord.valor, sizeof(ord.valor));
	return fs;
}

ostream& operator << (ostream &os, const Orden& r)
{
	os << "id: " << r.id << " - " << "cliente: " << r.cliente << " - " 
    << "producto: " << r.producto << " - " << "valor: " << r.valor;
	return os;
}

ostream& operator << (ostream &os, const Despacho& r)
{
	os << "cliente: " << r.cliente << " - " << "bultos: " 
    << r.bultos << " - " << "valor: " << r.valor;
	return os;
}

//por cliente y en caso de empate por producto, ambos ascendentes
int criterio(Orden a, Orden b)
{
	if (a.cliente == b.cliente)
		return a.producto.compare(b.producto);
	else
		return a.cliente > b.cliente ? 1 : -1;
}

int criterioDesp(Orden a, Orden b) {
    return a.cliente == b.cliente && a.producto == b.producto ? 0 : 1;
}

int main()
{
	Orden temp;
    Nodo<Orden>* lista = nullptr;
    Nodo<Despacho>* listaDesp = nullptr;
    fstream archivo;
     
   while(true){
        cout << "INGRESE UNA OPCION\n\n1: Leer Datos\n2: Mostrar\n3: Despachar\n4: Salir" << endl;
        int opcion;
        cin >> opcion;
        if(opcion == 1){
            while (lista != nullptr)
                pop(lista);
            while (listaDesp != nullptr)
                pop(listaDesp);
            archivo.open("Datos.bin", ios::binary | ios::in);
            if (!archivo){
            cout << "No se pudo abrir el archivo" << endl;
            return 1;
            }
            while (archivo >> temp){
                cout << temp << endl;
                insertar(temp, lista, criterio);
            }
            archivo.close();
            cout << endl;
        }
        else if(opcion == 2){
            cout << "Pedidos:" << endl;
            mostrar(lista);
            cout << endl;
            cout << "Despachos:" << endl;
            mostrar(listaDesp);
            cout << endl;
        }
        else if(opcion == 3){
            cout << "Despachar" << endl;
            
            Orden aDespachar;
            cout << "Ingrese el Cliente al que quiere despachar:" << endl;
            cin >> aDespachar.cliente;
            cout << "Ingrese el Producto a despachar:" << endl;
            cin >> aDespachar.producto;

            Despacho despacho;
            despacho.cliente = aDespachar.cliente;
            despacho.valor = 0;
            despacho.bultos = 0;
            Nodo<Orden>* ordenDespachada;
            
            while (true){
                ordenDespachada = extraer(aDespachar, lista, criterioDesp);
                if (ordenDespachada != nullptr){
                    cout << "id: " << ordenDespachada->dato.id << " - " 
                    << "cliente: " << ordenDespachada->dato.cliente << " - "
                    << "producto: " << ordenDespachada->dato.producto << " - " 
                    << "valor: " << ordenDespachada->dato.valor << endl;
                    despacho.valor += ordenDespachada->dato.valor;
                    despacho.bultos++;
                }
                else break;
            }
            if (despacho.valor > 0)
                insertarSinOrden(despacho, listaDesp);
            else
                cout << "No hay pedidos pendientes del cliente " << aDespachar.cliente
                << " de producto " << aDespachar.producto << endl;
        }
        else if(opcion == 4){
            //Libero memoria
            Nodo<Orden>* lista = nullptr;
            Nodo<Despacho>* listaDesp = nullptr;
            Nodo<Orden>* ordenDespachada = nullptr;
            while (lista != nullptr)
                pop(lista);
            while (listaDesp != nullptr)
                pop(listaDesp);
            break;
        }
        else
            cout << "La opcion ingresada no es valida" << endl;
            
        cout << endl;
    }
    return 0;
}