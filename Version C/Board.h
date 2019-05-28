#ifndef __BOARD_H__
#define __BOARD_H__

/**!< Biblioteca Pieces.h*/
#include "Pieces.h"

/**
  * @brief  Función que Imprime el tablero
  */
void PrintBoard();


/**
  * @brief Funcion que imprime cada pieza, es utilizada por Traverse
  *  
  * @param  this    Objeto Pieza
  * 
  * @return done    Bandera para saber si la tarea se completo con exito
  * 
  */
bool printPiece( Item this );

/**
  * @brief  Función que mueve la pieza, imprime el tablero e imprime las piezas
  * 
  * @param  Pieces_Black    DLL de las piezas Negras
  * 
  * @param  Pieces_White    DLL de las piezas Blancas
  * 
  * @param  _x              Nueva coordenada en x
  *               
  * @param  _y              Nueva coordenada en y
  * 
  * @param  _id             Id de la pieza a mover
  * 
  */
void print( DLL* Pieces_Black, DLL* Pieces_White, int _x, int _y, int _id );

/**
  * @brief  Función menu  
  */
void menu();

#endif