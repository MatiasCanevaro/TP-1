#ifndef LISTASORD_HPP_INCLUDED
#define LISTASORD_HPP_INCLUDED

template <typename T> struct Nodo {
    T dato; // valor que contiene el nodo
    Nodo<T>* sig; // puntero al siguiente nodo
};


template <typename T> Nodo<T>* buscar(T clave, Nodo<T>* lista, int (*criterio)(T, T))
{
	while (lista != nullptr && criterio(clave, lista->dato) > 0)
		lista = lista->sig;

	return lista != nullptr && criterio(clave, lista->dato) == 0 ? lista : nullptr;
}

template <typename T> void insertar(T valor, Nodo<T>*& lista, int (*criterio)(T, T))
{
	Nodo<T>* nuevo = new Nodo<T>;
	nuevo->dato = valor;

	Nodo<T>** pp = &lista;
	while (*pp != nullptr && criterio(nuevo->dato, (*pp)->dato) >= 0)
		pp = &((*pp)->sig);
	nuevo->sig = *pp;
	*pp = nuevo;
}

template <typename T> void insertarSinOrden(T valor, Nodo<T>*& lista)
{
    Nodo<T>* nuevo = new Nodo<T>;
    nuevo->dato = valor;

    Nodo<T>** pp = &lista;
    while (*pp != nullptr)
        pp = &((*pp)->sig);
    nuevo->sig = *pp;
    *pp = nuevo;
}

template <typename T> Nodo<T>* extraer(T clave, Nodo<T>*& lista, int (*criterio)(T, T))
{
	Nodo<T> **pp = &lista;
	while (*pp != nullptr && criterio(clave, (*pp)->dato) > 0)
		pp = &((*pp)->sig);


    Nodo<T> *aux;
	if (*pp != nullptr && criterio(clave, (*pp)->dato) == 0) {
		aux = *pp;
		*pp = (*pp)->sig;
		return aux;
	} else {
		return nullptr;
	}
}

template <typename T> bool borrar(T clave, Nodo<T>*& lista, int (*criterio)(T, T))
{
	Nodo<T>* extraido = extraer(clave, lista, criterio);
	if (extraido) {
		delete extraido;
		return true;
	} else {
		return false;
	}
}

template <typename T> T pop(Nodo<T>* &pila)
{
	if (pila == nullptr) {
		std::cout << "Error: pop en pila vacia" << std::endl;
		exit(EXIT_FAILURE);
		//modo no recomendado de terminar, en particular si uso objetos
	}
	T valor = pila->dato;
	Nodo<T>* aux_elim = pila;
	pila = pila->sig;
	delete aux_elim;
	return valor;
}

template <typename T> void mostrar(Nodo<T>* lista)
{ //Presupone que de ser neceario se hizo la sobrecarga de << para dato
	while (lista != nullptr) {
		std::cout << lista->dato << std::endl;
		lista = lista->sig;
	}
}

#endif // LISTASORD_HPP_INCLUDED
