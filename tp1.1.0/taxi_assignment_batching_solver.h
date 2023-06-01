#ifndef TAXI_ASSIGNMENT_BATCHING_SOLVER_H
#define TAXI_ASSIGNMENT_BATCHING_SOLVER_H

#include <cmath>
#include <cstdint>
#include <vector>
#include <iostream>
#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"
#include "ortools/graph/min_cost_flow.h"
#include <chrono>


class BatchingSolver
{
	public:
        BatchingSolver();
        BatchingSolver(TaxiAssignmentInstance &instance);

        void setInstance(TaxiAssignmentInstance &instance);
        void create_graph(int formato);
        void solve(int formato);

        double getObjectiveValue() const;
        TaxiAssignmentSolution getSolution() const;
        int getSolutionStatus() const;
        double getSolutionTime() const;
        double getRentFare() const;
        double getRentDist() const;
        
	private:
        // Completar con lo que sea necesario.
 

        // Instance, problem and results attributes
        TaxiAssignmentInstance _instance;
        TaxiAssignmentSolution _solution;
        operations_research::SimpleMinCostFlow _grafo;
        double _objective_value;
        double _rent_dist;
        double _rent_fare;
        int _solution_status;
        double _solution_time;

};

#endif