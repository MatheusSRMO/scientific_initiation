import os
import sys
import time
from tabulate import tabulate
from read_scp import execute
from read_scp import get_dimensions

def compile():
    # Executa o Makefile
    os.system("make")

def execute_c(path, range_coverage, algorithm="--greedy"):

    # Executa o main e salva a saida no arquivo temporario
    os.system(f"./main {path} {range_coverage} {algorithm} > temp")
    
    # Abre o arquivo temporario e salva o conteudo em uma variavel
    _file = open("temp", "r")
    content = _file.read()
    _file.close()
    
    # Remove o arquivo temporario
    os.remove("temp")
    
    return int(content.split("\n")[0])

if __name__ == "__main__":
    # Programa para executar os testes de arquivos .c
    # O programa deve receber como parâmetro o caminho para o diretório onde está o .c
    # O programa deve receber como parâmetro o caminho para o diretório onde contem os arquivos de entrada
    # O programa deve receber como parâmetro o caminho para o diretório onde contem os arquivos de saída
    
    # É necessario o uso do Makefile para compilar os arquivos .c
    
    # Pega os parâmetros do terminal
    path_in = sys.argv[1]
    path_out = sys.argv[2]
    range_coverage = float(sys.argv[3])
    algorithms = ["--greedy", "--local_search"]
    
    compile()
    
    # # cria um arquivo temporario para armazenar a saida do main
    # os.system("touch temp")
    
    # Pega todos os arquivos do diretorio de entrada
    files = os.listdir(path_in)
    files.sort()
    
    results = []
    
    for file in files:
        
        path = path_in + "/" + file
        dimensions = get_dimensions(path)
        _results = []
        
        t1 = time.time()
        num_sets_lp = execute(path, range_coverage)
        t2 = time.time()
        time_lp = t2 - t1
        
        _results.append(("linear_programing (py)", dimensions, num_sets_lp, time_lp))
        
        for algorithm in algorithms:
            t1 = time.time()
            # Executa o main e salva a saida no arquivo temporario
            num_sets_c = execute_c(path, range_coverage, algorithm)
            
            t2 = time.time()
            
            time_c = t2 - t1
            _results.append((algorithm.replace("--", ""), dimensions, num_sets_c, time_c))

        results.append((file, _results))
        
    # Tamanho maximo de cada coluna
    max_len = [0, 4, 0, 0]
    for idx, item in enumerate(results):
        arquivo = item[0]
        resultados = item[1]
        for i, resultado in enumerate(resultados):
            algoritmo, dimensions, execucoes, tempo = resultado
            if len(arquivo) > max_len[0]:
                max_len[0] = len(arquivo)
            if len(algoritmo) > max_len[2]:
                max_len[2] = len(algoritmo)
            if len(str(tempo)) > max_len[3]:
                max_len[3] = len(str(tempo))
    
    max_len[0] += 1
    max_len[2] += 1
    max_len[3] += 1
    
    # Montar uma lista de listas para a tabela
    tabela = []
    for idx, item in enumerate(results):
        arquivo = item[0]
        resultados = item[1]
        for i, resultado in enumerate(resultados):
            algoritmo, dimensions, execucoes, tempo = resultado
            if i == 0 and idx != 0:
                tabela.append(
                    ["-" * max_len[0], "-" * max_len[1], "-" * max_len[1], "-" * max_len[1], "-" * max_len[2], "-" * 8, "-" * max_len[3]]
                )
            tabela.append([arquivo, dimensions[0], dimensions[1], dimensions[2], algoritmo, execucoes, tempo])

    # Exibir a tabela
    tab = tabulate(tabela, headers=['Arquivo', 'V', 'C', 'E', 'Algoritmo', 'Esquinas', 'Tempo'], tablefmt='pretty')
    print(tab)
    
    # Salvar a tabela em um arquivo
    _file = open(path_out, "w")
    _file.write(tab)
    _file.close()
    