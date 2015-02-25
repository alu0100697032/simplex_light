/*
 * main.cpp
 *
 *  Created on: 12/2/2015
 *      Author: alu4406
 */

#include "prob.h"
int main() {

	/*
	 * FASE DESARROLLO
	 */
	char nombrefichero[85] = "ej1.lpp";
	/*
	 * FASE ENTREGA
	 */
	bool parar = false;
	char opcion;
	//cout << "Escriba el nombre del fichero a leer" << endl;
	//cin >> nombrefichero;
	PROBLEM problema1(nombrefichero);
	while (parar == false) {
		cin >> opcion;
		switch (opcion) {
		case 'p': {
			problema1.volcar_problema();
		}
			break;
		case 't': {
			problema1.volcar_tabla();
		}
			break;
		case 's': {
			problema1.mostrar_solucion();
		}
			break;
		case 'x': {
			parar = true;
		}
			break;
		default: {
			cout << "Opciones:" << endl;
			cout << "p para volvar el problema cargado desde fichero" << endl;
			cout << "t para representar las tablas del simplex" << endl;
			cout << "s para mostrar la solución del problema" << endl;
			cout << "x para salir del programa" << endl;
		}
			break;
		}
	}
}

