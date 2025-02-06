#include "q_circuit.h"
#include <algorithm>
#include <sstream>
#include <chrono>
#include <thread>

std::vector<std::shared_ptr<q_circuit>> q_circuit::saved_circuits;

void q_circuit::multi_qubit_gate(std::shared_ptr<component> gate, int qubit_range, int num_qubits)
{
  std::cout<<"Which q-bits would you like this gate to act on?"<<std::endl;
  std::cout<<"Please enter as an array, with the target bit first e.g [q0,q1]: ";
	std::string symbol = gate->get_symbol();
  while(true){
    std::string input;
    std::getline(std::cin, input);
    if(!input.empty()){
      std::vector<int> bit_array;
      bit_array = toolbox::extract_number(input, num_qubits);
      auto smallest = std::min_element(bit_array.begin(),bit_array.end());
      auto largest = std::max_element(bit_array.begin(),bit_array.end());
      if(bit_array[0] == -2){
        std::cout<<std::endl;
        std::cout<<"Error: There are only "<<num_qubits<<" qubits in the current circuit."<<std::endl;
        std::cout<<"Please enter again: ";
      }
      else if(static_cast<int>(bit_array.size()) != qubit_range){
        std::cout<<std::endl;
        std::cerr<<"Error: Wrong amount of qubits, this gate has a range of "<<qubit_range<<"."<<std::endl;
        std::cerr<<"Please enter again: ";
      }	
      else if((*largest-*smallest +1) > qubit_range ){
        std::cout<<std::endl;
        std::cerr<<"Error: This gate has a range of "<<qubit_range<<" adjacent qubits."<<std::endl;
        std::cerr<<"Please enter again: ";
      }
      else if(bit_array[0] != -1){
        bool replace{true};
        for(const auto& i: bit_array){
          if(components_vector[i].back().second->get_symbol() != "[I]"){
            replace = false;
          }
        }
        std::string ctrl_request = symbol +"_control";
        std::string trgt_request = symbol +"_target";
        std::shared_ptr<component> gate_ctrl = gate_a_base::search_library(1,ctrl_request);
        std::shared_ptr<component> gate_trgt = gate_a_base::search_library(1,trgt_request);
        int max_element = *(std::max_element(bit_array.begin(), bit_array.end()));
        int min_element = *(std::min_element(bit_array.begin(), bit_array.end()));
        if(bit_array[0] < bit_array[1]){
          trgt_request += "_flip";
          gate_trgt = gate_a_base::search_library(1,trgt_request);
        }
        if(min_element != bit_array[0] && max_element != bit_array[0]){
          std::cout<<std::endl;
          std::cerr<<"Error: Please enter the range starting from the target bit."<<std::endl;
          std::cerr<<"Please enter again: ";
          continue;
        }
        try{
          if(replace){
            std::vector<size_t> replace_gate;
            for(const auto v : bit_array){
              size_t position = toolbox::last_gate(components_vector[v]);
              replace_gate.push_back(position);
            }
            size_t largest_element = *(std::max_element(replace_gate.begin(), replace_gate.end()));
            for(const auto j: bit_array){
              j == bit_array.front() ? components_vector[j][largest_element] = toolbox::pair(bit_array, gate_trgt) : components_vector[j][largest_element] = toolbox::pair(bit_array, gate_ctrl);	
            }
            std::cout<<"Gate "<<symbol<<" added with target bit : q["<<bit_array[0]<<"]"<<std::endl;
            break;
          }
          else{
            for(const auto k: bit_array){
              k == bit_array.front() ? components_vector[k].push_back(toolbox::pair(bit_array, gate_trgt)) : components_vector[k].push_back(toolbox::pair(bit_array,gate_ctrl));
            }
            for (size_t i = 0; i < components_vector.size(); ++i) {
              auto it = std::find(bit_array.begin(), bit_array.end(), i);
              if (it == bit_array.end() && static_cast<int>(i) < num_qubits){
                components_vector[i].push_back(toolbox::pair(std::make_shared<identity>()));
              }
            }
            std::cout<<"Gate "<<symbol<<" added with target bit : q["<<bit_array[0]<<"]"<<std::endl;
            break;
          }
        }
        catch(std::bad_alloc& e){
          std::cerr << "System Error: " << e.what() << "\n";
          break;
        }
      }
      else{
        std::cout<<std::endl;
        std::cout<<"Error: Invalid input. Please enter qubit numbers in the format 'q0,q1,...'." <<std::endl;
        std::cout<<"Please enter again: ";
        bit_array.clear();
      }
    }
    else{
      std::cerr<<"Error: Empty Entry"<<std::endl;
      std::cout<<"Please enter again: ";
    }
  }
}
void q_circuit::series_add(std::string gate_choice, std::shared_ptr<component> gate)
{
  std::cout<<"Which q-bit would you like this gate to act on? (q0,q1,..)? "<<std::endl;
  std::cout<<"Selection: ";
  while(true){
    std::string bit_choice;
    std::getline(std::cin, bit_choice);
    std::cout<<std::endl;
    if(!bit_choice.empty()){
      int chosen_no{toolbox::extract_number(bit_choice)};
      if(chosen_no > num_qubits-1){
        std::cout<<std::endl;
        std::cout<<"Error: There are only "<<num_qubits<<" qubits in the current circuit. You have entered q["<<chosen_no<<"]"<<std::endl;
        std::cout<<"Please enter again: ";
      }
      else if(chosen_no != -1){     
        try{ 
          int index = chosen_no;
          if(components_vector[index].back().second->get_symbol() != "[I]"){
            components_vector[index].push_back(toolbox::pair(gate));
            for(int i{0}; i<static_cast<int>(components_vector.size()); i++){
              if(i == index || i > num_qubits-1){
                continue;
              }
              else{
                components_vector[i].push_back(toolbox::pair(std::make_shared<identity>()));
              }
            }
          }
          else{
            size_t position = toolbox::last_gate(components_vector[index]);
            components_vector[index][position] = toolbox::pair(gate);
          }
          std::cout<<"Gate ("<<toolbox::to_upper(gate_choice)<<") added to q["<<chosen_no<<"]"<<std::endl;
          std::cout<<std::endl;
          break;
        }
        catch(std::bad_alloc& e){
          std::cerr << "System Error: " << e.what() << "\n";
          break;
        }
      }
      else{
        std::cout<<std::endl;
        std::cout<<"Error: Cannot match to current qubit. (Enter q0/q1..etc): ";
      }
    }
    else{
      std::cerr<<"Error: Empty Entry"<<std::endl;
      std::cout<<"Please enter again: ";
    }
  }      
}
void q_circuit::parallel_add(std::shared_ptr<component> gate)
{
  std::cout<<"Which q-bits would you like to apply this gate on?"<<std::endl;
  std::cout<<"Please enter as an array, with the target bit first e.g [q0,q1]: ";
	std::string symbol = gate->get_symbol();
  while(true){
    std::string input;
    std::getline(std::cin, input);
    if(!input.empty()){
      std::vector<int> bit_array;
      bit_array = toolbox::extract_number(input, num_qubits);
      if(bit_array[0] == -2){
        std::cout<<std::endl;
        std::cout<<"Error: There are only "<<num_qubits<<" qubits in the current circuit."<<std::endl;
        std::cout<<"Please enter again: ";
      }
      else if(bit_array[0] != -1){
        bool replace{true};
        for(const auto& i: bit_array){
          if(components_vector[i].back().second->get_symbol() != "[I]"){
            replace = false;
          }
        }
        try{
          if(replace){
            std::vector<size_t> replace_gate;
            for(const auto v : bit_array){
              size_t position = toolbox::last_gate(components_vector[v]);
              replace_gate.push_back(position);
            }
            size_t largest_element = *(std::max_element(replace_gate.begin(), replace_gate.end()));
            std::cout<<"Gate "<<symbol<<" added on qubits: ";
            std::stringstream ss;
            for(const auto j: bit_array){
              components_vector[j][largest_element] = toolbox::pair(gate); 
              ss<<"q["<<j<<"] ";
            }
            std::cout<<ss.str()<<"."<<std::endl;
            break;
          }
          else{
            std::cout<<"Gate "<<symbol<<" added on qubits :";
            for(const auto k: bit_array){
              components_vector[k].push_back(toolbox::pair(gate));
              std::cout<<"q["<<k<<"] ";
              std::cout<<"."<<std::endl;
            }
            for (size_t i = 0; i < components_vector.size(); ++i) {
              auto it = std::find(bit_array.begin(), bit_array.end(), i);
              if (it == bit_array.end() && static_cast<int>(i) < num_qubits){
                components_vector[i].push_back(toolbox::pair(std::make_shared<identity>()));
              }
            }
            break;
          }
        }
        catch(std::bad_alloc& e){
          std::cerr << "System Error: " << e.what() << "\n";
          break;
        }
      }
      else{
        std::cout<<std::endl;
        std::cout<<"Error: Invalid input. Please enter qubit numbers in the format 'q0,q1,...'." <<std::endl;
        std::cout<<"Please enter again: ";
        bit_array.clear();
      }
    }
    else{
      std::cerr<<"Error: Empty Entry"<<std::endl;
      std::cout<<"Please enter again: ";
    }
  }
}
void q_circuit::add_gate()
{
  std::string gate_choice;
  std::string add_choice;
	std::cout<<"Possible gates: ";
	for(const auto& kv : gate_a_base::gates){
    std::cout << kv.first<<", ";
  }
	std::cout<<std::endl;
	std::cout<<"What gate would you like to add? ";
  while(true){
		std::getline(std::cin, gate_choice);
    std::shared_ptr<component> gate = gate_a_base::search_library(0,gate_choice);
    if (gate != nullptr){
			int gate_range{gate->get_qubit_range()};
			if(gate_range > num_qubits){
				std::cout<<std::endl;
				std::cout<<"Error: Gate too big for circuit."<<std::endl;
				std::cout<<"Please enter again: ";
				continue;
			}
      else if(gate_range > 1){
        multi_qubit_gate(gate, gate_range, num_qubits);
        break;
      }
      std::cout<<"Would you like to add your gate in: "<<std::endl;
      std::cout<<"1) Series. "<<std::endl<<"2) Parallel. \n"<<std::endl;
      std::cout<<"Selection: ";
      while(true){
		    std::getline(std::cin, add_choice);
        if(add_choice.empty()){
          std::cout<<"Error: Empty entry."<<std::endl;
          std::cout<<"Please enter again."<<std::endl;
          continue;
        }
        int add_choice_int = toolbox::int_verifier(add_choice);
        if(add_choice_int == 1){
          series_add(gate_choice, gate);
          break;
        }
        else if(add_choice_int == 2){
          parallel_add(gate);
          break;
        }
        else{
          std::cout<<"Error: Invalid entry. "<<std::endl;
          std::cout<<"Please enter again: ";
        }   
      }
      break;
    }
  }
  std::cout<<"Updated Circuit:"<<std::endl;
  std::cout<<*this<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(2500));
  std::cout<<std::endl;
}
void q_circuit::create_circuit()
{	
  std::string qubit_choice;
  std::cout<<"How many q-bits would you like in your circuit? (maximum of 5) ";
  while(true){
    std::getline(std::cin, qubit_choice);
    if(!qubit_choice.empty()){
      int qubits{toolbox::int_verifier(qubit_choice)};
      if(qubits == -1){
        std::cout<<std::endl;
        std::cerr<<"Error: Invalid Entry"<<std::endl;
        std::cout<<"Please enter again: ";
      }
      else if(qubits > 5 || qubits < 1){
        std::cout<<std::endl;
        std::cout<<"Error: The number of qubits should be beteen 1 and 5."<<std::endl;
        std::cout<<"Please enter again: ";
      }
      else if(qubits != -1){
        std::cout<<"Circuit with "<<qubit_choice<<" qubit(s) and 1 classical bit created.\n"<<std::endl;
        std::string state_choice;
        std::cout<<"What state would you like your qubits to be initialized in? \n"<<std::endl;
        std::cout<<"      [1]         [0]"<<std::endl;
        std::cout<<"1)    [0]     2)  [1]"<<std::endl;
        std::cout<<"     (ket 0)      (ket 1) "<<std::endl;
        while(true){
          std::cout<<"\nSelection: ";
          std::getline(std::cin, state_choice);
          if(!state_choice.empty()){
            int state{toolbox::int_verifier(state_choice)};
            if(state != -1 && state > 0 && state < 3){
              *this = q_circuit(qubits, state);
              std::cout<<"Qubits initialized in ket"<<state-1<<" state"<<std::endl;
              std::cout<<std::endl;
              break;
            }
            else{
              std::cout<<std::endl;
              std::cerr<<"Error: Invalid Entry"<<std::endl;
              std::cout<<"Please enter again: ";
            }
          }
          else{
            std::cerr<<"Error: Empty Entry"<<std::endl;
            std::cout<<"Please enter again: ";
          }
        }
        break;
      }
    }
    else{
      std::cerr<<"Error: Empty Entry"<<std::endl;
      std::cout<<"Please enter again: ";
    }
  }
}
void q_circuit::remove_gate()
{ 
  size_t longest_row{toolbox::longest_element(components_vector)};
  if(longest_row == 1){
    std::cout<<"No gates in circuit yet!"<<std::endl;
    std::cout<<std::endl;
  }
  else{
    std::cout<<"Current Circuit: "<<std::endl;
    std::cout<<*this<<std::endl;
    std::string removal_choice;
    int counter{1};
    std::map<int, std::pair<int, int>> counter_to_gate_map;
    std::cout<<"What gate would you like to remove?"<<std::endl;
    std::cout<<"Options:"<<std::endl;
    for(size_t k{1}; k < longest_row; k++){
      for(size_t i{0}; i < num_qubits; i++){
        circuit_element gate = components_vector[i][k];
        std::string symbol = gate.second->get_symbol();
        if(symbol != "[I]" && symbol != "•"){
          symbol = gate.second->get_type();
          if(gate.first.size() > 1){
            if(i != gate.first[0]){
              continue;
            }
          }
          std::cout<<counter<<") Gate: "<<symbol<<" on "<<"q["<<i<<"]"<<std::endl;
          counter_to_gate_map[counter] = std::make_pair(i,k);
          counter ++;
        }
      }
    }  
    while(true){
      std::cout<<"Selection: ";
      std::getline(std::cin,removal_choice);
      if(!removal_choice.empty()){
        //Selected option 'option'
        int option{toolbox::int_verifier(removal_choice)};
        if (counter_to_gate_map.find(option) != counter_to_gate_map.end()){
          //Chosen gate with circuit 'coordinates' (bit_choice,gate_choice)
          int bit_choice{counter_to_gate_map[option].first};
          int gate_choice{counter_to_gate_map[option].second};
          circuit_element gate = components_vector[bit_choice][gate_choice];
          std::string symbol = gate.second->get_type();
          for(auto v : gate.first){
            components_vector[v][gate_choice] = toolbox::pair(std::make_shared<identity>()); 
          }
          components_vector[bit_choice][gate_choice] = toolbox::pair(std::make_shared<identity>()); 
          bool identity_column{true};
          for(int i{0}; i<num_qubits; i++){
            if(components_vector[i][gate_choice].second->get_symbol() != "[I]"){
              identity_column = false;
            }
          }
          if(identity_column){
            for(int i{0}; i<num_qubits; i++){
              components_vector[i].erase(components_vector[i].begin() + gate_choice);
            }
          }
          std::cout<<"Gate: "<<symbol<<" on q["<<bit_choice<<"] removed successfully."<<std::endl;
          std::cout<<"Updated Circuit:"<<std::endl;
          std::cout<<*this<<std::endl;
          break;
        }
        else{
          std::cout<<std::endl;
          std::cout<<"Error: Invalid Entry."<<std::endl;
          std::cout<<"Please enter again: "<<std::endl; 
        }
      }
      else{
        std::cout<<std::endl;
        std::cout<<"Error: Empty entry."<<std::endl;
        std::cout<<"Please enter again: ";
      }
    }
  }
}
void q_circuit::calculate_circuit_matrix(std::vector<matrix> tensor_vector, int gate_pos)
{ 
  int longest_row{static_cast<int>(toolbox::longest_element(components_vector)-1)};
  if(longest_row == 0){
		std::cout<<std::endl;
    std::cout<<"Error: No gates in circuit yet!"<<std::endl;
    return;
  }
  if(gate_pos <= longest_row){
    matrix gate_tensor = components_vector[0][gate_pos].second->get_operator(); 
    toolbox::recursive_tensor_product(components_vector, num_qubits , 1, gate_pos, gate_tensor);
    tensor_vector.push_back(gate_tensor);
    gate_pos++;
    calculate_circuit_matrix(tensor_vector, gate_pos);
  }
  else if(gate_pos > longest_row){
    circuit_matrix = tensor_vector[0];
		//Mutliplies the tensor matrices of every gate produce together
    toolbox::recursive_matrix_multiplication(tensor_vector, 1, circuit_matrix);
		//Tensor product of qubit states
		matrix qubit_tensor = components_vector[0][0].second->get_operator(); 
		toolbox::recursive_tensor_product(components_vector, num_qubits, 1, 0, qubit_tensor);
		//qubit tensor matrix mutiplied by circuit matrix
		matrix applied_matrix = circuit_matrix * qubit_tensor;
    std::cout<<"Circuit Matrix representation:"<<std::endl;
    std::cout<<circuit_matrix<<std::endl;
		std::cout<<std::endl;
		std::cout<<"Applied to q-bit register: "<<std::endl;
		std::cout<<applied_matrix<<std::endl;
		std::cout<<"(qubits initalized in the ket"<<state<<" basis state)"<<std::endl;
		std::cout<<std::endl;
  }
}
void q_circuit::get_circuit_matrix()
{ 
  std::vector<matrix> tensor_vector;
  int gate_pos{1};
  calculate_circuit_matrix(tensor_vector, gate_pos);
}
void q_circuit::save()
{	  
  size_t longest_row{toolbox::longest_element(components_vector)};
  if(longest_row == 1){
    std::cout<<"No gates in circuit yet!"<<std::endl;
    std::cout<<std::endl;
  }
  else{
    saved_circuits.push_back(std::make_shared<q_circuit>(*this));
    size_t size{saved_circuits.size()};
    std::cout<<std::endl;
    std::cout<<"SAVING";
    for(int i{0}; i < 40; i++){
      std::cout<<".";
      std::cout.flush();
     std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
    for (int i = 0; i < 47; i++) {
        std::cout << '\b' << ' ' << '\b';
    }
    std::cout<<std::endl;
    std::cout<<" * * * * * * * * * * * * * * * * * * * *"<<std::endl;
    std::cout<<"       Circuit saved as: Circuit "<<size<<"."<<std::endl;
    std::cout<<" * * * * * * * * * * * * * * * * * * * *"<<std::endl;
    std::cout<<std::endl;
   std::this_thread::sleep_for(std::chrono::seconds(3));
  }
}
void q_circuit::add_to_circuit(std::shared_ptr<q_circuit> circuit, int circ_no)
{
  size_t longest_added_bit = toolbox::longest_element(circuit->components_vector);
  std::cout<<std::endl;
  std::cout<<"Which bit would you like to add the circuit to? [q0,q1...]"<<std::endl;
  std::cout<<"Selection: ";
  while(true){
    std::string bit_choice;
    std::getline(std::cin, bit_choice);
    if(!bit_choice.empty()){
      int bit_choice_numb{toolbox::extract_number(bit_choice)};
      if(bit_choice_numb != -1 && (bit_choice_numb >= 0 && bit_choice_numb < this->num_qubits)){
        if((this->num_qubits-bit_choice_numb) >= circuit->num_qubits){
          std::vector<int> changed_bits;
          for(int l{bit_choice_numb}; l < (bit_choice_numb+circuit->num_qubits); l++){
            changed_bits.push_back(l);
          }
          for(size_t k{1}; k < longest_added_bit; k++){
            for(int j{0}; j < this->num_qubits; j++){
              auto it = std::find(changed_bits.begin(), changed_bits.end(), j);
              if (it == changed_bits.end()){
                this->components_vector[j].push_back(toolbox::pair(std::make_shared<identity>()));
              }
              else{
                this->components_vector[j].push_back(circuit->components_vector[j-bit_choice_numb][k]);
              }
            }
          }
          std::cout<<"Circuit "<<circ_no<<" added to current circuit."<<std::endl;
          std::cout<<"Updated Circuit:"<<std::endl;
          std::cout<<*this<<std::endl;
          break;
        }
        else{
          std::cout<<std::endl;
          std::cout<<"Error: Not enough space in current circuit to add on that bit."<<std::endl;
          std::cout<<"#qubits in current circuit: "<<this->num_qubits<<std::endl;
          std::cout<<"#qubits in added circuit: "<<circuit->num_qubits<<std::endl;
          std::cout<<"Please enter again: ";
          continue;
        }
      }
      else{
        std::cout<<"Error: Invalid entry."<<std::endl;
        std::cout<<"Please enter again: ";
        continue;
      }
    }
    else{
      std::cout<<"Error: Empty entry"<<std::endl;
      std::cout<<"Please enter again: ";
      continue;
    }  
  }
}
void q_circuit::load()
{
  if(saved_circuits.size() == 0){
    std::cout<<"Error: No circuits have been saved yet."<<std::endl;
  }
  else{
    std::cout<<std::endl;
    std::cout<<"Options: "<<std::endl;
    std::cout<<std::endl;
    for(size_t i{0};i < saved_circuits.size(); i++){
      std::cout<<i+1<<") Circuit "<<i+1<<std::endl;
      std::cout<<*saved_circuits[i]<<std::endl;
      std::cout<<std::endl;
    }
    std::cout<<"Which circuit would you like to load?"<<std::endl;
    std::cout<<"Selection: ";
    while(true){
      std::string circuit_choice;
      std::getline(std::cin, circuit_choice);
      if(!circuit_choice.empty()){
        int circuit_number{toolbox::int_verifier(circuit_choice)};
        if(circuit_number > 0 && circuit_number <= static_cast<int>(saved_circuits.size())){
          std::cout<<"You have selected Circuit "<<circuit_number<<std::endl;
          std::cout<<std::endl;
          std::cout<<"Would you like to:"<<std::endl;
          std::cout<<"1) Overwrite current circuit? "<<std::endl;
          std::cout<<"2) Add this to your current circuit? "<<std::endl;
          std::cout<<std::endl;
          std::cout<<"Selection: ";
          std::string load_choice;
          std::getline(std::cin, load_choice);
          if(!load_choice.empty()){
            int load_choice_numb{toolbox::int_verifier(load_choice)};
            if(load_choice_numb == 1){
              std::cout<<"Circuit Overwritten."<<std::endl;
              std::cout<<"Updated Circuit: "<<std::endl;
              *this = *saved_circuits[circuit_number-1]; 
              std::cout<<*this<<std::endl;
              break;
            }
            //Add to circuit  
            else if(load_choice_numb == 2){
              if(this->num_qubits >= saved_circuits[circuit_number-1]->num_qubits){
              this->add_to_circuit(saved_circuits[circuit_number-1], circuit_number);
              break;
              }
              else{
                std::cout<<"Error: Saved circuit too large to be added to current circuit"<<std::endl;
                std::cout<<"Try option 1 (Overwrite current circuit.)"<<std::endl;
                break;
              }
            }
            else{
              std::cout<<"Error: Option not in range."<<std::endl;
              std::cout<<"Please enter again: ";
            }    
          }
          else{
              std::cout<<"Error: Empty entry"<<std::endl;
              std::cout<<"Please enter again: ";
          }
        }
        else{
          std::cout<<"Error: Option not in range."<<std::endl;
          std::cout<<"Please enter again: ";
        }
      }
      else {
        std::cout<<"Error: Empty entry"<<std::endl;
        std::cout<<"Please enter again: ";
      }
    }
  } 
}

std::ostream& operator<<(std::ostream &output, const q_circuit circuit) 
{
  output<<std::endl;
  for (int i{0}; i < (circuit.total_bits); i++){
		std::stringstream ss;
		int counter{0};
		int total_ss_length{0};
    for (size_t k{0}; k < circuit.components_vector[i].size(); k++){
			circuit_element gate = circuit.components_vector[i][k];
      std::string symbol = gate.second->get_symbol();
      if(symbol == "[I]"){
        output << "-----";
      } 
      else if(symbol == "q"){
        output<<"q["<<i<<"]--";
        if (circuit.components_vector[i].size() == 1){
          output<<"------------------------------";
        }
				ss<<std::string(6, ' ');
      } 
      else if(symbol == "c"){
        output<<"c["<<i-circuit.num_qubits<<"]==";
        if (toolbox::longest_element(circuit.components_vector) == 1){
          output<<"===============================";
        }
        else{
				int longest_bit{static_cast<int>(toolbox::longest_element(circuit.components_vector))};
				std::string creg = std::string(5*(longest_bit-1), '=');
        output<<creg;
        }
      } 
      else {
				int symbol_length = symbol.length();
				if (symbol == "⊕" || symbol == "•" || symbol == "■" ){
        	symbol_length -= 2;
      	} 
        int alignment_length{(3-symbol_length+2)/2};
        std::string padding(alignment_length, '-');
        output<<padding<<symbol<<padding;

				//To connect the bits in controlled, multi-qubit gates
				if (symbol == "⊕" || symbol == "•" || symbol == "■" || symbol == "x"){
					
          std::vector<int> gates_copy = (gate.first);
          std::sort(gates_copy.begin(), gates_copy.end()); 
          gates_copy.pop_back();
          auto i_is_bit = std::find(gates_copy.begin(), gates_copy.end(), i);
          if(i_is_bit != gates_copy.end()){
            int filler_length = 5*(k) - 3 - total_ss_length;
            if (filler_length > 0){ 
              std::string filler(filler_length, ' ');
              ss << filler << "|";
              total_ss_length += filler.length() + 1;  
            }
				  }
					counter+=k;
    		} 
    	}
  	}
		output<<std::endl;
		output<<ss.str();
    output<<std::endl;
  }
	output<<" * * * * * * * * * * * * * * * * * * * *";
  output << std::endl;
  return output;
}
