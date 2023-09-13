
def calcula_media(notas: list):
    soma = 0

    for nota in notas:
        soma += nota[1] * nota[0]

    return soma / sum(nota[0] for nota in notas)


NOTA_ESPERADA = 8.5

notas = [
    # Notas de 2022.1
    (3, 7.2),
    (4, 8.8),
    (3, 8.9),
    (6, 5.2),

    # Notas de 2022.2
    (4, 6.3),
    (4, 1.7),
    (3, 5.02),
    (4, 1.6),

    # Notas de 2023.1
    (3, 9.43),
    (4, 6.29),
    (4, 6.5),

    # Notas de 2023.2
    (4, NOTA_ESPERADA),
    (4, NOTA_ESPERADA),
    (3, NOTA_ESPERADA),
    (3, NOTA_ESPERADA),

    # # Notas de 2024.1
    # (4, NOTA_ESPERADA),
    # (4, NOTA_ESPERADA),
    # (3, NOTA_ESPERADA),
    # (3, NOTA_ESPERADA),
]

cr = calcula_media(notas)
print(f'CR: {cr:.2f}')
