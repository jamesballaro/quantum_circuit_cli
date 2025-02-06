main = main 

INCLUDE_DIR = include 

SRC_DIR = src

SRCS = $(wildcard $(SRC_DIR)/*.cpp)

OBJS = 	$(SRCS:.cpp=.o)

GCC = g++-11
CXXFLAGS = -Wall -Wextra -std=c++17 -I$(INCLUDE_DIR)

$(main): $(OBJS)
	$(GCC) $(CXXFLAGS) -o $(main) $(OBJS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(GCC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(SRC_DIR)/*.o  $(main)


#g++-11 -o main main.cpp q_circuit.cpp gate_a_base.cpp toolbox.cpp bits.cpp multi_bit_gates.cpp single_bit_gates.cpp complex_custom.cpp matrix.cpp

#./main


















