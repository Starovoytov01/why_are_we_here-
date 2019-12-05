#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _swap(int *arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void _qsort(int *arr, int *sub_arr, int low, int high){
    int pivot = arr[low];
    int i = low;
    int j = high;
    
    while (i <= j){
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j){
            _swap(arr, i, j);
            _swap(sub_arr, i, j);
            i++;
            j--;
        }
    }
    if (j > low)
        _qsort(arr, sub_arr, low, j);
    if (i < high)
        _qsort(arr, sub_arr, i, high);
}

int *sort(int n, char *apexs, int **table){
    int *power = calloc(n, sizeof(int));
    
    for(int i=0 ;i<n; i++){
        power[i] = 0;
        for(int j=0; j<n; j++){
            power[i] += table[i][j];
            power[i] += table[j][i];
        }
    }
    
    int *changes = calloc(n, sizeof(int));
    for(int i=0; i<n; i++){
        changes[i] = i;
    }
    
    _qsort(power, changes, 0, n-1);

    char  *temp_apexs = calloc(n, sizeof(char));
    int  **temp_table = calloc(n, sizeof(int*));

    for(int i=0; i<n; i++){
        temp_apexs[i] = apexs[i];
        temp_table[i] = table[i];
    }

    for(int i=0; i<n; i++){
        apexs[i] = temp_apexs[ changes[i] ];
        table[i] = temp_table[ changes[i] ];
    }

    
    return power;
}


int main(){
    printf("num of elements: "); //string1
    int n;
    scanf("%d",&n);
    getchar(); // delete \n
    if (n <= 0)
        exit(0);
    
    char apexs[n];
    char apexs2[n];
    int **table = calloc(n, sizeof(int*));
    
    printf("Enter names with one letter\n"); //string2
    for(int i=0; i<n; i++){
        printf("%d: ",i+1);
        scanf("%c", &apexs[i]);
        apexs2[i] = apexs[i];
        getchar(); //delete \n
        for (int j=0; j<i; j++){
            if( apexs[i] == apexs[j] ){
                printf("This name allready exist, enter another\n"); //string3
                i--;
            }
        }

    }
    
    printf("Enter for all elements connection dividing spaces:\n"); //string4
    printf("Exp: A B C\n"); //string5
    
    for(int i=0; i<n; i++){
        table[i] = calloc(n, sizeof(int));
    }
    
    for(int i=0; i<n; i++){
        printf("%c: ", apexs[i]);
        char c;
        int enter_cahr = 0;
        while( (c=getchar()) != '\n' ){
            if(c == ' '){
                enter_cahr = 0;
            } else if(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || enter_cahr == 0){
                for(int number = 0; number<n; number++){
                    if(apexs[number] == c){
                        table[i][number]++;
                        number=n;
                    }
                }
                
                enter_cahr = 1;
            }
        }
        if(enter_cahr == 0){
            for(int number = 0; number<n; number++){
                if(apexs[number] == c){
                    table[i][number]++;
                    number=n;
                }
            }
        }
    }
    
    printf("Table:\n"); //string6

    int graph_check = 1;
    for(int i=0; i<n; i++){
        int temp_graph_check = 0;
        for(int j=0; j<n; j++){
            if(table[i][j] == 1)
                temp_graph_check = 1;
    
            if(table[j][i] == 1)
                temp_graph_check = 1;
        }
        if(temp_graph_check == 0)
            graph_check=0;
    }
    if(graph_check == 0){
        printf("unrelated graph\n"); //string7
    } else {
        printf("related graph\n"); //string8

    }
    
    printf(" \t");
    for(int i=0; i<n; i++) {
        printf("%c ", apexs2[i]);
    }
    printf("\n");
    for(int i=0; i<n; i++) {
        printf("%c\t", apexs[i]);
        for (int j=0; j<n; j++) {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
    
    int *power = sort(n, apexs, table);
    printf("Sorted table:\n"); //string11
    
    printf("    \t");
    for(int i=0; i<n; i++) {
        printf("%c ", apexs2[i]);
    }
    printf("\n");
    
    for(int i=0; i<n; i++) {
        printf("%c (%d)\t", apexs[i], power[i]);
        for (int j=0; j<n; j++) {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }


    FILE *fp = fopen("graph.dot", "w"); //string9

    if(fp == NULL) {
        printf("Unable to create file\n"); //string10
        exit(0);
    }

    fputs("graph G {", fp);
    for(int i=0; i<n; i++){
        char temp_char = apexs[i];
        fputs(&temp_char, fp);
        fputs("; ", fp);
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            for(int k=0; k<table[i][j]; k++){
                char temp_char = apexs[i];
                fputs(&temp_char, fp);
                fputs("--", fp);
                temp_char = apexs[j];
                fputs(&temp_char, fp);
                fputs("; ", fp);
            }
        }
    }
    fputs("}", fp);



    fclose(fp);
    return 0;
}
