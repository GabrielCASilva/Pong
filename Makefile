# Compilador e flags
CC = g++
CFLAGS = -Wall -I/usr/include/raylib -Iinclude -std=c++20
LDFLAGS = -L/usr/lib64
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Diretórios
SRC_DIR = src
BUILD_DIR = build

# Arquivos fonte e objetos
SRCS = $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Alvo principal
TARGET = main

# Configurações do clang-tidy
CLANG_TIDY = clang-tidy
TIDY_CHECKS = -checks='cppcoreguidelines-*, modernize-*, readability-*, performance-*'
TIDY_FLAGS = $(TIDY_CHECKS) --warnings-as-errors='*' -header-filter='.*'

# Regra principal
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Regras para análise estática
tidy: $(SRCS)
	@$(foreach file,$^,\
		echo "Analisando $(file)"; \
		$(CLANG_TIDY) $(file) $(TIDY_FLAGS) -- $(CFLAGS) || true; \
	)

tidy-fix: $(SRCS)
	@$(foreach file,$^,\
		echo "Aplicando correções em $(file)"; \
		$(CLANG_TIDY) $(file) $(TIDY_FLAGS) -fix -- $(CFLAGS) || true; \
	)

# Geração do compile_commands.json
bear: clean
	bear -- make all

# Utilitários
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean-all: clean
	rm -rf .cache compile_commands.json

.PHONY: all tidy tidy-fix clean run bear clean-all
