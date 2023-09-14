import sys
import math
import numpy as np
import osmnx as ox
import matplotlib.pyplot as plt


def convert_geographic_to_cartesian_vitoria(latitude, longitude):
    """
    Converts geographic coordinates to cartesian coordinates in the Vitoria projection.

    Args:
        latitude (float): The latitude in degrees.
        longitude (float): The longitude in degrees.

    Returns:
        tuple: A tuple containing the cartesian coordinates (x, y).
    """
    latitude_vitoria = -20.3155  # Latitude de Vitória
    longitude_vitoria = -40.3128  # Longitude de Vitória

    lat_rad = math.radians(latitude)
    lon_rad = math.radians(longitude)
    lat_vitoria_rad = math.radians(latitude_vitoria)
    lon_vitoria_rad = math.radians(longitude_vitoria)

    x = (lon_rad - lon_vitoria_rad) * 6378137.0 / 16 * math.cos(lat_vitoria_rad)
    y = (lat_rad - lat_vitoria_rad) * 6378137.0 / 16 * math.cos(lat_vitoria_rad)

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
    return ox.graph_from_place(place_name, network_type='all_private')

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

def transform_coordinates_to_first_quadrant(coords):
    """
    Transforms coordinates to the first quadrant.

    Args:
        coords (list of tuple): A list of coordinates (latitude, longitude).

    Returns:
        list of tuple: Transformed coordinates (x, y).
    """
    return [convert_geographic_to_cartesian_vitoria(coord[1], coord[0]) for coord in coords]

def transform_graph_coordinates(graph):
    """
    Transforms geographic coordinates of graph nodes to cartesian coordinates.

    Args:
        graph (networkx.MultiDiGraph): The road network graph.

    Returns:
        list of tuple: Transformed coordinates (x, y) for graph nodes.
    """
    return [convert_geographic_to_cartesian_vitoria(node[1]['y'], node[1]['x']) for node in graph.nodes(data=True)]

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

        for node in graph.nodes(data=True):
            latitude, longitude = convert_geographic_to_cartesian_vitoria(node[1]["y"], node[1]["x"])
            file.write(f'{node[0]} [pos="{latitude},{longitude}!"];\n')
        for edge in graph.edges():
            file.write(f'{edge[0]} -- {edge[1]};\n')

        file.write('}')


if __name__ == '__main__':
    place_name = sys.argv[1]

    # Fetch the road network graph for the specific location
    graph = fetch_graph_for_location(place_name)

    # Fetch building geometries
    buildings = fetch_building_geometries(place_name)

    # Extract centroids from the building geometries
    building_centroids = extract_centroids_from_geometries(buildings)

    # Transform coordinates to the first quadrant
    transformed_building_centroids = transform_coordinates_to_first_quadrant(building_centroids)

    # Transform the coordinates of graph nodes
    transformed_graph_nodes = transform_graph_coordinates(graph)

    # Plot the graph and buildings
    plot_graph_and_buildings_original(building_centroids, graph)

    # Write the .tsp and .dot files
    # write_tsp_file(place_name, transformed_graph_nodes, transformed_building_centroids)
    write_dot_file(place_name, graph)
