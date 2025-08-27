#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <ctime>


#define N 10

class Operaciones {
    public:


        void llenarMatrizAleatoria(int M[N][N]){
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    M[i][j] = rand() % 10;
               }
            }
        }

        void llenarMatrizAscendente(int M[N][N]){
            
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    M[i][j] = (i * N) + j + 1;
                }
            }
        }

        void llenarMatrizDescendente(int M[N][N]) {
            for(int i = 0; i < N; i++) {
                for(int j = 0; j < N; j++) {
                    M[i][j] = (N * N) - (i * N + j);
                }
            }
        }

        void sumarMatrices(int A[N][N], int B[N][N], int R[N][N]){
            #pragma omp parallel for
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    R[i][j] = A[i][j] + B[i][j];
                }
            }
        }

        void restaMatrices(int A[N][N], int B[N][N], int R[N][N]){
            #pragma omp parallel for
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    R[i][j] = A[i][j] - B[i][j];
                }
            }
        }

        void multiplicarMatrices(int A[N][N], int B[N][N], int R[N][N]){
            #pragma omp parallel for
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    R[i][j] = 0;
                    for(int k = 0; k < N; k++){
                        R[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }

        void transponerMatriz(int A[N][N], int T[N][N]){
            #pragma omp parallel for
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    T[j][i] = A[i][j];
                }
            }
        }

};

int main()
{
    int opcion = -1;
    
    int ma[N][N], mb[N][N], mr[N][N];


    Operaciones oper;

    oper.llenarMatrizAscendente(ma);
    oper.llenarMatrizDescendente(mb);
    

    double inicio, fin, tiempo;
    do {
        printf("Selecciona una opcion\n");
        printf("0 Salir\n");
        printf("1 Sumar\n");
        printf("2 Restar\n");
        printf("3 Multiplicar\n");
        printf("4 Transpuesta\n");
        scanf(" %i", &opcion);
        switch (opcion) {
        case 0: 
            printf("Programa terminado");
        break;
        case 1:
            inicio = omp_get_wtime();
            //clock_t start = clock();
            oper.sumarMatrices(ma, mb, mr);
            
            fin = omp_get_wtime();
            //clock_t end = clock();

            
            tiempo = fin - inicio;
            //fin - inicio
            printf("\nEl tiempo de ejecucion del proceso fue de %f\n", tiempo);
        break;
        case 2:
            inicio = omp_get_wtime();
            oper.restaMatrices(ma, mb, mr);
            fin = omp_get_wtime();
            tiempo = fin - inicio;
            printf("\nEl tiempo de ejecucion del proceso fue de %f\n", tiempo);
            break;
        case 3:
            inicio = omp_get_wtime();
            oper.multiplicarMatrices(ma, mb, mr);
            fin = omp_get_wtime();
            tiempo = fin - inicio;
            printf("\nEl tiempo de ejecucion del proceso fue de %f\n", tiempo);
            break;
        case 4:
            inicio = omp_get_wtime();
            oper.transponerMatriz(ma, mr);
            fin = omp_get_wtime();
            tiempo = fin - inicio;
            printf("\nEl tiempo de ejecucion del proceso fue de %f\n", tiempo);
            break;
        default: break;
        }

        printf("Matriz A\n");
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                printf("%i \t", ma[i][j]);
            }
            printf("\n");
        }

        printf("\n");

        printf("Matriz B\n");
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                printf("%i \t", mb[i][j]);
            }
            printf("\n");
        }

        printf("\n");

        printf("Matriz Resultado\n");
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                printf("%i \t", mr[i][j]);
            }
            printf("\n");
        }

    }while(opcion != 0);

    return 0;
}