#include "taxi_assignment_batching_solver.h"


BatchingSolver::BatchingSolver() {}

BatchingSolver::BatchingSolver(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
    this->_objective_value = 0;
    this->_solution_status = 0;
    this->_solution_time = 0;
}

void BatchingSolver::setInstance(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
}

void BatchingSolver :: solve() {
    create_graph();

    int status = _grafo.Solve();
}


void BatchingSolver::create_graph() {
    int n = this->_instance.n;
    //Instanciamos las aristas
    std::vector<int64_t> taxis(n*n, -1);
    std::vector<int64_t> pasajeros(n*n, -1);
    std::vector<int64_t> capacidad(n*n, 1);
    std::vector<int64_t> distancia(n*n, -1);
    int indice = 0;
    //Creamos las 
    for (int i = 0; i < this->_instance.n; i++) {
        for (int j = this->_instance.n; j < 2*this->_instance.n; j++) {
            taxis[indice] = i; // Los indices representan las aristas, i representa el nodo del cual sale esa arista
            pasajeros[indice] = j; // Los indices represntas las aristas. 
            // i seria el inicio de la arista, y j el final
            distancia[indice] = 10*this->_instance.dist[i][j - n]; //Guarda las distiancias en numeros enteros
            indice++;
        }
    }

    std::vector<int64_t> balance(2*n, 0);
    for (int i = 0; i < this->_instance.n; i++) {
        balance[i] = 1; // balance de los taxis
        balance[n + i] = -1; //balance de los pasajeros
    }
    //creamos el grafo
    for (int i = 0; i < taxis.size(); ++i) {
        int arc = _grafo.AddArcWithCapacityAndUnitCost(taxis[i], pasajeros[i], capacidad[i], distancia[i]);
        if (arc != i) LOG(FATAL) << "Internal error";
    }
    // Agregamos el balance
    for (int i = 0; i < balance.size(); ++i) {
        _grafo.SetNodeSupply(i, balance[i]);
    }
}

double BatchingSolver::getObjectiveValue() const {
    return this->_objective_value;
}

TaxiAssignmentSolution BatchingSolver::getSolution() const {
    return this->_solution;
}

int BatchingSolver::getSolutionStatus() const {
    return this->_solution_status;
}

double BatchingSolver::getSolutionTime() const {
    return this->_solution_time;
}


