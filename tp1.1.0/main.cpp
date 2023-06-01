#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"
#include "checker.h"
#include "greedy_solver.h"
#include "taxi_assignment_batching_solver.h"

void ejercicio4(string filename, vector<string> directorio){
    fstream fout;
    fout.open(filename, ios::out);
    fout << "Dataset,Solucion Greedy,Solucion Batching 0,Solucion Batching 1,Solucion Batching 2,Mejora Comparativa Greedy-Batching 0,Mejora Comparativa Greedy-Batching 1,Mejora Comparativa Greedy-Batching 2, Tiempo Greedy, Tiempo Batching 0,Tiempo Batching 1,Tiempo Batching 2, Diferencia de tiempo Greedy-Batching 0,Diferencia de tiempo Greedy-Batching 1,Diferencia de tiempo Greedy-Batching 2, \n";
    for(string i : directorio){
        TaxiAssignmentInstance instance(i);
        GreedySolver Gsolver (instance);
        Gsolver.solve();
        double zg = Gsolver.getObjectiveValue();
        double tg = Gsolver.getSolutionTime();

        BatchingSolver Bsolver0 (instance);
        //Batching normal 
        Bsolver0.solve(0);
        double zb0 = Bsolver0.getObjectiveValue();
        double tb0= Bsolver0.getSolutionTime();
        
        BatchingSolver Bsolver1 (instance);
        Bsolver1.solve(1);
        double zb1 = Bsolver1.getObjectiveValue();
        double tb1 = Bsolver1.getSolutionTime();

        BatchingSolver Bsolver2 (instance);
        Bsolver2.solve(2);
        double zb2 = Bsolver2.getObjectiveValue();
        double tb2 = Bsolver2.getSolutionTime();

        //Testeamos greedy contra todos los tipos de Batching
        float gap0 = (zg - zb0)/zb0;
        float tgap0 = (tb0/tg);

        float gap1 = (zg - zb1)/zb1;
        float tgap1 = (tb1/tg);

        float gap2 = (zg - zb2)/zb2;
        float tgap2 = (tb2/tg);
        fout << i <<","<< zg <<","<< zb0 <<","<< zb1 <<","<< zb2 <<","<< gap0 <<","<< gap1 <<","<< gap2 <<","<<tg<<","<<tb0<<","<<tb1<<","<<tb2<<","<<tgap0<<","<< tgap1<<","<<tgap2<<","<<"\n";
    }
    fout.close();
    //espera a q te devuelvan el parcial pero si aprobas amigo tipo espera a fijarte cuando te la devuelvan. deberian dartelo pronto
    // que le explicaste a lari okay si tiene sentido
}


int main(int argc, char** argv) {
    std::string filename = "input/small_1.csv";

    TaxiAssignmentInstance instance(filename);
    // std::cout << filename << std::endl;

    // TaxiAssignmentSolution solution(instance.n);

    // GreedySolver solver(instance);

    // solver.solve();
    // TaxiAssignmentSolution FCFS = solver.getSolution();
    // std::cout<<FCFS<<std::endl;
    // std::cout<<solver.getObjectiveValue()<<std::endl;
    // std::cout<<solver.getSolutionStatus()<<std::endl;
    // std::cout<<solver.getSolutionTime()<<std::endl;

    BatchingSolver solver2(instance);
    solver2.solve(0);
    std::cout<<solver2.getObjectiveValue()<<std::endl;
    std::cout<<solver2.getRentDist()<<std::endl;
    std::cout<<solver2.getRentFare()<<std::endl;

    BatchingSolver solver3(instance);
    solver3.solve(1);
    std::cout<<solver3.getObjectiveValue()<<std::endl;
    std::cout<<solver3.getRentDist()<<std::endl;
    std::cout<<solver3.getRentFare()<<std::endl;
    

    BatchingSolver solver4(instance);
    solver4.solve(2);
    std::cout<<solver4.getObjectiveValue()<<std::endl;
    std::cout<<solver4.getRentDist()<<std::endl;
    std::cout<<solver4.getRentFare()<<std::endl;
    
    
    // std::vector<string> directorio = {"input/small_0.csv", "input/small_1.csv", "input/small_2.csv", "input/small_3.csv", "input/small_4.csv", "input/small_5.csv", "input/small_6.csv", "input/small_7.csv", "input/small_8.csv", "input/small_9.csv", "input/medium_0.csv", "input/medium_1.csv", "input/medium_2.csv", "input/medium_3.csv", "input/medium_4.csv", "input/medium_5.csv", "input/medium_6.csv", "input/medium_7.csv", "input/medium_8.csv", "input/medium_9.csv", "input/large_0.csv", "input/large_1.csv", "input/large_2.csv", "input/large_3.csv", "input/large_4.csv", "input/large_5.csv", "input/large_6.csv", "input/large_7.csv", "input/large_8.csv", "input/large_9.csv", "input/xl_0.csv", "input/xl_1.csv", "input/xl_2.csv", "input/xl_3.csv", "input/xl_4.csv", "input/xl_5.csv", "input/xl_6.csv", "input/xl_7.csv", "input/xl_8.csv", "input/xl_9.csv"};
    // ejercicio4("Experimentacion",directorio); //PITAZO





    return 0;
}