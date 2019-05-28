#!/usr/bin/env python
# -*- coding: utf-8 -*-


#from Tkinter import * #Python 2.x
from tkinter import * #Python 3.x
import os

"""
Clase tablero
No recibe argumentos y crea un tablero
"""
class Tablero():         #Tablero
    filas = 8               #numero de filas
    columnas = 8            #numero de columnas
    color1 = "#DDB88C"  #es la casilla blanca
    color2 = "#A66D4F"	#es la casilla oscura
    dim_casilla = 48	#Dimension de la casilla
    imagenes = {}           #Diccionario de imagenes para las piezas
    casilla_origen = None   #coordenadas de la pieza a mover
    casilla_destino = None  #coordenadas destino de la pieza
    piezas_dict = {}        #diccionario de piezas

    """
    Funcion que se inicia al momento de crear el objeto.
    Crea el espacio donde ira el tablero y la ventana derecha.
    """
    def __init__(self, raiz):           #funcion que se ejecuta al crear el tablero
        self.raiz = raiz
        self.turno = True
        self._drag_data = {"x": 0, "y": 0, "item": None}        #Coordenadas de la pieza en movimiento

        canvas_width = self.columnas * self.dim_casilla         #anchura de las casillas
        canvas_height = self.filas * self.dim_casilla           #altura de las casillas
        panes = PanedWindow(raiz, bg='grey', width=1.57*canvas_width)	#Espacio controlador donde ira el tablero y la ventana derecha
        panes.pack()
        
        self.canvas = Canvas(panes, width=canvas_width, height=canvas_height) # Espacio para dibujar el tablero
        self.canvas.pack(padx=8, pady=8)
        self.dibuja_Tablero()

        self.ventana_derecha = Canvas(panes,width=canvas_width, height=canvas_height)	# Espacio para agregar instrucciones y botones
        self.ventana_derecha.pack(padx=8, pady=8)

        instrucciones = "\nAJEDREZ\n\nEste juego esta diseñado para\n jugadores expertos en el tema.\n\nNo marca jaque mate.\n\n Pieza tocada es pieza jugada\n\n > Comienzan Blancas\n"

        label = Label(self.ventana_derecha, text=instrucciones,justify=CENTER)	# Etiqueta en la ventana derecha que muestra las instrucciones
        label.grid(row = 0, column = 0,columnspan=2, sticky='nsew')

        restart_button = Button(self.ventana_derecha, text = 'Reinicio', command=lambda:self.restart())	# Boton en la ventana derecha para reiniciar el juego
        restart_button.grid(row = 1, column = 0,sticky='nsew')

        exit_button = Button(self.ventana_derecha, text = 'Salir', command=lambda:exit())	# Boton en la ventana derecha para salir del juego
        exit_button.grid(row = 1, column = 1,sticky='nsew')
        
        panes.add(self.canvas)	#Agregamos el espacio del tablero al controlador
        panes.add(self.ventana_derecha)	#Agregamos el espacio de le ventana derecha al controlador

    """
    Funcion de clase (metodo) que dibuja el tablero en la pantalla.
    """
    def dibuja_Tablero(self):
        self.canvas.delete("area")	#Apuntamos al tablero
        color = self.color1
        for fil in range(self.filas):
            color = self.color1 if color == self.color2 else self.color2 
            for col in range(self.columnas):
                x1 = (col * self.dim_casilla)       #Indicamos las coordenadas iniciales de la casilla (vertice superior izquierdo)
                y1 = ((7 - fil) * self.dim_casilla)

                x2 = x1 + self.dim_casilla  #Indicamos las coordenadas finales de la casilla (vertice inferior derecho)
                y2 = y1 + self.dim_casilla
                
                self.canvas.create_rectangle(x1, y1, x2, y2,  fill=color)  #Creamos el rectángulo y le asignamos un color
                color = self.color1 if color == self.color2 else self.color2 #Cambiamos de color cada vez que se crea un rectangulo


    """
    Metodo que dibuja cada pieza en el tablero.
    """
    def dibuja_piezas(self):
        self.canvas.delete("ocupada")
        for cord, p in self.piezas_dict.items(): #Para cada pieza en el diccionario de piezas:
            x = p['x']
            y = p['y']
            if(x>=0 and y>=0): #Dibujamos solo las piezas que tengas coordenadas positivas
                if p is not None:
                    nom_fichero = "./piezas/%s%s.png" % (p['color'], p['type'])	#Creamos el nombre de la imagen de acuerdo a su color y typo de pieza
                    if p['color'] == 'w' :
                        nom_pieza = "%s%s%s" % (p['type'].upper(), x , y) #Creamos un id con su tipo y coordenadas para rastrear su posicion
                    if p['color'] == 'b' :
                        nom_pieza = "%s%s%s" % (p['type'], x , y)

                    if(nom_fichero not in self.imagenes): #Si la imgen no existe en el diccionario, se agrega
                        self.imagenes[nom_fichero] = PhotoImage(file=nom_fichero)
                    
                    #Creamos un objeto imagen
                    self.obj_imagen = self.canvas.create_image(0,0, image=self.imagenes[nom_fichero], tags=(nom_pieza, "ocupada"), anchor="c")
                    # Indicamos las coordenadas de inicio de la imagen
                    x0 = (y * self.dim_casilla) + int(self.dim_casilla/2)
                    y0 = ((7-x) * self.dim_casilla) + int(self.dim_casilla/2)
                    
                    # Asociamos funciones a las piezas que detectan los eventos del mause sobre ellas 
                    self.canvas.coords(nom_pieza, x0, y0)
                    self.canvas.tag_bind("ocupada", "<ButtonPress-1>", self.on_pieza_presionada)    # Cuando la pieza es presionada
                    self.canvas.tag_bind("ocupada", "<B1-Motion>", self.on_pieza_moviendo)          # Cuando la pieza esta siendo movida
                    self.canvas.tag_bind("ocupada", "<ButtonRelease-1>", self.on_pieza_soltada)     # Cuando la pieza es soltada

    """
    Metodo para crear cada pieza.
    Se crea un diccionario de cada pieza que contiene el color, el tipo de pieza y las coordenadas x,y.
    """
    def crea_piezas(self):
    	pza = 0        # El item de las piezas comienza en 0
    	xe = (0,1,6,7) # Filas de posicion inicial
    	ye = (0,1,2,3,4,5,6,7) # Columnas de posicion inicial
    	tipos = 'tcakqact' #Tipo de piezas en funcion de la columna
    	for x in xe:
    		for y in ye:
    			c = 'w' if pza <16 else 'b' # La mitad de las piezas son blancas y la otra mitad son negras
    			t = 'p' if x==1 or x==6 else tipos[y] # En las filas 1 y 6 solo hay peones
    			self.piezas_dict[pza] = {'color':c, 'type':t, 'x':x, 'y':y} # Agregamos un diccionario de la pieza al diccionario de id de piezas
    			pza += 1 # Aumentamos id
    
    """
    Metodo para saber que la pieza esta presionada y obtener sus coordenadas de origen.
    """
    def on_pieza_presionada(self, event):
        # Obtenemos las coordenadas de origen
        col_tamano = fila_tamano = self.dim_casilla
        seleccionada_columna = event.x // col_tamano
        seleccionada_fila = 7 - (event.y // fila_tamano)
        #Guardamos las coordenadas de origen
        self.casilla_origen = (seleccionada_fila, seleccionada_columna)

        #registramos el tema y su localizacion
        self._drag_data["item"] = self.canvas.find_closest(event.x, event.y)[0]
        self._drag_data["x"] = event.x
        self._drag_data["y"] = event.y

    """
    Metodo que rastrea a la pieza en movimiento y actualiza las coordenas para crear un efecto de dezplazamiento
    """
    def on_pieza_moviendo(self, event):
        if self.casilla_origen == None:     
            self._drag_data["item"] = None      #Reseteamos la informacion del drag
            self._drag_data["x"] = 0
            self._drag_data["y"] = 0
        else:
            # Calculamos cuanto se ha movido el raton
            delta_x = event.x - self._drag_data["x"]
            delta_y = event.y - self._drag_data["y"]
            # Movemos el objeto la distancia adecuada
            self.canvas.move(self._drag_data["item"], delta_x, delta_y)
            # Guardamos la nueva posicion
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
        # Obtenemos la casilla destino
        col_tamano = fila_tamano = self.dim_casilla
        seleccionada_columna = event.x // col_tamano
        seleccionada_fila = 7 - (event.y // fila_tamano)
        # Guardamos la casilla destino
        self.casilla_destino = (seleccionada_fila, seleccionada_columna)
        
        x,y = self.casilla_origen
        id_pza = self.busca_id(x,y)

        #Verificamos el color de la pieza y el turno
        if (self.turno == True and self.piezas_dict[id_pza]['color'] == 'w'): 
            self.movida()
        elif (self.turno == False and self.piezas_dict[id_pza]['color'] == 'b'):
            self.movida()

        self.dibuja_Tablero()   # Dibujamos el Tablero
        self.dibuja_piezas()    # Dibujamos las piezas
        

        # Escribimos el truno en la ventana derecha
        t = 'Blancas' if self.turno == True else 'Negras'
        depositLabel = Message(self.ventana_derecha, text = '\n\nTurno: %s'% t, width = 300, justify=CENTER)         
        depositLabel.grid(row = 2, column = 0, sticky ='nsew',columnspan = 2)
        
    """
    Metodo que realiza la jugada.
    Se ejecuta el programa escrito en C que evalua los archivos y verifica los movimientos de las piezas.
    """
    def movida(self):
        self.jugada() #Actualizamos las coordenadas del juego
        self.imprime_txt('py') #Se imprime el archivo .txt con los id de las piezas y sus coordenadas
        os.system("./Ajedrez.out") #Ejecutamos el programa en C que verifica los movimientos
        self.lee_txt() # Leemos el archivo .txt que devuelve C y acutualizamos las coordenadas
        self.turno = not self.turno 	#Cambiamos el turno

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
        id_pieza = self.busca_id(x,y) # Buscamos el id de la pieza que estaba en la casilla origen
        xx, yy = self.casilla_destino

        self.piezas_dict[id_pieza]['x'] = xx    # Actualizamos las coordenadas de la pieza
        self.piezas_dict[id_pieza]['y'] = yy

    """
    Metodo que lee el archivo .txt devuelto por el programa C y actualiza las coordenadas de las piezas.
    """
    def lee_txt(self):
        c_pza={}            # Creamos un diccionario para guardar las piezas del archivo
        file = open('Ajedrez.c.txt', 'r')
        dataArray = file.read()
        datas = dataArray.split('\n') # Separamos por renglones
        for line in datas:
            if len(line)>1:
                i,x,y = line.split(',') #Separamos el renglon por comas
                c_pza[int(i)] = {'x':int(x), 'y':int(y)} #Guardamos la pieza en el diccionario
        file.close()

        for i in range(32):         # Para cada id
            if i in c_pza:          # Si el id esta en el diccionario 'de C'
                self.piezas_dict[i]['x'] = c_pza[i]['x'] # Actualizamos coordenadas
                self.piezas_dict[i]['y'] = c_pza[i]['y']
            else:                   # Si no esta, significa que fueron comidas
                self.piezas_dict[i]['x'] = -1   # Actualizamos las coordenadas a -1 para que el programa las ignore
                self.piezas_dict[i]['y'] = -1

    """
    Metodo que imprime las piezas en un archivo .txt con el formato id, x, y.
    """
    def imprime_txt(self,name):
        f = open("Ajedrez.%s.txt"%name,"w")
        for i in range(0,len(self.piezas_dict)):
            if i in self.piezas_dict:
                x = self.piezas_dict[i]['x']
                y = self.piezas_dict[i]['y']
                if (x and y) >= 0:      # Imprimimos solo las piezas con coordenadas positivas
                    if i < 10:
                        data = "0%s,%s,%s\n" % (i,x,y)
                    else:
                        data = "%s,%s,%s\n" % (i,x,y)
                    f.write(data)
        f.close()


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
root = Tk()             # Creamos la raiz de la ventana
root.title("Ajedrez")   # Colocamos un titulo
#root.resizable(width=False,height=False) # La ventana no cambia de tamano

"""
Se crea un nuevo tablero.
"""
gui = Tablero(root)     # Creamos un tablero
gui.crea_piezas()       # Creamos las piezas
gui.imprime_txt('c')    # Creamos el archivo c.txt
gui.imprime_txt('py')   # Creamos el archivo py.txt

if __name__ == '__main__':
    gui.dibuja_Tablero()        # Dibujamos el tablero
    gui.dibuja_piezas()         # Dibujamos las piezas

    root.mainloop()             # Bucle para que la ventana no se cierre
