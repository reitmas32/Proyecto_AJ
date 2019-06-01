#!/usr/bin/env python
# -*- coding: utf-8 -*-


#from Tkinter import * #Python 2.x
from tkinter import * #Python 3.x
import os

"""
Clase tablero
Recibe la raiz (ventana principal) y crea un tablero.
"""
class Tablero():
    # Numero de filas.
    filas = 8

    # Numero de columnas.
    columnas = 8

    # Color casilla clara.
    color1 = "#DDB88C"

    # Color casilla oscura.
    color2 = "#A66D4F"

    # Dimension de la casilla.
    dim_casilla = 48

    # Diccionario de imagenes para las piezas.
    imagenes = {}

    # Coordenadas de la pieza a mover.     
    casilla_origen = None

    # Coordenadas destino de la pieza.
    casilla_destino = None

    # Diccionario de piezas.
    piezas_dict = {}  

    """
    Funcion que se inicia al momento de crear el objeto.
    Crea el espacio donde ira el tablero y la ventana derecha.
    """
    def __init__(self, raiz):
    	# Definimos a la raiz.
        self.raiz = raiz

        #Se declara el turno.
        self.turno = True

        # Coordenadas de la pieza en movimiento.
        self._drag_data = {"x": 0, "y": 0, "item": None}

        # Ancho de las casillas.
        canvas_width = self.columnas * self.dim_casilla

        # Alto de las casillas.
        canvas_height = self.filas * self.dim_casilla

        # Espacio controlador donde ira el tablero y la ventana derecha.
        panes = PanedWindow(raiz, bg='grey', width=1.57*canvas_width)	
        panes.pack()
        
        # Espacio para dibujar el tablero.
        self.canvas = Canvas(panes, width=canvas_width, height=canvas_height)
        self.canvas.pack(padx=8, pady=8)
        self.dibuja_Tablero()

        # Espacio para agregar instrucciones y botones.
        self.ventana_derecha = Canvas(panes,width=canvas_width, height=canvas_height)	
        self.ventana_derecha.pack(padx=8, pady=8)

        instrucciones = "\nAJEDREZ\n\nEste juego esta diseñado para\n jugadores expertos en el tema.\n\nNo marca jaque mate.\n\n Pieza tocada es pieza jugada\n\n > Comienzan Blancas\n"

        # Etiqueta en la ventana derecha que muestra las instrucciones.
        label = Label(self.ventana_derecha, text=instrucciones,justify=CENTER)
        label.grid(row = 0, column = 0,columnspan=2, sticky='nsew')

        # Boton en la ventana derecha para reiniciar el juego.
        restart_button = Button(self.ventana_derecha, text = 'Reinicio', command=lambda:self.restart())	
        restart_button.grid(row = 1, column = 0,sticky='nsew')

        # Boton en la ventana derecha para salir del juego.
        exit_button = Button(self.ventana_derecha, text = 'Salir', command=lambda:exit())	
        exit_button.grid(row = 1, column = 1,sticky='nsew')
        
        # Agregamos el espacio del tabelero y la ventana derecha al espacio controlador.
        panes.add(self.canvas)
        panes.add(self.ventana_derecha)

    """
    Funcion de clase (metodo) que dibuja el tablero en la pantalla.
    """
    def dibuja_Tablero(self):

    	# Apuntamos al tablero.
        self.canvas.delete("area")
        color = self.color1
        for fil in range(self.filas):
            color = self.color1 if color == self.color2 else self.color2 
            for col in range(self.columnas):

            	# Indicamos las coordenadas iniciales de la casilla (vertice superior izquierdo).
                x1 = (col * self.dim_casilla)      
                y1 = ((7 - fil) * self.dim_casilla)

                # Indicamos las coordenadas finales de la casilla (vertice inferior derecho).
                x2 = x1 + self.dim_casilla  
                y2 = y1 + self.dim_casilla
                
                # Creamos el rectángulo y le asignamos un color.
                self.canvas.create_rectangle(x1, y1, x2, y2,  fill=color)

                # Cambiamos de color cada vez que se crea un rectangulo.
                color = self.color1 if color == self.color2 else self.color2 


    """
    Metodo que dibuja cada pieza en el tablero.
    """
    def dibuja_piezas(self):
        self.canvas.delete("ocupada")

        # Para cada pieza en el diccionario de piezas:
        for cord, p in self.piezas_dict.items():
            x = p['x']
            y = p['y']

            # Dibujamos solo las piezas que tengas coordenadas positivas
            if(x>=0 and y>=0): 
                if p is not None:

                	# Creamos el nombre de la imagen de acuerdo a su color y typo de pieza.
                    nom_fichero = "./piezas/%s%s.png" % (p['color'], p['type'])	
                    
                    # Creamos un id con su tipo y coordenadas para rastrear su posicion.
                    if p['color'] == 'w' :
                        nom_pieza = "%s%s%s" % (p['type'].upper(), x , y) 
                    if p['color'] == 'b' :
                        nom_pieza = "%s%s%s" % (p['type'], x , y)

                    # Si la imgen no existe en el diccionario, se agrega.
                    if(nom_fichero not in self.imagenes):
                        self.imagenes[nom_fichero] = PhotoImage(file=nom_fichero)
                    
                    # Creamos un objeto imagen.
                    self.obj_imagen = self.canvas.create_image(0,0, image=self.imagenes[nom_fichero], tags=(nom_pieza, "ocupada"), anchor="c")

                    # Indicamos las coordenadas de inicio de la imagen.
                    x0 = (y * self.dim_casilla) + int(self.dim_casilla/2)
                    y0 = ((7-x) * self.dim_casilla) + int(self.dim_casilla/2)
                    
                    # Asociamos funciones a las piezas que detectan los eventos del mause sobre ellas.
                    self.canvas.coords(nom_pieza, x0, y0)

                    # Cuando la pieza es presionada.
                    self.canvas.tag_bind("ocupada", "<ButtonPress-1>", self.on_pieza_presionada)

                    # Cuando la pieza esta en movimiento.   
                    self.canvas.tag_bind("ocupada", "<B1-Motion>", self.on_pieza_moviendo)

                    # Cuando la pieza es soltada.     
                    self.canvas.tag_bind("ocupada", "<ButtonRelease-1>", self.on_pieza_soltada)

    """
    Metodo para crear cada pieza.
    Se crea un diccionario de cada pieza que contiene el color, el tipo de pieza y las coordenadas x,y.
    """
    def crea_piezas(self):

    	# El item de las piezas comienza en 0.
    	pza = 0

    	# Filas de posicion inicial.
    	xe = (0,1,6,7)

    	# Columnas de posicion inicial.
    	ye = (0,1,2,3,4,5,6,7)

    	# Tipo de piezas en funcion de la columna (Torre, Caballo, Alfil, Rey, Reina, Alfil, Caballo, Torre)
    	tipos = 'tcakqact' 
    	for x in xe:
    		for y in ye:

    			# La mitad de las piezas son blancas y la otra mitad son negras.
    			color = 'w' if pza <16 else 'b'

    			# En las filas 1 y 6 solo hay peones.
    			tipo = 'p' if x==1 or x==6 else tipos[y]

    			# Agregamos un diccionario de la pieza al diccionario de id de piezas.
    			self.piezas_dict[pza] = {'color':color, 'type':tipo, 'x':x, 'y':y}
    			pza += 1
    
    """
    Metodo para saber que la pieza esta presionada y obtener sus coordenadas de origen.
    """
    def on_pieza_presionada(self, event):

        # Obtenemos las coordenadas de origen.
        col_tamano = fila_tamano = self.dim_casilla
        seleccionada_columna = event.x // col_tamano
        seleccionada_fila = 7 - (event.y // fila_tamano)

        # Guardamos las coordenadas de origen.
        self.casilla_origen = (seleccionada_fila, seleccionada_columna)

        # Registramos el tema y su localizacion.
        self._drag_data["item"] = self.canvas.find_closest(event.x, event.y)[0]
        self._drag_data["x"] = event.x
        self._drag_data["y"] = event.y

    """
    Metodo que rastrea a la pieza en movimiento. 
    Actualiza las coordenas para crear un efecto de dezplazamiento.
    """
    def on_pieza_moviendo(self, event):
        if self.casilla_origen == None:

        	# Reseteamos la informacion del drag. 
            self._drag_data["item"] = None
            self._drag_data["x"] = 0
            self._drag_data["y"] = 0
        else:

            # Calculamos cuanto se ha movido el raton.
            delta_x = event.x - self._drag_data["x"]
            delta_y = event.y - self._drag_data["y"]

            # Movemos el objeto la distancia adecuada.
            self.canvas.move(self._drag_data["item"], delta_x, delta_y)

            # Guardamos la nueva posicion.
            self._drag_data["x"] = event.x
            self._drag_data["y"] = event.y

    """
    Metodo para saber que la pieza ha sido soltada.
    Obtiene las coordenas de destino, verifica el turno y realiza la jugada.
    """
    def on_pieza_soltada(self, event):
        self._drag_data["item"] = None
        self._drag_data["x"] = 0
        self._drag_data["y"] = 0

        # Obtenemos la casilla destino.
        col_tamano = fila_tamano = self.dim_casilla
        seleccionada_columna = event.x // col_tamano
        seleccionada_fila = 7 - (event.y // fila_tamano)

        # Guardamos la casilla destino.
        self.casilla_destino = (seleccionada_fila, seleccionada_columna)
        
        x,y = self.casilla_origen

        # Buscamos el id de la pieza de acuerdo a sus coordenadas de origen.
        id_pza = self.busca_id(x,y)

        # Verificamos el color de la pieza y el turno
        if (self.turno == True and self.piezas_dict[id_pza]['color'] == 'w'): 
            self.movida()
        elif (self.turno == False and self.piezas_dict[id_pza]['color'] == 'b'):
            self.movida()

        self.dibuja_Tablero()
        self.dibuja_piezas()
        

        # Escribimos el truno en la ventana derecha.
        texto = 'Blancas' if self.turno == True else 'Negras'
        depositLabel = Message(self.ventana_derecha, text = '\n\nTurno: %s'% texto, width = 300, justify=CENTER)         
        depositLabel.grid(row = 2, column = 0, sticky ='nsew',columnspan = 2)
        
    """
    Metodo que realiza la jugada.
    Se ejecuta el programa escrito en C que evalua los archivos y verifica los movimientos de las piezas.
    """
    def movida(self):

    	# Actualizamos las coordenadas del juego.
        self.jugada()

        # Se imprime el archivo .txt con los id de las piezas y sus coordenadas.
        self.imprime_txt('py')

        # Ejecutamos el programa en C que verifica los movimientos.
        os.system("./Ajedrez.out")

        # Leemos el archivo .txt que devuelve C y acutualizamos las coordenadas.
        self.lee_txt()

        # Cambiamos el turno
        self.turno = not self.turno

    """
    Metodo que recibe las coordenadas de una pieza y devuelve su id.
    """
    def busca_id(self,x,y):
    	for pieza, val in self.piezas_dict.items():
    		if val['x'] == x and val['y'] == y:
    			return pieza

    """
    Metodo que actualiza las coordenadas del diccionario de piezas despues de que la pieza es soltada.
    """
    def jugada(self):

        x,y = self.casilla_origen

        # Buscamos el id de la pieza que estaba en la casilla origen.
        id_pieza = self.busca_id(x,y)

        xx, yy = self.casilla_destino

        # Actualizamos las coordenadas de la pieza.
        self.piezas_dict[id_pieza]['x'] = xx
        self.piezas_dict[id_pieza]['y'] = yy

    """
    Metodo que lee el archivo .txt devuelto por el programa C y actualiza las coordenadas de las piezas.
    """
    def lee_txt(self):

        # Creamos un diccionario para guardar las piezas del archivo.
        c_pza={}
        file = open('Ajedrez.c.txt', 'r')
        dataArray = file.read()

        # Separamos la informacion por renglones.
        datas = dataArray.split('\n') 
        for line in datas:
            if len(line)>1:

            	# Separamos el renglon por comas.
                i,x,y = line.split(',')

                # Guardamos la pieza en el diccionario.
                c_pza[int(i)] = {'x':int(x), 'y':int(y)}

        file.close()

        for i in range(32):

        	# Si el id esta en el diccionario 'de C'
            if i in c_pza:
            	# Actualizamos coordenadas.
                self.piezas_dict[i]['x'] = c_pza[i]['x']
                self.piezas_dict[i]['y'] = c_pza[i]['y']

            # Si no esta, significa que fueron comidas.
            else:
            	# Actualizamos las coordenadas a -1 para que el programa las ignore.
                self.piezas_dict[i]['x'] = -1
                self.piezas_dict[i]['y'] = -1

    """
    Metodo que imprime las piezas en un archivo .txt con el formato id, x, y.
    Recibe un identificador (.c , .py) para completar el nombre del archivo.
    """
    def imprime_txt(self,name):
        file = open("Ajedrez.%s.txt"%name,"w")

        for i in range(0,len(self.piezas_dict)):

            if i in self.piezas_dict:
                x = self.piezas_dict[i]['x']
                y = self.piezas_dict[i]['y']

                # Imprimimos solo las piezas con coordenadas positivas.
                if (x and y) >= 0:
                    if i < 10:
                        data = "0%s,%s,%s\n" % (i,x,y)
                    else:
                        data = "%s,%s,%s\n" % (i,x,y)
                    file.write(data)
        file.close()


    """
   	Metodo que reinicia el juego.
    """
    def restart(self):
        self.piezas_dict = {}
        self.crea_piezas()
        self.imprime_txt('c')
        self.imprime_txt('py')
        self.turno = True
        self.dibuja_Tablero()
        self.dibuja_piezas()


"""
Ventana principal donde ira el tablero (raiz).
"""
root = Tk()

# Colocamos un titulo.
root.title("Ajedrez")

# La ventana no cambia de tamaño
root.resizable(width=False,height=False)


"""
Se crea un nuevo tablero.
"""
gui = Tablero(root)

# Creamos las piezas.   
gui.crea_piezas()

# Creamos los archivos .txt con las coordenadas de inicio.  
gui.imprime_txt('c')   
gui.imprime_txt('py')

if __name__ == '__main__':
    gui.dibuja_Tablero()
    gui.dibuja_piezas()

    # Bucle para que la ventana no se cierre.
    root.mainloop()             
