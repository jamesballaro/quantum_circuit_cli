#ifndef Q_CIRCUIT_H
#define Q_CIRCUIT_H

#include "matrix.h"
#include "toolbox.h"
#include "gate_a_base.h"
#include "component.h"
#include "single_bit_gates.h"
#include "multi_bit_gates.h"
#include "bits.h"
#include <memory>

class q_circuit
{ 
  friend std::ostream& operator<<(std::ostream &output, const q_circuit circuit);

  private:
    int num_qubits;
    int total_bits;
    int state;
    component_matrix components_vector;
    matrix circuit_matrix;
    static std::vector<std::shared_ptr<q_circuit>> saved_circuits;
  public:
    q_circuit() : num_qubits{2}, state{1} {gate_a_base::library_creator();}
    q_circuit(int q, int s) : num_qubits{q}, total_bits{q+1}, state{s}{
      components_vector.resize(total_bits);
      for(int i{0}; i < num_qubits; i++){
        components_vector[i].push_back(toolbox::pair(std::make_shared<qubit>(state)));
      }
      components_vector[num_qubits].push_back(toolbox::pair(std::make_shared<cbit>()));
      matrix A(1<<num_qubits,1<<num_qubits);
      circuit_matrix = A;
      gate_a_base::library_creator();
    }
    ~q_circuit()= default;
    void add_gate();
    void multi_qubit_gate(std::shared_ptr<component> gate, int qubit_range, int num_qubits);
    void series_add(std::string gate_choice, std::shared_ptr<component> gate);
    void parallel_add(std::shared_ptr<component> gate);
    void create_circuit();
    void remove_gate();
    void calculate_circuit_matrix(std::vector<matrix> tensor_vector, int gate_pos);
    void get_circuit_matrix();
    void save();
    void load();
    void add_to_circuit(std::shared_ptr<q_circuit> circuit, int circ_no);
};


#endif