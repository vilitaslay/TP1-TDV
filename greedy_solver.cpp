#include "greedy_solver.h"
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;


GreedySolver::GreedySolver() {}

GreedySolver::GreedySolver(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
    this->_objective_value = 0;
    this->_solution_status = 0;
    this->_solution_time = 0;
}

void GreedySolver::setInstance(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
}

void GreedySolver::solve() {
    //las filas son los vehículos
    //start timer
    auto begin = chrono::high_resolution_clock::now();
    vector<vector<double>> matrix_dist = this->_instance.dist;
    TaxiAssignmentSolution solucion = TaxiAssignmentSolution(this->_instance.n);
    int min_pos = 0;
    int dist_total = 0;
    for(int i = 0; i<matrix_dist.size();i++){
         int minimo = 999;
         for(int j = 0; j<matrix_dist.size();i++){
             if(minimo>matrix_dist[i][j] && solucion.isTaxiAssigned(j)){
                minimo = matrix_dist[i][j];
                min_pos = j;
            } 
        }
        dist_total += minimo;
        solucion.assign(min_pos, i);
    }
    //stop timer
    this->_objective_value = dist_total;
    this->_solution_status = 1;
    this->_solution = solucion;
    auto end = chrono::high_resolution_clock::now();
    auto elapse = chrono::duration_cast<chrono::nanoseconds>(end-begin);
    this->_solution_time = elapse.count();

}

double GreedySolver::getObjectiveValue() const {
    return this->_objective_value;
}

TaxiAssignmentSolution GreedySolver::getSolution() const {
    return this->_solution;
}

int GreedySolver::getSolutionStatus() const {
    return this->_solution_status;
}

double GreedySolver::getSolutionTime() const {
    return this->_solution_time;
}
