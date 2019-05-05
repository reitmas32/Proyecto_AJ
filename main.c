#include "Pieces.h"

int main(){
	DLL *Pieces_Black = Initialize(1);
	DLL *Pieces_White = Initialize(0);

	Erease(Pieces_White,Pieces_Black);
}