CC := gcc

INCLUDE_DIR := include
SRC_DIR := src
BUILD_DIR := build

CFLAGS := -Wall -Wextra -O2 -I$(INCLUDE_DIR)
SDLFLAGS := $(shell sdl2-config --cflags --libs)

SRCS := $(SRC_DIR)/main.c $(SRC_DIR)/criatura.c $(SRC_DIR)/grafico.c
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

TARGET := $(BUILD_DIR)/evolucao

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(SDLFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(SDLFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)