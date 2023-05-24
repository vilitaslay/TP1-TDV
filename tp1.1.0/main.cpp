#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"
#include "checker.h"
#include "greedy_solver.h"
#include "taxi_assignment_batching_solver.h"

void ejercicio4(string filename, vector<string> directorio){
    fstream fout;
    fout.open(filename, ios::out);
    fout << "Dataset,Solucion Greedy,Solucion Batching,Mejora Comparativa, Tiempo Greedy, Tiempo Batching, Diferencia de tiempo, \n";
    for(string i : directorio){
        TaxiAssignmentInstance instance(i);
        GreedySolver Gsolver (instance);
        Gsolver.solve();
        double zg = Gsolver.getObjectiveValue();
        double tg = Gsolver.getSolutionTime();

        BatchingSolver Bsolver (instance);
        Bsolver.solve();
        double zb = Bsolver.getObjectiveValue();
        double tb= Bsolver.getSolutionTime();
        float gap = (zg - zb)/zb;
        float tgap = (tb/tg);
        fout << i <<","<< zg <<","<< zb <<","<< gap<<","<<tg<<","<<tb<<","<<tgap<<"\n";
    }
    fout.close();
    //espera a q te devuelvan el parcial pero si aprobas amigo tipo espera a fijarte cuando te la devuelvan. deberian dartelo pronto
    // que le explicaste a lari okay si tiene sentido
}


int main(int argc, char** argv) {
    std::string filename = "input/small_1.csv";

    TaxiAssignmentInstance instance(filename);
    std::cout << filename << std::endl;

    TaxiAssignmentSolution solution(instance.n);

    GreedySolver solver(instance);

    solver.solve();
    // TaxiAssignmentSolution FCFS = solver.getSolution();
    // std::cout<<FCFS<<std::endl;
    // std::cout<<solver.getObjectiveValue()<<std::endl;
    // std::cout<<solver.getSolutionStatus()<<std::endl;
    // std::cout<<solver.getSolutionTime()<<std::endl;

    // BatchingSolver solver2(instance);
    // solver2.solve();
    // std::cout<<solver2.getObjectiveValue()<<std::endl;
    // std::cout<<solver2.getSolutionStatus()<<std::endl;
    // std::cout<<solver2.getSolutionTime()<<std::endl;

    // yo
    std::vector<string> directorio = {"input/small_0.csv", "input/small_1.csv", "input/small_2.csv", "input/small_3.csv", "input/small_4.csv", "input/small_5.csv", "input/small_6.csv", "input/small_7.csv", "input/small_8.csv", "input/small_9.csv", "input/medium_0.csv", "input/medium_1.csv", "input/medium_2.csv", "input/medium_3.csv", "input/medium_4.csv", "input/medium_5.csv", "input/medium_6.csv", "input/medium_7.csv", "input/medium_8.csv", "input/medium_9.csv", "input/large_0.csv", "input/large_1.csv", "input/large_2.csv", "input/large_3.csv", "input/large_4.csv", "input/large_5.csv", "input/large_6.csv", "input/large_7.csv", "input/large_8.csv", "input/large_9.csv", "input/xl_0.csv", "input/xl_1.csv", "input/xl_2.csv", "input/xl_3.csv", "input/xl_4.csv", "input/xl_5.csv", "input/xl_6.csv", "input/xl_7.csv", "input/xl_8.csv", "input/xl_9.csv"};
    ejercicio4("Experimentacion",directorio); //PITAZO





    return 0;
}