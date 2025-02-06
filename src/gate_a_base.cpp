#include "gate_a_base.h"
#include "toolbox.h"

//Initializing variables for each
namespace gate_a_base{
	component_library bits;
	component_library gates;
}

void gate_a_base::library_creator()
{ 
  using namespace gate_a_base;
  gates["CNOT"] = std::make_shared<cnot>();
  gates["PAULI X"] = std::make_shared<pauli_X>();
  gates["PAULI Y"] = std::make_shared<pauli_Y>();
  gates["PAULI Z"] = std::make_shared<pauli_Z>();
  gates["HADAMARD"] = std::make_shared<hadamard>();
	gates["PHASE"] = std::make_shared<phase>();
	gates["CZ"] = std::make_shared<cz>();
	gates["SWAP"] = std::make_shared<swap>();
	gates["TOFFOLI"] = std::make_shared<ccx>();

	bits["[CX]_TARGET"] = std::make_shared<target_cnot>();
	bits["[CX]_TARGET_FLIP"] = std::make_shared<target_flip_cnot>();
	bits["[CX]_CONTROL"] = std::make_shared<control_cnot>();
	bits["[CZ]_TARGET"] = std::make_shared<target_cz>();
	bits["[CZ]_CONTROL"] = std::make_shared<control_cz>();
	bits["SWAP_TARGET"] = std::make_shared<target_swap>();
	bits["SWAP_CONTROL"] = std::make_shared<control_swap>();
	bits["[CCX]_TARGET"] = std::make_shared<target_ccx>();
	bits["[CCX]_TARGET_FLIP"] = std::make_shared<target_flip_ccx>();
	bits["[CCX]_CONTROL"] = std::make_shared<control_ccx>();
}

std::shared_ptr<component> gate_a_base::search_library(int choice,std::string& request)
{ 
	auto& library = (choice == 1) ? bits : gates;
  request = toolbox::to_upper(request);
  auto library_iter = library.find(request);
  if(library_iter != library.end()){
		if(library == gates){
			std::cout<<std::endl;
    	std::cout<<" * * Gate retrieved: ("<<request<<")  * *"<<std::endl;
			std::cout<<std::endl;
		}
    return library_iter->second;
  }
  else{
		std::cout<<std::endl; 
    std::cerr<<"Error: Gate '" <<request<<"' is not in database. "<<std::endl;
		std::cout<<"Please enter again: ";
    return nullptr;
  }
}
void gate_a_base::gate_info()
{
	std::cout<<"Which gate would you like to see the information for? "<<std::endl;
	std::cout<<"Possible gates: ";
  std::cout<<"Selection: ";
	for(const auto& kv : gate_a_base::gates){
    std::cout << kv.first<<", ";
	}
	std::cout<<std::endl;
	std::string gate_choice;
	while(true){
    std::getline(std::cin, gate_choice);
		std::shared_ptr<component> gate = gate_a_base::search_library(0,gate_choice);
		if(gate != nullptr){
			std::cout<<std::endl;
			gate->get_info();
			//std::this_thread::sleep_for(std::chrono::seconds(4));
      std::cout<<"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "<<std::endl;
			std::cout<<std::endl;
			break;
		}
	}
}

