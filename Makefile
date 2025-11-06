# --- Variáveis do Compilador ---

# O compilador C++ que usaremos
CXX = g++

# Flags de pré-processador/include:
# -Iheaders/ diz ao g++ para procurar arquivos .h na pasta headers/
CPPFLAGS = -Iheaders/

# Flags de compilação C++:
# -std=c++17 : Usar o padrão C++17
# -Wall -Wextra : Ativar todos os avisos (boas práticas)
# -g : Incluir símbolos de debug (útil se o programa falhar)
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# --- Variáveis do Projeto ---

# Nome do programa executável final
TARGET = main

# Diretório para onde irão os arquivos objeto (.o)
# Isso mantém a pasta raiz limpa
OBJ_DIR = obj

# Lista de todos os arquivos-fonte (.cpp) na pasta src/
# O '\' no final permite quebrar a lista em várias linhas
SRCS = src/main.cpp \
       src/Sistema.cpp \
       src/Registro.cpp \
       src/DataHora.cpp

# Gera a lista de arquivos objeto (.o) correspondentes
# Troca "src/%.cpp" por "obj/%.o"
# Ex: src/main.cpp se torna obj/main.o
OBJS = $(SRCS:src/%.cpp=$(OBJ_DIR)/%.o)

# --- Regras do Make ---

# A regra 'all' é a padrão.
# Ela é executada se você digitar apenas "make".
all: $(TARGET)

# Depende de todos os arquivos objeto (.o).
# -o $@ : O nome do arquivo de saída (o Target, 'meu_programa')
# $^ : Todos os pré-requisitos (todos os .o da lista OBJS)
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

# Regra padrão para compilar um .cpp de 'src/' para um .o em 'obj/'
# Ex: obj/main.o depende de src/main.cpp
$(OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(@D) # Cria o diretório 'obj/' se ele não existir
	@echo "COMPILANDO $< => $@"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Regra para limpar o projeto
clean:
	@echo "LIMPANDO o projeto..."
	rm -f $(TARGET)    # Remove o executável
	rm -rf $(OBJ_DIR)  # Remove o diretório obj/ e tudo dentro dele

# Regra para compilar e executar
run: all
	@echo "--- EXECUTANDO $(TARGET) ---"
	./$(TARGET)