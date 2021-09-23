#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>


double microsegundos() { /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void sumaSubMax1 (int v[], int N){
    int i, j;
    int sumaMax = 0;
    int estaSuma;
    for (i = 0; i < N; i++){
        estaSuma = 0;
        for (j = i; j < N; j++){
            estaSuma = estaSuma + v[j];
            if (estaSuma > sumaMax) sumaMax = estaSuma;
        }
    }
}

void sumaSubMax2 (int v[], int N){
    int i;
    int sumaMax = 0;
    int estaSuma = 0;
    for (i = 0; i < N; i++){
        estaSuma = estaSuma + v[i];
        if (estaSuma > sumaMax){
            sumaMax = estaSuma;
        }
        else if (estaSuma < 0){
            estaSuma = 0;
        }
    }
}

void inicializar_semilla(){
    srand(time(NULL));
}

void aleatorio(int v[], int N){
    int i;
    int m = 2 * N + 1;
    for (i = 0; i < N; i++){
        v[i] = (rand() % m) - N;
    }
}

void listar_vector(int v[], int N){
    int i;
    for (i = 0; i < N; i++){
        printf(" %d ", v[i]);
    }
    printf("\t");
}
void test_recursivo_n1(){
    int v[32000],c[7]={500,1000,2000,4000,8000,16000,32000},i,j;
    double a,b,f_c,w=100;
    printf("\n\n%8s%8s%8s%16s%16s%16s\n\n", "n", "", "t(n)", "t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");
    for(j=0;j<6;j++) {
        for (i = 0; i < 7; i++) {
            if(c[i]>510) {
                printf("sec %d %d\t", j, c[i]);
                aleatorio(v, c[i]);
                a = microsegundos();
                //printf("%f\t", a = microsegundos());
                sumaSubMax1(v, c[i]);
                b = microsegundos();
                //printf("%f\t", b = microsegundos());
                f_c=1.0*c[i];
                printf("%f\t%f\t%f\t%f\n", b - a, (b-a)/pow(f_c,1.8), (b-a)/pow(f_c,2), (b-a)/pow(f_c,2.2));
            }           
            else{
                double d;
                printf("sec %d %d %s\t", j, c[i], "(*)");
                a = microsegundos();
                //printf("%f\t", a = microsegundos());
                for (int z = 0; z < w; z++) {
                    aleatorio(v,c[i]);
                    sumaSubMax1(v, c[i]);
                }
                b = microsegundos();
                d=(b-a)/w;
                f_c=1.0*c[i];
                printf("%f\t%f\t%f\t%f\n", d, d/pow(f_c,1.8), d/pow(f_c,2), d/pow(f_c,2.2));
            }
        }
    }
}

void test_recursivo_n2(){
    int v[32000],c[7]={500,1000,2000,4000,8000,16000,32000},i,j;
    double a,b,w=100,f_c,d;
    printf("\n\n%8s%16s%16s%16s%16s\n\n", "n", "t(n)", "t(n)/n^0.8", "t(n)/n^1", "t(n)/n^1.2");
    for(j=0;j<6;j++) {
        for (i = 0; i < 7; i++) { 
                printf("sec %d %d %s\t", j, c[i], "(*)");
                a = microsegundos();
                //printf("%f\t", a = microsegundos());
                for (int z = 0; z < w; z++) {
                    sumaSubMax2(v, c[i]);
                }
                b = microsegundos();
                f_c=1.0*c[i];
                d=(b-a)/w;
                printf("%f\t%f\t%f\t%f\n", d, d/pow(f_c,0.8), d/pow(f_c,1), d/pow(f_c,1.2));
        }
    }
}

int main(){

    inicializar_semilla();
    test_recursivo_n1();
    test_recursivo_n2();

    return 0;
}