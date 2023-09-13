import osmnx as ox
import networkx as nx
import geopandas as gpd
import matplotlib.pyplot as plt
DISTANCIA_MAXIMA = 50


def transformar_para_primeiro_quadrante(coordenadas):
    # Encontrar os menores valores de x e y
    min_x = min(coordenadas, key=lambda item: item[0])[0]
    min_y = min(coordenadas, key=lambda item: item[1])[1]

    # Subtrair os menores valores de x e y de todas as coordenadas
    pontos_transformados = [(x - min_x, y - min_y) for x, y in coordenadas]

    return pontos_transformados


# Defina o local que você está interessado
place_name = "Jardim da Penha, Vitoria, ES, Brasil"

# Obtém o grafo de rede para a área específica
graph = ox.graph_from_place(place_name, network_type='all_private')
# print(graph)

# Plotar o grafo
fig, ax = ox.plot_graph(graph)

residencias = ox.geometries_from_place(
    place_name, tags={'building': True}
)

# Extrair os centroides das residências
residencias['centroid'] = residencias['geometry'].centroid

# Plotar os centroides como pontos
fig, ax = plt.subplots(figsize=(10, 10))
residencias['centroid'].plot(ax=ax, markersize=5, color='b', alpha=0.7)
plt.title('Centroides das Residências')
plt.xlabel('Longitude')
plt.ylabel('Latitude')
plt.grid(False)
plt.show()


with open('grafo.tsplib', 'w') as f:
    f.write("TYPE: TSP\n")
    f.write(f"DIMENSION: {len(graph.nodes)}\n")
    f.write("EDGE_WEIGHT_TYPE: GEO\n")
    f.write("EDGE_WEIGHT_FORMAT: FUNCTION\n")
    f.write("EDGE_WEIGHT_FUNCTION: GEO\n")
    f.write("DISPLAY_DATA_TYPE: TWOD_COORDS\n")
    f.write("NODE_COORD_SECTION\n")

    for node in graph.nodes(data=True):
        f.write(f"{node[0]} {node[1]['y']} {node[1]['x']}\n")

    f.write("EOF\n")
