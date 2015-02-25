/*
 * main.cpp
 *
 *  Created on: 12/2/2015
 *      Author: alu4406
 */

#include "prob.h"
int main(){

	/*
	 * FASE DESARROLLO
	 */
	char nombrefichero[85] = "ej1.lpp";
	/*
	 * FASE ENTREGA
	 */
	//cout << "Escriba el nombre del fichero a leer" << endl;
	//cin >> nombrefichero;
	PROBLEM problema1(nombrefichero);
	problema1.volcar_tabla();

}



