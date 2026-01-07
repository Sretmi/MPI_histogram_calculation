#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <numeric>

// Değiştirilemeyecek Değerler
const int ARRAY_SIZE = 100;
const int HIST_SIZE = 10;

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    int rank, size;
    //işlemci numaralandırma ve sayısını bulma kısmı
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //işlemciler tam bölebilecek mi kontrolü
    if (ARRAY_SIZE % size != 0) {
        if (rank == 0) {
            std::cerr << "Hata: İşlemci sayısı (" << size 
                      << ") dizi boyutunu (" << ARRAY_SIZE << ") tam bölmelidir." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    int chunk_size = ARRAY_SIZE / size; 
    std::vector<int> global_data;       
    std::vector<int> local_data(chunk_size);

    //verileri burda rastgele ürettiriyoruz
    if (rank == 0) {
        global_data.resize(ARRAY_SIZE);
        std::srand(std::time(0));
        
        std::cout << "--- Orijinal Dizi (Ilk 20 eleman) ---" << std::endl;
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            global_data[i] = std::rand() % 10;
            if (i < 20) std::cout << global_data[i] << " ";
        }
        std::cout << "..." << std::endl << std::endl;
    }

    //işlemleri işlemcilere dağıtma
    MPI_Scatter(global_data.data(), chunk_size, MPI_INT, 
                local_data.data(), chunk_size, MPI_INT, 
                0, MPI_COMM_WORLD);

    //histogram hesabı
    int local_hist[HIST_SIZE] = {0};
    
    for (int i = 0; i < chunk_size; ++i) {
        int val = local_data[i];
        if (val >= 0 && val < HIST_SIZE) {
            local_hist[val]++;
        }
    }

    //işlemcilere işlemci numarasıyla işledikleri veri miktarını yazdırıyoruız
    printf("Islemci %d: %d adet veriyi isledi.\n", rank, chunk_size);

    //burda birleştiriyoruz
    int global_hist[HIST_SIZE] = {0};

    MPI_Reduce(local_hist, global_hist, HIST_SIZE, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    //ve geri kalanı yazdırıyoruz ana işlemcide
    if (rank == 0) {
        std::cout << "\n--- Final Histogram (Frekans Dagilimi) ---" << std::endl;
        std::cout << "Deger\t| Adet" << std::endl;
        std::cout << "--------|-------" << std::endl;
        
        int total_count = 0;
        for (int i = 0; i < HIST_SIZE; ++i) {
            std::cout << "  " << i << "\t|  " << global_hist[i] << std::endl;
            total_count += global_hist[i];
        }
        std::cout << "--------|-------" << std::endl;
        std::cout << "Toplam\t|  " << total_count << std::endl; // Sağlama (100 olmalı)
    }

    MPI_Finalize();
    return 0;
}