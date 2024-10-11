#include <iostream>
#include <string>
#include <casadi/casadi.hpp>

using namespace casadi;
int main(){
//    创建符号变量
    casadi::SX q = casadi::SX::sym("q",7);
    std::cout<<"q: "<<q<<std::endl;

    SX q2 = SX::sym("q2",7);
    std::cout<<"q2: "<<q2<<std::endl;

//    拼接符号变量
//      vertcat 垂直拼接 horzcat 水平拼接
    SX qh = SX::horzcat({q,q2});
    SX qv = SX::vertcat({q,q2});
    std::cout<<"qh: "<<qh<<std::endl;
    std::cout<<"qv: "<<qv<<std::endl;
//      转置符号变量
    SX qt = qh.T();
    std::cout<<"transpose of qh: " <<qt <<std::endl;

//    修改创建的符号变量的值
    SX t1 = SX::sym("t1",3);

    std::cout<<"t1 before: "<<t1<<std::endl;
    t1(0) = 3;
    t1(1) = 1;
    t1(2) = 4;
    std::cout<<"t1 after: "<<t1<<std::endl;

    SX t2 = SX::ones(3,1);
    t2(1) = 3;
    t2(2) = 1;
    std::cout<<"t2: "<<t2<<std::endl;

    SX T01 = casadi::SX::zeros(4,4);

    T01(Slice(0,3,1),3) = t1;
    T01(3,3) = 1;
    T01(2,2) = -1;
    T01(0,0) = cos(q(0));
    T01(0,1) = -sin(q(0));
    T01(1,0) = -sin(q(0));
    T01(1,1) = -cos(q(0));
    std::cout<<"T01: "<<T01<<std::endl;

    auto T12 = SX::zeros(4,4);
    T12(Slice(0,3),3) = t2;
    T12(3,3) = 1;
    T12(0,0) = cos(q(1));
    T12(0,1) = -sin(q(1));
    T12(2,0) = sin(q(1));
    T12(2,1) = cos(q(1));
    std::cout<<"T12: "<<T12<<std::endl;

//    矩阵乘法
    casadi::SX A = SX::zeros(2,2);
    A(0,0) = 100;
    A(0,1) = 50;
    A(1,0) = -1;
    A(0,1) = -2;
    casadi::SX B = SX::zeros(2,2);
    B(0,0) = 0.5;
    B(0,1) = 0.1;
    B(1,0) = 0.2;
    B(0,1) = 0.4;

    std::cout<< "test matrix multiplication: "<<std::endl;
    std::cout<< "A: "<<A<<std::endl;
    std::cout<< "B: "<<B<<std::endl;
    std::cout<< "element multiplication: "<<A*B<<std::endl;
    std::cout<< "matrix multiplication: "<<SX::mtimes(A,B)<<std::endl;
    return 0;
};