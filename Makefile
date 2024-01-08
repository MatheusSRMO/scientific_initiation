############
# Exemplo de makefile
# Prof. João Paulo A. Almeida
# Programação OO
#
# A princípio, você não precisa alterar nada, mas aqui assume-se que o diretório atual
# é o diretório onde estão os códigos fonte (.cpp).
#
# nome do compilador
CPP = g++
# opções de compilação
CFLAGS = -Wall -g -lsfml-graphics -lsfml-window -lsfml-system
CPPFLAGS = -std=c++17 
SOURCE_DIR = .
# Obtenha a lista de arquivos-fonte recursivamente
FONTES = $(wildcard $(SOURCE_DIR)/*.cpp $(SOURCE_DIR)/src/**/*.cpp)
# Obtenha a lista de arquivos-objeto preservando a estrutura de diretórios
OBJETOS = $(patsubst $(SOURCE_DIR)/%.cpp,%.o,$(FONTES))
# nome do arquivo executável
EXECUTAVEL = main
############ alvos
#
# use @ antes de todos os comandos, pois é necessário no script de teste
#
# alvo principal é o executável
all: $(EXECUTAVEL)
# para linkar o executável, precisamos dos arquivos-objetos
$(EXECUTAVEL): $(OBJETOS)
	@$(CPP) -o $@ $^
# alvo para cada arquivo-objeto depende do código fonte
# (observação, aqui não estamos capturando as dependências de arquivos .h)
%.o: $(SOURCE_DIR)/%.cpp
	@$(CPP) $(CPPFLAGS) -c $(CFLAGS) $^ -o $@ -O3 

custom:
	g++ -o main main.cpp src/**/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -std=c++17 -Wall -g -O3

clean:
	@rm *.o src/**/*.o $(EXECUTAVEL)