/*
 * prob.cpp
 *
 *  Created on: 12/2/2015
 *      Author: alu4406
 */

#include "prob.h"

PROBLEM::PROBLEM(char nombrefichero[85]) {
	unsigned i, j;
	double dummy;
	Vo = 0.0;
	ifstream textfile;
	textfile.open(nombrefichero);
	if (textfile.is_open()) {
		textfile >> (char *) clase >> (unsigned &) n >> (unsigned &) m;
		A.resize(m); // m filas
//leemos la fila de los n costes
		for (i = 0; i < n; i++) {
			textfile >> (double &) dummy;
			c.push_back(dummy);
		}
// si el problema es de máximo cambiamos de signo los costes
		if (strncmp(clase, "max", 3) == 0)
			for (i = 0; i < n; i++)
				c[i] *= -1.0;
// extendemos el vector c a tamaño n + nh
		nh = m;
		for (i = 0; i < nh; i++)
			c.push_back(0.0);
// leemos las m restricciones y asignamos A, b, ivb
		for (i = 0; i < m; i++) {
			for (j = 0; j < n; j++) {
				textfile >> (double &) dummy;
				A[i].push_back(dummy);
			}
			textfile >> (double &) dummy;
			b.push_back(dummy);
			if (dummy < CERONEG) {
				cout << "Lado derecho negativo, Modifique problema" << endl;
				exit(0);
			}
			A[i].resize(n + nh); // extendemos la fila a tamaño n +nh
			A[i][n + i] = 1.0; // ponemos un 1 en la columna n+i fila i correspondiente a la v. de holgura de la fila i
			ivb.push_back(n + i); // la v. básica asociada a la fila i es n + i
		}
		textfile.close();
		volcar_problema();
	} else {
		cout << "Error en la lectura del fichero" << endl;
	}
}

PROBLEM::~PROBLEM() {
	A.clear();
	b.clear();
	c.clear();
	ivb.clear();
}

void PROBLEM::volcar_problema() {

	//Clase de problema min o max
	cout << "Z= " << clase << " ";
	//Costes unitarios
	for (unsigned int i = 0; i < n; i++) {
		if (c[i] >= 0)
			cout << "+" << c[i] << "x" << i + 1 << " ";
		else
			cout << c[i] << "x" << i + 1 << " ";
	}
	cout << endl << "Sujeto a: " << endl;
	//Coeficientes tecnológicos y términos independientes
	for (unsigned int i = 0; i < m; i++) {
		cout << "     ";
		for (unsigned int j = 0; j <= n; j++) {
			if (j == n)
				cout << " <= " << b[i];
			else {
				if (A[i][j] >= 0)
					cout << "+" << A[i][j] << "x" << j + 1 << " ";
				else
					cout << A[i][j] << "x" << j + 1 << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void PROBLEM::volcar_tabla() {
	//Corregir: solo un bucle
	//ABECERA DE LA TABLA
	cout << "V.B    ";
	for (unsigned int i = 1; i <= n; i++) {
		cout << 'x' << i << "    ";
	}
	for (unsigned int i = 1; i <= m; i++) {
		cout << 'h' << i << "    ";
	}
	cout << 'b' << endl;
	cout
			<< "------------------------------------------------------------------------"
			<< endl;
	//CUERPO DE LA TABLA
	for (unsigned int i = 0; i < m; i++) {
		for (unsigned int j = 0; j <= n + m + 1; j++) {
			if (j == 0) { //Variables básicas
				if (ivb[i] >= n)
					cout << 'h' << ivb[i] - 2 << " |   ";
				else
					cout << 'x' << ivb[i] + 1 << " |   ";
			} else if (j == n + m + 1) { //términos independientes
				cout << b[i];
			} else { //coeficientes tecnológicos
				if (A[i][j - 1] >= 0)
					cout << A[i][j - 1] << "     ";
				else
					cout << A[i][j - 1] << "    ";
			}

		}
		cout << endl;
	}
	cout
			<< "------------------------------------------------------------------------"
			<< endl;
	cout << "-Z    ";
	//Costes unitarios
	for (unsigned int i = 0; i < n + m; i++) {
		cout << c[i] << "     ";
	}
	cout << Vo << endl; //Valor de la funcion objetivo
	// corregir: si es max ->> -Vo
}

void PROBLEM::mostrar_solucion() {
	cout << "**************************************************************"
			<< endl;
	cout << "                           SOLUCIÓN                           "
			<< endl;
	for (unsigned int i = 0; i <= m; i++) {
		if (i < m) { //Muestra las variables básicas
			if (ivb[i] >= n)
				cout << 'h' << ivb[i] << " = ";
			else
				cout << 'x' << ivb[i] << " = ";
			cout << b[i] << ' ';
		} else { //Muestra el valor de la función objetivo
			cout << "Z = " << Vo;
		}
	}
	cout << endl;
	cout << "**************************************************************"
			<< endl;
}

unsigned PROBLEM::entrante() {
	unsigned a = UERROR;
	double min = CERONEG;
	for (unsigned i = 0; i < n + nh - 1; i++) {
		if (c[i] < min) {
			a = i;
			min = c[i];
		}
	}
	return (a);
}

unsigned PROBLEM::saliente(unsigned s) {

	unsigned min = UERROR;
	for (int i = 0; i < m; i++){
		if(A[i][s] <= 0){
			min = UERROR; //duda
		}else if(b[i]/A[i][s] < min){
			min = b[i]/A[i][s];
		}
	}
	//return duda
}

/*void PROBLEM::actualizar_valores(unsigned s, unsigned r) {
 ivb[r] = s; // actualización de la base
 double temp = A[r][s];
 A[r] /= temp; //duda
 x[r] /= temp; //duda
 for (int i = 1; i < m; i++) {
 if (i != r && A[i][s] != 0) {
 temp = A[i][s];
 A[i] -= A[r] * temp; // la fila entera de i
 b[i] -= b[r] * temp;
 }
 Vo -= b[r] * c[s]; //actualizamos Vo
 c[i] -= c[s] * A[r][i];
 para todo //duda
 i<> s;
 cr[s] = 0.0;
 }

 }*/

/*void PROBLEM::Simplex_Light() {
	unsigned s, r;
	while ((s = entrante()) != UERROR) {
		volcar_tabla();
		r = saliente(s);
		if (r != UERROR)
			actualizar_valores(s, r);
		else
			cout << "¡PROBLEMA NO ACOTADO!" << endl;
	}
	volcar_tabla();
	mostrar_solucion();
}*/
