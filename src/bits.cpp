#include "bits.h"
void qubit::set_qu_operator()
{
 
  std::vector<std::complex<double>> qubit_data = {{1, 0},{0, 0}};
  qu_operator.set_data(qubit_data);
}
void qubit::set_qu_operator(int choice)
{
  std::vector<std::complex<double>> qubit_data;
  if(choice == 1){
    qubit_data = {{1, 0},{0, 0}};
  }
  else if(choice == 2){
    qubit_data = {{0, 0},{1, 0}};
  }
  qu_operator.set_data(qubit_data);
}
std::string qubit::get_symbol()
{
  return "q";
}
std::string qubit::get_type()
{
	return "Quantum Bit";
}

void cbit::set_qu_operator()
{
  std::vector<std::complex<double>> cbit_data = {{0, 0}};
  qu_operator.set_data(cbit_data);
}
std::string cbit::get_symbol()
{
  return"c";
}
std::string cbit::get_type()
{
	return "Classical Bit";
}

std::string control_ccx::get_type()
{
  return "CCX";
}
void control_ccx::set_qu_operator()
{
  std::vector<std::complex<double>> control_data = {{1, 0}};
  qu_operator.set_data(control_data); 
}
std::string control_ccx::get_symbol()
{
  return "•";
}

void control_swap::set_qu_operator()
{
  std::vector<std::complex<double>> control_data = {{1, 0}};
  qu_operator.set_data(control_data); 
}
std::string control_swap::get_type()
{
  return "SWAP";
}
std::string control_swap::get_symbol()
{
  return "x";
}

void control_cz::set_qu_operator()
{
  std::vector<std::complex<double>> control_data = {{1, 0}};
  qu_operator.set_data(control_data); 
}
std::string control_cz::get_type()
{
  return "CZ";
}
std::string control_cz::get_symbol()
{
  return "■";
}

void control_cnot::set_qu_operator()
{
  std::vector<std::complex<double>> control_data = {{1, 0}};
  qu_operator.set_data(control_data); 
}
std::string control_cnot::get_type()
{
  return "CNOT";
}
std::string control_cnot::get_symbol()
{
  return "•";
}
