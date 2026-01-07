# MPI Histogram Calculation

Bu proje, **MPI (Message Passing Interface)** kütüphanesini kullanarak büyük bir veri dizisindeki sayıların frekansını (histogramını) paralel olarak hesaplar.

Uygulama, "Böl ve Yönet" (Divide and Conquer) yaklaşımını kullanır. Ana işlemci veriyi üretir, parçalara ayırır (`Scatter`), diğer işlemciler kendi parçalarını sayar ve sonuçlar tekrar ana işlemcide birleştirilir (`Reduce`).

## 🚀 Özellikler

* **Veri Dağıtımı (MPI_Scatter):** Ana veri seti eşit parçalara bölünerek işlemcilere dağıtılır.
* **Paralel Hesaplama:** Her işlemci (Rank) kendi yerel verisi üzerinde histogram hesaplar.
* **Sonuç Birleştirme (MPI_Reduce):** Yerel sonuçlar toplanarak (`MPI_SUM`) ana işlemcide global histogram oluşturulur.
* **Dinamik Kontrol:** İşlemci sayısının veri boyutunu tam bölüp bölmediği kontrol edilir.

## 🛠️ Gereksinimler

* **C++ Derleyicisi:** GCC (g++) veya MSVC.
* **MPI Kütüphanesi:**
  * **Linux:** OpenMPI veya MPICH (`sudo apt install openmpi-bin libopenmpi-dev`)
  * **Windows:** Microsoft MPI (MS-MPI) SDK.

## 💻 Derleme ve Çalıştırma

Kodun derlenmesi ve çalıştırılması için MPI wrapper'larına ihtiyacınız vardır.

### Linux / macOS (OpenMPI)
```bash
# Derleme
mpic++ -o mpi_app main.cpp

# Çalıştırma (Örnek: 4 işlemci ile)
mpiexec -n 4 ./mpi_app