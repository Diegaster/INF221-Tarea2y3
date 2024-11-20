import random
import string

def generar_cadena_aleatoria(n):
    return ''.join(random.choices(string.ascii_lowercase, k=n))

def generar_cadena_similar(cadena, longitud):
    cadena_lista = list(cadena)
    
    if len(cadena) > longitud:
        cadena_lista = cadena_lista[:longitud]
    
    elif len(cadena) < longitud:
        faltantes = longitud - len(cadena)
        cadena_lista += random.choices(string.ascii_lowercase, k=faltantes)
    
    random.shuffle(cadena_lista)
    return ''.join(cadena_lista) 

def generar_datos_prueba(longitud_1, longitud_2):
    with open("cadenas1.txt", "w") as archivo1, \
        open("cadenas2.txt", "w") as archivo2:
        for _ in range(10):
            cadena_aleatoria_1 = generar_cadena_aleatoria(longitud_1)
            cadena_aleatoria_2 = generar_cadena_aleatoria(longitud_2)
            archivo1.write(f"{cadena_aleatoria_1} ")
            archivo2.write(f"{cadena_aleatoria_2} ")

        for _ in range(10):
            cadena_similar_1 = generar_cadena_aleatoria(longitud_1)
            cadena_similar_2 = generar_cadena_similar(cadena_similar_1, longitud_2)
            archivo1.write(f"{cadena_similar_1} ")
            archivo2.write(f"{cadena_similar_2} ")

if __name__ == "__main__":
    longitud_1 = int(input("Introduce la longitud de las cadenas a: "))
    longitud_2 = int(input("Introduce la longitud de las cadenas b: "))
    generar_datos_prueba(longitud_1, longitud_2)
    print(f"Datos de prueba generados y guardados en 'cadenas1.txt' y 'cadenas2.txt'.")
