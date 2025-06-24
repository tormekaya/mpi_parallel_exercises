# Basit MPI (Paralel Programlama) Örnekleri

Bu projede MPI (Message Passing Interface) kullanılarak C++ dilinde yazılmış çeşitli paralel programlama örnekleri yer almaktadır. Amaç, farklı sayısal tanımların paralel hesaplamalarla nasıl bulunabileceğini göstermek ve MPI kullanımı konusunda temel örnekler sunmaktır.

## 📂 İçerik Sıralaması

1. deniz_sayisi.cpp
2. defne_sayisi.cpp
3. palandoken_sayisi.cpp
4. bora_sayisi.cpp
5. palandoken_sayisi_block.cpp
6. palandoken_sayisi_blockcyclic.cpp
7. leibniz_pi.cpp

---

## 🐚 Deniz Sayısı

### Tanım:
Bir sayı **asal olmayan (bileşik)** ve kendisi ile **has bölenlerinin toplamı** **palindrom** ise ve kendisi de **palindrom** ise bu sayı bir **Deniz Sayısı**dır.

Örnek:  
1001 → Bileşik, Palindrom ve has bölenlerinin toplamı (343) da palindrom.

### Kod Özeti:
- MPI ile halkalı dağıtım.
- Master işlemci alt/üst limiti alır.
- Tüm işlemciler paylaşılan aralığı işler.

---

## 🌸 Defne Sayısı

### Tanım:
Bir sayının **rakamları farklı** olmalı ve **en az 15 tane palindromik böleni** bulunmalıdır.

Örnek:  
2904 → Rakamları farklı ve 16 palindromik böleni var.

### Kod Özeti:
- MPI ile eşit aralık paylaştırılır.
- Her işlemci sayıları kontrol eder.
- Sonuçlar toplanarak master işlemci tarafından gösterilir.

---

## 🏔️ Palandöken Sayısı

### Tanım:
Rakamları birbirinden farklı olan ve **tek rakamlarının sayısı**, çiftlerden fazla olan sayılardır.

Örnek:  
751824693 → Tek: 7,5,1,9,3 → 5 adet  
              Çift: 8,2,4,6 → 4 adet → ✅ Palandöken sayısı

### Kod Özeti:
- Halkalı dağıtım yapılır.
- Her işlemci sırayla tek-çift rakam sayısını kontrol eder.

---

## 🔢 Bora Sayısı

### Tanım:
**Rakamları birbirinden farklı** ve **basamakları soldan sağa artan** olan sayılardır.

Örnek:  
12467 → artan sıralı ve benzersiz rakamlar → ✅  
76241 → sıralı değil → ❌

### Kod Özeti:
- Her işlemci sıralı artan olup olmadığını kontrol eder.

---

## 🔁 Palandöken Sayıları (Blok Dağıtım)

### Özellik:
- Sayılar her işlemciye eşit sayıda blok halinde dağıtılır.
- Artan sayı miktarları ilk işlemcilere dağıtılır.

### Örnek:
altLimit = 1, ustLimit = 21, size = 4  
→ işlemciler blok halinde:  
rank 0: 1-6  
rank 1: 7-11  
rank 2: 12-16  
rank 3: 17-21

---

## 🔁 Palandöken Sayıları (Block-Cyclic Dağıtım)

### Özellik:
- Sayılar döngüsel olarak küçük bloklar halinde dağıtılır.
- Blok boyutu sabittir (örneğin 3).

### Örnek:
altLimit = 1, blokBoyutu = 3, size = 4  
→ Dağılım:  
rank 0: 1-3, 13-15, 25-27  
rank 1: 4-6, 16-18, 28-30  
rank 2: 7-9, 19-21  
rank 3: 10-12, 22-24

---

## 🧮 Leibniz Serisi ile Pi Sayısı Hesaplama

### Tanım:
π sayısı şu seri ile hesaplanabilir:

π ≈ 4 * (1 - 1/3 + 1/5 - 1/7 + 1/9 - ... )

### Kod Özeti:
- MPI ile terimler sırayla paylaştırılır.
- Her işlemci kendi kısmını hesaplar.
- Sonuçlar birleştirilip π değeri hesaplanır.

---

## 💡 Nasıl Çalıştırılır?

```bash
mpic++ -o program deniz_sayisi.cpp
mpirun -np 4 ./program
```

Tüm dosyalar aynı mantıkla derlenip çalıştırılabilir.

## 🎯 Amaç

Bu örnekler, MPI öğrenenler için başlangıç seviyesinde paralel programlama örnekleri sunar. Kodların her biri hem sayı teorisi açısından hem de dağıtım algoritmaları açısından temel bilgiler içerir.

