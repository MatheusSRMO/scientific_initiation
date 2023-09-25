import pulp

# Crie um problema PLI
problem = pulp.LpProblem("PLI", pulp.LpMinimize)  # Como não há custos, usamos LpMinimize apenas por conveniência

# Defina as variáveis binárias
num_vars = 10
x = [pulp.LpVariable(f"x{i}", cat=pulp.LpBinary) for i in range(1, num_vars + 1)]

# Defina as restrições
A = [
    [1, 1, 1, 1, 1, 0, 0, 0, 0, 0],
    [1, 0, 0, 0, 0, 1, 1, 1, 1, 1],
    [1, 1, 1, 0, 0, 0, 0, 1, 1, 1],
    [1, 0, 0, 0, 1, 1, 1, 0, 0, 0],
    [1, 0, 1, 1, 1, 1, 1, 0, 1, 0],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
]

b = [1, 1, 1, 1, 1, 1]

for i in range(len(b)):
    problem += pulp.lpSum(A[i][j] * x[j] for j in range(num_vars)) == b[i]

# Resolva o problema
problem.solve()

# Imprima a solução
print("Status:", pulp.LpStatus[problem.status])
for i in range(num_vars):
    print(f"x{i + 1} =", int(x[i].value()))
