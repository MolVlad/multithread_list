CC=g++ -std=c++17 -Ofast
LIBS=-pthread
OPT_FLAGS=-march=native
INC=-I./include
SRC_DIR=./source
SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)
OUT=a.out

.PHONY: debug run compile memory clean

run:
	$(CC) $(OPT_FLAGS) $(INC) -o $(OUT) $(SRC_FILES) $(LIBS)
	./$(OUT)

debug:
	$(CC) $(OPT_FLAGS) -DDEBUG $(INC) -o $(OUT) $(SRC_FILES) $(LIBS)
	./$(OUT)

compile:
	$(CC) $(OPT_FLAGS) $(INC) -o $(OUT) $(SRC_FILES) $(LIBS)

memory:
	$(CC) -g $(INC) -o $(OUT) $(SRC_FILES) $(LIBS)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(OUT)

clean:
	rm -f callgrind.out* a.out perf.data perf.data.old

