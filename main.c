#include <math.h>

char find_bin_pattern(int number){
    int mas[100] = {}, total = 0, count = 0;
    while (number>0){
        mas[total] = number%2;
        number = number/2;
        total+=1;
    }
    for (int i = 0; i<97; i++){
        if (mas[i] == 1 && mas[i+1] == 0 && mas[i+2] == 1){
            count+=1;
            mas[i] = 0;
            mas[i+1] = 0;
            mas[i+2] = 0;}
    }
    return count;
}
