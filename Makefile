# Compiler setup
CXX      := g++
CC       := gcc
AR       := ar
CXXFLAGS := -std=c++20 -Wall -Wextra -O2 -fPIC -Iinclude
CFLAGS   := -std=c17    -Wall -Wextra -O2 -Iinclude
LDFLAGS  := -Lbin -lpadpp

# Paths
SRC_DIR    := src
OBJ_DIR    := obj
BIN_DIR    := bin
BIN_C_DIR  := $(BIN_DIR)/c
BIN_CC_DIR := $(BIN_DIR)/cc
INC_DIR    := include
EX_C_DIR   := examples/c
EX_CC_DIR  := examples/cc

# Library
LIB_NAME   := libpadpp.so
LIB_PATH   := $(BIN_DIR)/$(LIB_NAME)

# Headers for install
HDR_DIRS   := padpp padpp-c
INSTALL_INC_DIR := /usr/include
INSTALL_LIB_DIR := /usr/lib

# Sources
CXX_SRCS   := $(wildcard $(SRC_DIR)/*.cc)
CXX_OBJS   := $(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o,$(CXX_SRCS))

# Examples
C_EXAMPLES   := $(wildcard $(EX_C_DIR)/*.c)
C_EXECS      := $(patsubst $(EX_C_DIR)/%.c,$(BIN_C_DIR)/%,$(C_EXAMPLES))

CC_EXAMPLES  := $(wildcard $(EX_CC_DIR)/*.cc)
CC_EXECS     := $(patsubst $(EX_CC_DIR)/%.cc,$(BIN_CC_DIR)/%,$(CC_EXAMPLES))

.PHONY: all clean install uninstall

all: $(LIB_PATH) $(C_EXECS) $(CC_EXECS)

# Object files
$(OBJ_DIR):
	mkdir -p $@

$(BIN_DIR) $(BIN_C_DIR) $(BIN_CC_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Shared library
$(LIB_PATH): $(CXX_OBJS) | $(BIN_DIR)
	$(CXX) -shared -o $@ $^

# C example binaries
$(BIN_C_DIR)/%: $(EX_C_DIR)/%.c $(LIB_PATH) | $(BIN_C_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# C++ example binaries
$(BIN_CC_DIR)/%: $(EX_CC_DIR)/%.cc $(LIB_PATH) | $(BIN_CC_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

# Install to system
install: $(LIB_PATH)
	install -Dm755 $(LIB_PATH) $(DESTDIR)$(INSTALL_LIB_DIR)/$(LIB_NAME)
	@for dir in $(HDR_DIRS); do \
		install -d $(DESTDIR)$(INSTALL_INC_DIR)/$$dir; \
		cp -r include/$$dir/*.h $(DESTDIR)$(INSTALL_INC_DIR)/$$dir/; \
	done

# Uninstall
uninstall:
	rm -f $(DESTDIR)$(INSTALL_LIB_DIR)/$(LIB_NAME)
	@for dir in $(HDR_DIRS); do \
		rm -rf $(DESTDIR)$(INSTALL_INC_DIR)/$$dir; \
	done

# Clean all
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
