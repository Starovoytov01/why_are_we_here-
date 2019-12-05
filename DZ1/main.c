#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
int main(){
    
    printf("Enter numbers\n");
    printf("END -> [Ctrl + X]\n");
    int flag = 0, n = 0, *decimal = calloc(1, sizeof(int));
    while(flag > -1){

        printf("%d: ", flag);
        long int temp_dec_num;
        scanf("%ld", &temp_dec_num);
        char c = getchar();
        if(c == 24){ // ^X
            n = flag;
            flag = -1;
        } else {
            if( temp_dec_num < -2147483647 || 2147483647 < temp_dec_num){
                printf("!!! Enter numbers between -2147483647 and 2147483647\n");
            } else {
                if(flag > 1){
                    int *temp_dec = calloc(flag, sizeof(int));
                    for(int i=0; i<flag; i++){
                        temp_dec[i] = decimal[i];
                    }
                    decimal[flag] = (int) temp_dec_num;
                } else{
                    decimal[flag] = (int) temp_dec_num;
                }
                flag++;
            }
        }
        
    }
    if(n < 1)
        exit(9);

    char **binary = calloc(n, sizeof(char*));
    for(int i=0; i<n; i++){
        binary[i] = calloc(32, sizeof(char));
        int temp_decimal = decimal[i];
        if(temp_decimal < 0){
            temp_decimal*=-1;
            binary[i][0] = '-';
        } else {
            binary[i][0] = 0;
        }
            
        int j=32;
        if(temp_decimal == 0){
            binary[i][31] = '0';
        } else {
            while(temp_decimal != 0 && j > 0){
                binary[i][--j] = '0' + temp_decimal%2;
                temp_decimal /= 2;
            }
        }
    }
    
    printf("Output 1st set: {");
    for(int i=0; i<n-1; i++){
        printf("%d, ", decimal[i]);
    }
    printf("%d };\n",decimal[n-1]);
    
    printf("Output 2nd set: {");
    for(int i=0; i<n-1; i++){
        for(int j=0; j<32; j++){
            if(binary[i][j] != 0)
                printf("%c", binary[i][j]);
        }
        printf(", ");
    }
    for(int j=0; j<32; j++){
        if(binary[n-1][j] != 0)
            printf("%c", binary[n-1][j]);
    }
    printf(" };\n");

    return 0;
}
