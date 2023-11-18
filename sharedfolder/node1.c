# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>
#include "Texto/text.h"

int main ( int argc, char *argv[] ){
	
	int rank, size, len;
    char version[MPI_MAX_LIBRARY_VERSION_STRING];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_library_version(version, &len);
	
	divideFile();
    
    char* trend = findTrendWord("/home/curso/Desktop/sharedfolder/Texto/input.txt");
    if (trend) {
        printf("Trend word is: %s\n", trend);
    } else {
        printf("No trend word found\n");
    }

    printf("Files divided into outputA.txt and outputB.txt.\n");
	
	MPI_Finalize();	
			
	return 0;
}
