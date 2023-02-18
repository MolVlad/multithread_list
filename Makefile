CC=g++ -std=c++17 -Ofast
LIBS=-pthread
OPT_FLAGS=-march=native
INC=-I./include
SRC_DIR=./source
SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)
OUT=a.out
VALGRING_FLAGS=--leak-check=full --show-leak-kinds=all --track-origins=yes --fair-sched=yes

.PHONY: debug run compile memory clean

run:
	$(CC) $(OPT_FLAGS) -DNOPRINT $(INC) -o $(OUT) $(SRC_FILES) $(LIBS)
	./$(OUT)

print:
	$(CC) $(OPT_FLAGS) -DLIST_SIZE=30 $(INC) -o $(OUT) $(SRC_FILES) $(LIBS)
	./$(OUT)

real_random:
	$(CC) $(OPT_FLAGS) -DREAL_RANDOM -DLIST_SIZE=30 $(INC) -o $(OUT) $(SRC_FILES) $(LIBS)
	./$(OUT)

debug:
	$(CC) $(OPT_FLAGS) -DDEBUG $(INC) -o $(OUT) $(SRC_FILES) $(LIBS)
	./$(OUT)

compile:
	$(CC) $(OPT_FLAGS) $(INC) -o $(OUT) $(SRC_FILES) $(LIBS)

memory:
	$(CC) -g -DLIST_SIZE=100000 -DNOPRINT $(INC) -o $(OUT) $(SRC_FILES) $(LIBS)
	valgrind $(VALGRING_FLAGS) ./$(OUT)

clean:
	rm -f a.out 
