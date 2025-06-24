#include <mpi.h>
#include <iostream>

using namespace std;
int main(int argc, char* argv[]) {

    int rank, size,N;
    double kismi= 0, final= 0,formul;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        cout << "N Giriniz: ";
        cin >> N; 
    }

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD); 

    for (int i = rank; i <= N; i += size) {
        if (i%2==0){
	formul=1.0/((2*i)+1);}
        else {
	formul=-1.0/((2*i)+1);}
     kismi+=formul;
}     
    MPI_Reduce(&kismi,&final,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

    if (rank == 0) {
        final=final*4;
        cout  << " Sonuç:" << final << endl;
     }
    MPI_Finalize();
    return 0;
}

