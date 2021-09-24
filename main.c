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

int sumaSubMax1 (int v[], int N){
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
    return sumaMax;
}

int sumaSubMax2 (int v[], int N){
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
    return sumaMax;
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
void test1(){
    int x, y,k;
    int v[] = {7, 7, -5, -7, 6};
    printf("\ntest1\n");
    printf("%30s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
    k= sizeof(v)/ sizeof(int);
    listar_vector(v,k);
    x = sumaSubMax1(v,k);
    y = sumaSubMax2(v,k);
    printf("%15d%15d\n\n", x, y);
}

void test2(){
    int i, x, y,N=5;
    int v[N];
    printf("test2\n");
    printf("%30s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
    for (i = 0; i < N; i++){
        aleatorio(v,N);
        listar_vector(v,N);
        x = sumaSubMax1(v,N);
        y = sumaSubMax2(v,N);
        printf("%15d%15d\n", x, y);
    }
}

void test_propio(){
    int x, y,k,v[30]={-9,2,-5,-4,6,4,0,9,2,5,-2,-1,-9,-7,-1,9,-2,1,-7,-8,15,-2,-5,-4,16,7,-5,6,7,-7};
    printf("\ntest propio\n\n");

    k= sizeof(v)/ sizeof(int);
    listar_vector(v,k);
    printf("\n\n%15s%15s\n", "sumaSubMax1", "sumaSubMax2");
    x = sumaSubMax1(v,k);
    y = sumaSubMax2(v,k);
    printf("%10d%10d\n", x, y);

}


void test_recursivo_n1(){
    int *v,c[7]={500,1000,2000,4000,8000,16000,32000},i,j;
    double a,b,f_c,d;
    printf("\n\n%8s%8s%8s%16s%16s%16s\n\n", "n", "", "t(n)", "t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");
    for (i = 0; i < 7; i++) {
        v=malloc(c[i]*sizeof(int));
        printf("sec %d %d\t", j, c[i]);
        aleatorio(v, c[i]);
        a = microsegundos();
        sumaSubMax1(v, c[i]);
        b = microsegundos();
        if(b-a>500.0) {
                f_c=1.0*c[i];
                printf("%f\t%f\t%f\t%f\n", b - a, (b-a)/pow(f_c,1.8), (b-a)/pow(f_c,2), (b-a)/pow(f_c,2.2));
            }
            else {
                a = microsegundos();
                for (int z = 0; z <= 100; z++) {
                    aleatorio(v, c[i]);
                    sumaSubMax1(v, c[i]);
                }
                b = microsegundos();
                d = (b - a) / 100;
                f_c = 1.0 * c[i];
                printf("%f\t%f\t%f\t%f\n", d, d / pow(f_c, 1.8), d / pow(f_c, 2), d / pow(f_c, 2.2));
            }
        }
    free(v);
}

void test_recursivo_n2(){
    int *v,c[7]={500,1000,2000,4000,8000,16000,32000},i,j;
    double a,b,f_c,d;
    printf("\n\n%8s%16s%16s%16s%16s\n\n", "n", "t(n)", "t(n)/n*0.8", "t(n)/n", "t(n)/n*1.2");
    for (i = 0; i < 7; i++) {
        v= malloc(c[i]* sizeof(int));
        printf("sec %d %s\t", c[i], "(*)");
        a = microsegundos();
        //printf("%f\t", a = microsegundos());
        for (int z = 0; z < 100; z++) {
            sumaSubMax2(v, c[i]);
        }
        b = microsegundos();
        f_c=1.0*c[i];
        d=(b-a)/100;
        printf("%f\t%f\t%f\t%f\n", d, d/(f_c*0.8), d/(f_c*1), d/(f_c*1.2));
    }
    free(v);
}

int main(){

    inicializar_semilla();
    test1();
    test2();
    test_propio();
    test_recursivo_n1();
    test_recursivo_n2();

    return 0;
}
