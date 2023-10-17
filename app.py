import os
import sys
import subprocess





if __name__ == "__main__":
    # Programa para executar os testes de arquivos .c
    # O programa deve receber como parâmetro o caminho para o diretório onde está o .c
    # O programa deve receber como parâmetro o caminho para o diretório onde contem os arquivos de entrada
    # O programa deve receber como parâmetro o caminho para o diretório onde contem os arquivos de saída
    
    # É necessario o uso do Makefile para compilar os arquivos .c
    
    # Pega os parâmetros do terminal
    file_path_c = sys.argv[1]
    path_in = sys.argv[2]
    path_out = sys.argv[3]
    
    # Executa o Makefile
    os.system("make -C " + file_path_c)
    
    # cria um arquivo temporario para armazenar a saida do main
    os.system("touch temp")
    
    # Pega todos os arquivos do diretorio de entrada
    files = os.listdir(path_in)
    print(files)
    
    for file in files:
        # Executa o main e salva a saida no arquivo temporario
        os.system(f"./main {path_in}/{file} 300 > temp")
        
        # Abre o arquivo temporario e salva o conteudo em uma variavel
        file = open("temp", "r")
        content = file.read()
        file.close()
        
        # Remove o arquivo temporario
        os.remove("temp")
        
        print(content)
    
    