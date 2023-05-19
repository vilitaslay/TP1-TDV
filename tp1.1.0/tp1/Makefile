CC = g++
CFLAGS = -std=c++17
INCDIRS =/home/linux/Documents/TD5/herramientas/or-tools_x86_64_Ubuntu-18.04_cpp_v9.6.2534/include/
LIBDIRS = /home/linux/Documents/TD5/herramientas/or-tools_x86_64_Ubuntu-18.04_cpp_v9.6.2534/lib/
SRC = taxi_assignment_instance.cpp taxi_assignment_solution.cpp checker.cpp greedy_solver.cpp taxi_assignment_batching_solver.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = taxi_batching

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -L$(LIBDIRS) -lortools -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -I$(INCDIRS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)