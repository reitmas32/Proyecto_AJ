#include "Pieces.h"

/**
 *@brief Funcion encargada de comparar dos items
 *
 *@param this Primer item a comparar
 *
 *@param other Segundo item a comparar
 *
 *@return True si son iguales en caso cotrario false
 *
 */

static bool Compare(Item this, Item other){
	if(this.id == other.id){				/**!<Compara el id de los items*/		
		return true;						/**!<Si son iguales retorna true*/
	}else{
		return false;						/**!<Si son diferentes retorna false*/	
	}
}


/**
 *@brief Funcion encargada de mover una Piece de tipo Tower
 *
 *@param this DLL de los Items aliados
 *
 *@param other DLL de los Items enemigos
 *
 *@param piece Objeto a mover
 *
 *@param _x Coordenada a la que se va a mover el objeto en x
 *
 *@param _y Coordenada a la que se va a mover el objeto en y
 *
 *@return True si se puede mover el objeto en caso contrario False
 *
 */

static bool Tower_Move(DLL* this, DLL *other, Item *piece, int _x, int _y){
	assert(this);						/**!<Verifica que exista la primer DLL*/	
	assert(other);						/**!<Verifica que exista la segunda DLL*/	
}

/**
 *@brief Funcion encargada de mover una Piece de tipo Bishop
 *
 *@param this DLL de los Items aliados
 *
 *@param other DLL de los Items enemigos
 *
 *@param piece Objeto a mover
 *
 *@param _x Coordenada a la que se va a mover el objeto en x
 *
 *@param _y Coordenada a la que se va a mover el objeto en y
 *
 *@return True si se puede mover el objeto en caso contrario False
 *
 */

static bool Bishop_Move(DLL* this, DLL *other, Item *piece, int _x, int _y){
	assert(this);						/**!<Verifica que exista la primer DLL*/	
	assert(other);						/**!<Verifica que exista la segunda DLL*/	
}

/**
 *@brief Funcion encargada de mover una Piece de tipo Pawn
 *
 *@param this DLL de los Items aliados
 *
 *@param other DLL de los Items enemigos
 *
 *@param piece Objeto a mover
 *
 *@param _x Coordenada a la que se va a mover el objeto en x
 *
 *@param _y Coordenada a la que se va a mover el objeto en y
 *
 *@return True si se puede mover el objeto en caso contrario False
 *
 */

static bool Pawn_Move(DLL* this, DLL *other, Item *piece, int _x, int _y){
	assert(this);						/**!<Verifica que exista la primer DLL*/	
	assert(other);						/**!<Verifica que exista la segunda DLL*/	
}

/**
 *@brief Funcion encargada de mover una Piece de tipo King
 *
 *@param this DLL de los Items aliados
 *
 *@param other DLL de los Items enemigos
 *
 *@param piece Objeto a mover
 *
 *@param _x Coordenada a la que se va a mover el objeto en x
 *
 *@param _y Coordenada a la que se va a mover el objeto en y
 *
 *@return True si se puede mover el objeto en caso contrario False
 *
 */

static bool King_Move(DLL* this, DLL *other, Item *piece, int _x, int _y){
	assert(this);						/**!<Verifica que exista la primer DLL*/	
	assert(other);						/**!<Verifica que exista la segunda DLL*/	
}

/**
 *@brief Funcion encargada de mover una Piece de tipo Queen
 *
 *@param this DLL de los Items aliados
 *
 *@param other DLL de los Items enemigos
 *
 *@param piece Objeto a mover
 *
 *@param _x Coordenada a la que se va a mover el objeto en x
 *
 *@param _y Coordenada a la que se va a mover el objeto en y
 *
 *@return True si se puede mover el objeto en caso contrario False
 *
 */

static bool Queen_Move(DLL* this, DLL *other, Item *piece, int _x, int _y){
	assert(this);						/**!<Verifica que exista la primer DLL*/	
	assert(other);						/**!<Verifica que exista la segunda DLL*/	
}

/**
 *@brief Funcion encargada de mover una Piece de tipo Horse
 *
 *@param this DLL de los Items aliados
 *
 *@param other DLL de los Items enemigos
 *
 *@param piece Objeto a mover
 *
 *@param _x Coordenada a la que se va a mover el objeto en x
 *
 *@param _y Coordenada a la que se va a mover el objeto en y
 *
 *@return True si se puede mover el objeto en caso contrario False
 *
 */

static bool Horse_Move(DLL* this, DLL *other, Item *piece, int _x, int _y){
	assert(this);						/**!<Verifica que exista la primer DLL*/	
	assert(other);						/**!<Verifica que exista la segunda DLL*/	
}

DLL *Initialize(int type){

	DLL *this = DLL_New();							/**!<Crea la DLL generica*/

	if(type == 0){
		/**!<Creación de las piezas blancas*/

		DLL_InsertBack(this,(Item){1,3,1,2});		/**!<Crea al Peon 1*/
		DLL_InsertBack(this,(Item){2,3,2,2});		/**!<Crea al Peon 2*/
		DLL_InsertBack(this,(Item){3,3,3,2});		/**!<Crea al Peon 3*/
		DLL_InsertBack(this,(Item){4,3,4,2});		/**!<Creaal Peon 4*/
		DLL_InsertBack(this,(Item){5,3,5,2});		/**!<Crea al Peon 5*/
		DLL_InsertBack(this,(Item){6,3,6,2});		/**!<Crea al Peon 6*/
		DLL_InsertBack(this,(Item){7,3,7,2});		/**!<Crea al Peon 7*/
		DLL_InsertBack(this,(Item){8,3,8,2});		/**!<Crea al Peon 8*/
		DLL_InsertBack(this,(Item){9,1,1,1});		/**!<Crea a la Torre 1*/
		DLL_InsertBack(this,(Item){10,6,2,1});		/**!<Crea al Caballo 1*/
		DLL_InsertBack(this,(Item){11,2,3,1});		/**!<Crea al Alfin 1*/
		DLL_InsertBack(this,(Item){12,4,4,1});		/**!<Crea al Rey*/
		DLL_InsertBack(this,(Item){13,5,5,1});		/**!<Crea a la Reina*/
		DLL_InsertBack(this,(Item){14,2,6,1});		/**!<Crea al Alfin 2*/
		DLL_InsertBack(this,(Item){15,6,7,1});		/**!<Crea al Caballo 2*/
		DLL_InsertBack(this,(Item){16,1,8,1});		/**!<Crea a la Torre 2*/

	}else{

		/**!<Creación de la piezas negras*/

		DLL_InsertBack(this,(Item){17,3,1,7});		/**!<Creando el Peon 1*/
		DLL_InsertBack(this,(Item){18,3,2,7});		/**!<Creando el Peon 2*/
		DLL_InsertBack(this,(Item){19,3,3,7});		/**!<Creando el Peon 3*/
		DLL_InsertBack(this,(Item){20,3,4,7});		/**!<Creando el Peon 4*/
		DLL_InsertBack(this,(Item){21,3,5,7});		/**!<Creando el Peon 5*/
		DLL_InsertBack(this,(Item){22,3,5,7});		/**!<Creando el Peon 6*/
		DLL_InsertBack(this,(Item){23,3,7,7});		/**!<Creando el Peon 7*/
		DLL_InsertBack(this,(Item){24,3,8,7});		/**!<Creando el Peon 8*/
		DLL_InsertBack(this,(Item){25,1,1,8});		/**!<Creando la Torre 1*/
		DLL_InsertBack(this,(Item){26,6,2,8});		/**!<Creando al Caballo 1*/
		DLL_InsertBack(this,(Item){27,2,3,8});		/**!<Creando Alfil 1*/
		DLL_InsertBack(this,(Item){28,4,4,8});		/**!<Creando al Rey*/
		DLL_InsertBack(this,(Item){29,5,5,8});		/**!<Creando a la Reina*/
		DLL_InsertBack(this,(Item){30,2,6,8});		/**!<Creando al Alfin 2*/
		DLL_InsertBack(this,(Item){31,6,7,8});		/**!<Creando al Caballo 2*/
		DLL_InsertBack(this,(Item){32,1,8,8});		/**!<Creando a la Toree 2*/

	}

	return this;									/**!<Retorna la DLL rellenada con las piezas correspondientes*/

}
void Erease(DLL *this, DLL *other){
	assert(this);					/**!<Verifica que exista la primer DLL*/
	assert(other);					/**!<Verifica que exista la segunda DLL*/

	DLL_Delete(this);				/**!<Elimina la primer DLL*/
	DLL_Delete(other);				/**!<elimina la segunda DLL*/

}
	


bool Piece_Move(DLL *white, DLL *black, int _x, int _y, int _id){
	assert(white);												/**!<Verifica que exista la DLL de piezas blancas*/
	assert(black);												/**!<Verifica que exista la DLL de piezas negras*/

	bool done = false;											/**!<Bandera que indica si se puede hacer el movimiento o no*/
	Item tmp = {_id,0,0,0};										/**!<Item generico para comparar los ids en las DLLs*/

	if(_id >=1 && _id <=16){									/**!<Ve si la pieza es blanca*/

		DLL_Search(white,tmp,Compare);							/**!<Busca la pieza en la DLL de su equipo*/
		DLL_Peek(white,&tmp);									/**!<Actualiza el item generico y lo convierte en la pieza a mover*/

		switch(tmp.type){										/**!<Ve de que tipo de pieza se trata*/
			case 1:
				done = Tower_Move(white,black,&tmp,_x,_y); 		/**!<Movimiento de la Torre*/
				break;
			case 2:
				done = Bishop_Move(white,black,&tmp,_x,_y); 	/**!<Movimiento del Alfil*/
				break;
			case 3:
				done = Pawn_Move(white,black,&tmp,_x,_y); 		/**!<Movimiento del Peon*/
				break;
			case 4:
				done = King_Move(white,black,&tmp,_x,_y); 		/**!<Movimiento del Rey*/
				break;
			case 5:
				done = Queen_Move(white,black,&tmp,_x,_y);		/**!<Movimiento de la Reina*/
				break;
			case 6:
				done = Horse_Move(white,black,&tmp,_x,_y); 		/**!<Movimiento del Caballo*/
				break;
		}

		if (done == true){										/**!<Si es valido el movimiento*/
			white -> cursor -> data.x = _x;						/**!<Actualizamos las coordenadas de la pieza en x*/
			white -> cursor -> data.y = _y;						/**!<Actualizamos las coordenadas de la pieza en y*/
		}

	}else if(_id >16 && _id <=32){								/**!<Ve si la pieza es negra*/

			DLL_Search(black,tmp,Compare);						/**!<Busca la pieza en la DLL de su equipo*/
			DLL_Peek(black,&tmp);								/**!<Actualiza el item generico y lo convierte en la pieza a mover*/

			switch(tmp.type){
				case 1:
					done = Tower_Move(black,white,&tmp,_x,_y); 		/**!<Movimiento de la Torre*/
					break;
				case 2:
					done = Bishop_Move(black,white,&tmp,_x,_y); 	/**!<Movimiento del Alfil*/
					break;
				case 3:
					done = Pawn_Move(black,white,&tmp,_x,_y); 		/**!<Movimiento del Peon*/
					break;
				case 4:
					done = King_Move(black,white,&tmp,_x,_y); 		/**!<Movimiento del Rey*/
					break;
				case 5:
					done = Queen_Move(black,white,&tmp,_x,_y);		/**!<Movimiento de la Reina*/
					break;
				case 6:
					done = Horse_Move(black,white,&tmp,_x,_y); 		/**!<Movimiento del Caballo*/
					break;

		}

		if (done == true){											/**!<Si es valido el movimiento*/
			black -> cursor -> data.x = _x;							/**!<Actualizamos las coordenadas de la pieza en x*/
			black -> cursor -> data.y = _y;							/**!<Actualizamos las coordenadas de la pieza en y*/
		}
	}

}