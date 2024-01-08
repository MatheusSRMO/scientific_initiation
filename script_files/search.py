import abc
import numpy as np

""" 
Definimos o parâmetro de limite superior como o número de conjuntos da melhor solução legal atual. Se apenas as operações ADD SET e REMOVE SET forem aplicadas, esse limite superior pode ser usado para restringir a vizinhança durante a busca. Com essa restrição, a operação ADD SET pode ser aplicada na solução atual apenas se o número de conjuntos na solução atual for menor que upperbound−1. O limite superior é calculado a partir da primeira solução legal, que cobre todos os elementos de X. Se a solução legal for aprimorada durante a busca, o parâmetro de limite superior é atualizado automaticamente. A motivação para restringir a vizinhança durante a busca é explicada abaixo.
"""


class AbstractSearch(object):

    __metaclass__ = abc.ABCMeta

    def __init__(self, A: np.ndarray):
        self.A = A
        self.X = [0 for _ in range(len(A[0]))] # solution vector
        self.tabu_list = []
        self.tabu_list_max_size = 10
    
    def get_upper_bound(self):
        return sum(self.X)

    # ADD_SET(S), um conjunto S (que não está em X)/ X = X U S
    def add_set(self, s):
        self.X = np.logical_or(self.X, s)

    # REMOVE_SET(S), um conjunto S (que está em X)/ X = X - S
    def remove_set(self, s):
        self.X = np.logical_and(self.X, np.logical_not(s))

    # SWAP SETS(S1,S2)=REMOVE SET(S1)+ADD SET(S2)
    def swap_sets(self, s1, s2):
        self.remove_set(s1)
        self.add_set(s2)

    def get_neighbors(self, s: list):
        neighbors = []
        for i in range(len(s)):
            s_candidate = s.copy()
            s_candidate[i] = 1 - s_candidate[i]
            neighbors.append(s_candidate)
        return neighbors

    """ 
        Pega o melhor vizinho de s, ou seja, o vizinho que tem o menor custo, respeitando as restrições do problema.
        O vizinho é obtido aplicando uma das operações: ADD_SET, REMOVE_SET ou SWAP_SETS.
        Em caso de empate, a operação é escolhida aleatoriamente.
        Em caso do melhor vizinho ser tabu, é aplicado o critério de aspiração.
    """
    def get_best_neighbor(self, s: list):
        neighbors = self.get_neighbors(s)
        best_neighbor = [neighbors[0]]
        best_cost = self.fitness(best_neighbor[0])
        for neighbor in neighbors[1:]:
            cost = self.fitness(neighbor)
            if cost < best_cost and neighbor not in self.tabu_list[0:self.tabu_list_max_size]:
                # Se for um vizinho melhor que todos os melhores vizinhos anteriores e não estiver na lista tabu
                best_neighbor = [neighbor]
                best_cost = cost
            elif cost == best_cost and neighbor not in self.tabu_list[0:self.tabu_list_max_size]:
                # Se for um vizinho igual ao melhor vizinho anterior e não estiver na lista tabu
                best_neighbor.append(neighbor)
        
        if len(best_neighbor) > 1:
            best_neighbor = best_neighbor[np.random.randint(0, len(best_neighbor))]
        else:
            best_neighbor = best_neighbor[0]
        
        self.tabu_list.append(best_neighbor)
        return best_neighbor

    def get_cost(self, s):
        return sum(s)

    def number_of_uncovered_elements(self, s):
        return sum(self.A.dot(s) == 0)

    # Objetive min this function
    def fitness(self, s): # Fitness = NrOfUncoveredElements + |C|
        return self.get_cost(s) + self.number_of_uncovered_elements(s)

    def all_elements_covered(self, s):
        return self.number_of_uncovered_elements(s) == 0

    def is_feasible(self, solution):
        return self.all_elements_covered(solution)

