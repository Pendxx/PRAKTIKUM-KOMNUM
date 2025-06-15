#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double f(double x) {
    return sin(x);
}

double romberg(double a, double b, int n) {
    double R[10][10];
    R[0][0] = (f(a) + f(b)) * (b - a) / 2;

    for (int i = 1; i < n; ++i) {
        int N = 1 << i;
        double h = (b - a) / N;
        double sum = 0;
        for (int k = 1; k < N; k += 2)
            sum += f(a + k * h);

        R[i][0] = 0.5 * R[i - 1][0] + h * sum;

        for (int j = 1; j <= i; ++j) {
            R[i][j] = R[i][j - 1] + (R[i][j - 1] - R[i - 1][j - 1]) / (pow(4, j) - 1);
        }
    }

    cout << fixed << setprecision(10);
    cout << "Tabel Romberg:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j)
            cout << R[i][j] << "\t";
        cout << endl;
    }

    return R[n - 1][n - 1];
}

int main() {
    double a = 0, b = M_PI;
    int n = 5;

    double result = romberg(a, b, n);
    cout << "\nHasil integrasi Romberg: " << result << endl;
    cout << "Seharusnya: 2\n";
    
    return 0;
}

