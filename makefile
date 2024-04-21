# Compiler to use
CC = g++

# Include path
INCLUDES = -I./headers

# Source files
SOURCES = source/main.cpp source/jeu.cpp

# Output binary
OUTPUT = Connect4Unix

all: $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CC) $(INCLUDES) -o $(OUTPUT) $(SOURCES)

clean:
	rm -f $(OUTPUT)