import math
import osmnx as ox
import networkx as nx
import geopandas as gpd
import matplotlib.pyplot as plt

latitude_vitoria = -20.297617
longitude_vitoria = -40.295776


# Defina o local que você está interessado
place_name = "Jardim da Penha, Vitoria, ES, Brasil"

# Obtém o grafo de rede para a área específica
graph = ox.graph_from_place(place_name, network_type='all_private')
# print(graph)

# Plotar o grafo
# fig, ax = ox.plot_graph(graph)



def transform_cors_to_xy(latitude, longitude):
    # Define o ponto central do mapa
    latitude_vitoria = -20.3155  # Latitude de Vitória, por exemplo
    longitude_vitoria = -40.3128  # Longitude de Vitória, por exemplo

    # Defina a projeção do mapa (EPSG:3857 - Mercator)
    crs = {'init': 'epsg:3857'}

    # Converta latitude e longitude para radianos
    lat_rad = math.radians(latitude)
    lon_rad = math.radians(longitude)
    lat_vitoria_rad = math.radians(latitude_vitoria)
    lon_vitoria_rad = math.radians(longitude_vitoria)

    # Calcule as coordenadas XY
    x = (lon_rad - lon_vitoria_rad) * 6378137.0 / 16 * math.cos(lat_vitoria_rad)
    y = (lat_rad - lat_vitoria_rad) * 6378137.0 / 16 * math.cos(lat_vitoria_rad)

    return x, y


# Escrever um arquivo .dot para o grafo com as coordenadas dos nós
with open("graph.dot", "w") as f:
    f.write('strict graph {\n')

    for node in graph.nodes(data=True):
        latitude, longitude = transform_cors_to_xy(node[1]["y"], node[1]["x"])
        f.write(f'{node[0]} [pos="{latitude},{longitude}!"];\n')
    for edge in graph.edges():
        f.write(f'{edge[0]} -- {edge[1]};\n')

    f.write('}')
