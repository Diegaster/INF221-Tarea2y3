
def leer_datos(archivo):
    tiempos_fuerza_bruta = {"vacíos": [], "aleatorios": [], "similares": []}
    tiempos_dp = {"vacíos": [], "aleatorios": [], "similares": []}
    
    with open(archivo, 'r') as file:
        lineas = file.readlines()
    

    seccion = None
    

    for linea in lineas:
        if "-----" in linea: 
            if "Cadenas vacÃ­as" in linea:
                seccion = "vacíos"
            elif "Cadenas aleatoriamente distintas entre sÃ" in linea:
                seccion = "aleatorios"
            elif "Cadenas similares" in linea:
                seccion = "similares"
        elif seccion:  
            if "(Fuerza Bruta)" in linea:
                
                try:
                   
                    tiempo_fb = int(linea.split(":")[-1].strip().split()[0])  
                    print(f"Tiempo de Fuerza Bruta detectado: {tiempo_fb}")  
                    tiempos_fuerza_bruta[seccion].append(tiempo_fb)
                except ValueError:
                    print(f"Linea ignorada (no es un tiempo de Fuerza Bruta): {linea}")  
            elif "(DP)" in linea:
                
                try:
                    
                    tiempo_dp = int(linea.split(":")[-1].strip().split()[0])  
                    print(f"Tiempo de DP detectado: {tiempo_dp}")  
                    tiempos_dp[seccion].append(tiempo_dp)
                except ValueError:
                    print(f"Linea ignorada (no es un tiempo de DP): {linea}")  
    
    return tiempos_fuerza_bruta, tiempos_dp


def calcular_promedio(tiempos):
    if len(tiempos) == 0:
        return 0  
    return sum(tiempos) / len(tiempos)


def calcular_promedios(archivo):
    tiempos_fuerza_bruta, tiempos_dp = leer_datos(archivo)
    
    for caso in tiempos_fuerza_bruta:
        promedio_fb = calcular_promedio(tiempos_fuerza_bruta[caso])
        promedio_dp = calcular_promedio(tiempos_dp[caso])
        
        if promedio_fb == 0:
            print(f"No se encontraron datos de Fuerza Bruta para el caso {caso}.")
        else:
            print(f"Promedio de Fuerza Bruta para el caso {caso}: {promedio_fb} ns")
        
        if promedio_dp == 0:
            print(f"No se encontraron datos de DP para el caso {caso}.")
        else:
            print(f"Promedio de DP para el caso {caso}: {promedio_dp} ns")
        
        print()

archivo = 'datos.txt'

calcular_promedios(archivo)
