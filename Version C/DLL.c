/*Biblioteca de prototipos de la DLL*/
#include "DLL.h"

/*Función qu crea un nuevo nodo*/
static NodePtr newNode(Item _data){

	/*Pide memoria para un nuevo nodo*/
	NodePtr n = (NodePtr)malloc(sizeof(Node));	

	if(n){											
		n -> data = _data;							
		n -> next = NULL;							
		n -> prev = NULL;							
	}

	/*Retorna un aputnador de tipo Node*/
	return n;										
}

/*Función que resetea la DLL*/
static void reset(DLL *this){
	this -> first = this -> last = this -> cursor = NULL;		
	this -> len = 0;											
}

DLL *DLL_New(){

	/*Pide memoria para una una nueva DLL*/
	DLL *list = (DLL*)malloc(sizeof(DLL));

	if(list){									
		reset(list);							
	}

	/*Retorna un apuntador de tipo DLL*/
	return list;								
}

void DLL_Delete(DLL *this){

	/*Comprueba que exista la DLL*/
	if(this){		

		/*Elimina todos los nodos de la DLL*/							
		DLL_MakeEmpty(this);

		/*Elimina a la DLL*/					
		free(this);								
	}
}

bool DLL_InsertBack(DLL *this, Item _data){

	/*Verifica que exista la DLL*/
	assert(this);													

	/**!<Bandera que indica si la inserción fue correcta o no*/
	bool done = false;												

	NodePtr n = newNode(_data);										

	if(n){															
		done = true;												

		/*Ve si esta vacia la DLL*/
		if(DLL_IsEmpty(this)){										
			this -> first = this -> last =this -> cursor = n;		
			this -> len = 1;										
		}else{
			this -> last -> next = n;								
			n -> prev = this -> last;								
			this -> last = n;										
			++this -> len;											
		}
	}

	/*Retorna el valor de la bandera*/
	return done;													
}

bool DLL_InsertFront(DLL *this, Item _data){

	/*Verifica que exista la DLL*/
	assert(this);													

	/**!<Bandera que indica si la inserción fue correcta o no*/
	bool done = false;												

	NodePtr n = newNode(_data);										

	if(n){															
		done = true;												


		/*Ve si esta vacia la DLL*/
		if(DLL_IsEmpty(this)){										
			this -> first = this -> last = this -> cursor = n;		
			this -> len = 1;										
		}else{
			n -> next = this -> first;								
			this -> first -> prev = n;								
			this -> first = n;										
			++this -> len;											
		}
	}

	/*Retorna el valor de la bandera*/
	return done;													
}

bool DLL_InsertAfter(DLL *this, Item _data){

	/*Verifica que exista la DLL*/
	assert(this);													

	/**!<Bandera que indica si la inserción fue correcta o no*/
	bool done = false;												

	/*Ve si al DLL esta vacia y si cursor es igual a last*/
	if(DLL_IsEmpty(this) || this -> cursor == this -> last){		

		/*Hace un insertBack e iguala done al resultado de la función*/
		done = DLL_InsertBack(this, _data);		

	}else{
		NodePtr n = newNode(_data);									

		if(n){														
			done = true;											

			n-> next = this -> cursor -> next;						
			this -> cursor -> next -> prev = n;						
			this -> cursor -> next = n;								
			n -> prev = this -> cursor;								
			++this -> len;											
		}
	}

	/*Retorna el valor de la bandera*/
	return done;													
}

bool DLL_InsertBefore(DLL *this, Item _data){

	/*Verifica que exista la DLL*/
	assert(this);													

	/**!<Bandera que indica si la inserción fue correcta o no*/
	bool done = false;												

	/*Ve si la DLL esta vacia y el cursor es igual a first*/
	if(DLL_IsEmpty(this) || this -> cursor == this -> first){		

		/*Hace un insertFront e iguala done al resultado de la función*/
		done = DLL_InsertFront(this, _data);						
	}else{
		NodePtr n = newNode(_data);									

		if(n){														
			done = true;											
			n -> prev = this -> cursor -> prev;						
			this -> cursor -> prev -> next = n;						
			this -> cursor -> prev = n;								
			n -> next = this -> cursor; 							
			++this -> len;											
		}
	}

	/*Retorna el valor de la bandera*/
	return done;													
}
bool DLL_Remove(DLL *this, ItemPtr _data_back){

	/*Verifica que exista la DLL*/
	assert(this);												

	/**!<Bandera que indica si la eliminación fue correcta o no*/
	bool done = false;											

	/*Ve si la DLL no esta vacia y si el cursor es diferente de NULL*/
	if(!DLL_IsEmpty(this) && NULL != this -> cursor){			
		done = true;											

		/*Ve si el cursor esta en first*/
		if(this -> cursor == this -> first){		

			/*Hace un RemoveFront*/
			DLL_RemoveFront(this, _data_back);		

		/*Ve si el cursor esta en last*/
		}else if(this -> cursor == this -> last){	
			/*Hace un RemoveBack*/			
			DLL_RemoveBack(this ,_data_back);					
		}else{

			/*Retorna el valor del nodo*/
			*_data_back = this -> cursor -> data;				

			/*Crea un apuntador de tipo node llamado left y lo iguala a cursor -> prev*/
			NodePtr left = this -> cursor -> prev;	

			/*Crea un apuntador de tipo node  llamado right y lo iguala a cursor -> next*/			
			NodePtr right = this -> cursor -> next;		

			/*Elimina el nodo en el que esta el cursor*/		
			free(this -> cursor);								

			/*Ve si left y right son diferentes a NULL*/
			if(left == NULL && right == NULL){	

				/*Resetea a la DLL*/				
				reset(this);									
			}else{
				this -> cursor = left;							
				this -> cursor -> next = right;					
				right -> prev = this -> cursor;					
				--this -> len;									
			}
		}
	}

	/*Retorna el valor de la bandera*/
	return done;												
}

bool DLL_RemoveFront(DLL *this, ItemPtr _data_back){

	/*Verifica que exista la DLL*/
	assert(this);										

	/**!<Bandera que indica si la eliminación es correcta o no*/
	bool done = false;									

	/*Ve si la DLL no esta vacia*/
	if(!DLL_IsEmpty(this)){								
		done = true;		

		/*Retorna el valor del nodo*/							
		*_data_back = this -> first -> data;			
		NodePtr tmp = this -> first -> next;			
		free(this -> first);							
		this -> first = tmp;							

		/*Ve que first sea diferente a NULL*/
		if(NULL != this -> first){						
			this -> first -> prev = NULL;				
			--this -> len;								
		}else{	

			/*Resetea la DLL*/
			reset(this);								
		}
	}

	/*Retorna el valor de la bandera*/
	return done;										
}

bool DLL_RemoveBack(DLL *this, ItemPtr _data_back)
{
	/*Verifica que exista la DLL*/
	assert(this);										

	/**!<Bandera que indica si la eliminación es correcta o no*/
	bool done = false;									

	/*Ve si la DLL no esta vacia*/
	if(!DLL_IsEmpty(this)){								
		done = true;	

		/*Retorna el valor del nodo*/								
		*_data_back = this -> last -> data;				
		NodePtr tmp = this -> last -> prev;				
		free(this -> last);								
		this -> last = tmp;								
		if(NULL != this -> last){						
			this -> last -> next = NULL;				
			--this -> len;								
		}else{
			reset(this);								
		}
	}
	
	/*Retorna el valor de la bandera*/
	return done;										

}

bool DLL_RemoveAfter(DLL *this, ItemPtr _data_back){										

	/*Verifica que exista la DLL*/
	assert(this);																			

	/**!<Bandera que indica si la eliminación es correcta o no*/
	bool done = false;																		

	/*Ve que la DLL no este vacia y que el cursor sea diferente de last y que el cursor sea diferente de NULL*/
	if(!DLL_IsEmpty(this) && this -> cursor != this -> last && this -> cursor != NULL)		
	{
		
		done = true;																		
		NodePtr tmp1 = this -> cursor -> next;												
		*_data_back = tmp1 -> data;															
		NodePtr tmp2 = tmp1 -> next;														
		free(tmp1);																			
		this -> cursor -> next = tmp2;														
		
		if(tmp2 != NULL){																	
			tmp2 -> prev = this -> cursor;													
		}else{
			this -> last = this -> cursor;													
		}
		--this -> len;																		
	}

	/*Retorna el valor de la bandera*/
	return done;																			

}

bool DLL_RemoveBefore(DLL *this, ItemPtr _data_back){

	/*Verifica que exista la DLL*/
	assert(this);																			

	/**!<Bandera que indica si la eliminación es correcta o no*/
	bool done = false;																		

	/*Ve que la DLL no este vacia y que el cursor sea diferente a first y que el cursor sea diferente a NULL*/
	if(!DLL_IsEmpty(this) && this -> cursor != this -> first && this -> cursor != NULL)		
	{
		done = true;																		
		NodePtr tmp1 = this -> cursor -> prev;												
		*_data_back = tmp1 -> data;															
		NodePtr tmp2 = tmp1 -> prev;														
		free(tmp1);																			
		this -> cursor -> prev = tmp2;														

		if(tmp2 != NULL){																	
			tmp2 -> next = this -> cursor; 													
		}else{
			this -> first = this -> cursor;													
		}
		--this -> len;																		
	}
	return done;																			
}

size_t DLL_Len(DLL *this){

	/*Verifica que exista la DLL*/
	assert(this);			

	return this -> len;		
}

bool DLL_IsEmpty(DLL *this){

	/*Verifica que exista la DLL*/
	assert(this);					
	return this -> first == NULL;	
}

void DLL_MakeEmpty(DLL *this){

	/*Verifica que exista la DLL*/
	assert(this);		

	/*Bucle que se repite mientras first sea diferente de NULL*/						
	while(NULL != this -> first){				
		NodePtr tmp = this -> first -> next;	
		free(this -> first);					
		this -> first = tmp;					
	}

	/*Resetea la DLL*/
	reset(this);								
}

bool DLL_Peek(DLL *this, ItemPtr _data_back){

	/*Verifica que exista la DLL*/
	assert(this);										

	/**!<Bandera que indica si se pudo observar el nodo*/
	bool done = false;									

	/*Ve si la lista no esta vacia y si el cursor es diferente de NULL*/
	if(!DLL_IsEmpty(this) && this -> cursor != NULL){	

		/*Retorna el valor del Nodo*/
		*_data_back = this -> cursor -> data;			
		done = true;									
	}

	/*Retorna el valor de la bandera*/
	return done;										
}

void DLL_CursorFirst(DLL *this){

	/*Verifica que exista la DLL*/
	assert(this);						

	this -> cursor = this -> first;		
}

void DLL_CursorLast(DLL *this){

	/*Verifica que exista la DLL*/
	assert(this);						
	this -> cursor = this -> last;		
}

void DLL_CursorNext(DLL *this){

	/*Verifica que exista la DLL*/
	assert(this);									
	if(this -> cursor != NULL){						
		this -> cursor = this -> cursor -> next;	
	}
}

void DLL_CursorPrev(DLL *this){

	/*Verifica que exista la DLL*/
	assert(this);									
	if(this -> cursor != NULL){						
		this -> cursor = this -> cursor -> prev;	
	}
}

bool DLL_FindIf(DLL *this, Item _key, bool (*cmp)(Item, Item)){

	/*Verifica que exista la DLL*/
	assert(this);														

	/**!<Bandera que indica si se encontro el Item*/
	bool found = false;													

	/*Bucle que se repite mientras it sea diferente de NULL*/
	for(NodePtr it = this -> first; it != NULL; it = it -> next){	

		/*Llamado a función que compara dos Items*/	
		if(cmp(_key, it -> data)){										
			found = true;												
			break;
		}
	}

	/*Retorna el valor de la bandera*/
	return found;														
}

bool DLL_Search(DLL *this, Item _key, bool (*cmp)(Item, Item)){

	/*Verifica que exista la DLL*/
	assert(this);															

	/**!<Bandera que indica si se encontro el Item*/
	bool found = false;														

	/*Comprueba que la DLL no este vacia*/
	if(!DLL_IsEmpty(this)){				

		/*Bucle que se repite mientras it sea diferente de NULL*/									
		for(NodePtr it = this -> first; it != NULL; it = it -> next){		

			/*Llamado a función que compra Items*/
			if(cmp(_key, it-> data)){										
				found = true;												
				this -> cursor = it;										
				break;
			}
		}
	}
	/*Retorna el valor de la bandera*/
	return found;															

}

void DLL_Traverse(DLL *this, bool (*pfun)(Item)){

	/*Verifica que exista la DLL*/
	assert(this);													

	/*Bucle que se repite mientras it sea diferente de NULL*/
	for(NodePtr it = this -> first; it != NULL; it = it -> next){	

		/*<Llamado a función*/
		pfun(it -> data);											
	}
}

void DLL_TraverseTwo( DLL* this, bool ( *pfun )( ItemPtr ) ){

	/*Verifica qu exista la DLL*/
	 assert( this );													

	 /*Bucle que se repite mientras it sea diferente de NULL*/
	for(NodePtr it = this -> first; it != NULL; it = it -> next ){	

		/*Llamado a función*/	
		pfun( &it -> data );											
	}
}