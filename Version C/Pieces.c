/*Biblioteca de los prototipos del TDU Piece*/
#include "Pieces.h"

/*Funcion que Compara Ids*/
static bool CompareId(Item this, Item other){
	/*Compara el id de los items*/
	if(this.id == other.id){		
		/*Si son iguales retorna true*/				
		return true;						
	}else{
		/*Si son diferentes retorna false*/
		return false;							
	}
}

/*Funcion que compara coordenadas*/
static bool CompareCoordinates( Item this, Item other ){
    if( this.x == other.x && this.y == other.y ){
        return true;
    }else{
        return false;
    }
}


static bool Tower_Move(DLL* this, DLL *other, Item *piece, int _x, int _y){
	/*Verifica que exista la primer DLL*/
	assert(this);			

	/*Verifica que exista la segunda DLL*/				
	assert(other);						

	/**!< bandera que sirve para validar el movimiento*/
	bool done = false;

	/*Item temporal para comparar las coordenadas a donde llegara la pieza*/
    Item tmp = { .x = _x, .y = _y };    

    /*Si se movio en una direccion*/
	if( _x == piece -> x || _y == piece -> y ){				

		/*Comprueba que no haya nadie de mi equipo*/
		if( !DLL_FindIf( this, tmp, CompareCoordinates) ){      

			/*Valido el movimiento*/
			done = true;			

			/*Comprueba que si haya alguien del otro equipo*/							

			if( DLL_Search( other, tmp, CompareCoordinates ) ){  

				/*Borro la piza del otro equipo*/  

				DLL_Remove( other, &tmp );							
			
			}
		}

	}

	return done;
}

static bool Bishop_Move(DLL* this, DLL *other, Item *piece, int _x, int _y){
	/*Verifica que exista la primer DLL*/	
	assert(this);						

	/*Verifica que exista la segunda DLL*/
	assert(other);						

	/**!< bandera que sirve para validar el movimiento*/
	bool done = false;

	/*Item temporal para comparar las coordenadas a donde llegara la pieza*/
	Item tmp = { .x = _x, .y = _y };    

	if( _x - piece -> x == piece -> y - _y ||

		/*Comprueba que la diferencia entre las coordenadas en 'x' y 'y' sea igual*/
		piece -> x - _x == piece -> y - _y){	

		 /*Compruebo que no haya nadie de mi equipo*/
		if( !DLL_FindIf( this, tmp, CompareCoordinates) ){     

			/*Valido el movimiento*/
			done = true;										

			/*Comprueba que si haya alguien del otro equipo*/
			if( DLL_Search( other, tmp, CompareCoordinates ) ){    

				/*Borro la piza del otro equipo*/
				DLL_Remove( other, &tmp );							
			
			}
		}		
	}

	return done;	
}

static bool Pawn_Move(DLL* this, DLL *other, Item *piece, int _x, int _y){

	/*Verifica que exista la primer DLL*/
	assert(this);		

	/*Verifica que exista la segunda DLL*/	
	assert(other);						

	/**!< bandera que sirve para validar el movimiento*/
	bool done = false;                  
 
 	/*Item temporal para comparar las coordenadas a donde llegara la pieza*/
    Item tmp = { .x = _x, .y = _y };    

    /*Si solo se mueve hacia enfrente o haci atras*/
    if( _x == piece -> x ){              
 
 		/*Si solo se movio uno hacia adelante o hacia atras*/
        if( _y == piece -> y + 1 || _y == piece -> y - 1 ){       
 
 			/*Comprueba que no haya nadie de mi equipo*/
            if( !DLL_FindIf( this, tmp, CompareCoordinates) ){      
 
 				/*Comprueba que no haya nadie del otro equipo*/
                if( !DLL_FindIf( other, tmp, CompareCoordinates ) ){    
 
 					/*Valido el movimiento*/
                    done = true;                                        
                }
            }
        }

        /*Si se mueve dos hacia atras o hacia enfrente*/
        else if( (_y == piece -> y + 2 && piece -> y == 2 ) || 
                 (_y == piece -> y - 2 && piece -> y == 7 ) ){    
 
 			/*Comprueba que no haya nadie de mi equipo*/
            if( !DLL_FindIf( this, tmp, CompareCoordinates) ){      
 

 				/*Comprueba que no haya nadie del otro equipo*/
                if( !DLL_FindIf( other, tmp, CompareCoordinates ) ){    
 
 					/*Valido el movimiento*/
                    done = true;                                        
                }
            }
        }
    }

    /*Si se movio hacia un lado*/
    else if( _x == piece -> x + 1 || _x == piece -> x - 1 ){      
 
        if( _y == piece -> y + 1 || _y == piece -> y - 1 ){
 
 			/*Compruebo que no haya nadie de mi equipo*/
            if( !DLL_FindIf( this, tmp, CompareCoordinates) ){      
 
 				/*Compruebo que haya alguien del otro equipo*/
                if( DLL_Search( other, tmp, CompareCoordinates ) ){ 

                	/*Borro la piza del otro equipo*/
					DLL_Remove( other, &tmp );		

					/*Valido el movimiento*/				
                    done = true;                                        
                }
            }
        }
    } 
	if( piece -> y == 8 || piece -> y == 1 ){
		piece -> type = 5;
		piece -> letter = 'Q';
	}
	return done;
}


static bool King_Move(DLL* this, DLL *other, Item *piece, int _x, int _y){

	/*Verifica que exista la primer DLL*/
	assert(this);			

	/*Verifica que exista la segunda DLL*/				
	assert(other);						

	/**!<Bandera que sive para validar el movimiento*/
	bool done = false;                  
 
 	/*Item temporal para comparar las coordenadas a donde llegara la pieza*/
    Item tmp = { .x = _x, .y = _y };    
 

 	/*Si no se mueve al los lados*/
    if( _x == piece -> x ){              
 
 		/*Si solo se movio uno hacia adelante o hacia atras*/
        if( _y == piece -> y + 1 || _y == piece -> y - 1 ){       
 
 			/*Compruebo que no haya nadie de mi equipo*/
            if( !DLL_FindIf( this, tmp, CompareCoordinates) ){      

            	/*Valido el movimiento*/
				done = true;										
 
 				/*Compruebo que si haya alguien del otro equipo*/
                if( DLL_Search( other, tmp, CompareCoordinates ) ){    
 
 					/*Borro la piza del otro equipo*/
					DLL_Remove( other, &tmp );							
              
                }
            }
        }
	}

	/*Si no se mueve al los lados */
	else if( _y == piece -> y ){		

		/*Si solo se movio uno hacia atras o hacia adelante*/
		if( _x == piece -> x + 1 || _x == piece -> x - 1 ){		

			/*Compruebo que no haya nadie de mi equipo*/
            if( !DLL_FindIf( this, tmp, CompareCoordinates) ){      

            	/*Valido el movimiento*/
				done = true;										
 
 				/*Compruebo que si haya alguien del otro equipo*/
                if( DLL_Search( other, tmp, CompareCoordinates ) ){    
 
 					/*Borro la piza del otro equipo*/
					DLL_Remove( other, &tmp );							
                }
            }
		}

	}
	/*Si se movi uno hacia los lados*/
	else if( _x == piece -> x + 1 || _x == piece -> x - 1 ){		

		/*Si solo se movio uno hacia adelante o hacia atras*/
        if( _y == piece -> y + 1 || _y == piece -> y - 1 ){       
 
 			/*Compruebo que no haya nadie de mi equipo*/
            if( !DLL_FindIf( this, tmp, CompareCoordinates) ){      

            	/*Valido el movimiento*/
				done = true;										
 
 				/*Compruebo que si haya alguien del otro equipo*/
                if( DLL_Search( other, tmp, CompareCoordinates ) ){    
 
 					/*Borro la piza del otro equipo*/
					DLL_Remove( other, &tmp );							
              
                }
            }
        }
	}
        
	return done;	
}

static bool Queen_Move(DLL* this, DLL *other, Item *piece, int _x, int _y){
	/*Verifica que exista la primer DLL*/
	assert(this);		

	/*Verifica que exista la segunda DLL*/		
	assert(other);							

	bool done = false;

	/*Utilizo las otras dos funciones ya que la reyna semueve como culaquiera de las dos */
	if( Tower_Move( this, other, piece, _x, _y ) ^ Bishop_Move( this, other, piece, _x, _y ) ){		
		/*En la linea anterior se utilizo la compuerta logica XOR '^' */
		done = true;
	}

	return done;
}

static bool Horse_Move(DLL* this, DLL *other, Item *piece, int _x, int _y){

	/*Verifica que exista la primer DLL*/
	assert(this);			

	/*Verifica que exista la segunda DLL*/					
	assert(other);						

	bool done = false;

	/*Item temporal para comparar las coordenadas a donde llegara la pieza*/
	Item tmp = { .x = _x, .y = _y };    

	/*Compruebo todas las combinaciones de las piezas*/

	if( ( _x == piece -> x + 1 && _y == piece -> y + 2 ) ||
		( _x == piece -> x + 1 && _y == piece -> y - 2 ) ||
		( _x == piece -> x - 1 && _y == piece -> y + 2 ) ||
		( _x == piece -> x - 1 && _y == piece -> y - 2 ) ||
		( _x == piece -> x + 2 && _y == piece -> y + 1 ) ||
		( _x == piece -> x + 2 && _y == piece -> y - 1 ) ||
		( _x == piece -> x - 2 && _y == piece -> y + 1 ) ||
		( _x == piece -> x - 2 && _y == piece -> y - 1 ) 		
		){

			done = true;

			/*Compruebo que no haya nadie de mi equipo*/
            if( !DLL_FindIf( this, tmp, CompareCoordinates) ){      

            	/*Valido el movimiento*/
				done = true;										
 
 				/*Compruebo que si haya alguien del otro equipo*/
                if( DLL_Search( other, tmp, CompareCoordinates ) ){    
 
 					/*Borro la piza del otro equipo*/
					DLL_Remove( other, &tmp );							
              
                }
            }
		}

	return done;
}


DLL *Initialize(int type){

	/*Crea la DLL generica*/
	DLL *this = DLL_New();							

	if(type == 0){

		/*Creación de las piezas blancas*/

		/*Crea al Peon 1*/
		DLL_InsertBack(this,(Item){1,3,1,2});	

		/*Crea al Peon 2*/	
		DLL_InsertBack(this,(Item){2,3,2,2});	

		/*Crea al Peon 3*/	
		DLL_InsertBack(this,(Item){3,3,3,2});

		/*Crea al Peon 4*/		
		DLL_InsertBack(this,(Item){4,3,4,2});

		/*Crea al Peon 5*/		
		DLL_InsertBack(this,(Item){5,3,5,2});

		/*Crea al Peon 6*/		
		DLL_InsertBack(this,(Item){6,3,6,2});	

		/*Crea al Peon 7*/	
		DLL_InsertBack(this,(Item){7,3,7,2});	

		/*Crea al Peon 8*/	
		DLL_InsertBack(this,(Item){8,3,8,2});	

		/*Crea a la Torre 1*/	
		DLL_InsertBack(this,(Item){9,1,1,1});	

		/*Crea al Caballo 1*/	
		DLL_InsertBack(this,(Item){10,6,2,1});		

		/*Crea al Alfin 1*/
		DLL_InsertBack(this,(Item){11,2,3,1});		

		/*Crea al Rey*/
		DLL_InsertBack(this,(Item){12,4,4,1});	

		/*Crea a la Reina*/	
		DLL_InsertBack(this,(Item){13,5,5,1});		

		/*Crea al Alfin 2*/
		DLL_InsertBack(this,(Item){14,2,6,1});		

		/*Crea al Caballo 2*/
		DLL_InsertBack(this,(Item){15,6,7,1});		

		/*Crea a la Torre 2*/
		DLL_InsertBack(this,(Item){16,1,8,1});		

	}else{

		/*Creación de la piezas negras*/

		/*Creando el Peon 1*/
		DLL_InsertBack(this,(Item){17,3,1,7});	

		/*Creando el Peon 2*/	
		DLL_InsertBack(this,(Item){18,3,2,7});		

		/*Creando el Peon 3*/
		DLL_InsertBack(this,(Item){19,3,3,7});		

		/*Creando el Peon 4*/
		DLL_InsertBack(this,(Item){20,3,4,7});		

		/*Creando el Peon 5*/
		DLL_InsertBack(this,(Item){21,3,5,7});	

		/*Creando el Peon 6*/	
		DLL_InsertBack(this,(Item){22,3,6,7});	

		/*Creando el Peon 7*/	
		DLL_InsertBack(this,(Item){23,3,7,7});	

		/*Creando el Peon 8*/	
		DLL_InsertBack(this,(Item){24,3,8,7});	

		/*Creando la Torre 1*/	
		DLL_InsertBack(this,(Item){25,1,1,8});	

		/*Creando al Caballo 1*/	
		DLL_InsertBack(this,(Item){26,6,2,8});	

		/*Creando Alfil 1*/	
		DLL_InsertBack(this,(Item){27,2,3,8});	

		/*Creando al Rey*/	
		DLL_InsertBack(this,(Item){28,4,4,8});		

		/*Creando a la Reina*/
		DLL_InsertBack(this,(Item){29,5,5,8});	

		/*Creando al Alfin 2*/	
		DLL_InsertBack(this,(Item){30,2,6,8});

		/*Creando al Caballo 2*/		
		DLL_InsertBack(this,(Item){31,6,7,8});		

		/*Creando a la Toree 2*/
		DLL_InsertBack(this,(Item){32,1,8,8});		

	}

	/*Retorna la DLL rellenada con las piezas correspondientes*/
	return this;									
}

void Erease(DLL *this, DLL *other){

	/*Verifica que exista la primer DLL*/
	assert(this);		

	/*Verifica que exista la segunda DLL*/			
	assert(other);					

	/*Elimina la primer DLL*/
	DLL_Delete(this);	

	/*Elimina la segunda DLL*/
	DLL_Delete(other);				

}
	
bool Piece_Move(DLL *white, DLL *black, int _x, int _y, int _id){

	/*Verifica que exista la DLL de piezas blancas*/
	assert(white);					

	/*Verifica que exista la DLL de piezas negras*/							
	assert(black);												

	/**!<Bandera que indica si se puede hacer el movimiento o no*/
	bool done = false;		

	/*Item generico para comparar los ids en las DLLs*/									
	Item tmp = {_id,0,0,0};										

	/*Ve si la pieza es blanca*/
	if(_id >=1 && _id <=16){									

		/*Busca la pieza en la DLL de su equipo*/
		DLL_Search(white,tmp,CompareId);

		/*Actualiza el item generico y lo convierte en la pieza a mover*/							
		DLL_Peek(white,&tmp);									

		/*Ve de que tipo de pieza se trata*/
		switch(tmp.type){										
			case 1:
				/*Movimiento de la Torre*/
				done = Tower_Move(white,black,&tmp,_x,_y); 		
				break;
			case 2:
				/*Movimiento del Alfil*/
				done = Bishop_Move(white,black,&tmp,_x,_y); 	
				break;
			case 3:
				/*Movimiento del Peon*/
				done = Pawn_Move(white,black,&tmp,_x,_y); 		
				break;
			case 4:
				/*Movimiento del Rey*/
				done = King_Move(white,black,&tmp,_x,_y); 		
				break;
			case 5:
				/*Movimiento de la Reina*/
				done = Queen_Move(white,black,&tmp,_x,_y);		
				break;
			case 6:
				/*Movimiento del Caballo*/
				done = Horse_Move(white,black,&tmp,_x,_y); 		
				break;
		}

		/*Si es valido el movimiento*/
		if (done == true){		

			/*Actualizamos las coordenadas de la pieza en x*/								
			white -> cursor -> data.x = _x;	

			/*Actualizamos las coordenadas de la pieza en y*/					
			white -> cursor -> data.y = _y;						
		}

	/*Ve si la pieza es negra*/
	}else if(_id >16 && _id <=32){								

			/*Busca la pieza en la DLL de su equipo*/
			DLL_Search(black,tmp,CompareId);			

			/*Actualiza el item generico y lo convierte en la pieza a mover*/
			DLL_Peek(black,&tmp);								

			switch(tmp.type){
				case 1:
					/*Movimiento de la Torre*/
					done = Tower_Move(black,white,&tmp,_x,_y); 		
					break;
				case 2:
					/*Movimiento del Alfil*/
					done = Bishop_Move(black,white,&tmp,_x,_y); 	
					break;
				case 3:
					/*Movimiento del Peon*/
					done = Pawn_Move(black,white,&tmp,_x,_y); 		
					break;
				case 4:
					/*Movimiento del Rey*/
					done = King_Move(black,white,&tmp,_x,_y); 		
					break;
				case 5:
					/*Movimiento de la Reina*/
					done = Queen_Move(black,white,&tmp,_x,_y);		
					break;
				case 6:
					/*Movimiento del Caballo*/
					done = Horse_Move(black,white,&tmp,_x,_y); 		
					break;

		}

		/*Si es valido el movimiento*/
		if (done == true){	

			/*Actualizamos las coordenadas de la pieza en x*/										
			black -> cursor -> data.x = _x;	

			/*Actualizamos las coordenadas de la pieza en y*/
			black -> cursor -> data.y = _y;							
		}
	}
	return done;
}