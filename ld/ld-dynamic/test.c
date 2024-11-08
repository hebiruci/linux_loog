#include <stdio.h>
#include <unistd.h> 
int add(int, int);
int sub(int, int);

int main(){

int a =1;
int b =2;

printf("sum=%d, sub=%d\n", add(a,b), sub(a,b));
sleep(10000);
return 0;
}
