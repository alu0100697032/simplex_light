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
	//char nombrefichero[85] = "ej1.lpp";
	char nombrefichero[85];
	/*
	 * FASE ENTREGA
	 */
	bool parar = false;
	char opcion;
	cout << "Escriba el nombre del fichero a leer" << endl;
	cin >> nombrefichero;
	PROBLEM problema1(nombrefichero);
	cout << "¡Fichero cargado!" << endl << endl;
	cout << "Opciones:" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "-Pulse n para cargar un nuevo fichero             -" << endl;
	cout << "-Pulse t para representar las tablas del simplex  -" << endl;
	cout << "-Pulse r para resolver el problema                -" << endl;
	cout << "-Pulse s para mostrar la solución del problema    -" << endl;
	cout << "-Pulse h ver opciones                             -" << endl;
	cout << "-Pulse x para salir del programa                  -" << endl;
	cout << "---------------------------------------------------" << endl;
	while (parar == false) {
		cin >> opcion;
		switch (opcion) {
		case 'n':
		case 'N': {
			cout << "Escriba el nombre del fichero a leer:" << endl;
			cin >> nombrefichero;
			PROBLEM problema1(nombrefichero);
		}
			break;
		case 't':
		case 'T': {
			problema1.volcar_tabla();
		}
			break;
		case 'r':
		case 'R	': {
			problema1.Simplex_Light();
		}
			break;
		case 's':
		case 'S': {
			problema1.mostrar_solucion();
		}
			break;
		case 'h':
		case 'H': {
			cout << "Opciones:" << endl;
				cout << "---------------------------------------------------" << endl;
				cout << "-Pulse n para cargar un nuevo fichero             -" << endl;
				cout << "-Pulse t para representar las tablas del simplex  -" << endl;
				cout << "-Pulse r para resolver el problema                -" << endl;
				cout << "-Pulse s para mostrar la solución del problema    -" << endl;
				cout << "-Pulse h ver opciones                             -" << endl;
				cout << "-Pulse x para salir del programa                  -" << endl;
				cout << "---------------------------------------------------" << endl;
		}
			break;
		case 'x':
		case 'X': {
			cout << "¡Programa cerrado!" << endl;
			parar = true;
		}
			break;
		default: {
			cout
					<< "Seleccione una de las opciones. h para desplegar la lista de opciones:"
					<< endl;
		}
			break;
		}
	}
}

