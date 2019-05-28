#include "DLL.h"
#include "Pieces.h"

int main()
{
    
    /*Se generan las DLL de cada equipo*/                      
    DLL* WhiteNew=DLL_New();                                                                                           
    DLL* BlackNew=DLL_New();

    /*Los contenidos del archivo Ajedrez.py.txt se guardan en las DLL recien creadas*/
    read_txt_New(WhiteNew,BlackNew);                                                                                   

    /*Se generan dos DLL para comprobar los movimientos*/
    DLL* WhiteOld=DLL_New();                                                                                            
    DLL* BlackOld=DLL_New();

    /*Los contenidos del archivo Ajedrez.c.txt se guardan en las DLL recien creadas*/
    read_txt_Old(WhiteOld,BlackOld);                                                                                    

    /*Llamada a funcion DLL_TraverseThree junto con Compare Coordinates para ver si el movimiento se realizo en las piezas blancas*/
    bool moved=DLL_TraverseThree( WhiteOld, WhiteNew, CompareCoordinates );                                            

    if(moved)                                                                                                           
    {
        /*En caso afirmativo se verifica que sea válido el movimiento*/
        Piece_Move(WhiteOld, BlackOld, WhiteNew->cursor->data.x, WhiteNew->cursor->data.y, WhiteNew->cursor->data.id);  

    }
    else
    {
        /*Llamada a DLL_TraverseThree con el fin de encontrar que pieza negra se movio*/
        DLL_TraverseThree( BlackOld, BlackNew, CompareCoordinates );
        /*Llamada a Piece_move para comprobar que el movimiento sea valido*/
        Piece_Move(WhiteOld, BlackOld, BlackNew->cursor->data.x, BlackNew->cursor->data.y, BlackNew->cursor->data.id);  

    }

    /*Serie de pasos con el fin de borrar el contenido del archivo Ajedrez.c.txt*/
    FILE* open=fopen("Ajedrez.c.txt","w"); 
    fprintf(open,"\n");
    fclose( open ); 

    /*Manda a imprimir en Ajedrez.c.txt la DLL WhiteOld*/
    DLL_Traverse(WhiteOld, print_txt);
    /*Manda a imprimir en Ajedrez.c.txt la DLL BlackOld*/
    DLL_Traverse(BlackOld, print_txt);                                                                                  

    /*Se borran todas las DLL*/
    Erease(WhiteOld,BlackOld);                                                                                          
    Erease(WhiteNew,BlackNew);

    WhiteOld=NULL;                                                                                                      
    BlackOld=NULL;
    WhiteNew=NULL;
    BlackNew=NULL;

    return 0;
}