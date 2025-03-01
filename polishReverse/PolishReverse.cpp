#include<iostream>
#include<cctype>
#include"mystack"

int main(){
    Mystack my_stack;

    int c =0 , operatorCount = 0 , operandCount = 0;
    while((c=getchar())!=EOF && c !='\n'){
        if(isdigit(c)){
            int push = c-'0';
            my_stack.push(push);
            operandCount ++;
        }else{
          
            operatorCount++;

            int a=0, b=0, result =0;
            my_stack.top(a); //第一个弹出，作为减数、除数
            my_stack.pop();
            my_stack.top(b); //第二个弹出，作为被减数、被除数
            my_stack.pop();

            /*判断运算符，进行运算*/
            switch(c){
                case '+':
                    result = a+b;
                    break;
                case '-':
                    result = b-a;
                    break;
                case '*':
                    result = a*b;
                    break;
                case '/':
                    result = b/a;
                    break;
            }
            /*将计算得到的结果压入栈中*/
            my_stack.push(result);
        }
    }

    if (operandCount - operatorCount != 1 || my_stack.size() != 1) {
        std::cout << "none" << std::endl;  // 最终不符合规则
        return 0;
    }

    /*循环完成，弹出结果*/
    int d=0;
    my_stack.top(d);
    std::cout << d  << std::endl;
    return 0;
}