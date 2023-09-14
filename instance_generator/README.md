# Programa de Conversão de Coordenadas e Visualização de Gráficos

Este programa Python é projetado para converter coordenadas geográficas em coordenadas cartesianas, bem como visualizar gráficos de redes rodoviárias e geometrias de edifícios usando a biblioteca OSMnx. Ele também fornece a capacidade de salvar esses gráficos em arquivos .dot para visualização posterior.

## Requisitos

Para executar este programa, você precisará ter as seguintes dependências instaladas no seu ambiente Python:

- Python 3.x (recomendado)
- numpy
- matplotlib
- networkx
- osmnx
- geopandas
- pyproj

Você pode instalar essas dependências executando o seguinte comando no terminal:

```bash
pip install -r requirements.txt
```

## Como Usar

Para usar este programa, siga estas etapas:

1. Clone ou baixe o repositório em seu computador.

2. Navegue até o diretório do projeto usando o terminal ou prompt de comando.

3. Execute o programa com o seguinte comando, fornecendo o nome de um bairro como argumento:

```bash
python programa.py "Nome do Bairro"
```

**Nota:** Tenha cuidado ao fornecer o nome do bairro como argumento. O programa pode consumir muita memória ou tempo de execução se você fornecer nomes de cidades ou países em vez de nomes de bairros.

4. O programa irá buscar dados de rede rodoviária e geometrias de edifícios para o bairro especificado, converter coordenadas e exibir um gráfico com os resultados.

5. Você também pode encontrar arquivos .dot gerados na pasta "outputs/dot", que podem ser usados para visualização posterior.

## Funções Principais

- `convert_geographic_to_cartesian_vitoria`: Converte coordenadas geográficas para coordenadas cartesianas no sistema de projeção de Vitória.

- `format_place_name`: Formata o nome do local para ser usado como nome de arquivo.

- `convert_geolocation_to_xy`: Converte geolocalização (latitude e longitude) em coordenadas cartesianas.

- `fetch_graph_for_location`: Obtém o gráfico da rede rodoviária para um local específico.

- `fetch_building_geometries`: Obtém geometrias de edifícios para um local específico.

- `extract_centroids_from_geometries`: Extrai centróides de um GeoDataFrame de geometrias.

- `transform_coordinates_to_first_quadrant`: Transforma coordenadas para o primeiro quadrante.

- `transform_graph_coordinates`: Transforma as coordenadas geográficas dos nós do gráfico em coordenadas cartesianas.

- `plot_graph_and_buildings_original`: Plota o gráfico da rede rodoviária e geometrias de edifícios.

- `write_tsp_file`: Escreve o arquivo .tsp contendo coordenadas para nós e edifícios.

- `write_dot_file`: Escreve o arquivo .dot para visualização contendo coordenadas de nós e edifícios.

## Avisos Importantes

- **Cuidado com o Nome do Bairro:** Ao usar o programa, certifique-se de fornecer o nome de um bairro válido. Fornecer nomes de cidades ou países pode resultar em consumo excessivo de memória ou tempo de execução prolongado.

- **Limite de Memória e Tempo de Execução:** Dependendo do tamanho e da complexidade da área especificada, a execução do programa pode levar algum tempo e requerer uma quantidade significativa de memória. Esteja ciente dessas limitações ao usá-lo.

- **Arquivos Gerados:** O programa gera arquivos .dot na pasta "outputs/dot". Certifique-se de verificar essa pasta após a execução para visualizar os resultados.
