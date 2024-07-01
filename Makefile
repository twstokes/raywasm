SRC_DIR 	:= src
BUILD_DIR 	:= build
WASM 	  	:= $(BUILD_DIR)/raytracer.js
CFLAGS		:= -Wall -g

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(subst $(SRC_DIR), $(BUILD_DIR), $(SRCS:.c=.o))

all : $(OBJS) $(WASM)

$(WASM) : $(OBJS) | $(BUILD_DIR)
	@echo "------ Make $(EXE) ------"
	rm -f $(EXE)
	emcc $(CFLAGS) -O3 -g -s EXPORTED_RUNTIME_METHODS='["cwrap"]' -s EXPORTED_FUNCTIONS='["_malloc", "_free"]' -o ${WASM} ${OBJS}

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "------ Make $(@) ------"
	rm -f $@
	emcc $(CFLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*

run: $(WASM)
	emrun index.html
