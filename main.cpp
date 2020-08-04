#include <iostream>
#include "arbol.h"
using namespace std;

int main(){
	Arbol arbolRN;
	
	arbolRN.insertar(10);
	arbolRN.insertar(15);
	arbolRN.insertar(21);
	arbolRN.insertar(3);
	arbolRN.eliminar(21);
	return 0;
}
