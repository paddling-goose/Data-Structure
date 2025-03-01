#include<iostream>

int getLine(char*str){
    int c=0,i=0;
    while((c = getchar())!='\n'){
        str[i++]=c;
    }
    str[i++]='\n';
    str[i] ='\0';
    return i-1;
}

int main(){
    int n=0;
    scanf("%d ",&n);

    for(int i=0; i<n ;i++){
        char str[81];
        int sum = getLine(str);

        int count =0, index =1;
        for(int j=0;j<sum;j++){ 
            if(str[j] == 'I'){
                count++;
            }else if(str[j] == 'O' && count>0){
                count--;
            }else{
                std::cout << "false" << std::endl;
                index =0;
                break;
            } 
        }
        if(index)
            std::cout << "true" << std::endl;
    }
    return 0;
}