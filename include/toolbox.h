#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "matrix.h"
#include "component.h"
#include "single_bit_gates.h"
#include "multi_bit_gates.h"
#include "bits.h"
#include <memory>


using circuit_element = std::pair<std::vector<int>,std::shared_ptr<component>>;
using bit_row = std::vector<circuit_element>;
using component_matrix = std::vector<bit_row>;

namespace toolbox{
    //Convert to uppercase
    std::string to_upper(std::string& string);
    //Verify integer input
    int int_verifier(const std::string& integer);
    //Extract qubit selection for single and multiple qubits
    int extract_number(const std::string& input);
    std::vector<int> extract_number(const std::string& input, int num_qubits);
    //Longest element in a given vector containing any type
    template<typename T>
    size_t longest_element(const std::vector<std::vector<T>>& vector);
	//Last element in vector that is a gate (not identity)
	size_t last_gate(bit_row components);

    //Circuit matrix tools:
    //Recursive tensor product (for a column of gates in parallel)
    void recursive_tensor_product(const component_matrix& components_vector, int num_qubits, int bit_position, int gate_position, matrix& gate_tensor);
    //Recursive matrix multiplication (for a series of tensor products (gates in series))
    void recursive_matrix_multiplication(std::vector<matrix>& tensor_vector, size_t index, matrix& matrix_product);
    //Pair creator
	circuit_element pair(std::vector<int> qubit_choice, std::shared_ptr<component> gate);
	circuit_element pair(std::shared_ptr<component> gate);
}

template<typename T>
size_t toolbox::longest_element(const std::vector<std::vector<T>>& vector) 
{
  size_t maxLength{0};
  for(const auto& innerVec : vector){
    if(innerVec.size() > maxLength){
      maxLength = innerVec.size();
    }
  }
  return maxLength;
}

#endif