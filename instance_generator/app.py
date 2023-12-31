import sys
import math
import numpy as np
import osmnx as ox
import matplotlib.pyplot as plt


CONST_REDUCTION_FACTOR = 16 # for graphviz compression


def get_geographic_coordinates_from_place_name(graph):
    """
    Gets the geographic coordinates (latitude and longitude) from a place name.

    Args:
        place_name (str): The place name to get the coordinates from.

    Returns:
        tuple: A tuple containing the geographic coordinates (latitude, longitude).
    """
    
    # Obtem as cordenadas do nó mais a sudoeste do grafo
    min_latitude = min([node[1]['y'] for node in graph.nodes(data=True)])
    min_longitude = min([node[1]['x'] for node in graph.nodes(data=True)])
    
    return min_latitude, min_longitude

def convert_geographic_to_cartesian_vitoria(graph, latitude, longitude):
    """
    Converts geographic coordinates to cartesian coordinates in the place_name projection.

    Args:
        latitude (float): The latitude in degrees.
        longitude (float): The longitude in degrees.

    Returns:
        tuple: A tuple containing the cartesian coordinates (x, y).
    """
    latitude_reference, longitude_reference = get_geographic_coordinates_from_place_name(graph)
    
    lat_rad = math.radians(latitude)
    lon_rad = math.radians(longitude)
    lat_vitoria_rad = math.radians(latitude_reference)
    lon_vitoria_rad = math.radians(longitude_reference)

    x = (lon_rad - lon_vitoria_rad) * 6378137.0
    y = (lat_rad - lat_vitoria_rad) * 6378137.0

    return x, y

def format_place_name(place_name):
    """
    Formats the place name to be used as a file name.

    Args:
        place_name (str): The place name to format.

    Returns:
        str: The formatted place name.
    """
    return (
        place_name
        .replace(' ', '_')
        .replace(',', '_')
        .replace('.', '_')
        .replace('__', '_')
        .lower()
    )

def convert_geolocation_to_xy(latitude, longitude):
    """
    Converts geolocation (latitude and longitude) to cartesian coordinates.

    Args:
        latitude (float): The latitude in degrees.
        longitude (float): The longitude in degrees.

    Returns:
        tuple: A tuple containing the cartesian coordinates (x, y).
    """
    EARTH_RADIUS = 6378137
    lat_rad = math.radians(latitude)
    lon_rad = math.radians(longitude)
    x = EARTH_RADIUS * lon_rad
    y = EARTH_RADIUS * math.log(math.tan(math.pi / 4 + lat_rad / 2))
    return x, y

def fetch_graph_for_location(place_name):
    """
    Fetches the road network graph for a specific location.

    Args:
        place_name (str): The name of the place to fetch data for.

    Returns:
        networkx.MultiDiGraph: The road network graph.
    """
    return ox.graph_from_place(
        place_name, network_type='drive_service', simplify=True
    )

def fetch_building_geometries(place_name):
    """
    Fetches building geometries for a specific location.

    Args:
        place_name (str): The name of the place to fetch building data for.

    Returns:
        geopandas.GeoDataFrame: Geometries of the buildings.
    """
    return ox.features_from_place(place_name, tags={'building': True})

def extract_centroids_from_geometries(geometries):
    """
    Extracts centroids from a GeoDataFrame of geometries.

    Args:
        geometries (geopandas.GeoDataFrame): Geometries to extract centroids from.

    Returns:
        list: A list of tuples containing centroid coordinates (x, y).
    """
    geometries = geometries.to_crs(epsg=4326)
    geometries['centroid'] = geometries['geometry'].centroid
    return [(geom.x, geom.y) for geom in geometries['centroid']]

def transform_coordinates_to_first_quadrant(graph, coords):
    """
    Transforms coordinates to the first quadrant.

    Args:
        coords (list of tuple): A list of coordinates (latitude, longitude).

    Returns:
        list of tuple: Transformed coordinates (x, y).
    """
    return [convert_geographic_to_cartesian_vitoria(graph, coord[1], coord[0]) for coord in coords]

def transform_graph_coordinates(graph):
    """
    Transforms geographic coordinates of graph nodes to cartesian coordinates.

    Args:
        graph (networkx.MultiDiGraph): The road network graph.

    Returns:
        list of tuple: Transformed coordinates (x, y) for graph nodes.
    """
    return [convert_geographic_to_cartesian_vitoria(graph, node[1]['y'], node[1]['x']) for node in graph.nodes(data=True)]

def plot_graph_and_buildings(coords_buildings, coords_nodes):
    """
    Plots the road network graph and building geometries.

    Args:
        coords_buildings (list of tuple): Building centroid coordinates (x, y).
        coords_nodes (list of tuple): Transformed coordinates (x, y) for graph nodes.
    """
    fig, ax = plt.subplots()
    coords_buildings_array = np.array(coords_buildings)
    ax.scatter(coords_buildings_array[:, 0], coords_buildings_array[:, 1], c='r', s=1)
    coords_nodes_array = np.array(coords_nodes)
    ax.scatter(coords_nodes_array[:, 0], coords_nodes_array[:, 1], c='g', s=1)
    plt.show()

def plot_graph_and_buildings_original(coords_buildings, graph):
    """
    Plots the road network graph and building geometries.

    Args:
        coords_buildings (list of tuple): Building centroid coordinates (x, y).
        graph (networkx.MultiDiGraph): The road network graph.
    """    
    fig, ax = plt.subplots()
    coords_buildings_array = np.array(coords_buildings)
    ax.scatter(coords_buildings_array[:, 0], coords_buildings_array[:, 1], c='r', s=1)

    ox.plot_graph(graph, ax=ax, node_color='g', edge_color='gray', node_size=7)

    plt.show()

def write_tsp_file(place_name, coords_nodes, coords_buildings):
    """
    Writes the .tsp file containing coordinates for nodes and buildings.

    Args:
        place_name (str): The name of the place.
        coords_nodes (list of tuple): Transformed coordinates (x, y) for graph nodes.
        coords_buildings (list of tuple): Building centroid coordinates (x, y).
    """
    formatted_place_name = format_place_name(place_name)

    with open(f'outputs/dot/{formatted_place_name}.tsp', 'w') as file:
        file.write(f'NAME: {place_name}\n')
        file.write('TYPE: TSP\n')
        dimension = len(coords_nodes) + len(coords_buildings)
        file.write('DIMENSION: ' + str(dimension) + '\n')
        file.write('EDGE_WEIGHT_TYPE: EUC_2D\n')
        file.write('NODE_COORD_SECTION\n')

        k = 0
        for i in range(len(coords_nodes)):
            file.write(
                str(i + 1) +
                ' ' +
                str(coords_nodes[i][0]) +
                ' ' +
                str(coords_nodes[i][1]) +
                '\n'
            )
            k += 1

        for i in range(len(coords_buildings)):
            file.write(
                str(k + 1) +
                ' ' +
                str(coords_buildings[i][0]) +
                ' ' +
                str(coords_buildings[i][1]) +
                '\n'
            )
            k += 1

        file.write('FIT\n')

        for i in range(len(coords_nodes)):
            file.write(str(i + 1) + '\n')

        file.write('EOF\n')

def write_dot_file(place_name, graph):
    """
    Writes the .dot file for visualization containing node and building coordinates.

    Args:
        place_name (str): The name of the place.
        coords_nodes (list of tuple): Transformed coordinates (x, y) for graph nodes.
        coords_buildings (list of tuple): Building centroid coordinates (x, y).
    """
    formatted_place_name = format_place_name(place_name)

    with open(f'outputs/dot/{formatted_place_name}.dot', 'w') as file:
        file.write('strict graph {\n')

        map_node_id_to_index = {}
        k = 1
        for node in graph.nodes(data=True):
            latitude, longitude = convert_geographic_to_cartesian_vitoria(graph, node[1]["y"], node[1]["x"])
            latitude /= CONST_REDUCTION_FACTOR
            longitude /= CONST_REDUCTION_FACTOR
            # Escreve os nós do grafo em verde escuro, texto branco, com o um circulo de raio 0.05 em volta do nó
            file.write(f'{k} [pos="{latitude},{longitude}!", color="#006400", fontcolor="#FFFFFF", style=filled, fillcolor="#006400", shape=circle, width=0.005, height=0.005];\n')
            map_node_id_to_index[node[0]] = k
            k += 1
        
        for edge in graph.edges():
            id1 = map_node_id_to_index[edge[0]]
            id2 = map_node_id_to_index[edge[1]]
            file.write(f'{id1} -- {id2};\n')

        file.write('}')

def write_scp_file(place_name, graph, coords_nodes, coords_buildings):
    """
    Writes the .scp file containing coordinates for nodes and buildings.

    Args:
        place_name (str): The name of the place.
        coords_nodes (list of tuple): Transformed coordinates (x, y) for graph nodes.
        coords_buildings (list of tuple): Building centroid coordinates (x, y).
    """
    """
        Format:
        NAME : <string>
        TYPE : SCP
        COMMENT : <string>
        DIMENSION : <int>
        EDGES_DIMENSION : <int>
        CONSTRUCTIONS_DIMENSION : <int>
        EDGE_WEIGHT_TYPE : EUC_2D
        NODE_COORD_SECTION
        <int> <float> <float>
        <int> <float> <float>
        ...
        <int> <float> <float>
        EDGES_SECTION
        <int> <int>
        <int> <int>
        ...
        <int> <int>
        CONSTRUCTIONS_SECTION // id, x, y
        <int> <float> <float>
        <int> <float> <float>
        ...
        <int> <float> <float>
    """
    formatted_place_name = format_place_name(place_name)

    with open(f'../data/scp/{formatted_place_name}.scp', 'w') as file:
        file.write(f'NAME : {place_name}\n')
        file.write('TYPE : SCP\n')
        file.write('COMMENT : \n')
        dimension = len(coords_nodes)
        file.write('DIMENSION : ' + str(dimension) + '\n')
        edges_dimension = len(graph.edges())
        file.write('EDGES_DIMENSION : ' + str(edges_dimension) + '\n')
        file.write('CONSTRUCTIONS_DIMENSION : ' + str(len(coords_buildings)) + '\n')
        file.write('EDGE_WEIGHT_TYPE : EUC_2D\n')
        file.write('NODE_COORD_SECTION\n')
        
        map_node_id_to_index = {}
        k = 1
        for node in graph.nodes(data=True):
            latitude, longitude = convert_geographic_to_cartesian_vitoria(graph, node[1]["y"], node[1]["x"])
            file.write(f'{k} {latitude} {longitude}\n')
            map_node_id_to_index[node[0]] = k
            k += 1

        file.write('EDGES_SECTION\n')

        for edge in graph.edges():
            id1 = map_node_id_to_index[edge[0]]
            id2 = map_node_id_to_index[edge[1]]
            file.write(f'{id1} {id2}\n')

        file.write('CONSTRUCTIONS_SECTION\n')

        for i in range(len(coords_buildings)):
            file.write(
                str(i + 1) +
                ' ' +
                str(coords_buildings[i][0]) +
                ' ' +
                str(coords_buildings[i][1]) +
                '\n'
            )

        file.write('EOF\n')


if __name__ == '__main__':
    place_name = sys.argv[1]

    # Fetch the road network graph for the specific location
    graph = fetch_graph_for_location(place_name)

    # Fetch building geometries
    buildings = fetch_building_geometries(place_name)

    # Extract centroids from the building geometries
    building_centroids = extract_centroids_from_geometries(buildings)

    # Transform coordinates to the first quadrant
    transformed_building_centroids = transform_coordinates_to_first_quadrant(graph, building_centroids)

    # Transform the coordinates of graph nodes
    transformed_graph_nodes = transform_graph_coordinates(graph)

    # Plot the graph and buildings
    plot_graph_and_buildings_original(building_centroids, graph)

    # Write the .tsp and .dot files
    # write_tsp_file(place_name, transformed_graph_nodes, transformed_building_centroids)
    # write_dot_file(place_name, graph)
    write_scp_file(place_name, graph, transformed_graph_nodes, transformed_building_centroids)
