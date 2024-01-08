
# nome do compilador
CPP = g++
# opções de compilação
CFLAGS = -Wall -g -lsfml-graphics -lsfml-window -lsfml-system -O3
CPPFLAGS = -std=c++17 
SOURCE_DIR = .

# Obtenha a lista de arquivos-fonte recursivamente
FONTES = $(wildcard $(SOURCE_DIR)/*.cpp $(SOURCE_DIR)/src/**/*.cpp)

# Obtenha a lista de arquivos-objeto preservando a estrutura de diretórios
OBJETOS = $(patsubst $(SOURCE_DIR)/%.cpp,%.o,$(FONTES))

# nome do arquivo executável
EXECUTAVEL = main

############ alvos

# alvo principal é o executável
all: $(EXECUTAVEL)

# para linkar o executável, precisamos dos arquivos-objetos
$(EXECUTAVEL): $(OBJETOS)
	@$(CPP) -o $@ $^ $(CFLAGS)

# alvo para cada arquivo-objeto depende do código fonte
# (observação, aqui não estamos capturando as dependências de arquivos .h)
%.o: $(SOURCE_DIR)/%.cpp
	@$(CPP) $(CPPFLAGS) -c $(CFLAGS) $^ -o $@ 

# alvo para limpar os arquivos-objeto e o executável
clean:
	@rm *.o src/**/*.o $(EXECUTAVEL)

# alvo para executar o programa
run:
	make
	@./$(EXECUTAVEL)