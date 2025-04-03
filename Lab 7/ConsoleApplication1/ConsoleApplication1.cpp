#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double PHI = (sqrt(5) - 1) / 2;
const double PI = 3.141592653589793;

int main() {
    setlocale(LC_ALL, "rus");
    double a = 0.0, b = 20.0;
    double epsilon = 1e-6;
    double x1 = b - PHI * (b - a);
    double x2 = a + PHI * (b - a);

    double E_x1 = (-1 + sqrt(1 + 4 * x1)) / 2;
    double F_x1 = 2 * E_x1 + cos(x1);
    double Psi_x1 = PI / 6 + 0.02 * E_x1 * F_x1;
    double S1 = (E_x1 > F_x1) ? -1 : 3 * E_x1 * F_x1 * sin(Psi_x1);

    double E_x2 = (-1 + sqrt(1 + 4 * x2)) / 2;
    double F_x2 = 2 * E_x2 + cos(x2);
    double Psi_x2 = PI / 6 + 0.02 * E_x2 * F_x2;
    double S2 = (E_x2 > F_x2) ? -1 : 3 * E_x2 * F_x2 * sin(Psi_x2);

    while ((b - a) > epsilon) {
        if (S1 > S2) {
            b = x2;
            x2 = x1;
            S2 = S1;
            x1 = b - PHI * (b - a);
            E_x1 = (-1 + sqrt(1 + 4 * x1)) / 2;
            F_x1 = 2 * E_x1 + cos(x1);
            Psi_x1 = PI / 6 + 0.02 * E_x1 * F_x1;
            S1 = (E_x1 > F_x1) ? -1 : 3 * E_x1 * F_x1 * sin(Psi_x1);
        }
        else {
            a = x1;
            x1 = x2;
            S1 = S2;
            x2 = a + PHI * (b - a);
            E_x2 = (-1 + sqrt(1 + 4 * x2)) / 2;
            F_x2 = 2 * E_x2 + cos(x2);
            Psi_x2 = PI / 6 + 0.02 * E_x2 * F_x2;
            S2 = (E_x2 > F_x2) ? -1 : 3 * E_x2 * F_x2 * sin(Psi_x2);
        }
    }

    double x_opt = (a + b) / 2;
    double E_opt = (-1 + sqrt(1 + 4 * x_opt)) / 2;
    double F_opt = 2 * E_opt + cos(x_opt);
    double Psi_opt = PI / 6 + 0.02 * E_opt * F_opt;
    double S_max = (E_opt > F_opt) ? -1 : 3 * E_opt * F_opt * sin(Psi_opt);

    cout << fixed << setprecision(6);
    cout << "Оптимальное значение x: " << x_opt << endl;
    cout << "Максимальная площадь: " << S_max << endl;

    return 0;
}
