#include <mpi.h>
#include <iostream>
#include <clocale>

using namespace std;

bool PalandokenSayi(long long sayi); //Palandöken sayısını bulan fonksiyon bildirimi. Uygulamaya böyle bir fonksiyonun bulunduğunu bildirdik.

int main(int argc, char* argv[]) {
    
    setlocale(LC_ALL, "Turkish"); //Türkçe karakterlerin düzgün bir şekilde yazdırılması için locale ayarını Türkçe yaptık.

    int rank, size;
    long long altLimit, ustLimit, globalSayac = 0, yerelSayac = 0;

    MPI_Init(&argc, &argv); //MPI ortamını başlatır.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //Her bir işlemciye bir rank numarası verir.
    MPI_Comm_size(MPI_COMM_WORLD, &size); //Toplam işlemci sayısını verir.

    if (rank == 0) {
        cout << "Alt limiti Giriniz: ";
        cin >> altLimit; //Alt limiti kullanıcıdan alır.
        cout << "Üst limiti Giriniz: ";
        cin >> ustLimit; //Üst limiti kullanıcıdan alır.
    }

    MPI_Bcast(&altLimit, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD); //Alt limiti sadece admin makinesi bildiği için broadcast yaparak diğer işlemcilere göndeririz.
    MPI_Bcast(&ustLimit, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD); //Üst limiti sadece admin makinesi bildiği için broadcast yaparak diğer işlemcilere göndeririz.

    for (long long i = altLimit + rank; i <= ustLimit; i += size) //Rank numarasına göre işlemci sayısına bölerek işlem yapar. Admin makinesi dahil. 
        if (PalandokenSayi(i))
            yerelSayac++; //Palandöken sayısını bulur ve yerel sayacı arttırır.

    MPI_Reduce(&yerelSayac, &globalSayac, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD); //Tüm işlemcilerdeki yerel sayacı toplar ve global sayaca atar.

    if (rank == 0) //Sınavda Bu değeri admin makinesinin yazdırılması istendiği için rank 0 da yazdırırız.
        cout << altLimit << " ile " << ustLimit << " arasında " << globalSayac << " adet Palandöken Sayısı vardır." << endl;

    MPI_Finalize(); //MPI ortamını sonlandırır.
    return 0;
}

bool PalandokenSayi(long long sayi) {
    int rakamlar[20]; //Gelen sayımız long long olduğu için 20 rakamdan oluşan bir dizi oluşturduk. long long int 64-bit genişliğinde bir tamsayıdır. 19 tane rakam ve 1 eksi işareti bulundurur.
    bool rakamVar[10] = {false}; // Toplamda 10 adet rakamımız olduğu için 10 elemanlı bir dizi oluşturduk. Rakamların tekrar etmemesi için kontrol yapacağız.
    int uzunluk = 0; //Rakamların uzunluğunu tutmak için bir değişken oluşturduk.

    while (sayi > 0) {
        int rakam = sayi % 10; //Sayının son rakamını alırız.
        if (rakamVar[rakam]) //Rakamın daha önce alınıp alınmadığını kontrol ederiz.
            return false; //Eğer alındıysa false döndürürüz.
        rakamlar[uzunluk++] = rakam; //Rakamı diziye ekleriz.
        rakamVar[rakam] = true; //Rakamın alındığını işaretleriz.
        sayi /= 10; //Sayıyı 10'a böleriz.
    }

    int tekSayac = 0, ciftSayac = 0; //Tek ve çift sayıları saymak için iki değişken oluşturduk.
    for (int i = 0; i < uzunluk; i++) { //Rakamların uzunluğu kadar döngü oluşturduk.
        if (rakamlar[i] % 2 == 0) //Rakamın çift olup olmadığını kontrol ederiz.
            ciftSayac++; //Çiftse ciftSayac'ı arttırırız.
        else
            tekSayac++; //Tekse tekSayac'ı arttırırız.
        
    }

    return tekSayac > ciftSayac; //Tek sayılar çift sayılardan fazla ise true döndürürüz.
}

