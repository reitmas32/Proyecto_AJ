#include "Pieces.h"
#include <math.h>
 
/*Funcion que compara Ids*/
static bool Compare(Item this, Item other){
    // los items son iguales
    if(this.id == other.id){        
        return true;                       
    }else{
        return false;                       
    }
}
 
/**!< Funcion que compara coordenadas*/
bool CompareCoordinates( Item this, Item other ){
    if( this.x == other.x && this.y == other.y ){ 
        return true;
    }else{
        return false;
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
    /*Verifica la existencia de ambas DLL*/
    assert(this);                       
    assert(other);                     
  
    /*Bandera que sirve para validar el movimiento*/
    bool done = false;
    
    /*Item temporal para comparar las coordenadas actuales con las del destino la pieza*/
    Item tmp = { .x = _x, .y = _y };    
  
     /*Comprueba que se haya movido en una sola direccion*/
    if( _x == piece -> x || _y == piece -> y ){       
        /*Comprueba que no haya nadie del mismo equipo en dicha casilla*/
        if( !DLL_FindIf( this, tmp, CompareCoordinates) ){      
            
            done = true;                                        

            /*Observa si hay alguien del otro equipo en dicha casilla*/
            if( DLL_Search( other, tmp, CompareCoordinates ) ){    
                
                /*Borra la pieza del otro equipo*/
                DLL_Remove( other, &tmp );                          
              
            }
        }
  
    }
  
    return done;
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

    /*Verifica la existencia de las DLL*/
    assert(this);                       
    assert(other);                      
 
    bool done = false;
 
    /*Item temporal para comparar las coordenadas actuales con las del destino la pieza*/
    Item tmp = { .x = _x, .y = _y };    
 
    /*Comprueba que la diferencia entre las coordenadas en 'x' y 'y' sea igual*/
    if( abs(_x - piece -> x) == abs(_y - piece -> y) ){   
 
        /*Comprueba que no haya nadie del mismo equipo en dicha casilla*/
        if( !DLL_FindIf( this, tmp, CompareCoordinates) ){      
 
            done = true;                                        
 
            /*Observa si hay alguien del otro equipo en dicha casilla*/
            if( DLL_Search( other, tmp, CompareCoordinates ) ){    
 
                /*Borra la piza del otro equipo*/
                DLL_Remove( other, &tmp );                          
             
            }
        }       
    }
 
    return done;    
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

    /*Verifica la existencia de ambas DLL*/
    assert(this);                       
    assert(other);                      
 
    /*Bandera que sive para validar el movimiento*/
    bool done = false;      
  
    /*Item temporal para comparar las coordenadas actuales con las del destino la pieza*/
    Item tmp = { .x = _x, .y = _y };    
  
    /*Comprueba que el movimiento se realice unicamente sobre el eje y*/
    if( _x == piece -> x ){        
 
      /*Comprueba si la pieza se movio dos espacios hacia enfrente y que se encuentre ya sea en la casilla uno en y o en la 6*/
      if( abs(_y-piece->y)==2 && ((piece->y==1) || (piece->y==6))){   

            /*Comprueba que no haya nadie del mismo equipo en la misma casilla*/
            if( !DLL_FindIf( this, tmp, CompareCoordinates) ){     

                /*Comprueba que no haya nadie del otro equipo*/
                if( !DLL_FindIf( other, tmp, CompareCoordinates ) ){

                    done = true;                                        
                }
            }
        }
 
        /*Revisa si la pieza pertenece a las blancas*/
        if(piece->id<16)
        {
            /*Peon blanco unicamente avanza de y=1 a y=7*/
            if( _y == piece -> y + 1 ){       
             
                /*Comprueba que no haya nadie del mismo equipo*/
                if( !DLL_FindIf( this, tmp, CompareCoordinates) ){      
                    
                    /*Comprueba que si hay alguien del otro equipo*/
                    if( !DLL_FindIf( other, tmp, CompareCoordinates ) ){    
  
                        done = true;                                        
                    }   
                }
            }
        }
        else if(piece->id>15)
        {
            /*Peon negro avanza unicamente de y=6 a y=0*/
            if( _y == piece -> y - 1 ){      

                /*Comprueba que no haya nadie del mismo equipo*/
                if( !DLL_FindIf( this, tmp, CompareCoordinates) ){      
                    
                    /*Comprueba que no haya nadie del otro equipo*/
                    if( !DLL_FindIf( other, tmp, CompareCoordinates ) ){    
  
                        done = true;                                        
                    }   
                }
            }
        }    
    }
    else if( _x == piece -> x + 1 || _x == piece -> x - 1 ){/*Si se mueve uno en diagonal*/
  
        if( _y == piece -> y + 1 || _y == piece -> y - 1 ){

            /*Comprueba que no haya nadie del mismo equipo*/
            if( !DLL_FindIf( this, tmp, CompareCoordinates) ){      
  
                /*Comprueba que no haya nadie del otro equipo*/
                if( DLL_Search( other, tmp, CompareCoordinates ) ){ 
 
                    DLL_Remove( other, &tmp );                      
                    done = true;                                        
                }
            }
        }
    } 
    return done;
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

    /*Verifica la existencia de ambas DLL*/
    assert(this);                       
    assert(other);                      
 
    /*Bandera que sirve para validar el movimiento*/
    bool done = false;                  
    
    /*Item temporal para comparar las coordenadas actuales con las del destino la pieza*/
    Item tmp = { .x = _x, .y = _y };    
  
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
    else if( _y == piece -> y ){     /*Si no se mueve al los lados */
 
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
    else if( _x == piece -> x + 1 || _x == piece -> x - 1 ){      /*Si se movi uno hacia los lados*/
    
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

    /*Verifica la existencia de ambas DLL*/
    assert(this);                       
    assert(other);                      
 
    bool done = false;
 
    if( Tower_Move( this, other, piece, _x, _y ) ^ Bishop_Move( this, other, piece, _x, _y ) ){     /*Utilizo las otras dos funciones ya que la reyna semueve como culaquiera de las dos */
    
        done = true;
    }
 
    return done;
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

    /*Verifica la existencia de ambas DLL*/
    assert(this);                       
    assert(other);                      
 
    bool done = false;
    
    /*Item temporal para comparar las coordenadas a donde llegara la pieza*/
    Item tmp = { .x = _x, .y = _y };    
 
    /*Si la pieza se mueve dos espacios en 'x' y uno en 'y' o dos en 'y' y uno en 'x'*/
    if( ( abs( _x - piece->x )==1 && abs( _y - piece->y )==2 ) || ( abs( _x - piece->x )==2 && abs( _y - piece->y ) ) ){
 
            done = true;

            /*Comprueba que no haya nadie del mismo equipo*/
            if( !DLL_FindIf( this, tmp, CompareCoordinates) ){      
 
                /*Es valido el movimiento*/
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

void Erease(DLL *this, DLL *other){

    /*Verifica la existencia de ambas DLL*/
    assert(this);                   
    assert(other);                  
    
    /*Se borran ambas DLL*/
    DLL_Delete(this);               
    DLL_Delete(other);              
 
}
 
bool Piece_Move(DLL *white, DLL *black, int _x, int _y, int _id){

    /*Verifica la existencia de las DLL*/
    assert(white);                                              
    assert(black);                                              
 
    /*Bandera que indica si se puede hacer el movimiento o no*/
    bool done = false;                                          

    /**!<Item generico para comparar los ids en las DLLs*/
    Item tmp = {_id,0,0};                                       
 
    /*Identifica si la pieza es blanca*/
    if(_id >=0 && _id <16){                                   
 
        /*Busca la pieza en la DLL de su equipo*/
        DLL_Search(white,tmp,Compare);  
        /*<Actualiza el item generico y lo convierte en la pieza a mover*/                        
        DLL_Peek(white,&tmp);                                   
 
        /*Movimiento de la Torre*/
        if(tmp.id==0||tmp.id==7)
                done = Tower_Move(white,black,&tmp,_x,_y);      
        /*Movimiento del Alfil*/
        if(tmp.id==2||tmp.id==5)
                done = Bishop_Move(white,black,&tmp,_x,_y);    
        /*Movimiento del Peon*/ 
        if(tmp.id>7&&tmp.id<16)
                done = Pawn_Move(white,black,&tmp,_x,_y);      
        /*Movimiento del Rey*/
        if(tmp.id==3)
                done = King_Move(white,black,&tmp,_x,_y);      
        /*Movimiento de la Reina*/ 
        if(tmp.id==4)
                done = Queen_Move(white,black,&tmp,_x,_y);     
        /*Movimiento del Caballo*/
        if(tmp.id==1||tmp.id==6)
                done = Horse_Move(white,black,&tmp,_x,_y);     
 
        /*Si es valido el movimiento*/
        if (done == true){                                      
            /*Actualizamos las coordenadas de la pieza en x*/
            white -> cursor -> data.x = _x;                      
            /*Actualizamos las coordenadas de la pieza en y*/
            white -> cursor -> data.y = _y;                       
        }
 
    }else if(_id >15 && _id <32){/*!<Ve si la pieza es negra*/                           
 
            /*Busca la pieza en la DLL de su equipo*/
            DLL_Search(black,tmp,Compare);                      
            /*Actualiza el item generico y lo convierte en la pieza a mover*/
            DLL_Peek(black,&tmp);                               
 
            /*Actualiza el item generico y lo convierte en la pieza a mover*/
            if(tmp.id==24||tmp.id==31)
                    done = Tower_Move(black,white,&tmp,_x,_y);      
            /*Movimiento del Alfil*/
            if(tmp.id==26||tmp.id==29)
                    done = Bishop_Move(black,white,&tmp,_x,_y);     
            /*Movimiento del Peon*/
            if(tmp.id>15&&tmp.id<24)
                    done = Pawn_Move(black,white,&tmp,_x,_y);       
            /*Movimiento del Rey*/
            if(tmp.id==27)
                    done = King_Move(black,white,&tmp,_x,_y);       
            /*Movimiento de la Reina*/
            if(tmp.id==28)
                    done = Queen_Move(black,white,&tmp,_x,_y);      
            /*Movimiento del Caballo*/
            if(tmp.id==25||tmp.id==30)
                    done = Horse_Move(black,white,&tmp,_x,_y);      

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
 
void print_txt(Item this)
{
    /*Se genera un apuntador tipo File*/
    FILE *Ajedrez;                                                                                 
    /*Se iguala el apuntador a Archivo con el archivo Ajedrez.c.txt, se abre de tipo escribir al final del archivo*/ 
    Ajedrez=fopen("Ajedrez.c.txt", "a");                                                           
     
            /*Condicional necesaria para que el ID siempre sea impreso en formato decenas con unidades*/
            if(this.id<10)                                                                           
            {
                fprintf(Ajedrez,"0%d,%d,%d\n",this.id,this.y,this.x);   
            }
            else
            {
                fprintf(Ajedrez,"%d,%d,%d\n",this.id,this.y,this.x);        
            }       
                
    /*Cerramos el archivo*/;                
    fclose( Ajedrez );                                                                                
}
 
void read_txt_New(DLL* this, DLL* other)
{
    /*Se genera un arreglo que guarda el contenido del archivo txt.*/
    char cadena[1000];                                                                              
 
    /*Se declara un apuntador a Archivo*/
    FILE *Ajedrez;            
    /*Se iguala el apuntador de Archivo con el archivo Ajedrez.py.txt */                                                                      
    Ajedrez=fopen("Ajedrez.py.txt","r");                                                            


    while(feof(Ajedrez)==0)                                                                         
    {
        fgets(cadena,1000,Ajedrez); 

        /*Bucle con un apuntado de tipo char que recorra toda la cadena cadena hasta terminarla*/                                                                
        for(char* letra=&cadena[0];*letra!='\0';letra++)                                            
        {

            /*Estructura que guardara los datos de las piezas*/
            Item pieza;  

            /**!<Condicional que revisa que se está leyendo el id de una pieza para extraer sus datos*/                                                                           
            if(*letra=='0'||*letra=='1'||*letra=='2'||*letra=='3')      
            {                         

                /**!<Se guarda las decenas del ID y hacemos su conversión de char a int*/                                                      
                int num1=*letra-'0';                                                                

                /*Se aumenta en 1 el apuntado letra para leer las unidades del ID*/
                letra++;    
                /**!<Se guardan las unidades del ID y hacemos su conversión de char a int*/                                                                        
                int num2=*letra-'0';                                                                
 
                /*Se guarda el ID en la estructura*/
                pieza.id=(num1*10)+num2;                                                            
 
                /*Se aumeta el apuntador letra dos veces para omitir las comas y se guardan las coordenadas en la estructura*/
                letra+=2;                                                                          
                pieza.y=*letra-'0';                                                                 
 
                letra+=2;                                                                           
                pieza.x=*letra-'0';                                                                 
 
                 /*Condicional generada con el fin de ver si el ID de la pieza pertenece a las piezas negras o blancas */
                if(pieza.id<16)                                                                     
                {
                    /*Pasos de seguridad generados con el fin de que se controle el ingreso de datos y no se repitan piezas*/
                    if(DLL_Len(this)!=0)
                        {
                            DLL_CursorLast(this);
                            if(Compare(this->cursor->data,pieza))
                                return;
                        }

                    /*Guardamos la estructura Piece en el back de la DLL de piezas blancas*/
                    DLL_InsertBack(this,pieza);                                                     
                }
                else
                {
                    /*Pasos de seguridad generados con el fin de que se controle el ingreso de datos y no se repitan piezas*/
                    if(DLL_Len(other)!=0)
                        {
                            DLL_CursorLast(other);
                            if(Compare(other->cursor->data,pieza))
                                return;
                        }
                    /*Se guarda la estructura Piece en el back de la DLL de piezas negras*/
                    DLL_InsertBack(other,pieza);                                                    
                }
            }
        }
    }
    /*Se cierra el archivo*/
    fclose( Ajedrez );                                                                              
}
 
void read_txt_Old(DLL* this, DLL* other)
{
    /*Se genera un arreglo que guarda el contenido del archivo txt.*/
    char cadena[1000];                                                                             
 
    /*Se declara un apuntador a Archivo*/
    FILE *Ajedrez;      
    /*Se iguala el apuntador de Archivo con el archivo Ajedrez.py.txt */                                                                      
    Ajedrez=fopen("Ajedrez.c.txt","r");                                                         
 
    while(feof(Ajedrez)==0)                                                                         
    {
        fgets(cadena,1000,Ajedrez);   

        /*Bucle con un apuntado de tipo char que recorra toda la cadena cadena hasta terminarla*/                                                                
        for(char* letra=&cadena[0];*letra!='\0';letra++)                                            
        {
            /*Estructura que guardara los datos de las piezas*/
            Item pieza;               
            /**!<Condicional que revisa que se está leyendo el id de una pieza para extraer sus datos*/                                                                           
            if(*letra=='0'||*letra=='1'||*letra=='2'||*letra=='3')
            {
                /**!<Se guarda las decenas del ID y hacemos su conversión de char a int*/                                     
                int num1=*letra-'0';   
 
                /*Se aumenta en 1 el apuntado letra para leer las unidades del ID*/
                letra++;    
                /**!<Se guardan las unidades del ID y hacemos su conversión de char a int*/                                                                        
                int num2=*letra-'0';    
 
                /*Se guarda el ID en la estructura*/
                pieza.id=(num1*10)+num2;
                                        
                /*Se aumeta el apuntador letra dos veces para omitir las comas y se guardan las coordenadas en la estructura*/
                letra+=2;       
                pieza.y=*letra-'0';
 
                letra+=2;          
                pieza.x=*letra-'0';
 
                /*Condicional generada con el fin de ver si el ID de la pieza pertenece a las piezas negras o blancas */
                if(pieza.id<16) 
                {
                    /*Pasos de seguridad generados con el fin de que se controle el ingreso de datos y no se repitan piezas*/
                    if(DLL_Len(this)!=0)
                        {
                            DLL_CursorLast(this);
                            if(Compare(this->cursor->data,pieza))
                                return;
                        }
                    /*Se guarda la estructura Piece en el back de la DLL de piezas blancas*/
                    DLL_InsertBack(this,pieza);                                                     
                }
                else
                {
                    /*Pasos de seguridad generados con el fin de que se controle el ingreso de datos y no se repitan piezas*/
                    if(DLL_Len(other)!=0)
                        {
                            DLL_CursorLast(other);
                            if(Compare(other->cursor->data,pieza))
                                return;
                        }
                    /*Se guarda la estructura Piece en el back de la DLL de piezas negras*/
                    DLL_InsertBack(other,pieza);                                                    
                }
            }
        }
    }
    /*Se cierra el archivo*/
    fclose( Ajedrez );                                                                              
}