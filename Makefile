FLAGS = -Wall -Werror -g -std=c++14
FILE1 = lab7
FILE2 = Hash
FILE3 = Node

all: $(FILE1)

$(FILE1): $(FILE1).o $(FILE2).o $(FILE3).o
	g++ $(FLAGS) $(FILE1).o $(FILE2).o $(FILE3).o -o $(FILE1)

$(FILE1).o: $(FILE1).cpp
	g++ -c $(FLAGS) $(FILE1).cpp -o $(FILE1).o

$(FILE2).o: $(FILE2).cpp
	g++ -c $(FLAGS) $(FILE2).cpp -o $(FILE2).o

$(FILE3).o: $(FILE3).cpp
	g++ -c $(FLAGS) $(FILE3).cpp -o $(FILE3).o

run: all
	./$(FILE1)

memcheck: all
	valgrind ./$(FILE1)

clean:
	rm -rf *.o $(FILE1)
