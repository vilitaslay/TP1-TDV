#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"
#include "checker.h"
#include "greedy_solver.h"
#include "min_cost_flow_solver.h"
using namespace std;

int main(int argc, char** argv) {
    std::string filename = "input/small_1.csv";

    TaxiAssignmentInstance instance(filename);
    std::cout << filename << std::endl;

    TaxiAssignmentSolution solution(instance.n);

    GreedySolver solver(instance);

    solver.solve();

    TaxiAssignmentSolution FCFS = solver.getSolution();
    std::cout<<FCFS<<std::endl;
    cout<<solver.getObjectiveValue()<<endl;
    cout<<solver.getSolutionStatus()<<endl;
    cout<<solver.getSolutionTime()<<endl;

    MinCostFlowSolver solverpro(instance);
    solverpro.solve();
    TaxiAssignmentSolution MCF=solverpro.getSolution();
    cout<<MCF<<endl;
    cout<<solverpro.getObjectiveValue()<<endl;
    cout<<solverpro.getSolutionStatus()<<endl;
    cout<<solverpro.getSolutionTime()<<endl;


    return 0;
}