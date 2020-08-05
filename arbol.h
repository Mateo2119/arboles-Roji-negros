#ifndef ARBOL_H
#define ARBOL_H
#include <iostream>
#include <cstdlib>
using namespace std;


struct Nodo{
	bool rojo;
	int info;
	Nodo* izq;
	Nodo* der;
	Nodo* padre;
	
	//Constructor
	Nodo(int dato){
		this->info = dato;
		this->rojo = true; //Siempre el nodo a insertar es rojo
		izq = NULL;
		der = NULL;
		padre = NULL;
	}
};


class Arbol{
	private: 
		Nodo *raiz;
	protected:		
		void ajustarRN(Nodo *&, Nodo *&);
		void supresionRN(Nodo *&, Nodo *&);	
		void giroIzq(Nodo *&, Nodo*&);
		void giroDer(Nodo *&, Nodo*&);			
	public: 
		Arbol(){
			raiz = NULL;	
		}
	void insertar(const int &n);
	void eliminar(const int &n);	
	void imprimir();
	void destructor(Nodo* raiz);
};
//---------Giros------------//
void Arbol::giroIzq(Nodo *&raiz, Nodo *&x){ 
    Nodo *x_der = x->der;   
    x->der = x_der->izq;
  
    if (x->der != NULL){
    	x->der->padre = x; 
	}
	x_der->padre = x->padre; 
  
    if (x->padre == NULL){
    	raiz = x_der;
	}       
  
    else if (x == x->padre->izq){
    	x->padre->izq = x_der; 
	}
    else{
    	x->padre->der = x_der;	
	}
    x_der->izq = x; 
    x->padre = x_der; 
}
void Arbol::giroDer(Nodo *&raiz, Nodo *&x){ 
    Nodo *x_izq = x->izq;   
    x->izq = x_izq->der;
  
    if (x->izq != NULL){
    	x->izq->padre = x; 
	}
	x_izq->padre = x->padre; 
  
    if (x->padre == NULL){
    	raiz = x_izq;
	}
	else if (x == x->padre->izq){
    	x->padre->izq = x_izq; 
	}
    else{
    	x->padre->der = x_izq;	
	}
    x_izq->izq = x; 
    x->padre = x_izq; 
} 
//-----------AJUSTAR INSERCION--------//
void Arbol::ajustarRN(Nodo *&raiz, Nodo *&x){
	//Nodos padre y abuelo de x
	Nodo *x_abuelo = NULL;
	Nodo *x_padre = NULL;
	//Mientras que x sea rojo, su padre sea rojo y x no sea la raiz
	while((x->rojo == true) && (x != raiz) && (x->padre->rojo == true)){
		x_abuelo = x->padre->padre;
		x_padre = x->padre;
		//----------------------------SIMETRIA A---------------------------//	
		//Si el padre de x es hijo izquierdo
		if(x_padre == x_abuelo->izq){
			Nodo *x_tio = x_abuelo->der;
			//Caso 1: el padre y el tio son rojos
			if(x_tio != NULL && x_tio->rojo == true){
				//Intercambiamos los colores del abuelo, del tio y del padre
				x_abuelo->rojo = true;
				x_tio->rojo = false;
				x_padre->rojo = false;
				x = x_abuelo;
				if(x_abuelo == raiz) {
					x_abuelo->rojo = false;
				}
			}
			else{
				//Caso 2: x es hijo del mismo lado de su tio
				if(x == x_padre->der){
					giroIzq(raiz, x_padre);
					x = x_padre;
					x_padre = x->padre;
					//Aqui ya es caso 3
				}
				//Caso 3: x es hijo del lado contrario de su tio
				giroDer(raiz, x_abuelo);
				swap(x_padre->rojo, x_abuelo->rojo);
				x = x_padre;				
			}
		}
		//----------------------------SIMETRIA B---------------------------//	
		//Si el padre de x es hijo derecho
		Nodo *x_tio = x_abuelo->izq;
			//Caso 1: el padre y el tio son rojos
			if(x_tio != NULL && x_tio->rojo == true){
				//Intercambiamos los colores del abuelo, del tio y del padre
				x_abuelo->rojo = true;
				x_tio->rojo = false;
				x_padre->rojo = false;
				x = x_abuelo;
				if(x_abuelo == raiz) {
					x_abuelo->rojo = false;
				}
			}
			else{
				//Caso 2: x es hijo del mismo lado de su tio
				if(x == x_padre->izq){
					giroDer(raiz, x_padre);
					x = x_padre;
					x_padre = x->padre;
					//Aqui ya es caso 3
				}
				//Caso 3: x es hijo del lado contrario de su tio
				giroIzq(raiz, x_abuelo);
				swap(x_padre->rojo, x_abuelo->rojo);
				x = x_padre;				
			}	
	}
	//Volvemos a la raiz negra
	
	raiz->rojo = false;
}
//-----------------AJUSTAR SUPRESION--------------//
void Arbol::supresionRN(Nodo *&raiz, Nodo *&x){
	//Nodos padre y abuelo de x
	Nodo *x_abuelo = NULL;
	Nodo *x_padre = NULL;
	Nodo *w = NULL;
	//Mientras que x no sea la raiz y x sea negro
	while((x != raiz) && (x->rojo == false)){
		x_abuelo = x->padre->padre;
		x_padre = x->padre;
		//---------------SIMETRIA A--------------------//
		if(x == x_padre->izq){
			w = x_padre->der;
			if(w->rojo == true){
				//CASO 1: x es hijo izquierdo y w es rojo
				w->rojo = false;
				x_padre->rojo = true;
				giroIzq(raiz, x_padre);
			}
			//Si los hijos de w son negros
			if((w->der->rojo == false) && (w->izq->rojo == false)){
				//CASO 2:
				w->rojo = true;
				x = x_padre;
			}
			else{
				//Si el hiho derecho de w es negro
				if(w->der->rojo == false){
					//Caso 3
					w->izq->rojo = false;
					w->rojo = true;
					giroDer(raiz,w);
					w = x_padre->der;
				}
				//Caso 4:
				x->rojo = x_padre->rojo; //Se igualan los colores
				x_padre->rojo = false;
				giroIzq(raiz, w);
				x = raiz;
			}
		}
		//-------------------SIMETRIA B-----------------------//
		if(x == x_padre->der){
			w = x_padre->izq;
			if(w->rojo == true){
				//CASO 1: x es hijo izquierdo y w es rojo
				w->rojo = false;
				x_padre->rojo = true;
				giroDer(raiz, x_padre);
			}
			//Si los hijos de w son negros
			if((w->izq->rojo == false) && (w->der->rojo == false)){
				//CASO 2:
				w->rojo = true;
				x = x_padre;
			}
			else{
				//Si el hiho izquierdo de w es negro
				if(w->izq->rojo == false){
					//Caso 3
					w->der->rojo = false;
					w->rojo = true;
					giroIzq(raiz,w);
					w = x_padre->izq;
				}
				//Caso 4:
				x->rojo = x_padre->rojo; //Se igualan los colores
				x_padre->rojo = false;
				giroDer(raiz, w);
				x = raiz;
			}
		}	
	}
	
}
//------------INSERCION BASICA (recursiva)------------//
Nodo* inser_bas(Nodo* raiz, Nodo *x){ 
    // Arbol vacio
    if (raiz == NULL) 
       return x; 
  
    if (x->info < raiz->info){ 
        raiz->izq  = inser_bas(raiz->izq, x); 
        raiz->izq->padre = raiz; 
    } 
    else if (x->info > raiz->info){ 
        raiz->der = inser_bas(raiz->der, x); 
        raiz->der->padre = raiz; 
    } 
  
    return raiz; 
}
//------------ELIMINACION BASICA------------//

Nodo* minValueNode(Nodo* nodo) 
{ 
    Nodo* current = nodo; 
  
    /* loop down to find the leftmost leaf */
    while (current && current->izq != NULL) 
        current = current->izq; 
  
    return current; 
} 

Nodo* eliminar_bas(Nodo* raiz, int clave){ 
    //ELIMINACION 
    if (raiz == NULL) return raiz; 
  
    
    if (clave < raiz->info) 
        raiz->izq = eliminar_bas(raiz->izq, clave); 
  
    else if (clave > raiz->info) 
        raiz->der = eliminar_bas(raiz->der, clave); 

    else
    { 
        if (raiz->izq == NULL) 
        { 
            Nodo* temp = raiz->der; 
            free(raiz); 
            return temp; 
        } 
        else if (raiz->der == NULL) 
        { 
            Nodo *temp = raiz->izq; 
            free(raiz); 
            return temp; 
        } 
  
        Nodo* temp = minValueNode(raiz->der); 
  
        raiz->info = temp->info; 
  
        raiz->der = eliminar_bas(raiz->der, temp->info); 
    } 
    return raiz; 
}  


void imprimirInordenColores(Nodo* raiz) 
{ 	
    if (raiz != NULL) 
    { 
        imprimirInordenColores(raiz->izq); 
        cout<<raiz->info;
        cout<<"(";
        if(raiz->rojo) {
        	cout<<"rojo";
		}else {
			cout<<"negro";
		}
        cout<<")";
        cout<<" "; 
        imprimirInordenColores(raiz->der); 
        
    } 
} 

//----------INSERTAR------------//
void Arbol::insertar(const int &n){
	//Se crea el nodo
	Nodo* x = new Nodo(n);
	raiz = inser_bas(raiz, x);
	//Insertar como arbol Roji-negro
	ajustarRN(raiz, x);
	cout<<"\n";
	cout<<"Arbol binario inorden despues de insercion";
	cout<<"\n";
	imprimirInordenColores(raiz);
}


//----------BORRAR------------//
void Arbol::eliminar(const int &n){
	raiz = eliminar_bas(raiz, n);
	Nodo* x = new Nodo(n);
	//Eliminar como arbol Roji-negro
	supresionRN(raiz, x);
	cout<<"\n";
	cout<<"Arbol binario inorden despues de borrado";
	cout<<"\n";
	imprimirInordenColores(raiz);
}
void Arbol::destructor(Nodo* raiz){
	int aux;
	if (raiz != NULL)
    {
        destructor(raiz->izq);
        cout<<"Eliminado " <<raiz->info;
        raiz->info = NULL;

        destructor(raiz->der);

   }else{
    cout<<"Eliminado la raiz " <<raiz->info;
  	raiz->info = NULL;
   }
    
	
	
}



#endif

