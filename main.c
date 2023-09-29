#include <stdio.h>
#include <stdlib.h>
#define min(x,y) (((x)>(y)) ? (x) : (y))
void main() {
    int a, b, c;
    while(a>1000 || a<=1 || b>1000 || b<=1){
    scanf("%d  %d", &a, &b);
    for (int i = 1; i <= min(a, b)/2; i++){
        if (a%i == 0 && b%i == 0){
            c = i;}}} 
printf("HOD = %d\n", c);
}