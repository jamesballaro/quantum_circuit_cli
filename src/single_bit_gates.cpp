#include "single_bit_gates.h"

void pauli_X::set_qu_operator()
{
  std::vector<std::complex<double>> pauli_x_data = {{0, 0},{1, 0},{1, 0},{0, 0}};
  qu_operator.set_data(pauli_x_data); 
}
std::string pauli_X::get_symbol()
{
  return "[X]";
}
void pauli_X::get_info()
{
	std::cout<<"Pauli X Matrix Representation:"<<std::endl;
	std::cout<<qu_operator;
  std::cout<<"Pauli X Gate Symbol: [X]"<<std::endl;
	std::cout<<"Gate information:"<<std::endl;
	std::cout<<"Pauli X: The Pauli gates (X,Y,Z) are the three Pauli matrices and act on a single qubit. The Pauli X, Y and Z equate,"
							"respectively, to a rotation around the x, y and z axes of the Bloch sphere by pi radians. The Pauli-X gate is the quantum"
							" equivalent of the NOT gate for classical computers with respect to the standard basis It is sometimes called a bit-flip "<<std::endl;
}
std::string pauli_X::get_type()
{
	return "Pauli X";
}

void pauli_Y::set_qu_operator()
{
  std::vector<std::complex<double>> pauli_y_data = {{0, 0},{0, -1},{0, 1},{0, 0}};
  qu_operator.set_data(pauli_y_data); 
}
std::string pauli_Y::get_symbol()
{
  return "[Y]";
}
void pauli_Y::get_info()
{
	std::cout<<"Pauli Y Matrix Representation:"<<std::endl;
	std::cout<<qu_operator;
  std::cout<<"Pauli Y Gate Symbol: [Y]"<<std::endl;
	std::cout<<"Gate information:"<<std::endl;
	std::cout<<"Pauli Y: The Pauli gates (X,Y,Z) are the three Pauli matrices and act on a single qubit. The Pauli X, Y and Z equate,"
							"respectively, to a rotation around the x, y and z axes of the Bloch sphere by pi radians. The Pauli-X gate is the quantum"
							" equivalent of the NOT gate for classical computers with respect to the standard basis It is sometimes called a bit-flip "<<std::endl;
}
std::string pauli_Y::get_type()
{
	return "Pauli Y";
}

void pauli_Z::set_qu_operator()
{
  std::vector<std::complex<double>> pauli_z_data = {{1, 0},{0, 0},{0, 0},{-1, 0}};
  qu_operator.set_data(pauli_z_data);
    
}
std::string pauli_Z::get_symbol()
{
  return "[Z]";
}
void pauli_Z::get_info()
{
	std::cout<<"Pauli Z Matrix Representation:"<<std::endl;
	std::cout<<qu_operator;
  std::cout<<"Pauli Z Gate Symbol: [Z]"<<std::endl;
	std::cout<<"Gate information:"<<std::endl;
	std::cout<<"Pauli X: The Pauli gates (X,Y,Z) are the three Pauli matrices and act on a single qubit. The Pauli X, Y and Z equate,"
							"respectively, to a rotation around the x, y and z axes of the Bloch sphere by pi radians. The Pauli-X gate is the quantum"
							" equivalent of the NOT gate for classical computers with respect to the standard basis It is sometimes called a bit-flip "<<std::endl;
}
std::string pauli_Z::get_type()
{
	return "Pauli Y";
}

void hadamard::set_qu_operator()
{
  std::vector<std::complex<double>> hadamard_data = {{1/sqrt(2), 0},{1/sqrt(2), 0},{1/sqrt(2), 0},{-1/sqrt(2), 0}};
  qu_operator.set_data(hadamard_data);
    
}
std::string hadamard::get_symbol()
{
  return "[H]";
}
void hadamard::get_info()
{
	std::cout<<"Hadamard Matrix Representation:"<<std::endl;
	std::cout<<qu_operator;
  std::cout<<"Hadamard Gate Symbol: [H]"<<std::endl;
	std::cout<<"Gate information:"<<std::endl;
	std::cout<<"Hadamard: The Hadamard transform is used extensively in quantum computing. The 2 x 2 Hadamard transform H1 is the quantum logic gate known as the Hadamard gate,"
							" and the application of a Hadamard gate to each qubit of an n-qubit register in parallel is equivalent to the Hadamard transform "
							" H_{n}."<<std::endl;
}
std::string hadamard::get_type()
{
	return "Hadamard";
}

void phase::set_qu_operator()
{
  std::vector<std::complex<double>> phase_data = {{1, 0},{0, 0},{0, 0},{0, 1}};
  qu_operator.set_data(phase_data);
    
}
std::string phase::get_symbol()
{
  return "[P]";
}
void phase::get_info()
{
	std::cout<<"Phase Matrix Representation:"<<std::endl;
	std::cout<<qu_operator;
  std::cout<<"Phase Gate Symbol: [P]"<<std::endl;
	std::cout<<"Gate information:"<<std::endl;
	std::cout<<"Phase: info"<<std::endl;
}
std::string phase::get_type()
{
	return "Phase";
}

void identity::set_qu_operator()
{
  std::vector<std::complex<double>> identity_data = {{1, 0},{0, 0},{0, 0},{1, 0}};
  qu_operator.set_data(identity_data); 
}
std::string identity::get_symbol()
{
  return "[I]";
}
std::string identity::get_type()
{
	return "Identity";
}
void identity::get_info()
{
	std::cout<<"Identity Gate Matrix Representation:"<<std::endl;
	std::cout<<qu_operator;
	std::cout<<"Gate information:"<<std::endl;
	std::cout<<"Identity: where I is basis independent and does not modify the quantum state." 
							"The identity gate is most useful when describing mathematically the result of"
							 "various gate operations or when discussing multi-qubit circuits."<<std::endl;
}
