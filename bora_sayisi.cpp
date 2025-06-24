#include <mpi.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool isBoraNumber(long long num);

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int myRank, numProcesses;
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

    long long lowerLimit, upperLimit;
    int totalBoraNumbers = 0;

    if (myRank == 0) {
        // Master process
        cout << "Enter the lower limit: ";
        cin >> lowerLimit;
        cout << "Enter the upper limit: ";
        cin >> upperLimit;
    } 
        MPI_Bcast(&lowerLimit, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
        MPI_Bcast(&upperLimit, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD)

    // Each process calculates its local count of Bora Numbers
    int localBoraCount = 0;
    for (long long i = lowerLimit + myRank; i <= upperLimit; i += numProcesses) {
        if (isBoraNumber(i)) {
            localBoraCount++;
        }
    }

    // Reduce local counts to get the total count at master process
    MPI_Reduce(&localBoraCount, &totalBoraNumbers, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (myRank == 0) {
        // Master process prints the total count of Bora Numbers
        cout << "Total Bora Numbers between " << lowerLimit << " and " << upperLimit << " (inclusive) are: " << totalBoraNumbers << endl;
    }

    MPI_Finalize();
    return 0;
}

bool isBoraNumber(long long num) {
    vector<int> digits;
    while (num > 0) {
        int digit = num % 10;   // Sayının son basamağını alır
        digits.push_back(digit); // Son basamağı vektöre ekler
        num /= 10;               // Sayıyı 10'a böler, son basamağı çıkarır
    }

    // Check if digits are unique and in strictly increasing order
    int n = digits.size();   // Vektördeki eleman sayısını alır
    for (int i = 0; i < n - 1; ++i) {
        if (digits[i] <= digits[i + 1]) {
            return false;   // Eğer rakamlar sıralı değilse false döndürür
        }
    }

    return true;   // Rakamlar sıralı ve benzersiz ise true döndürür
}