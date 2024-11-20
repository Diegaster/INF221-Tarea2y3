import random
import string

def generar_matriz_unidimensional(archivo, operacion):
    alfabeto = string.ascii_lowercase
    with open(archivo, 'w') as f:
        for char in alfabeto:
            costo = random.randint(1, 9)
            f.write(f'{costo} ')
        f.write("\n") 


def generar_matriz_bidimensional(archivo, operacion):
    alfabeto = string.ascii_lowercase
    with open(archivo, 'w') as f:
        for i in range(26):
            for j in range(26):
                costo = random.randint(1, 9)
                f.write(f'{costo} ')
            f.write("\n")  

generar_matriz_unidimensional("cost_insert.txt", "insert")
generar_matriz_unidimensional("cost_delete.txt", "delete")
generar_matriz_bidimensional("cost_replace.txt", "replace")
generar_matriz_bidimensional("cost_transpose.txt", "transpose")
