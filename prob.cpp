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

	cout << "Z= " << clase << " ";
	for (unsigned int i = 0; i < n; i++) {
		if (c[i] >= 0)
			cout << "+" << c[i] << "x" << i + 1 << " ";
		else
			cout << c[i] << "x" << i + 1 << " ";
	}
	cout << endl << "Sujeto a: " << endl;
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
	/*
	 * Fila 0 encabezado una columna vacía, una columna por cada X (n) +
	 * una columna por cada h, condicion, (m) + una columna con b
	 * Luego m filas, una por h, en el cruce de la h de la fila con la h
	 * de la columna vale 1 el resto 0
	 * Luego una fila más con Z, cuando cruza con las h de la columna vale 0
	 */

	/*
	 * CABECERA DE LA TABLA
	 */
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
	/*
	 * CUERPO DE LA TABLA
	 */
	for (unsigned int i = 0; i <= m; i++) {
		for (unsigned int j = 0; j < n + m + 2; j++) {
			if (j == 0) { //Variables básicas
				if (ivb[i] >= n)
					cout << 'h' << ivb[i] << " | ";
				else
					cout << 'x' << ivb[i] << " | ";
			} else if (j == n + m + 1) { //términos independientes
				cout << b[i];
			} else {
				cout << A[i][j - 1] << "  "; //coeficientes tecnológicos
			}

		}
		cout << endl;
	}
	cout
			<< "------------------------------------------------------------------------"
			<< endl;
	cout << "-Z    ";
	for (unsigned int i = 0; i < n+m; i++){
		cout << c[i] << "  ";
	}
	cout << Vo << endl;
}
