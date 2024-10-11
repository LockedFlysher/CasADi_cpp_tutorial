//
// Created by lock on 2024/10/11.
//
#include <casadi/casadi.hpp>
#include <iostream>
using namespace casadi;

void print(const std::string name,DM dm){
    std::cout<<name<<": \n"<<dm<<std::endl;
}
void print(const std::string name,SX sx){
    std::cout<<name<<": \n"<<sx<<std::endl;
}

void print(const std::string name,Function f){
    std::cout<<name<<": \n"<<f<<std::endl;
}

int main() {
    /*
     * 如何创建Function
     * a.使用符号表达式
     * b.使用字典构建（后面结尾再说）
     * */
//    定义输入
    SX x = SX::sym("x",1);
    SX y = SX::sym("y",1);
//    定义输出
    SX f = SX::sym("f");
//    建立关系
    f = x*x+y*y;
    SX f2 = SX::sym("f2");
    f2 = x+y;
    Function myFunction = Function("myFunction",{x,y},{f,f2});
    print("myFunction",myFunction);

    /*
     * Function的调用
     * a.计算函数值
     * b.替换得到符号表达式
     * */
    std::vector<DM> input = {2,3};
    std::vector<DM> output = myFunction(input);

    std::cout<<output[0]<<std::endl;

    /*
     * 多输出的Function
     * 取得
     * */
    std::cout<<output[1]<<std::endl;

    /*
     * Function的自带的函数
     * 求导，Jacobian
     * */
    Function jac = myFunction.jacobian();
    print("jac",jac);
    std::vector<DM> jacInput = {DM::zeros(1,1),DM::ones(1,1),DM::ones(1,1),DM::ones(1,1)};
    auto jacOut = jac(jacInput);
    std::cout<<jacOut<<std::endl;
    /*
     * 嵌套Function
     * */
    Function cosFunction = Function("cosFunction",{x},{cos(x)});
    Function sinFunction = Function("sinFunction",{x},{sin(x)});
    Function inheritFunction = Function("inheritFunction",{x},sinFunction(cosFunction(x)[0]));
    print("inheritFunction",inheritFunction);
    DM inheritIn = DM::ones(1,1);
    DM inheritOut = inheritFunction({inheritIn})[0];
    print("inheritOut",inheritOut);

    /*
     * 使用字典构建Function（引出求解器构建）
     * */


    return 0;
}