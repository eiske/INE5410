#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

unsigned int compute_pi(unsigned int, unsigned int);

int main(int argc, char **argv){
  MPI_Init(&argc, &argv);
  unsigned int pontos;
  unsigned int pontos_no_circulo;
  unsigned int i;
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0) {
    for (int i = 1; i < size; ++i) {
      MPI_Recv(&pontos, pontos, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      pontos_no_circulo = compute_pi(rank, pontos);
    }
  } else {
    MPI_Send(&pontos, pontos, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();

  if(argc != 2){
    printf("Uso:\n");
    printf("\t%s <numero de pontos a serem sorteados>\n", argv[0]);
    return 1;
  }
  
  pontos = atoi(argv[1]);

  // retorna quantos pontos sorteados cairam dentro do circulo
  // aqui estamos considerando uma semente para o gerador de 
  // numeros aleatorios fixa = 0

  // calcula a aproximacao de Pi baseado nos pontos sorteados
  printf("Pi = %.040f\n", ((double)pontos_no_circulo/(double)pontos)*4);

  return 0;
}

unsigned int compute_pi(unsigned int seed, unsigned int pontos){
  unsigned int i;
  unsigned int pontos_no_circulo;
  double x, y;

  pontos_no_circulo = 0;
  srand(seed);
  
  for(i=0; i<pontos; i++){
  	// sorteia um ponto: coordenadas x e y dentro do quadrado
  	// consideramos que R = 1, então x e y pertencem ao intervalo [0; 1]
    x = (double)rand()/(double)(RAND_MAX);
    y = (double)rand()/(double)(RAND_MAX);      
    
    // verifica se o ponto sorteado encontra-se dentro do circulo
    // um ponto (x, y) esta dentro do circulo se: x^2 + y^2 < R^2
    // nesse caso, consideramos R = 1
    if( (x*x + y*y) < 1 ){
      pontos_no_circulo++;
    }      
  }
  
  return pontos_no_circulo;
}
