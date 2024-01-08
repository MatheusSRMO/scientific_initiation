import numpy as np
import random
from search import AbstractSearch
from file_handler import FileHandler

"""
2.6 Selection criteria
A solução é aceita para a próxima iteração com base nos seguintes critérios: a melhor solução (empates são resolvidos aleatoriamente) do entorno torna-se a solução atual na próxima iteração, se não for uma solução tabu. A solução é considerada tabu se for obtida aplicando um dos movimentos ao conjunto que está na lista tabu. Se a melhor solução do entorno for tabu, é aplicado o critério de aspiração. Para os critérios de aspiração, utilizamos uma versão padrão [9], segundo a qual o status tabu de um movimento é ignorado se o movimento tiver uma aptidão melhor do que a solução atual melhor.

O pseudocódigo do algoritmo geral de busca local, que se mostrou o melhor na avaliação experimental, é apresentado abaixo. Este algoritmo utiliza a função de aptidão simples definida na seção 2.3, aplica apenas movimentos ADD SET e REMOV E SET, e faz uso da memória de curto prazo. Além disso, o parâmetro de limite superior é utilizado para reduzir a vizinhança.

Algoritmo de busca local
1. Gerar a solução inicial
2. Inicializar a lista tabu e o parâmetro UPPERBOUND
3. Gerar a vizinhança da solução atual conforme descrito na seção 2.2 (aplicar apenas movimentos ADD SET e REMOV E SET)
4. Avaliar as soluções da vizinhança
5. Selecionar a solução para a próxima iteração (ver seção 2.6)
6. Atualizar a lista tabu e o parâmetro UPPERBOUND
7. Ir para o passo 3 se os critérios de parada não forem atendidos, caso contrário, vá para o passo 8
8. Retornar a melhor solução legal
"""

""" 
double fitness(int** A, int* X, int m, int n) {
    double cont = 0;
    for(int i = 0; i < n; i++) {
        cont += X[i];
    }

    for(int i = 0; i < m; i++) {
        bool covered = false;
        for(int j = 0; j < n; j++) {
            if(A[i][j] == 1 && X[j] == 1) {
                covered = true;
                break;
            }
        }
        cont += !covered;
    }

    return cont;
}"""
def fitness(A, X):
    cont = 0
    for i in range(len(X)):
        cont += X[i]
    for i in range(len(A)):
        covered = False
        for j in range(len(X)):
            if A[i][j] == 1 and X[j] == 1:
                covered = True
                break
        cont += not covered
    return cont


class LocalSearch(AbstractSearch):

    def __init__(self, A):
        super(LocalSearch, self).__init__(A)
        self.n = len(A[0])
        self.m = len(A)

    def greedy_set_cover(self):
        V = np.zeros(self.n, dtype=int)
        print("V: ", V)
        U = np.ones(self.m, dtype=int)
        done = False
        while not done:
            done = True
            max_intersection = 0
            max_set = -1
            for j in range(self.n):
                if V[j] == 0:
                    intersection = 0
                    for i in range(self.m):
                        if U[i] == 1 and self.A[i][j] == 1:
                            intersection += 1
                    if intersection > max_intersection:
                        max_intersection = intersection
                        max_set = j
            if max_set != -1:
                V[max_set] = 1
                for i in range(self.m):
                    if self.A[i][max_set] == 1:
                        U[i] = 0
                done = False
        return list(V)

    def run(self):
        self.tabu_list = []
        self.tabu_list_max_size = 10
        self.upper_bound = self.get_upper_bound()
        self.best_legal_solution = self.X.copy()
        best_neighbor = self.get_best_neighbor(self.X)
        i = 0
        while i < 1e2*3:
            best_neighbor = self.get_best_neighbor(best_neighbor)
            print("fitness: ", self.fitness(best_neighbor), i)
            if self.fitness(best_neighbor) < self.fitness(self.best_legal_solution) and self.is_feasible(best_neighbor):
                i = 0
                self.best_legal_solution = best_neighbor.copy()
                self.upper_bound = self.get_upper_bound()
                self.tabu_list = []
                continue          
            if len(self.tabu_list) > self.tabu_list_max_size:
                self.tabu_list.pop(0)
            i+=1

        return self.best_legal_solution 


if __name__ == "__main__":
    file_reader = FileHandler("OR-Library/scp41.txt")
    A, c = file_reader.process()
    # A = np.array([[1, 0, 1, 0],
    #               [0, 1, 1, 0],
    #               [0, 0, 1, 1],
    #               [1, 0, 0, 1]])
    print("A: ", A)
    local_search = LocalSearch(A)
    # local_search.X = local_search.greedy_set_cover()

    solution = local_search.run()
    print("solution: ", solution, "fitness: ", local_search.fitness(solution))
