#include <mpi.h>
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

// Fonksiyon tanımları
bool DenizNumber(long long number);
bool ProperDivision(long long number);
bool IsPalindrome(long long number);
bool IsPrime(long long number);

int main(int argc, char* argv[]) {
    int myRank, size;
    int count = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long lowerLimit;
    long long upperLimit;

    if (myRank == 0) { // master bilgisayar
        cout << "Alt limiti giriniz: ";
        cin >> lowerLimit;
        cout << "Üst limiti giriniz: ";
        cin >> upperLimit;
    }

    MPI_Bcast(&lowerLimit, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
    MPI_Bcast(&upperLimit, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    for (long long number = lowerLimit + myRank; number <= upperLimit; number += size) {
        if (DenizNumber(number)) {
            count += 1;
        }
    }

    int globalCount = 0;
    MPI_Reduce(&count, &globalCount, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (myRank == 0) {
        cout << "Toplam Deniz Sayısı: " << globalCount << endl;
    }

    MPI_Finalize();
    return 0;
}

bool DenizNumber(long long number) {
    bool result1 = IsPrime(number);
    bool result2 = ProperDivision(number);
    bool result3 = IsPalindrome(number);

    return result1 && result2 && result3;
}

bool ProperDivision(long long number) {
    long long sum = 0;
    for (long long i = 1; i < number; i++) {
        if (number % i == 0) {
            sum += i;
        }
    }

    return IsPalindrome(sum);
}

bool IsPalindrome(long long number) {
    if (number < 0) {
        return false;
    }
    string str = to_string(number);
    int length = str.length();

    for (int i = 0; i < length / 2; i++) {
        if (str[i] != str[length - i - 1]) {
            return false;
        }
    }

    return true;
}

bool isPrime(long long number) {
    if (number <= 1)
        return false;
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0)
            return false;
    }
    return true;
}
