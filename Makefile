CC 		:= gcc

INCLUDE_DIR 	:= include
SRC_DIR 	:= src
BUILD_DIR 	:= build

CCFLAGS 	:= -Wall -Wextra -O2 -I$(INCLUDE_DIR)

SRCS 		:= $(SRC_DIR)/main.c $(SRC_DIR)/criatura.c $(SRC_DIR)/grafico.c
OBJS 		:= $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
TARGET		:= $(BUILD_DIR)/evolucao

.PHONY: all clean

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $^
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c -o $@ $<

clean :
	rm -rf $(BUILD_DIR)
