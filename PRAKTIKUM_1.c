#include <stdio.h>
#include <math.h>

#define EPSILON 0.0001
#define MAX_ITER 100

// Fungsi yang akan dicari akarnya
double f(double x) {
    return x*x*x - x - 2;
}

int main() {
    double a, b, xr, fa, fb, fxr;
    int iter = 0;

    // Input interval dari pengguna
    printf("Masukkan nilai a: ");
    scanf("%lf", &a);
    printf("Masukkan nilai b: ");
    scanf("%lf", &b);

    fa = f(a);
    fb = f(b);

    // Validasi apakah f(a) dan f(b) mengapit akar
    if (fa * fb > 0) {
        printf("Fungsi tidak mengapit akar (f(a) * f(b) > 0)\n");
        return 1;
    }

    FILE *logFile = fopen("iterasi.dat", "w");
    FILE *funcFile = fopen("fungsi.dat", "w");

    printf("Iterasi\t\ta\t\tb\t\txr\t\tf(xr)\n");

    do {
        xr = b - (fb * (a - b)) / (fa - fb);
        fxr = f(xr);
        iter++;

        printf("%d\t\t%.6f\t%.6f\t%.6f\t%.6f\n", iter, a, b, xr, fxr);
        fprintf(logFile, "%d %.6f %.6f\n", iter, xr, fxr);

        if (fa * fxr < 0) {
            b = xr;
            fb = fxr;
        } else {
            a = xr;
            fa = fxr;
        }

        if (fabs(fxr) < EPSILON || iter >= MAX_ITER)
            break;

    } while (1);

    double start = a - 1;
    double end = b + 1;
    for (double x = start; x <= end; x += 0.01)
        fprintf(funcFile, "%.6f %.6f\n", x, f(x));

    fclose(logFile);
    fclose(funcFile);

    FILE *gnuplotScript = fopen("plot_script.gp", "w");
    fprintf(gnuplotScript,
        "set title 'Metode Regula Falsi'\n"
        "set xlabel 'x'\n"
        "set ylabel 'f(x)'\n"
        "set grid\n"
        "plot 'fungsi.dat' with lines title 'f(x)', \\\n"
        "     'iterasi.dat' using 2:3 with points pointtype 7 linecolor rgb 'red' title 'Titik Iterasi'\n"
        "pause -1 'Tekan ENTER untuk keluar'\n"
    );
    fclose(gnuplotScript);

    printf("\nAkar pendekatan: %.6f setelah %d iterasi\n", xr, iter);
    printf("Jalankan grafik dengan: gnuplot -p plot_script.gp\n");

    return 0;
}
