#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"
#include "checker.h"
#include "greedy_solver.h"
#include "min_cost_flow_solver.h"


int main(int argc, char** argv) {
    std::string filename = "input/small_1.csv";

    TaxiAssignmentInstance instance(filename);
    TaxiAssignmentInstance instance2(filename);
    std::cout << filename << std::endl;

    TaxiAssignmentSolution solution(instance.n);

    GreedySolver solver(instance);

    solver.solve();

    
    TaxiAssignmentSolution FCFS = solver.getSolution();
    std::cout<<FCFS<<std::endl;
    cout<<solver.getObjectiveValue()<<endl;
    cout<<solver.getSolutionStatus()<<endl;
    cout<<solver.getSolutionTime()<<endl;

    MinCostFlowSolver::MinCostFlowSolversolverpro(instance2);
    solverpro.MinCostFlowSolver::solve();
    // TaxiAssignmentSolution MCF=MinCostFlowSolver::solverpro.getSolution();
    // cout<<MCF<<endl;
    // cout<<MinCostFlowSolver::solverpro.getObjectiveValue()<<endl;
    // cout<<MinCostFlowSolver::solverpro.getSolutionStatus()<<endl;
    // cout<<MinCostFlowSolver::solverpro.getSolutionTime()<<endl;


    return 0;
}