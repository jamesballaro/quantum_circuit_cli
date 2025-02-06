#ifndef GATE_A_BASE_H
#define GATE_A_BASE_H

#include <map>
#include <memory>
#include "component.h"
#include "single_bit_gates.h"
#include "multi_bit_gates.h"
#include "bits.h"

namespace gate_a_base{
	//Library of all component_classes
  typedef std::map<std::string,std::shared_ptr<component>> component_library;
	extern component_library bits;
	extern component_library gates;
	//Library searcher, takes a key and returns a component
	std::shared_ptr<component> search_library(int choice, std::string& request);
	//Function to intialize the library with necessary gates and control bits etc.
  void library_creator();
  void gate_info();
}

#endif