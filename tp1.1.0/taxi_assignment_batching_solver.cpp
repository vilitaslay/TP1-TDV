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

    auto begin = std::chrono::high_resolution_clock::now();
    create_graph();
    // okay

    int status = _grafo.Solve();
    //Esto resuelve el grafo? los escucho
    //esto lo hace lo q esta aca abajo
    // if (status == operations_research::MinCostFlow::OPTIMAL) {
    //     std::cout << "Flujo de costo minimo " << _grafo.OptimalCost() << std::endl;
    //     std::cout << "";
    //     std::cout << " (Flujo / Capacidad)  Costo" << std::endl; //capacity cost es el costo no? por q carajo le dice capacity cost
    //     for (std::size_t i = 0; i < _grafo.NumArcs(); ++i) {
    //         int64_t flow = _grafo.Flow(i);
    //         if (flow == 0) continue;
    //         int64_t cost = _grafo.Flow(i) * _grafo.UnitCost(i);
    //         std::cout << _grafo.Tail(i) << " -> " << _grafo.Head(i)
    //                     << "  " << _grafo.Flow(i) << "  / "
    //                     << _grafo.Capacity(i) << "       " << cost << std::endl;
    //     }
    // } else {
    //     std::cout << "Solving the min cost flow problem failed. Solver status: "
    //             << status << std::endl;
    // }
    this->_objective_value=(_grafo.OptimalCost())/10.00;
    this->_solution_status=status;
    auto end = std::chrono::high_resolution_clock::now();
    auto elapse = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin);
    this->_solution_time = elapse.count();
    

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


