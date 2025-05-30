import datetime
from tkinter import *
from tkinter import messagebox

class Parqueadero:
    def __init__(self, filas=8, columnas=8):
        self.filas = filas
        self.columnas = columnas
        self.tarifa = 50  
        self.vehiculos = {}
        self.inicializar_parqueadero()

    def inicializar_parqueadero(self):
        self.mapa = []
        for i in range(self.filas):
            fila = []
            for j in range(self.columnas):
                if i == 0 or i == self.filas-1 or j == 0 or j == self.columnas-1:
                    fila.append(2)  
                else:
                    fila.append(0)  
            self.mapa.append(fila)
        self.mapa[0][0] = 3  
        self.mapa[self.filas-1][self.columnas-1] = 4  

    def ingresar_vehiculo(self, placa):
        for i in range(self.filas):
            for j in range(self.columnas):
                if self.mapa[i][j] == 0:
                    self.mapa[i][j] = 1
                    hora_entrada = datetime.datetime.now()
                    self.vehiculos[placa] = (i, j, hora_entrada)
                    return True
        return False

    def sacar_vehiculo(self, placa):
        if placa in self.vehiculos:
            i, j, hora_entrada = self.vehiculos[placa]
            self.mapa[i][j] = 0
            hora_salida = datetime.datetime.now()
            minutos = (hora_salida - hora_entrada).total_seconds() / 60
            total = minutos * self.tarifa
            del self.vehiculos[placa]
            return total
        return None

class AppParqueadero:
    def __init__(self, root):
        self.root = root
        self.parqueadero = Parqueadero()
        
        
        self.colores = {
            0: "#1FF526",  
            1: "#FC1100",
            2: "#9E9E9E",  
            3: "#044981",  
            4: "#E00698"   
        }
        
        self.setup_ui()

    def setup_ui(self):
        self.root.title("Parqueadero")
        self.root.geometry("700x600")
        
        
        main_frame = Frame(self.root)
        main_frame.pack(fill=BOTH, expand=True)
        
        control_frame = Frame(main_frame)
        control_frame.pack(side=TOP, fill=X, padx=10, pady=10)
        
        Button(control_frame, text="Ingresar Vehículo", command=self.mostrar_ingreso, 
              bg="#4CAF50", fg="white").pack(side=LEFT, padx=5)
        Button(control_frame, text="Pagar el parqueadero", command=self.mostrar_salida,
              bg="#F44336", fg="white").pack(side=LEFT, padx=5)
        
       
        self.mapa_frame = Frame(main_frame, bg="white")
        self.mapa_frame.pack(fill=BOTH, expand=True, padx=10, pady=10)
        self.actualizar_mapa()

    def actualizar_mapa(self):
        
        for widget in self.mapa_frame.winfo_children():
            widget.destroy()
            
        for i in range(self.parqueadero.filas):
            self.mapa_frame.grid_rowconfigure(i, weight=1)
        for j in range(self.parqueadero.columnas):
            self.mapa_frame.grid_columnconfigure(j, weight=1)
        
        for i in range(self.parqueadero.filas):
            for j in range(self.parqueadero.columnas):
                celda = Frame(self.mapa_frame, 
                             bg=self.colores[self.parqueadero.mapa[i][j]],
                             borderwidth=1, 
                             relief="solid")
                celda.grid(row=i, column=j, sticky="nsew", padx=2, pady=2)
                               
                texto = ""
                if self.parqueadero.mapa[i][j] == 3:
                    texto = "E"
                elif self.parqueadero.mapa[i][j] == 4:
                    texto = "S"
                elif self.parqueadero.mapa[i][j] == 1:
                    
                    for placa, (fi, co, _) in self.parqueadero.vehiculos.items():
                        if fi == i and co == j:
                            texto = placa
                            break
                
                if texto:
                    Label(celda, text=texto, bg=self.colores[self.parqueadero.mapa[i][j]], 
                         fg="white", font=('Arial', 8)).pack(expand=True)

    def mostrar_ingreso(self):
        top = Toplevel(self.root)
        top.title("Ingresar Vehículo")
        top.geometry("300x150")
        
        Label(top, text="Placa del vehículo:").pack(pady=5)
        placa_entry = Entry(top)
        placa_entry.pack(pady=5)
        
        def procesar():
            placa = placa_entry.get().strip().upper()
            if placa:
                if self.parqueadero.ingresar_vehiculo(placa):
                    self.actualizar_mapa()
                    top.destroy()
                else:
                    messagebox.showerror("No hay espacios disponibles")
        
        Button(top, text="Registrar", command=procesar, bg="#4CAF50", fg="white").pack(pady=10)

    def mostrar_salida(self):
        top = Toplevel(self.root)
        top.title("Sacar Vehículo")
        top.geometry("300x150")
        
        Label(top, text="Placa del vehículo:").pack(pady=5)
        placa_entry = Entry(top)
        placa_entry.pack(pady=5)
        
        def procesar():
            placa = placa_entry.get().strip().upper()
            if placa:
                total = self.parqueadero.sacar_vehiculo(placa)
                if total is not None:
                    self.actualizar_mapa()
                    messagebox.showinfo("Pago", f"Total a pagar: ${total:,.0f} COP")
                    top.destroy()
                else:
                    messagebox.showerror("Error", "Vehículo no encontrado")
        
        Button(top, text="Procesar Salida", command=procesar, bg="#F44336", fg="white").pack(pady=10)

if __name__ == "__main__":
    root = Tk()
    app = AppParqueadero(root)
    root.mainloop()