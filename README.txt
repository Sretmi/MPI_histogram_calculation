# MPI Histogram Calculation

This project computes the frequency distribution (histogram) of elements within a large dataset in parallel using the **MPI (Message Passing Interface)** framework.

The implementation follows a "Divide and Conquer" approach: the root process (`Rank 0`) generates the data and partitions it across all available processes via `MPI_Scatter`[cite: 11]. Each worker computes a local histogram on its chunk, and the results are aggregated back into the global histogram at `Rank 0` using `MPI_Reduce` (`MPI_SUM`)[cite: 11].

---

## 🚀 Key Features

- **Workload Partitioning (`MPI_Scatter`):** The input array is divided into equal chunks and distributed to all processes[cite: 11].
- **Parallel Computation:** Each rank calculates bin frequencies independently on its localized memory buffer[cite: 11].
- **Reduction Aggregation (`MPI_Reduce`):** Local histogram arrays are summed element-wise across processes using `MPI_SUM`[cite: 11].
- **Workload Validation:** Checks whether `ARRAY_SIZE` is evenly divisible by `size` before processing to prevent boundary violations[cite: 11].

---

## 🛠️ Prerequisites

- **C++ Compiler:** GCC (`g++`), Clang, or MSVC (supporting C++11 or newer)[cite: 11].
- **MPI Implementation:**
  - **Linux / macOS:** OpenMPI or MPICH (`sudo apt install openmpi-bin libopenmpi-dev`)
  - **Windows:** Microsoft MPI (MS-MPI) SDK & Runtime.

---

## 💻 Build and Execution

Compile and run the program using your platform's MPI wrappers.

### Linux / macOS (OpenMPI / MPICH)

```bash
# Compile
mpic++ -O3 -o mpi_app main.cpp

# Execute (e.g., using 4 processes)
mpirun -n 4 ./mpi_app
```

### Windows (MS-MPI)

If compiling via MinGW / Command Prompt:

```cmd
:: Compile
g++ -O3 -o mpi_app.exe main.cpp -I"%MSMPI_INC%" -L"%MSMPI_LIB64%" -lmsmpi

:: Execute (e.g., using 4 processes)
mpiexec -n 4 .\mpi_app.exe
```

---

## 📊 Pipeline Parameters

The core operational constants defined in the source code:

| Parameter | Value | Description |
| :--- | :--- | :--- |
| `ARRAY_SIZE` | `100` | Total number of generated data elements[cite: 11]. |
| `HIST_SIZE` | `10` | Total number of frequency bins (`[0 - 9]`)[cite: 11]. |
| `chunk_size` | `ARRAY_SIZE / size` | Number of elements processed by each individual MPI rank[cite: 11]. |
