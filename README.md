# Quantum Circuit CLI  

### **Overview**  
**Quantum Circuit CLI** is an interactive command-line tool for constructing and simulating quantum circuits. It allows users to initialize qubit states, apply quantum gates, view circuit diagrams, and compute matrix representations of circuits. The tool is built in C++ and follows a gate-based quantum computing model.  

---

## **Features**
- 🧑‍💻 **Interactive CLI** for designing quantum circuits  
- ⚛ **Supports common quantum gates** (Hadamard, CNOT, Pauli, Toffoli, etc.)  
- 🔢 **Customizable qubit initialization** (|0⟩ or |1⟩ states)  
- 📜 **Displays circuit diagrams in ASCII**  
- 📊 **Computes the full matrix representation of circuits**  
- 💾 **Supports saving and loading circuits**  
- 🚀 **Error handling for invalid inputs**  

---

## **Installation and Compilation**
### **Prerequisites**
- C++17 or later  
- A C++ compiler (e.g., `g++-11`)  
- `make` utility installed  

### **Clone the Repository**
```sh
git clone https://github.com/your-username/quantum_circuit_cli.git
cd quantum_circuit_cli
```
### **Compile & run the program**
```
make 
./main
```

## **How to Use**
Upon running the program, you are presented with the main menu:
```
************************************************
    Welcome to the Quantum Circuits Program!
************************************************

Options:
1) Create quantum circuit.
2) See gate information.
3) Exit program.
```
### **Creating a Quantum Circuit**
	1.	Select option 1 to create a new circuit.
	2.	Choose the number of qubits (1 to 5).
	3.	Select an initial state (ket0 or ket1).

```
How many q-bits would you like in your circuit? (maximum of 5) 4
Circuit with 4 qubit(s) and 1 classical bit created.

What state would you like your qubits to be initialized in? 

      [1]         [0]
1)    [0]     2)  [1]
     (ket 0)      (ket 1)

Selection: 1
Qubits initialized in ket0 state
```

### **Adding Gates**
	1.	Choose option 1 (Add gate).
	2.	Select a quantum gate from the available list.
	3.	Specify whether to place the gate in series (on one qubit) or parallel (on multiple qubits).

```
Possible gates: CNOT, CZ, HADAMARD, PAULI X, PAULI Y, PAULI Z, PHASE, SWAP, TOFFOLI,
What gate would you like to add? Hadamard

 * * Gate retrieved: (HADAMARD)  * *

Would you like to add your gate in:
1) Series.
2) Parallel.

Selection: 1
Which q-bit would you like this gate to act on? (q0,q1,..)?
Selection: q0

Gate (HADAMARD) added to q[0]
```

### **Example Circuit after adding Gates:**
```
Updated Circuit:

q[0]---[H]--[Y]-

q[1]---[X]------

q[2]---[H]------

q[3]---[H]------

c[0]============
```

### **Viewing the circuit matrix representation:**
Select option 4 to view the matrix representation of the circuit:
```
Circuit Matrix representation:
[    0               0               0               0               0-0.353553i     0-0.353553i     0-0.353553i     0-0.353553i     ]
[    0               0               0               0               0-0.353553i     0+0.353553i     0-0.353553i     0+0.353553i     ]
...
(qubits initialized in the ket0 basis state)
```
### **Saving and Loading Circuits**
You can save a circuit (option 5) and load it later (option 6), either replacing youre current circuit or adding it as an extension.


## **Project Structure**
```
quantum_circuit_cli/
│── src/                     # Source files
│   ├── main.cpp             # Main program logic
│   ├── q_circuit.cpp        # Circuit operations
│   ├── matrix.cpp           # Matrix math utilities
│   ├── multi_bit_gates.cpp  # Multi-qubit gate logic
│   ├── single_bit_gates.cpp # Single-qubit gate logic
│   ├── gate_a_base.cpp      # Gate management
│   ├── toolbox.cpp          # Utility functions
│── include/                 # Header files
│── Makefile                 # Compilation script
│── README.md                # Documentation
```

Developed as a university project as an exercise in learning basic quantum computing concepts and core OOP in C++ principles.