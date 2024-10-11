//
// Created by lock on 2024/10/11.
//
#include <iostream>
#include <casadi/casadi.hpp>

using namespace casadi;

/*
 * test problem:
 * min x0^2 + x1^2
 * s.t. x0+x1-10 = 0
 * */

int main() {
//    auto x= SX::sym("x",2);
//    auto obj = pow(x(0),2)+ pow(x(1),2);
//    auto g = x(0)+x(1)-10;
//
//    SXDict nlp = {{"x",x},{"f",obj},{"g",g}};
//    Function solver = nlpsol("solver","ipopt",nlp);
//    std::map<std::string,DM> arg,res;
//    arg["lbx"] = -DM::inf(2);
//    arg["ubx"] = DM::inf(2);
//    arg["lbg"] = 0;
//    arg["ubg"] = 0;
//
//    arg["x0"] = DM::zeros(2);
//
//    res = solver(arg);
//
//    std::cout<<"----------"<<std::endl;
//    std::cout<<"obj in solution = " <<res.at("f")<<std::endl;
//    std::cout<<"primal solution = " << res.at("x")<<std::endl;
//    std::cout<<"dual solution(x) =" <<res.at("lam_x")<<std::endl;
//    std::cout<<"dual solution(g) =" <<res.at("lam_g")<<std::endl;

    /*
     * test problem 2
     * max 2x+y
     * s.t x+y <=40
     *      4x-y>=10
     *      2x+y<=50
     *      x,y>0
     * */
//    auto x = SX::sym("x", 2);
//    auto obj = 2 * x(0) + x(1);
//    auto g = SX::vertcat(
//            {x(0) + x(1),
//             4 * x(0) - x(1),
//             2 * (x(0) + x(1))});
//
//    SXDict nlp = {{"x", x},
//                  {"f", obj},
//                  {"g", g}};
//    Function solver = nlpsol("solver", "ipopt", nlp);
//    std::map<std::string, DM> arg, res;
//    arg["lbx"] = 0;
//    arg["ubx"] = DM::inf(2);
//    arg["lbg"] = DM::vertcat({-DM::inf(), 10, -DM::inf()});
//    arg["ubg"] = DM::vertcat({40, DM::inf(), 50});
//
//    arg["x0"] = DM::zeros(2);
//
//    res = solver(arg);
//
//    std::cout << "----------" << std::endl;
//    std::cout << "obj in solution = " << res.at("f") << std::endl;
//    std::cout << "primal solution = " << res.at("x") << std::endl;
//    std::cout << "dual solution(x) =" << res.at("lam_x") << std::endl;
//    std::cout << "dual solution(g) =" << res.at("lam_g") << std::endl;

    /*
     * Nonlinear optimization problem
     *
     * min (x-2)^2 + (y-1)^2
     * s.t x^2+y^2<=4
     *     x*y>=1
     *     x+y>=1
     *
     * */

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

    std::cout << "----------" << std::endl;
    std::cout << "obj in solution = " << res.at("f") << std::endl;
    std::cout << "primal solution = " << res.at("x") << std::endl;
    std::cout << "dual solution(x) =" << res.at("lam_x") << std::endl;
    std::cout << "dual solution(g) =" << res.at("lam_g") << std::endl;

    return 0;
}