# PRAKTIKUM-KOMNUM

## PRAKTIKUM 1

### 1. Fungsi f(double x)
```c
double f(double x) {
    return x*x*x - x - 2;
}
```

- Deskripsi: Mendefinisikan fungsi matematika yang akan dicari akarnya, yaitu
![image](https://github.com/user-attachments/assets/9f60a8e0-3e21-4420-8fef-28da9d97abea)
- Kegunaan: Digunakan untuk mengevaluasi nilai fungsi pada titik tertentu, baik untuk iterasi maupun plotting.

### 2. Fungsi main()
Merupakan fungsi utama yang menjalankan seluruh proses pencarian akar menggunakan Metode Regula Falsi.
```c
printf("Masukkan nilai a: ");
scanf("%lf", &a);
printf("Masukkan nilai b: ");
scanf("%lf", &b);
```
- Deskripsi: Meminta pengguna memasukkan dua nilai awal (a dan b) sebagai interval pencarian akar.
- Tujuan: Titik awal metode Regula Falsi harus mengapit akar (yakni f(a)×f(b)<0).
```c
if (fa * fb > 0) {
    printf("Fungsi tidak mengapit akar (f(a) * f(b) > 0)\n");
    return 1;
}
```
- Deskripsi: Memastikan bahwa akar berada di antara a dan b. Jika tidak, program berhenti.

### 3. Iterasi Regula Falsi
```c
do {
    xr = b - (fb * (a - b)) / (fa - fb);
    fxr = f(xr);
    ...
} while (1);

```

- Deskripsi: Melakukan iterasi dengan rumus Metode Regula Falsi:
![image](https://github.com/user-attachments/assets/b6b4127c-6501-463a-a9aa-4cd0f2d175f7)
- Kondisi berhenti: Ketika ∣f(xr)∣<ϵ∣f(xr​)∣<ϵ atau iterasi mencapai batas maksimum (MAX_ITER).

### 4. Output Iterasi ke File
```c
FILE *logFile = fopen("iterasi.dat", "w");
fprintf(logFile, "%d %.6f %.6f\n", iter, xr, fxr);
```

- Deskripsi: Menyimpan hasil tiap iterasi (nilai xr dan f(xr)) ke file iterasi.dat.
- Tujuan: Digunakan untuk plotting grafik titik-titik iterasi.

### 5. Pembuatan Data Fungsi untuk Plot
```c
FILE *funcFile = fopen("fungsi.dat", "w");
for (double x = start; x <= end; x += 0.01)
    fprintf(funcFile, "%.6f %.6f\n", x, f(x));
```

- Deskripsi: Menyimpan nilai fungsi pada rentang sekitar akar ke file fungsi.dat.
- Tujuan: Untuk menggambar kurva fungsi dalam grafik.

### 6. Pembuatan Skrip Gnuplot
```c
FILE *gnuplotScript = fopen("plot_script.gp", "w");
fprintf(gnuplotScript,
    ...
);
```

- Deskripsi: Membuat skrip plot_script.gp untuk memvisualisasikan grafik fungsi dan titik-titik iterasi menggunakan Gnuplot.
- Perintah: Menampilkan grafik dengan:
  ```bash
  gnuplot -p plot_script.gp
  ```

### 7. Output Akhir
```c
printf("\nAkar pendekatan: %.6f setelah %d iterasi\n", xr, iter);
```

- Deskripsi: Menampilkan hasil akhir berupa nilai pendekatan akar dan jumlah iterasi yang dilakukan.

### Kesimpulan
Program ini menerapkan Metode Regula Falsi untuk mencari akar fungsi f(x)=x3−x−2f(x)=x3−x−2. Prosesnya mencakup validasi interval, iterasi numerik, perekaman data, dan visualisasi hasil dengan Gnuplot. Setiap bagian berfungsi saling mendukung untuk memastikan pendekatan akar dapat dihitung dan divisualisasikan dengan baik.

## PRAKTIKUM 2

### Bagian 1: Header dan Fungsi Target
```cpp
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
```

- #include <iostream>: Untuk input/output seperti cout.
- #include <cmath>: Agar bisa memakai fungsi matematika seperti sin(), pow(), M_PI.
- #include <iomanip>: Agar bisa mengatur format angka saat ditampilkan (setprecision).
- using namespace std;: Supaya tidak perlu menulis std:: di depan fungsi-fungsi standar.
```c
double f(double x) {
    return sin(x);  // contoh fungsi yang ingin diintegralkan
}
```
- Fungsi f(x) mendefinisikan fungsi matematika yang ingin diintegralkan. Contoh: f(x)=sin⁡(x). Bisa diubah sesuai kebutuhan.
  
### Bagian 2: Fungsi Romberg
```cpp
double romberg(double a, double b, int n) {
    double R[10][10]; // Matriks segitiga Romberg untuk menyimpan nilai integral
```

- #Fungsi romberg() menerima batas integral a, b dan jumlah level n.
- R[10][10] adalah matriks untuk menyimpan hasil metode trapezoid dan hasil Richardson extrapolation.
```cpp
    R[0][0] = (f(a) + f(b)) * (b - a) / 2;
```
- Menghitung nilai awal (Trapezoid pertama dengan 1 interval) dan menyimpannya di R[0][0].

### Bagian 3: Perulangan untuk Mengisi Tabel Romberg
```cpp
    for (int i = 1; i < n; ++i) {
        int N = 1 << i; // Jumlah segmen = 2^i
        double h = (b - a) / N;
```

- Perulangan dari level ke-1 sampai level ke-(n-1).
- N = 2^i (operator << adalah bit shift, jadi 1 << 3 = 8).
- h adalah panjang setiap segmen pada level ini.
```cpp
        double sum = 0;
        for (int k = 1; k < N; k += 2)
            sum += f(a + k * h);
```
- Menghitung jumlah nilai f(x) di titik-titik tengah baru yang belum dihitung di level sebelumnya (misalnya pada x = a + h, a + 3h, dst.).
- k += 2 karena hanya menghitung titik baru (tengah), bukan yang sudah dipakai sebelumnya.
```cpp
        R[i][0] = 0.5 * R[i - 1][0] + h * sum;
```
- Menghitung nilai trapezoid level baru berdasarkan hasil level sebelumnya (rumus recursive dari trapezoidal rule).
```cpp
        for (int j = 1; j <= i; ++j) {
            R[i][j] = R[i][j - 1] + (R[i][j - 1] - R[i - 1][j - 1]) / (pow(4, j) - 1);
        }
```
- Ini bagian eksstrapolasi Richardson, untuk meningkatkan akurasi hasil trapezoid sebelumnya.
- Rumusnya:
![image](https://github.com/user-attachments/assets/d17f6d30-aa0b-4493-8676-d0eace42c24a)

- Menyimpan hasil di R[i][j] yang lebih akurat.

### Bagian 4: Menampilkan Tabel Romberg
```cpp
    cout << fixed << setprecision(10);
    cout << "Tabel Romberg:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j)
            cout << R[i][j] << "\t";
        cout << endl;
    }
```

- Menampilkan tabel hasil Romberg dari R[0][0] sampai R[n-1][n-1].
- setprecision(10) agar angka ditampilkan dengan 10 digit desimal.

### Bagian 5: Return Nilai Terakurat
```cpp
    return R[n - 1][n - 1];
}
```

- Nilai terbaik dan paling akurat dari hasil integrasi ada di kanan bawah tabel: R[n-1][n-1].

### Bagian 6: Fungsi main()
```cpp
int main() {
    double a = 0, b = M_PI; // integral dari 0 ke pi
    int n = 5; // jumlah level Romberg

    double result = romberg(a, b, n);
```

- Memanggil fungsi romberg() untuk menghitung integral dari 00 sampai ππ.
- n = 5 berarti akan menggunakan 5 level perbaikan akurasi.

```cpp
    cout << "\nHasil integrasi Romberg: " << result << endl;
    cout << "Seharusnya: 2 (karena integral sin(x) dari 0 ke pi)\n";
    
    return 0;
}
```

- Menampilkan hasil integrasi dan memberi referensi hasil yang benar :
![image](https://github.com/user-attachments/assets/d31b556c-43b7-4718-bb2d-b41ccdaad7b4)




