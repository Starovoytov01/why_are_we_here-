#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    printf("num of elements: "); //string1
    int n;
    scanf("%d",&n);
    getchar(); // delete \n
    if (n <= 0)
        exit(0);
    
    char apexs[n];
    int table[n][n];
    
    printf("Enter names with one letter\n"); //string2
    for(int i=0; i<n; i++){
        printf("%d: ",i+1);
        scanf("%c", &apexs[i]);
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
        for(int j=0; j<n; j++){
            table[i][j] = 0;
        }
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

    for(int i=0; i<n; i++) {
        printf("%c ", apexs[i]);
        for (int j=0; j<n; j++) {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
    
    FILE *fp=fopen("graph.dot", "w"); //string9

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
