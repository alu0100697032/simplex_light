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
		cout << "Fichero cargado" << endl;
	}else {
		cout << "Error en la lectura del fichero" << endl;
	}
}

PROBLEM::~PROBLEM(){
	A.clear();
	b.clear();
	c.clear();
	ivb.clear();
}