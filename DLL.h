#ifndef DLL_INC
#define DLL_INC

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

/**
 *@struct Define el TDU Piece con un identificar, un tipo y sus coordenadas en x,y
 */

typedef struct Piece{
	int id;
	int type;
	int x;
	int y;
}Piece;

typedef  struct Piece Item;			/**!<Typedefiniendo int como Item*/
typedef Item* ItemPtr;				/**!<Typedefiniendo Item* como ItemPtr*/

/**
 *@struct Define el TDU Node con su campo de data y dos apuntadores de tipo struct Node
 */

typedef struct Node{
	Item data;
	struct Node *next;
	struct Node *prev;
}Node;

typedef Node *NodePtr;		/**!<Typedefiniendo Node* como NodePtr*/

/**
 *@struct Define el DLL con sus 3 apuntadores de tipo node y un campo de entero len
 */

typedef struct DLL{
	NodePtr first;
	NodePtr last;
	NodePtr cursor;
	size_t len;
}DLL;

/**
 *@brief Función encargada de crear una nueva DLL
 *
 *@return Un apuntador de tipo DLL
 *
 */

DLL *DLL_New();

/**
 *@brief Funcion encargada de eliminar una DLL
 *
 *@param this Apuntador de tipo DLL
 *
 */
void DLL_Delete(DLL *this);

/**
 *@brief Función encargada de insertar un nodo en el back de una DLL
 *
 *@param this Apuntador de tipo DLL
 *
 *@param _data Item a ingresar a la DLL
 *
 *@return True si se inserto correctamente de lo contrario False
 *
 */

bool DLL_InsertBack(DLL *this, Item _data);

/**
 *@brief Función encargada de insertar un nodo en el front de una DLL
 *
 *@param this Apuntador de tipo DLL
 *
 *@param _data Item a ingresar a la DLL 
 *
 *@return True si se inserto correctamente de lo contrario False
 *
 */
bool DLL_InsertFront(DLL *this, Item _data);

/**
 *@brief Función encargada de insertar un nodo despues del cursor en una DLL
 *
 *@param this Apuntador de tipo DLL
 *
 *@param _data Item a ingresar a la DLL 
 *
 *@return True si se inserto correctamente de lo contrario False
 *
 */

bool DLL_InsertAfter(DLL *this, Item _data);

/**
 *@brief Función encargada de insertar un nodo antes del cursor en una DLL
 *
 *@param this Apuntador de tipo DLL
 *
 *@param _data Item a ingresar a la DLL 
 *
 *@return True si se inserto correctamente de lo contrario False
 *
 */

bool DLL_InsertBefore(DLL *this, Item _data);

/**
 *@brief Función encargada de eliminar el nodo al que apunta el cursor de una DLL
 *
 *@param this Apuntador de tipo DLL
 *
 *@param _data_back Apuntador de tipo Item para devolver el valor del nodo
 *
 *@return True si se removio correctamente de lo contrario False
 *
 */

bool DLL_Remove(DLL *this, ItemPtr _data_back);

/**
 *@brief Función encargada de eliminar un nodo del front de una DLL
 *
 *@param this Apuntador de tipo DLL
 *
 *@param _data_back Apuntador de tipo Item para devolver el valor del nodo
 *
 *@return True si se removio correctamente de lo contrario False
 *
 */

bool DLL_RemoveFront(DLL *this, ItemPtr _data_back);

/**
 *@brief Función encargada de eliminar un nodo del back de una DLL
 *
 *@param this Apuntador de tipo DLL
 *
 *@param _data_back Apuntador de tipo Item para devolver el valor del nodo
 *
 *@return True si se removio correctamente de lo ocntrario False
 *
 */

bool DLL_RemoveBack(DLL *this, ItemPtr _data_back);

/**
 *@brief Función encargada de eliminar un nodo despues del cursor de una DLL
 *
 *@param this Apuntador de tipo DLL
 *
 *@param _data_back Apuntador de tipo Item para devolver el valor del nodo
 *
 *@return True si se removio correctamente de lo contrario False
 *
 */

bool DLL_RemoveAfter(DLL *this, ItemPtr _data_back);

/**
 *@brief Función encargada de eliminar un nodo antes del cursor de una DLL
 *
 *@param this Apuntador de tipo DLL
 *
 *@param _data_back Apuntador de tipo Item para devolver el valor del nodo
 *
 *@return True si se removio correctamente de lo contrario False
 *
 */

bool DLL_RemoveBefore(DLL *this, ItemPtr _data_back);

/**
 *@brief Función encargada de devolver el numero de elementos en la DLL
 *
 *@param this Apuntador de tipo DLL
 *
 *@return El numero de elementos en la DLL
 *
 */

size_t DLL_Len(DLL *this);

/**
 *@brief Función encargada de ver si esta vacia una DLL
 *
 *@param this Apuntador de tipo DLL
 *
 *@return True si esta vacia de lo contrario False 
 *
 */

bool DLL_IsEmpty(DLL *this);

/**
 *@brief Función encargada de vaciar una DLL
 *
 *@param this Apuntador de tipo DLL
 *
 */

void DLL_MakeEmpty(DLL *this);

/**
 *@brief Función encargada de mostrar el valor en el que esta el cursor de una DLL
 *
 *@param this Apuntador de tipo DLL
 *
 *@param _data_back Apuntador de tipo Item para devolver el valor del nodo
 *
 *@return True si se pudo observar el nodo de lo contrario False
 *
 */

bool DLL_Peek(DLL *this, ItemPtr _data_back);

/**
 *@brief Función encargada de mover el cursor al front de una DLL
 *
 *@param this Apuntador de tipo DLL
 *
 */

void DLL_CursorFirst(DLL *this);

/**
 *@brief Función encargada de mover el cursor al back de una DLL
 *
 *@param this Apuntador de tipo DLL
 *
 */

void DLL_CursorLast(DLL *this);

/**
 *@brief Función encargada de mover el cursor a la siguiente posición en una DLL
 *
 *@param this Apuntador de tipo DLL
 *
 */

void DLL_CursorNext(DLL *this);

/**
 *@brief Función encargada de mover el cursor a la posición anterior en una DLL;
 *
 *@param this Apuntador de tipo DLL
 *
 */

void DLL_CursorPrev(DLL *this);

/**
 *@brief Función encargada de recorrer una DLL buscando un Item
 *
 *@param this Apuntador de tipo DLL
 *
 *@param _key Item a buscar en la DLL
 *
 *@param cmp Función encargada de comparar dos Items
 *
 *@return True si se encontro el Item de lo contrario False
 *
 */

bool DLL_FindIf(DLL *this, Item _key, bool (*cmp)(Item, Item));

/**
 *@brief Función encargada de recorrer una DLL buscando un Item y moviendo el cursor a ese Item
 *
 *@param this Apuntador de tipo DLL
 *
 *@param _key Item a buscar en la DLL
 *
 *@param cmp Función encargada de comparar dos Items
 *
 *@return True si se encontro el Item de lo contrario False
 *
 */

bool DLL_Search(DLL *this, Item _key, bool (*cmp)(Item, Item));

/**
 *@brief Función encargada de recorrer una DLL
 *
 *@param this Aputnador de tipo DLL
 *
 *@param pfun Función que puede hacer cualquier cosa que necesite el valor de un nodo
 *
 */

void DLL_Traverse(DLL *this, void (*pfun)(Item));
#endif