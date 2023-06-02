#include "taxi_assignment_batching_solver.h"


BatchingSolver::BatchingSolver() {}

BatchingSolver::BatchingSolver(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
    this->_objective_value = 0;
    this->_solution_status = 0;
    this->_solution_time = 0;
    this->_rent=0;
}

void BatchingSolver::setInstance(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
}

void BatchingSolver :: solve(int formato) {

    auto begin = std::chrono::high_resolution_clock::now();
    create_graph(formato);// creamos el grafo
    int status = _grafo.Solve();
    // // Esto imprime las combinaciones que se realizaron
    // if (status == operations_research::MinCostFlow::OPTIMAL) {
    //     std::cout << "Flujo de costo minimo " << _grafo.OptimalCost() << std::endl;
    //     std::cout << "";
    //     std::cout << " (Flujo / Capacidad)  Costo" << std::endl;
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
    //Reconstruimos la solucion

    //si el formato es uno de los nuevos, en donde los costos del grafo no son las distancias, sino los ratios que explicamos en el informe.
    
    
    if(formato!=0){
        for (std::size_t i = 0; i < _grafo.NumArcs(); ++i) {
            this->_objective_value+=_grafo.Flow(i)*this->_instance.dist[_grafo.Tail(i)][_grafo.Head(i)-this->_instance.n]+0.00;              
        }
        this->_rent=_grafo.OptimalCost()/1000.00;     
    }
    else{
        this->_objective_value=(_grafo.OptimalCost())/10;
        for (std::size_t i = 0; i < _grafo.NumArcs(); ++i){
            double aux=this->_instance.pax_trip_dist[_grafo.Head(i)-this->_instance.n];
            double aux1=this->_instance.pax_tot_fare[_grafo.Head(i)-this->_instance.n];
            if(aux1<=0){
                    aux1=1;
            }
            if(aux<=0){
                    aux=1;
            }
            double aux2 = aux*aux1;
            this->_rent+=(_grafo.Flow(i)*this->_instance.dist[_grafo.Tail(i)][_grafo.Head(i)-this->_instance.n]+0.00)/(aux2);   
            // std::cout<<"taxi "<< _grafo.Tail(i) <<" ---> pax "<< _grafo.Head(i)- this->_instance.n << " Rentabilidad: " << (_grafo.Flow(i)*this->_instance.dist[_grafo.Tail(i)][_grafo.Head(i)-this->_instance.n]+0.00)/(aux2) << std::endl;         
        }
    }

    this->_solution_status=status;
    auto end = std::chrono::high_resolution_clock::now();
    auto elapse = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin);
    this->_solution_time = elapse.count();
}


void BatchingSolver::create_graph(int formato) {
    int n = this->_instance.n;
    double parametro;
    //Instanciamos las aristas
    std::vector<double> precios=this->_instance.pax_tot_fare;
    std::vector<double> distpas=this->_instance.pax_trip_dist;
    std::vector<int64_t> taxis(n*n, -1); // Representan los inicios de las aristas
    std::vector<int64_t> pasajeros(n*n, -1); // Representan los finales de las aristas
    std::vector<int64_t> capacidad(n*n, 1); // todas las capacidades de las aristas
    std::vector<int64_t> distancia(n*n, -1); // todas las distancias de las aristas
    int indice = 0;
    //Creamos todos los inicios de las aristas y los finales
    for (int i = 0; i < this->_instance.n; i++) {
        for (int j = this->_instance.n; j < 2*this->_instance.n; j++) {
            taxis[indice] = i; // Los indices representan las aristas, i representa el nodo del cual sale esa arista
            //Primero armamos todas las aristas que salen de un nodo, y al finalizar con ese nodo pasamos al proximo.
            pasajeros[indice] = j; // Los indices represntas las aristas. 
            // i seria el inicio de la arista, y j el final
            distancia[indice] = 10*this->_instance.dist[i][j - n]; //Guarda las distiancias en numeros enteros
            indice++;
        }
    }
    //De esta manera creamos un nodo bipartito con los taxis a la izquierda y los pasajeros a la derecha.
    std::vector<int64_t> balance(2*n, 0);
    for (int i = 0; i < this->_instance.n; i++) {
        balance[i] = 1; // balance de los taxis
        balance[n + i] = -1; //balance de los pasajeros
    }
    // Con el formato elegimos el tipo de batching que queremos realizar. y agregamos los arcos en funcion al formato.
    if(formato==0){
        for (int i = 0; i < taxis.size(); ++i) {
            int arc = _grafo.AddArcWithCapacityAndUnitCost(taxis[i], pasajeros[i], capacidad[i], distancia[i]);
            if (arc != i) LOG(FATAL) << "Internal error";
        }
    }
    else{
        for (int i = 0; i < taxis.size(); ++i) {
            int j=i%n;
            double aux1=precios[j];
            double aux2=distpas[j];
            if (aux1 <=0){
                aux1=1;
            }
            if (aux2 <=0){
                aux2=1;
            }
            double aux = aux1*aux2;
            parametro=(distancia[i]/aux)*100;
            int arc = _grafo.AddArcWithCapacityAndUnitCost(taxis[i], pasajeros[i], capacidad[i], parametro);
            if (arc != i) LOG(FATAL) << "Internal error";
        }        
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

double BatchingSolver::getRent() const {
    return this->_rent;
}
