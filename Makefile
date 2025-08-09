CC = clang 
CFLAGS = -g 

TARGET_EXEC := MarvelousVM

BUILD_DIR := ./build
SRC_DIR := ./src

SRCS := $(shell find $(SRC_DIR) -name '*.c' -or -name '*.s')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I, $(INC_DIRS))

CPPFLAGS := $(INC_FLAGS) -MMD -MP

$(TARGET_EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $(BUILD_DIR)/$(TARGET_EXEC) $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
