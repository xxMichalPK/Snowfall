APP_FILE = $(BIN_DIR)/Snowfall.exe

SRC_DIR = ./src
BIN_DIR = ./bin

INCLUDE_DIR = ./include
LIB_DIR 	= ./lib
RES_DIR		= ./resources

SOURCES = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/**/*.cpp)
RES_FILE = $(BIN_DIR)/resources.res

NO_CONSOLE = -Wl,-subsystem,windows
CXX_FLAGS = -I$(INCLUDE_DIR) -L$(LIB_DIR)
CXX_LIBS  = -lsfml-graphics -lsfml-window -lsfml-system

build: $(APP_FILE)

run: $(APP_FILE)
	$(APP_FILE)

$(RES_FILE): $(SRC_DIR)/resources.rc
	mkdir -p $(@D)
	windres $^ -O coff -o $@

$(APP_FILE): $(SOURCES) $(RES_FILE)
	mkdir -p $(@D)
	g++ $(CXX_FLAGS) $^ -o $@ $(CXX_LIBS)
	cp -r $(LIB_DIR)/* $(BIN_DIR)/
	cp -r $(RES_DIR) $(BIN_DIR)/

.PHONY:
clean:
	rm -rf ./bin