#include <iostream>

using namespace std;

void mostrarvec(int vec[], int dim){
	for (int i=0; i<dim; ++i)
		cout << vec[i] << '\t';
    cout << endl;
}

void mostrarmat(int m[][5], int dfil){
    const int dcol = 5;

    for (int i=0; i<dfil; ++i) {
            for (int j=0; j<dcol; ++j)
                    cout << m[i][j] << '\t';
            cout << endl;
    }
}

void revertir_vector(int vec[], int dim){
    int i{}, j{}, k{};
    j = dim-1;
    for(i=0; i<j; i++, j--){
        k = vec[i];
        vec[i] = vec[j];
        vec[j] = k;
    }
}

void trasp_matriz(int m[][5], int dfil){
    int copia_matriz[dfil][dfil]{};
    for(int i=0; i<dfil; ++i){
        for(int j=0; j<dfil; ++j){
            copia_matriz[i][j] = m[i][j];
        }
    }
    for(int i=0; i<dfil; ++i) {
        for(int j=0; j<dfil; ++j) {
            m[i][j] = copia_matriz[j][i];
        }
    }
}

int main(){
    
    const int dim5 {5};
    const int dim10 {10};

    int vec5[dim5] {4, 11, 19, 8, 3};
    int vec10[dim10] {23, 15, 1, 7, 6, 27, 2, 14, 12, 9};

    int matriz[dim5][dim5] {36, 7, 19, 28, 45,
                            17, 33, 42, 3, 25,
                            22, 41, 32, 11, 9,
                            39, 47, 14, 4, 23,
                            16, 38, 8, 27, 44};
    
    cout << "vector de 5 elementos" << endl;
    mostrarvec(vec5,dim5);
    cout << "reverso" << endl;
    revertir_vector(vec5,dim5);
    mostrarvec(vec5,dim5);
    cout << "-----------------------------------------------" << endl;
    
    cout << "vector de 10 elementos" << endl;
    mostrarvec(vec10,dim10);
    cout << "reverso" << endl;
    revertir_vector(vec10,dim10);
    mostrarvec(vec10,dim10);
    cout << "-----------------------------------------------" << endl;
    
    cout << "Matriz" << endl;
    mostrarmat(matriz,dim5);
    cout << "Traspuesta" << endl;    
    trasp_matriz(matriz,dim5);
    mostrarmat(matriz,dim5);
    
    return 0;
}