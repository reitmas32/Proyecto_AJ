#include "DLL.h"

/**
 *@brief Función encargada de crear un nuevo nodo
 *
 *@param _data Item que tendra el nodo
 *
 *@return Apuntador de tipo Node
 *
 */

static NodePtr newNode(Item _data){
	NodePtr n = (NodePtr)malloc(sizeof(Node));		/**!<Pide memoria para un nuevo nodo*/
	if(n){											/**!<Verifica que se haya creado el nuevo nodo*/
		n -> data = _data;							/**!<Inicializa data con el Item proporsionado*/
		n -> next = NULL;							/**!<Inicializa el apuntador next a NULL*/
		n -> prev = NULL;							/**!<Inicializa el apuntador prev a NULL*/
	}
	return n;										/**!<Retorna un aputnador de tipo Node*/
}

/**
 *@brief Función encargada de resetar los apuntador de una DLL
 *
 *@param this Apuntador de tipo DLL
 *
 */

static void reset(DLL *this){
	this -> first = this -> last = this -> cursor = NULL;		/**!<Cambia el valor de first, last y cursor a NULL*/
	this -> len = 0;											/**!<Cambia el valor de Len a 0*/
}

DLL *DLL_New(){
	DLL *list = (DLL*)malloc(sizeof(DLL));		/**!<Pide memoria para una una nueva DLL*/
	if(list){									/**!<Verifica que se haya creado la DLL*/
		reset(list);							/**!<La resetea*/
	}
	return list;								/**!<Retorna un apuntador de tipo DLL*/
}

void DLL_Delete(DLL *this){
	if(this){									/**!<Comprueba que exista la DLL*/
		DLL_MakeEmpty(this);					/**!<elimina todos los nodos de la DLL*/
		free(this);								/**!<Elimina a la DLL*/
	}
}

bool DLL_InsertBack(DLL *this, Item _data){
	assert(this);													/**!<Verifica que exista la DLL*/

	bool done = false;												/**!<Bandera que indica si la inserción fue correcta o no*/

	NodePtr n = newNode(_data);										/**!<Crea un nuevo nodo*/

	if(n){															/**!<Verifica que se haya creado correctamente el nodo*/
		done = true;												/**!<Cambia el valor de la bandera*/

		if(DLL_IsEmpty(this)){										/**!<Ve si esta vacia la DLL*/
			this -> first = this -> last =this -> cursor = n;		/**!<Iguala first,last y cursor al nuevo nodo*/
			this -> len = 1;										/**!<Iguala len a 1*/
		}else{
			this -> last -> next = n;								/**!<Iguala last -> next al nuevo nodo*/
			n -> prev = this -> last;								/**!<Iguala n -> prev a last*/
			this -> last = n;										/**!<Iguala last al nuevo nodo*/
			++this -> len;											/**!<Incrementa Len*/
		}
	}
	return done;													/**!<Retorna el valor de la bandera*/
}

bool DLL_InsertFront(DLL *this, Item _data){
	assert(this);													/**!<Verifica que exista la DLL*/

	bool done = false;												/**!<Bandera que indica si la inserción fue correcta o no*/

	NodePtr n = newNode(_data);										/**!<Crea un nuevo nodo*/

	if(n){															/**!<Verifica que se haya creado correctamente el nodo*/
		done = true;												/**!<Cambia el valor de la bandera*/

		if(DLL_IsEmpty(this)){										/**!<Ve si esta vacia la DLL*/
			this -> first = this -> last = this -> cursor = n;		/**!<Iguala a first,last y cursor al nuevo nodo*/
			this -> len = 1;										/**!<Iguala len a 1*/
		}else{
			n -> next = this -> first;								/**!<Iguala n -> next a first*/
			this -> first -> prev = n;								/**!<Iguala first -> prev al nuevo nodo*/
			this -> first = n;										/**!<Iguala first al nuevo nodo*/
			++this -> len;											/**!<Incrementa a len*/
		}
	}
	return done;													/**!<Retorna el valor de la bandera*/
}

bool DLL_InsertAfter(DLL *this, Item _data){

	assert(this);													/**!<Verifica que exista la DLL*/

	bool done = false;												/**!<Bandera que indica si la inserción fue correcta o no*/

	if(DLL_IsEmpty(this) || this -> cursor == this -> last){		/**!<Ve si al DLL esta vacia y si cursor es igual a last*/
		done = DLL_InsertBack(this, _data);							/**!<Hace un insertBack e iguala done al resultado de la función*/
	}else{
		NodePtr n = newNode(_data);									/**!<Crea un nuevo nodo*/

		if(n){														/**!<Verifica que se haya creado correctamente el nodo*/
			done = true;											/**!<Cambia el valor de la bandera*/

			n-> next = this -> cursor -> next;						/**!<Iguala n -> next a cursor -> next*/
			this -> cursor -> next -> prev = n;						/**!<Iguala cursor -> next -> prev al nuevo nodo*/
			this -> cursor -> next = n;								/**!<Iguala cursor -> next al nuevo nodo*/
			n -> prev = this -> cursor;								/**!<Iguala n -> prev al cursor*/
			++this -> len;											/**!<Incrementa len*/
		}
	}
	return done;													/**!<Retorna el valor de la bandera*/
}

bool DLL_InsertBefore(DLL *this, Item _data){
	assert(this);													/**!<Verifica que exista la DLL*/

	bool done = false;												/**!<Bandera que indica si la inserción fue correcta o no*/

	if(DLL_IsEmpty(this) || this -> cursor == this -> first){		/**!<Ve si la DLL esta vacia y el cursor es igual a first*/
		done = DLL_InsertFront(this, _data);						/**!<Hace un insertFront e iguala done al resultado de la función*/
	}else{
		NodePtr n = newNode(_data);									/**!<Crea un nuevo nodo*/

		if(n){														/**!<Verifica que se haya creado correctamente el nodo*/
			done = true;											/**!<Cambia el valor de la bandera*/
			n -> prev = this -> cursor -> prev;						/**!<Iguala n -> prev a cursor -> prev*/
			this -> cursor -> prev -> next = n;						/**!<Iguala cursor -> prev al nuevo nodo*/
			this -> cursor -> prev = n;								/**!<Iguala cursor -> prev al nuevo nodo*/
			n -> next = this -> cursor; 							/**!<Iguala n-> next a cursor*/
			++this -> len;											/**!<Incrementa len*/
		}
	}
	return done;													/**!<Retorna el valor de la bandera*/
}
bool DLL_Remove(DLL *this, ItemPtr _data_back){

	assert(this);												/**!<Verifica que exista la DLL*/

	bool done = false;											/**!<Bandera que indica si la eliminación fue correcta o no*/

	if(!DLL_IsEmpty(this) && NULL != this -> cursor){			/**!<Ve si la DLL no esta vacia y si el cursor es diferente de NULL*/
		done = true;											/**!<Cambia el valor de la bandera*/

		if(this -> cursor == this -> first){					/**!<Ve si el cursor esta en first*/
			DLL_RemoveFront(this, _data_back);					/**!<Hace un RemoveFront*/
		}else if(this -> cursor == this -> last){				/**!<Ve si el cursor esta en last*/
			DLL_RemoveBack(this ,_data_back);					/**!<Hace un RemoveBack*/
		}else{

			*_data_back = this -> cursor -> data;				/**!<Retorna el valor del nodo*/

			NodePtr left = this -> cursor -> prev;				/**!<Crea un apuntador de tipo node llamado left y lo iguala a cursor -> prev*/
			NodePtr right = this -> cursor -> next;				/**!<Crea un apuntador de tipo node  llamado right y lo iguala a cursor -> next*/
			free(this -> cursor);								/**!<Elimina el nodo en el que esta el cursor*/

			if(left == NULL && right == NULL){					/**!<Ve si left y right son diferentes a NULL*/
				reset(this);									/**!<Resetea a la DLL*/
			}else{
				this -> cursor = left;							/**!<Iguala el cursor a left*/
				this -> cursor -> next = right;					/**!<Iguala cursor -> next a right*/
				right -> prev = this -> cursor;					/**!<Iguala right -> prev a cursor*/
				--this -> len;									/**!<Decrementa len*/
			}
		}
	}
	return done;												/**!<Retorna el valor de la bandera*/
}

bool DLL_RemoveFront(DLL *this, ItemPtr _data_back){

	assert(this);										/**!<Verifica que exista la DLL*/

	bool done = false;									/**!<Bandera que indica si la eliminación es correcta o no*/

	if(!DLL_IsEmpty(this)){								/**!<Ve si la DLL no esta vacia*/
		done = true;									/**!<Cambia el valor de la bandera*/
		*_data_back = this -> first -> data;			/**!<Retorna el valor del nodo*/
		NodePtr tmp = this -> first -> next;			/**!<Crea un apuntador a node llamado tmp y lo iguala a first -> next*/
		free(this -> first);							/**!<Elimina first*/
		this -> first = tmp;							/**!<Iguala first a tmp*/

		if(NULL != this -> first){						/**!<Ve que first sea diferente a NULL*/
			this -> first -> prev = NULL;				/**!<Iguala first -> prev a NULL*/
			--this -> len;								/**!<Decrementa len*/
		}else{	
			reset(this);								/**!<Resetea la DLL*/
		}
	}
	return done;										/**!<Retorna el valor de la bandera*/
}

bool DLL_RemoveBack(DLL *this, ItemPtr _data_back)
{
	assert(this);										/**!<Verifica que exista la DLL*/

	bool done = false;									/**!<Bandera que indica si la eliminación es correcta o no*/

	if(!DLL_IsEmpty(this)){								/**!<Ve si la DLL no esta vacia*/
		done = true;									/**!<Cambia el valor de la bandera*/
		*_data_back = this -> last -> data;				/**!<Retorna el valor del nodo*/
		NodePtr tmp = this -> last -> prev;				/**!<Crea un apuntador de tipo node llamado tmp y lo iguala a last -> prev*/
		free(this -> last);								/**!<Elimina last*/
		this -> last = tmp;								/**!<Iguala last a tmp*/
		if(NULL != this -> last){						/**!<Ve que last sea diferente de NULL*/
			this -> last -> next = NULL;				/**!<Iguala last -> next a NULL*/
			--this -> len;								/**!<Decrementa len*/
		}else{
			reset(this);								/**!<Resetea la DLL*/
		}
	}
	
	return done;										/**!<Retorna el valor de la bandera*/

}

bool DLL_RemoveAfter(DLL *this, ItemPtr _data_back){										

	assert(this);																			/**!<Verifica que exista la DLL*/

	bool done = false;																		/**!<Bandera que indica si la eliminación es correcta o no*/

	if(!DLL_IsEmpty(this) && this -> cursor != this -> last && this -> cursor != NULL)		/**!<Ve que la DLL no este vacia y que el cursor sea diferente de last y que el cursor sea diferente de NULL*/
	{
		
		done = true;																		/**!<Cambia el valor de la bandera*/
		NodePtr tmp1 = this -> cursor -> next;												/**!<Crea un apuntador de tipo node llamado tmp1 y lo iguala a cursor -> next*/
		*_data_back = tmp1 -> data;															/**!< Retorna el valor del nodo*/
		NodePtr tmp2 = tmp1 -> next;														/**!<Crea un apuntador de tipo node llamdo tmp2 y lo iguala a tmp1 -> next*/
		free(tmp1);																			/**!<Elimina tmp1*/
		this -> cursor -> next = tmp2;														/**!<Iguala cursor -> next a tmp2*/
		
		if(tmp2 != NULL){																	/**!<Ve si tmp2 es diferente a NULL*/
			tmp2 -> prev = this -> cursor;													/**!<Iguala tmp2 -> prev al cursor*/
		}else{
			this -> last = this -> cursor;													/**!<Iguala last a cursor*/
		}
		--this -> len;																		/**!<Decrementa len*/
	}
	return done;																			/**!<Retorna el valor de la bandera*/

}

bool DLL_RemoveBefore(DLL *this, ItemPtr _data_back){

	assert(this);																			/**!<Verifica que exista la DLL*/

	bool done = false;																		/**!<Bandera que indica si la eliminación es correcta o no*/

	if(!DLL_IsEmpty(this) && this -> cursor != this -> first && this -> cursor != NULL)		/**!<Ve que la DLL no este vacia y que el cursor sea diferente a first y que el cursor sea diferente a NULL*/
	{
		done = true;																		/**!<Cambia el valor de la bandera*/
		NodePtr tmp1 = this -> cursor -> prev;												/**!<Crea un apuntador de tipo node llamado tmp1 y lo iguala a cursor -> prev*/
		*_data_back = tmp1 -> data;															/**!<Retorna el valor del nodo*/
		NodePtr tmp2 = tmp1 -> prev;														/**!<Crea un apuntador de tipo node llamado tmp2 y lo iguala a tmp1 -> prev*/
		free(tmp1);																			/**!<Elimina tmp1*/
		this -> cursor -> prev = tmp2;														/**!<Iguala el cursor -> prev a tmp2*/

		if(tmp2 != NULL){																	/**!<Ve si tmp2 es diferente a NULL*/
			tmp2 -> next = this -> cursor; 													/**!<Iguala tmp2 -> next a cursor*/
		}else{
			this -> first = this -> cursor;													/**!<Iguala first a cursor*/
		}
		--this -> len;																		/**!<Decrementa len*/
	}
	return done;																			/**!<Retorna el valor de la bandera*/
}

size_t DLL_Len(DLL *this){
	assert(this);			/**!<Verifica que exista la DLL*/
	return this -> len;		/**!<Retorna len*/
}

bool DLL_IsEmpty(DLL *this){
	assert(this);					/**!<Verifica que exista la DLL*/
	return this -> first == NULL;	/**!<Retorna True si first es igual a NULL de lo contrario False*/
}

void DLL_MakeEmpty(DLL *this){

	assert(this);								/**!<Verifica que exista la DLL*/
	while(NULL != this -> first){				/**!<Bucle que se repite mientras first sea diferente de NULL*/
		NodePtr tmp = this -> first -> next;	/**!<Crea un apuntador de tipo node llamado tmp y lo iguala a first -> next*/
		free(this -> first);					/**!<Elimina first*/
		this -> first = tmp;					/**!<Iguala first a tmp*/
	}
	reset(this);								/**!<Resetea la DLL*/
}

bool DLL_Peek(DLL *this, ItemPtr _data_back){
	assert(this);										/**!<Verifica que exista la DLL*/

	bool done = false;									/**!<Bandera que indica si se pudo observar el nodo*/

	if(!DLL_IsEmpty(this) && this -> cursor != NULL){	/**!<Ve si la lista no esta vacia y si el cursor es diferente de NULL*/
		*_data_back = this -> cursor -> data;			/**!<Retorna el valor del Nodo*/
		done = true;									/**!<Cambia el valor de la bandera*/
	}
	return done;										/**!<Retorna el valor de la bandera*/
}

void DLL_CursorFirst(DLL *this){

	assert(this);						/**!<Verifica que exista la DLL*/
	this -> cursor = this -> first;		/**!<Iguala cursor a first*/
}

void DLL_CursorLast(DLL *this){

	assert(this);						/**!<Verifica que exista la DLL*/
	this -> cursor = this -> last;		/**!<Iguala cursor a last*/
}

void DLL_CursorNext(DLL *this){

	assert(this);									/**!<Verifica que exista la DLL*/
	if(this -> cursor != NULL){						/**!<Verifica que el cursor sea diferente de NULL*/
		this -> cursor = this -> cursor -> next;	/**!<Iguala cursor a cursor -> next*/
	}
}

void DLL_CursorPrev(DLL *this){

	assert(this);									/**!<Verifica que exista la DLL*/
	if(this -> cursor != NULL){						/**!<Verifica que el cursor sea diferente de NULL*/
		this -> cursor = this -> cursor -> prev;	/**!<Iguala cursor a cursor -> prev*/
	}
}

bool DLL_FindIf(DLL *this, Item _key, bool (*cmp)(Item, Item)){

	assert(this);														/**!<Verifica que exista la DLL*/

	bool found = false;													/**!<Bandera que indica si se encontro el Item*/

	for(NodePtr it = this -> first; it != NULL; it = it -> next){		/**!<Bucle que se repite mientras it sea diferente de NULL*/
		if(cmp(_key, it -> data)){										/**!<Llamado a función que compara dos Items*/
			found = true;												/**!<Cambia el valor de la bandera*/
			break;
		}
	}
	return found;														/**!<Retorna el valor de la bandera*/
}

bool DLL_Search(DLL *this, Item _key, bool (*cmp)(Item, Item)){

	assert(this);															/**!<Verifica que exista la DLL*/

	bool found = false;														/**!<Bandera que indica si se encontro el Item*/

	if(!DLL_IsEmpty(this)){													/**!<Comprueba que la DLL no este vacia*/
		for(NodePtr it = this -> first; it != NULL; it = it -> next){		/**!<Bucle que se repite mientras it sea diferente de NULL*/
			if(cmp(_key, it-> data)){										/**!<Llamado a función que compra Items*/
				found = true;												/**!<Cambia el valor de la bandera*/
				this -> cursor = it;										/**!<Iguala cursor a it*/
				break;
			}
		}
	}
	return found;															/**!<Retorna el valor de la bandera*/

}

void DLL_Traverse(DLL *this, void (*pfun)(Item)){

	assert(this);													/**!<Verifica que exista la DLL*/

	for(NodePtr it = this -> first; it != NULL; it = it -> next){	/**!<Bucle que se repite mientras it sea diferente de NULL*/
		pfun(it -> data);											/**!<Lamado a función*/
	}
}




