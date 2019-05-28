/**!< Bibliotaca Pieces*/
#include "Board.h"

/**!< Definicion de Colores*/
#define back "\x1b[49m"
#define backBlack "\x1b[40m"
#define backWhite "\x1b[45m"
#define black "\x1b[37m"
#define white "\x1b[31m"
#define amarillo "\x1b[34m"

/**!< Funcion que vacia el Buffer*/
static void flush_in(){
    int ch;

    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

/**!< Funcion para controlar el cursor*/
static void gotoxy( short x, short y ){
	printf("%c[%d;%df",0x1B, y, x );
}

/**!< Funcion que compara coordenadas*/
static bool CompareCoordinates( Item this, Item other ){
    if( this.x == other.x && this.y == other.y ){
        return true;
    }else{
        return false;
    }
}

/**!< FUncion que tranforma las coordenadas de x, las pasa de caracter a numero entero para su mejor manejo*/
static int transform_x( char _x ){


    switch ( _x )               /**!< Switch para saber que letra ingreso el usuario*/
    {
        case 'A':               /**!< Si ingreso A o a*/
        case 'a':{
        
            return 1;           /**!< Es la fila 1*/
            break;
        }
        case 'B':               /**!< Si engreso B o b*/
        case 'b':{

            return 2;           /**!< Es la fila 2*/
            break;
        }
        case 'C':               /**!< Si engreso C o c*/
        case 'c':{

            return 3;           /**!< Es la fila 3*/
            break;
        }
        case 'D':               /**!< Si engreso D o d*/
        case 'd':{

            return 4;           /**!< Es la fila 4*/
            break;
        }
        case 'E':               /**!< Si engreso E o e*/
        case 'e':{

            return 5;          /**!< Es la fila 5*/
            break;
        }
        case 'F':               /**!< Si engreso F o f*/
        case 'f':{

            return 6;           /**!< Es la fila 6*/
            break;
        }
        case 'G':               /**!< Si engreso G o bg*/
        case 'g':{

            return 7;           /**!< Es la fila 7*/
            break;
        }
        case 'H':               /**!< Si engreso H o h*/
        case 'h':{

            return 8;           /**!< Es la fila 8*/
            break;
        }
        default:                /**!< S i engreso otra letra*/
            return 9;           /**!< Habra un error*/
            break;
    }
}

/**!< Asigna las letras a cadaelmento, es llamada por DLL_Traverse2*/
static bool AssignsLetter( ItemPtr this ){

    bool done = false;                          /**!< Bandera*/

    switch ( this -> type )                     /**!< switch para saber que tipo de pieza es*/
    {
        case 1:{                                /**!< Si es 1*/

            this -> letter = 'T';               /**!< letter es T*/

            done = true;                        /**!< Regrasa true*/

        }break;
        case 2:{                                /**!< Si es 2*/

            this -> letter = 'A';               /**!< letter es A*/

            done = true;                        /**!< Regrasa true*/

        }break;
        case 3:{                                /**!< Si es 3*/

            this -> letter = 'P';               /**!< letter es P*/

            done = true;                        /**!< Regrasa true*/

        }break;
        case 4:{                                /**!< Si es 4*/

            this -> letter = 'K';               /**!< letter es K*/

            done = true;                        /**!< Regrasa true*/

        }break;
        case 5:{                                /**!< Si es 5*/

            this -> letter = 'Q';               /**!< letter es Q*/

            done = true;                        /**!< Regrasa true*/

        }break;
        case 6:{                                /**!< Si es 6*/

            this -> letter = 'C';               /**!< letter es C*/

            done = true;                        /**!< Regrasa true*/

        }break;
        default:{                                /**!< Si no es ninguna de las anteriores*/

            done = false;                        /**!< Regrasa false*/

        }break;
    }

    return done;
}


void PrintBoard(){

	system( "clear" );                      /**!< Borro pantalla*/

    gotoxy( 1, 1 );                         /**!< Coloco el cursor al inicio de la terminal*/

	for( size_t j = 1; j <= 40; ++j ){      /**!< Ciclos para que la pantalla de haga negra despues de cada llamada a la funcion */

		for( size_t i = 1; i <=80; ++i ){

			gotoxy( i, j );

			printf( back " " );
		}
	}
                
	for ( int j = 1; j <= 8; ++j ){                 /**!< Imprimer las letras del tablero*/

		gotoxy( 2, 2 + ( j*2 ) );                   /**!< 'x' se mentiene constante y 'y' variable*/
		printf( amarillo "%c", j + 48 );            /**!< Imprime los numeros del 1 al 8*/
	}

	for (int i = 1; i <= 8; ++i){                   /**!< Imprime los numeros del tablero*/

		gotoxy( 2 + ( i*4 ), 2 );                   /**!< 'y' se mantine constante y 'x' variable*/
		printf( amarillo "%c", 64 + i  );           /**!< IMprime las letras de la A a la H*/
	}

	for( size_t i = 1; i <= 8; ++i ){               /**!< Imprime cada casilla del tablero, ciclo de x*/

		for (int j = 1; j <= 8; ++j){               /**!< Imprime cada casilla del tablero, ciclo de y*/

			gotoxy( ( i*4 ) + 2  , ( j*2 ) + 2 );   /**!< Tanto x como y varian*/
			if ( i % 2 == 0 && j % 2 != 0 ){        /**!< SI i es pra y j no */
				printf( backBlack " " );            /**!< El fondo debe ser Negro*/
			}   
			else if ( i % 2 != 0 && j % 2 == 0 ){   /**!< Si i no es par y j si*/
				printf( backBlack " " );            /**!< El fondo debe ser Negro*/           
			}
			else{                                   /**!< Sino, es decir i y j son pares o impares al mismo timpo*/
				printf( backWhite " " );            /**!< El fonde debe ser Blando*/
			}
		}
	}
}

bool printPiece( Item this ){

    bool done = false;                          /**!< Bandera*/

	if ( this.id >= 1 && this.id <= 16 ) {      /**!< Si es una pieza blanca*/

        done = true;

		if ( this.x % 2 == 0 &&                 /**!< Si 'x' es par y 'y' no*/
             this.y % 2 != 0 ){

			    printf( backBlack "" );
		}
		else if ( this.x % 2 != 0 &&            /**!< Si 'x' no es par y 'y' si */
                  this.y % 2 == 0 ){

			        printf( backBlack "" );
		}
		else{                                   /**!< Si 'x' y 'y' son pares o impares*/

			printf(backWhite "" );
		}

		gotoxy( ( this.x*4 )+2, ( this.y*2 ) + 2 );
		printf( black "%c", this.letter );      /**!< Se imprime la letra de la pieza*/

	}
	else if( this.id >= 17 && this.id <= 32 ){  /**!< Si es una pieza negra*/

        done = true;

        if ( this.x % 2 == 0 &&                 /**!< Si 'x' es par y 'y' no*/
                this.y % 2 != 0 ){

                printf( backBlack "" );
        }
        else if ( this.x % 2 != 0 &&            /**!< Si 'x' no es par y 'y' si */
                    this.y % 2 == 0 ){

                printf( backBlack "" );
        }
        else{                                   /**!< Si 'x' y 'y' son pares o impares*/
            printf(backWhite "" );
        }	
        gotoxy( ( this.x*4 )+2, ( this.y*2 ) + 2 );
        printf( white "%c", this.letter );      /**!< Se imprime la letra de la pieza*/
	}
    else{

        done = false;
    }
	
    return done;
}


void print( DLL* Pieces_Black, DLL* Pieces_White, int _x, int _y, int _id ){

	Piece_Move( Pieces_White, Pieces_Black, _x, _y, _id );      /**!< Se manda a llamar la funcion de mover pieza*/

	system( "clear" );                                          /**!< Se limpia la panatalla*/
	gotoxy( 0, 0 );                                             /**!< Se coloca el cursor en 0,0*/
	PrintBoard();                                               /**!< Se manda a llamar la funcion para imprimir el tablero*/
	DLL_Traverse( Pieces_White, printPiece );                   /**!< Se manda a imprimir las piezas blancas*/
	DLL_Traverse( Pieces_Black, printPiece );                   /**!< Se menda a imprimir las piezas negras*/
	gotoxy( 0, 40 );                                            /**!< Se coloca el cirsor en 0,40*/

}

void menu(){                                                    
    DLL *Pieces_Black = Initialize(1);                          /**!< Se crean e inicializan las piezas negras*/
	DLL *Pieces_White = Initialize(0);                          /**!< Se crean e inicializan las piezas blancas*/

	DLL_TraverseTwo( Pieces_Black, AssignsLetter );             /**!< Se ingresan las letras a las piezas negras*/
	DLL_TraverseTwo( Pieces_White, AssignsLetter );             /**!< Se ingresan las letras a las piezas blancas*/

    print( Pieces_Black, Pieces_White, 0, 0, 0 );               /**!< Se imprime el tablero para inizializarlo*/

    bool turn = 1;                                              /**!< Contador que indica el turno*/

    int x_int;                                                  /**!< Coordenada en 'x' donde se encuentra la pieza*/
    int _y;                                                     /**!< Coordenada en 'y' donde se encuentra la pieza*/
    int x_int_new;                                              /**!< Coordenada en 'x' a donde se movera*/
    int y_new;                                                  /**!< Coordenada en 'y' a donde se movera*/
    int _id;                                                    /**!< id para localizar la pieza que se movera*/
                       
    char _x;                                                    /**!< Coordenada en 'x' donde se encuentra la pieza, es la que ingresara el usuario*/
    char x_new;                                                 /**!< Coordenada en 'x' a donde se movera la pieza, es la que ingresara el usuario*/

    char op = 's' ;                                             /**!< Opción para continuar jugando*/

    bool first = 1;                                             /**!< Auxiliar para saber si es el primer movimiento*/

    while ( op == 's' )                                         /**!< Ciclo para jugar*/
    {
        gotoxy( 45, 2 );                                        /**!< Coordenada para imprimir información*/

        if( turn == 1 ){                                       /**!< Si le toca a Blancas*/

            turn = 0;                                          /**!< Actualizo el turno*/

            gotoxy( 45, 2 );
            printf( back black "TURNO -Blancas:" );            /**!< Mensaje sobre el turno*/
            gotoxy( 45, 4); 
            printf( "Ingresa coordenadas actuales ");          /**!< Instrucciones*/

            gotoxy( 45, 6 );
            printf( "x: " );

            if( first == 1 ){                                   /**!< Si es le primer movimiento*/
                _x = getchar();                                 /**!< Se lee la coordenada actual en 'x'*/
                first = 0;
            }
            else{                                              /**!< Si no*/
               flush_in();                                     /**!< Se vacia el buffer*/
               _x = getchar();                                 /**!< Se lee la coordenada actual en 'x'*/
            }
        
            gotoxy( 50, 6 );
            printf( "y: " );
            scanf( "%d", &_y);                                  /**!< Se lee la coordenada actual en 'y'*/

            gotoxy( 45, 8);
            printf( "Ingresa las nuevas coordenadas");         /**!< Instrucciones*/

            gotoxy( 45, 9 );
            printf( "x: " );
            flush_in();                                         /**!< Vacio el buffer*/
            x_new = getchar();                                  /**!< Se lee la nueva coordenada en 'x'*/

            gotoxy( 50, 9 );
            printf( "y: " );
            scanf( "%d", &y_new);                               /**!< Se lee la nueva coordenada en 'y'*/
            
            x_int = transform_x( _x );                          /**!< Transformo la coordenada en actual en ´x´´*/
            x_int_new = transform_x( x_new );                   /**!< Transformo la nueva coordenade en 'x'*/

            Item tmp = { .x = x_int, .y = _y };                 /**!< Creo un Item temporal*/
            DLL_Search( Pieces_White, tmp, CompareCoordinates );/**!< Busco el Item temporal*/

            DLL_Peek( Pieces_White, &tmp );                     /**!< Guardo la pieza que se movera en el temporal*/

            _id = tmp.id;                                       /**!< Igualo el _id al id de la pieza que se movera*/

            if ( !Piece_Move( Pieces_White, Pieces_Black, x_int_new, y_new, _id ) ){    /**!< Si no se ´puede mover la pieza*/

                turn = 1;                                                               /**!< El turno vuelve a ser el mismo*/
                gotoxy( 50, 15 );
                printf( "ERROR" );                                                      /**!< Mensaje de ERROR */
                gotoxy( 50, 17 );
                printf( "Datos invalidos" );
            }

        }
        else if( turn == 0 ){                                       /**!< Si le toca a Blancas*/
            
            turn = 1;                                               /**!< Actualizo el turno*/

            gotoxy( 45, 2 );
            printf( back black "TURNO -Negras:" );                  /**!< Mensaje sobre el turno*/
            gotoxy( 45, 4); 
            printf( "Ingresa coordenadas actuales ");                /**!< Instrucciones*/

            gotoxy( 45, 6 );
            printf( "x: " );                                        
            flush_in();                                             /**!< Se vacia el buffer*/
            _x = getchar();                                         /**!< Se lee la coordenada actual en 'x'*/

            gotoxy( 50, 6 );
            printf( "y: " );
            scanf( "%d", &_y);                                      /**!< Se lee la coordenada actual en 'y'*/

            gotoxy( 45, 8);
            printf( "Ingresa las nuevas coordenadas");              /**!< Instrucciones*/

            gotoxy( 45, 9 );
            printf( "x: " );
            flush_in();                                             /**!< Vacio el buffer*/
            x_new = getchar();                                      /**!< Se lee la nueva coordenada en 'x'*/

            gotoxy( 50, 9 );
            printf( "y: " );
            scanf( "%d", &y_new);                                   /**!< Se lee la nueva coordenada en 'y'*/
            
            x_int = transform_x( _x );                              /**!< Transformo la coordenada en actual en ´x´´*/
            x_int_new = transform_x( x_new );                       /**!< Transformo la nueva coordenade en 'x'*/

            Item tmp = { .x = x_int, .y = _y };                     /**!< Creo un Item temporal*/
            DLL_Search( Pieces_Black, tmp, CompareCoordinates );    /**!< Busco el Item temporal*/

            DLL_Peek( Pieces_Black, &tmp );                         /**!< Guardo la pieza que se movera en el temporal*/

            _id = tmp.id;                                           /**!< Igualo el _id al id de la pieza que se movera*/

            if ( !Piece_Move( Pieces_White, Pieces_Black, x_int_new, y_new, _id ) ){    /**!< Si no se ´puede mover la pieza*/

                turn = 0;                                                               /**!< El turno vuelve a ser el mismo*/
                gotoxy( 50, 15 );
                printf( "ERROR" );                                                      /**!< Mensaje de ERROR */
                gotoxy( 50, 17 );
                printf( "Datos invalidos" );
            }
            
        }
        gotoxy( 45, 12 );
        printf( "Continuar s/n:" );                                             /**!< Se pregunta si se quire continuar*/
        flush_in();                                                             /**!< Se vacia el buffer*/
        op = getchar();                                                         /**!< Se lee la opción*/
        print( Pieces_Black, Pieces_White, 0, 0, 0 );                           /**!< Se imprime el tablero*/
    }
    gotoxy( 3, 22 );                                                            /**!< Se coloca el cursor al final de la terminal*/
    Erease(Pieces_White,Pieces_Black);                                          /**!< Se borran las piezas*/
}