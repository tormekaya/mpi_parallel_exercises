#include <iostream>
#include <mpi.h>
#include <cmath>
#include <set>
#include <string>

using namespace std;

// Palindrome kontrol fonksiyonu
bool isPalindrome(long long number) {
    string originalString = to_string(number);
    string reversedString = string(originalString.rbegin(), originalString.rend());
    return originalString == reversedString;
}

// Defne Sayısı kontrol fonksiyonu
bool isDefneNumber(long long number) {
    set<int> uniqueDigits;
    long long tempNumber = number;

    // Rakamların birbirinden farklı olup olmadığını kontrol et
    while (tempNumber > 0) {
        int digit = tempNumber % 10;
        if (uniqueDigits.find(digit) != uniqueDigits.end()) return false; // Eğer rakam set içinde bulunuyorsa false döner
        uniqueDigits.insert(digit); // Rakamı sete ekle
        tempNumber /= 10;
    }

    int palindromeDivisorCount = 0; // Palindromik bölen sayısını tutar

    bool isDefneNumber(long long number) {
    int palindromeDivisorCount = 0; // Palindromik bölen sayısını tutar

    for (int i = 1; i <= number; ++i) {
        // Eğer i sayısı number sayısına tam bölünüyorsa
        if (number % i == 0) {
            // Eğer bölen palindromikse sayacı artır
            if (isPalindrome(i)) palindromeDivisorCount++;
        }
        // Eğer palindromik bölen sayısı 15 veya daha fazla ise true döner
        if (palindromeDivisorCount >= 15) return true;
    }

    // 15'ten az palindromik böleni varsa false döner
    return false;
}

int main(int argc, char *argv[]) {
    int processRank, numberOfProcesses; // MPI işlem sırası ve toplam işlem sayısı
    long long lowerLimit, upperLimit; // Alt ve üst limitler

    // MPI ortamını başlat
    MPI_Init(&argc, &argv);
    // MPI işlem sırasını al
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);
    // Toplam işlem sayısını al
    MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcesses);

    // Sadece master (processRank 0) işlem girdi alır
    if (processRank == 0) {
        cout << "Alt limit: ";
        cin >> lowerLimit;
        cout << "Ust limit: ";
        cin >> upperLimit;
    }

    // Alt ve üst limitleri tüm işlemlere gönder
    MPI_Bcast(&lowerLimit, 1, MPI_LONG_LONG_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&upperLimit, 1, MPI_LONG_LONG_INT, 0, MPI_COMM_WORLD);

    // Toplam aralık uzunluğu
    long long range = upperLimit - lowerLimit + 1;
    // Her işleme düşen aralık büyüklüğü
    long long chunkSize = range / numberOfProcesses;
    // Her işlemin başlama noktası
    long long start = lowerLimit + processRank * chunkSize;
    // Her işlemin bitiş noktası
    long long end = (processRank == numberOfProcesses - 1) ? upperLimit : start + chunkSize - 1;

    int localDefneCount = 0; // Her işlemin bulduğu Defne Sayısı
    // Her işlemin kendi aralığındaki sayıları kontrol etmesi
    for (long long i = start; i <= end; ++i) {
        if (isDefneNumber(i)) {
            localDefneCount++; // Eğer i sayısı Defne Sayısı ise sayacı artır
        }
    }

    int globalDefneCount;
    // Her işlemin bulduğu Defne Sayılarını master işlemede topla
    MPI_Reduce(&localDefneCount, &globalDefneCount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Sonuçları sadece master işlem ekrana yazdırır
    if (processRank == 0) {
        cout << "Toplam Defne Sayisi: " << globalDefneCount << endl;
    }

    // MPI ortamını sonlandır
    MPI_Finalize();
    return 0;
}
