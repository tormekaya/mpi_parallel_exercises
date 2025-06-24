#include <mpi.h>
#include <iostream>
#include <clocale>

using namespace std;

bool PalandokenSayi(long long sayi); // Palandöken sayısını bulan fonksiyon bildirimi. Uygulamaya böyle bir fonksiyonun bulunduğunu bildirdik.

int main(int argc, char* argv[]) {

    setlocale(LC_ALL, "Turkish"); // Türkçe karakterlerin düzgün bir şekilde yazdırılması için locale ayarını Türkçe yaptık.

    int rank, size;
    long long altLimit, ustLimit, globalSayac = 0, yerelSayac = 0;

    MPI_Init(&argc, &argv); // MPI ortamını başlatır.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Her bir işlemciye bir rank numarası verir.
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Toplam işlemci sayısını verir.

    if (rank == 0) {
        cout << "Alt limiti Giriniz: ";
        cin >> altLimit; // Alt limiti kullanıcıdan alır.
        cout << "Üst limiti Giriniz: ";
        cin >> ustLimit; // Üst limiti kullanıcıdan alır.
    }

    MPI_Bcast(&altLimit, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD); // Alt limiti tüm işlemcilere göndeririz.
    MPI_Bcast(&ustLimit, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD); // Üst limiti tüm işlemcilere göndeririz.

    // Blok dağıtım hesaplamaları
    long long toplamSayilar = ustLimit - altLimit + 1;               // Örneğin: 1 - 20 arası 20 sayı
    long long blokBoyutu = toplamSayilar / size;                     // Örneğin: 20 / 4 = 5
    long long kalan = toplamSayilar % size;                          // Artan sayılar: 20 % 4 = 0

    // Blok dağıtımı başlangıç ve bitiş hesaplama
    long long baslangic = altLimit + rank * blokBoyutu + min(rank, kalan);
    long long bitis = baslangic + blokBoyutu - 1;
    if (rank < kalan) {
        bitis++; // İlk kalan işlemciler 1 sayı fazla alır
    }

    /*
    Örnek: altLimit = 1, ustLimit = 21, size = 4
    toplamSayilar = 21, blokBoyutu = 5, kalan = 1

    İşlemciler için baslangic hesaplamaları:
    rank = 0: baslangic = 1 + 0*5 + min(0,1) = 1
    rank = 1: baslangic = 1 + 1*5 + min(1,1) = 7
    rank = 2: baslangic = 1 + 2*5 + min(2,1) = 11
    rank = 3: baslangic = 1 + 3*5 + min(3,1) = 16
    */

    for (long long i = baslangic; i <= bitis; i++) {
        if (PalandokenSayi(i)) {
            yerelSayac++; // Palandöken sayısını bulur ve yerel sayacı arttırır.
        }
    }

    // Tüm işlemcilerdeki yerel sayaçları toplar ve master işlemciye atar
    MPI_Reduce(&yerelSayac, &globalSayac, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << altLimit << " ile " << ustLimit << " arasında " << globalSayac << " adet Palandöken Sayısı vardır." << endl;
    }

    MPI_Finalize(); // MPI ortamını sonlandırır.
    return 0;
}

bool PalandokenSayi(long long sayi) {
    int rakamlar[20]; // long long 64-bit için yeterli büyüklükte bir dizi
    bool rakamVar[10] = {false}; // 0-9 arası rakamların tekrar kontrolü için
    int uzunluk = 0;

    while (sayi > 0) {
        int rakam = sayi % 10; // Sayının son rakamını alırız.
        if (rakamVar[rakam]) // Eğer daha önce geldiyse false döneriz.
            return false;
        rakamlar[uzunluk++] = rakam;
        rakamVar[rakam] = true;
        sayi /= 10;
    }

    int tekSayac = 0, ciftSayac = 0; // Tek ve çift rakam sayaçları
    for (int i = 0; i < uzunluk; i++) {
        if (rakamlar[i] % 2 == 0)
            ciftSayac++;
        else
            tekSayac++;
    }

    return tekSayac > ciftSayac; // Tek rakam sayısı daha fazlaysa Palandöken sayısıdır
}
