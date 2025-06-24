#include <mpi.h>
#include <iostream>
#include <clocale>

using namespace std;

bool PalandokenSayi(long long sayi); // Palandöken sayısını bulan fonksiyon bildirimi

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Turkish"); // Türkçe karakter desteği

    int rank, size;
    long long altLimit, ustLimit, globalSayac = 0, yerelSayac = 0;

    MPI_Init(&argc, &argv); // MPI ortamı başlatılır
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // işlemci sırası alınır
    MPI_Comm_size(MPI_COMM_WORLD, &size); // toplam işlemci sayısı alınır

    if (rank == 0) {
        cout << "Alt limiti Giriniz: ";
        cin >> altLimit;
        cout << "Üst limiti Giriniz: ";
        cin >> ustLimit;
    }

    MPI_Bcast(&altLimit, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
    MPI_Bcast(&ustLimit, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    long long toplamSayilar = ustLimit - altLimit + 1;
    long long blokBoyutu = 3; // sabit blok boyutu

    /*
    ÖRNEK: altLimit = 1, ustLimit = 30, blokBoyutu = 3, size = 4

    işlemciler (rank)  = 0, 1, 2, 3

    İlk dağıtım:
    - rank 0 → i = 1 + 0*3 = 1 → işler: 1, 2, 3
    - rank 1 → i = 1 + 1*3 = 4 → işler: 4, 5, 6
    - rank 2 → i = 1 + 2*3 = 7 → işler: 7, 8, 9
    - rank 3 → i = 1 + 3*3 = 10 → işler: 10, 11, 12

    Sonraki dağıtım (i += blokBoyutu * size = 12):
    - rank 0 → i = 13 → işler: 13, 14, 15
    - rank 1 → i = 16 → işler: 16, 17, 18
    - rank 2 → i = 19 → işler: 19, 20, 21
    - rank 3 → i = 22 → işler: 22, 23, 24

    Devam:
    - rank 0 → i = 25 → işler: 25, 26, 27
    - rank 1 → i = 28 → işler: 28, 29, 30
    - rank 2 → i = 31 (dışarıda kaldı)
    - rank 3 → i = 34 (dışarıda kaldı)
    */

    for (long long i = altLimit + rank * blokBoyutu; i <= ustLimit; i += size * blokBoyutu) {
        for (long long j = 0; j < blokBoyutu && (i + j) <= ustLimit; j++) {
            if (PalandokenSayi(i + j))
                yerelSayac++;
        }
    }

    MPI_Reduce(&yerelSayac, &globalSayac, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        cout << altLimit << " ile " << ustLimit << " arasında " << globalSayac << " adet Palandöken Sayısı vardır." << endl;

    MPI_Finalize();
    return 0;
}

bool PalandokenSayi(long long sayi) {
    int rakamlar[20];
    bool rakamVar[10] = {false};
    int uzunluk = 0;

    while (sayi > 0) {
        int rakam = sayi % 10;
        if (rakamVar[rakam])
            return false;
        rakamlar[uzunluk++] = rakam;
        rakamVar[rakam] = true;
        sayi /= 10;
    }

    int tekSayac = 0, ciftSayac = 0;
    for (int i = 0; i < uzunluk; i++) {
        if (rakamlar[i] % 2 == 0)
            ciftSayac++;
        else
            tekSayac++;
    }

    return tekSayac > ciftSayac;
}
