//
// Created by lock on 2024/10/11.
//
// DM ： Dense Matrix

#include "iostream"
#include "string"
#include "casadi/casadi.hpp"

using namespace casadi;

void print(const std::string name,DM dm){
    std::cout<<name<<": \n"<<dm<<std::endl;
}
void print(const std::string name,SX sx){
    std::cout<<name<<": \n"<<sx<<std::endl;
}

int main(){
//    创建稠密矩阵，以及基本的操作
    DM q = DM::ones(7,1);
    print("q",q);
    DM q2 = DM::rand(7,1);
    print("q2",q2);

    auto qh = DM::horzcat({q, q2});
    print("qh",qh);
    auto qv = DM::vertcat({q, q2});
    print("qv",qv);

    DM qt = qh.T();
    print("qt",qt);

//    修改稠密矩阵的变量
    DM t1 = DM::zeros(3,1);
    DM t2 = DM::ones(3,1);

    print("t1 before",t1);
    print("t2 before",t2);
    t1(0) = 0;
    t1(1) = 0;
    t1(2) = 0.214;

    t2(1) = 0.15;
    t2(2) = -0.2314;
    print("t1 after",t1);
    print("t2 after",t2);

    DM T01 = DM::zeros(4,4);
    T01(Slice(0,3),3) = t1;

    casadi::DM A = DM::zeros(2,2);
    A(0,0) = 100;
    A(0,1) = 50;
    A(1,0) = -1;
    A(0,1) = -2;
    casadi::DM B = DM::zeros(2,2);
    B(0,0) = 0.5;
    B(0,1) = 0.1;
    B(1,0) = 0.2;
    B(0,1) = 0.4;

    std::cout<< "test matrix multiplication: "<<std::endl;
    std::cout<< "A: "<<A<<std::endl;
    std::cout<< "B: "<<B<<std::endl;
    std::cout<< "element multiplication: "<<A*B<<std::endl;
    std::cout<< "matrix multiplication: "<<DM::mtimes(A,B)<<std::endl;
    return 0;
}