#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"
#include "checker.h"
#include "greedy_solver.h"
#include "taxi_assignment_batching_solver.h"



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

    BatchingSolver solver2(instance2);
    solver2.solve();
    cout<<solver2.getObjectiveValue()<<endl;
    cout<<solver2.getSolutionStatus()<<endl;
    cout<<solver2.getSolutionTime()<<endl;
    return 0;
}