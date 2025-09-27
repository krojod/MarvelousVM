CC = clang 
CFLAGS = -g 

TARGET_EXEC := MarvelousVM
TEST_EXEC := TestVM

MAIN_FILE := main.c

BUILD_DIR := ./build
SRC_DIR := ./src
TEST_DIR := ./test

SRCS := $(shell find $(SRC_DIR) -name '*.c' -or -name '*.s')
TESTS := $(shell find $(TEST_DIR) -name '*.c')
TESTSOURCE := $(shell find $(SRC_DIR) -not -name '$(MAIN_FILE)' -name '*.c' -or -name '*.s')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
TESTS_OBJS := $(TESTS:%=$(BUILD_DIR)/%.o)
TESTSOURCE_OBJS := $(TESTSOURCE:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I, $(INC_DIRS))

CPPFLAGS := $(INC_FLAGS) -MMD -MP -Wall

CUNITFLAG := -lcunit

test: clean $(TESTS_OBJS) $(TESTSOURCE_OBJS)
	$(CC) $(TESTS_OBJS) $(TESTSOURCE_OBJS) -o $(BUILD_DIR)/$(TEST_EXEC) $(LDFLAGS) $(CUNITFLAG)
	$(BUILD_DIR)/$(TEST_EXEC)

$(TARGET_EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $(BUILD_DIR)/$(TARGET_EXEC) $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
