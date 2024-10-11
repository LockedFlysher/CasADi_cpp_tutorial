//
// Created by lock on 2024/10/11.
//
#include <iostream>
#include <string>
#include <casadi/casadi.hpp>
#include <dlfcn.h>
using namespace casadi;

int main(){
    auto x = SX::sym("x", 2);
    auto obj = pow(x(0)-2,2) + pow(x(1)-1,2);
    auto g = SX::vertcat(
            {pow(x(0),2) + pow(x(1),2),
             x(0)*x(1),
             x(0)+x(1)});

    SXDict nlp = {{"x", x},
                  {"f", obj},
                  {"g", g}};
    Function solver = nlpsol("solver", "ipopt", nlp);
    std::map<std::string, DM> arg, res;
    arg["lbx"] = -DM::inf(2);
    arg["ubx"] = DM::inf(2);
    arg["lbg"] = DM::vertcat({-DM::inf(), 1, 1});
    arg["ubg"] = DM::vertcat({4, DM::inf(), DM::inf()});

    arg["x0"] = DM::zeros(2);

    res = solver(arg);

    std::cout << "----- solution 1 -----" << std::endl;
    std::cout << "obj in solution = " << res.at("f") << std::endl;
    std::cout << "primal solution = " << res.at("x") << std::endl;
    std::cout << "dual solution(x) =" << res.at("lam_x") << std::endl;
    std::cout << "dual solution(g) =" << res.at("lam_g") << std::endl;

    solver.generate_dependencies("f.c");
    std::string compile_command = "gcc -fPIC -shared -O3 f.c -o f.so";
    int flag = system(compile_command.c_str());
    casadi_assert(flag==0,"Compilation failed");

//    load .so to solver
    Function solverSO = nlpsol("solver","ipopt","/home/lock/CLionProjects/CasADi_tutorial/cmake-build-debug/f.so");
    res = solverSO(arg);


    std::cout << "----- solution 1 -----" << std::endl;
    std::cout << "obj in solution = " << res.at("f") << std::endl;
    std::cout << "primal solution = " << res.at("x") << std::endl;
    std::cout << "dual solution(x) =" << res.at("lam_x") << std::endl;
    std::cout << "dual solution(g) =" << res.at("lam_g") << std::endl;
}