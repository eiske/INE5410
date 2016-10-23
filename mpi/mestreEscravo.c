#include <mpi.h>
#include <stdio.h>

int main (int argc, char **argv) {
	int rank, size;
	char string[] = "Mensagem";
	MPI_Status st;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		for (int i = 1; i < size; i++){
			MPI_Send(&string, 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
		}

		for (int i =1; i < size; ++i) {
			MPI_Recv(&rank, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Rank: %d\n", rank);
		}
	}
	else {
		MPI_Recv(&string, 8, MPI_CHAR, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}


	MPI_Finalize(); 

	return 0;
}