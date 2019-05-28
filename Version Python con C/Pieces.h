#ifndef __PIECES_H__
#define __PIECES_H__

/**!< Biblioteca para la utilización de DLL´s*/
#include "DLL.h"

/**
 *@brief Funcion encargada de eliminar las DLLs
 *
 *@param this DLL de las piezas blancas
 *
 *@param other DLL de las piezas negras
 *
 */

void Erease(DLL *this, DLL *other);

/**
 *@brief Funcion encargada de mover una pieza cualquiera
 *
 *@param white DLL de los Items blancos
 *
 *@param black DLL de los Items negros
 *
 *@param _x Coordenada a la que se va a mover el objeto en x
 *
 *@param _y Coordenada a la que se va a mover el objeto en y
 *
 *@param _id Identificar de la pieza a mover
 *
 *@return True si se puede mover la pieza en caso contrario False
 *
 */

bool Piece_Move(DLL *white, DLL *black, int _x, int _y, int _id);

/**
 *@brief Funcion que imprime un objeto Item en un archivo txt 
 * 
 *@param Objeto Item a imprimir 
 *
 */

void print_txt(Item this);

/**
 *@brief Función que lee el contenido del archivo Ajedrez.py.txt y guarda el contenido en dos DLL diferentes 
 *
 *@para this Apuntador a la DLL que guarda las piezas blancas
 *  
 *@para other Apuntador a la DLL que guarda las piezas negras 
 *
 */ 
void read_txt_New(DLL* this, DLL* other);

/**
 *@brief Función que lee el contenido del archivo Ajedrez.c.txt y guarda el contenido en dos DLL diferentes 
 *
 *@para this Apuntador a la DLL que guarda las piezas blancas
 *  
 *@para other Apuntador a la DLL que guarda las piezas negras 
 *
 */ 

void read_txt_Old(DLL* this, DLL* other);

/**
 *@brief Funcion que compara las coordenadas de dos objetos Item para ver si son iguales 
 * 
 *@param this Primer Objeto Item a comparar
 * 
 *@param other Segundo Objeto Item a comparar 
 *  
 *@return Un valor booleano indicando si son iguales las coordenadas 
 *
 */ 

bool CompareCoordinates( Item this, Item other );

#endif