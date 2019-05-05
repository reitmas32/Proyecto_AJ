#ifndef __PIECES_H
#define __PIECES_H

#include "DLL.h"

/**
 *@brief Funcion encargada de inicializar una DLL con las piezas del equipo que se le indique
 *
 *@param type Tipo de DLL que es, 0 para blanca 1 para negra
 *
 *@return Apuntador de tipo DLL
 *
 */

DLL *Initialize(int type);

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

#endif