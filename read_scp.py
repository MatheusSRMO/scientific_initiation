import sys
import pulp

pulp.LpSolverDefault.msg = False

def linear_programing(A):
    # Criação do problema
    prob = pulp.LpProblem("Problema_Cobertura_Conjuntos", pulp.LpMinimize)

    # Variáveis de decisão
    conjuntos = range(len(A[0]))
    x = [pulp.LpVariable(f"x_{i}", 0, 1, pulp.LpInteger) for i in conjuntos]

    # Função objetivo
    prob += pulp.lpSum(x), "Total de conjuntos selecionados"

    # Restrições
    for i in range(len(A)):
        prob += pulp.lpSum(A[i][j] * x[j] for j in conjuntos) >= 1, f"Restricao_{i}"

    # Resolvendo o problema
    prob.solve()

    # Verificando o status da solução
    # if pulp.LpStatus[prob.status] == "Optimal":
    solucao = [int(pulp.value(var)) for var in x]
    return solucao
    # else:
    #     return None


def distance_points(x1, y1, x2, y2):
    return ((x2 - x1)**2 + (y2 - y1)**2)**(1/2)

def read_scp(file_path):
    file = open(file_path, "r")
    lines = file.readlines()
    file.close()
    
    name = lines[0].split(":")[1].strip()
    comment = lines[2].split(":")[1].strip()
    dimension = int(lines[3].split(":")[1].strip())
    edges_dimension = int(lines[4].split(":")[1].strip())
    constructions_dimension = int(lines[5].split(":")[1].strip())
    edge_weight_type = lines[6].split(":")[1].strip()
    
    nodes = []
    edges = []
    constructions = []
    
    for i in range(8, 8 + dimension):
        nodes.append(
            (
                int(lines[i].split()[0]),
                float(lines[i].split()[1]),
                float(lines[i].split()[2])
            )
        )
    
    for j in range(i + 2, i + 2 + edges_dimension):       
        edges.append(
            (
                int(lines[j].split()[0]),
                int(lines[j].split()[1])
            )
        )
        
        
    for k in range(j + 2, j + 2 + constructions_dimension):
        constructions.append(
            (
                int(lines[k].split()[0]),
                float(lines[k].split()[1]),
                float(lines[k].split()[2])
            )
        )
    
    return name, comment, dimension, edges_dimension, constructions_dimension, edge_weight_type, nodes, edges, constructions

def construct_coverage_matrix(coverage_radius: int, nodes: list, constructions: list):
    matrix = []
    for construction in constructions:
        matrix.append([])
        for node in nodes:
            if distance_points(construction[1], construction[2], node[1], node[2]) <= coverage_radius:
                matrix[-1].append(1)
            else:
                matrix[-1].append(0)
    return matrix

def print_matrix(matrix):
    for line in matrix:
        print(line)

def print_set(set):
    print("{", end="")
    for i in range(len(set)):
        if i != len(set) - 1:
            print(f"{set[i]}, ", end="")
        else:
            print(f"{set[i]}", end="")
    print("}")

def cont_sets(set):
    cont = 0
    for i in set:
        cont += i
    return cont

def execute(path, coverage_radius):
    (
        name,
        comment,
        dimension,
        edges_dimension,
        constructions_dimension,
        edge_weight_type,
        nodes,
        edges, 
        constructions
    ) = read_scp(path)
    
    A = construct_coverage_matrix(coverage_radius, nodes, constructions)
    _set = linear_programing(A)
    # print_set(_set)
    return cont_sets(_set) if _set != None else 'inf'

def main():
    path_scp = sys.argv[1]
    coverage_radius = int(sys.argv[2])
    print(execute(path_scp, coverage_radius))
    

if __name__ == "__main__":
    main()