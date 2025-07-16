def pesqBinaria(lista, numero, menor, maior):
    resp = False
    meio = (maior + menor) // 2
    
    if menor > maior:
        return False 
    
    if numero == lista[meio]:
        resp = True
        return resp
        
    elif numero > lista[meio]:
        return pesqBinaria(lista, numero, meio + 1, maior)
     
    else:   
         return pesqBinaria(lista, numero, menor, meio - 1)
         
    return resp


lista = [1,2,3,4,5,6,7,8]
numero = 5
menor = 0
maior = len(lista) - 1
meio = (maior + menor)/2
resposta = pesqBinaria(lista, numero, menor, maior)
print(resposta)