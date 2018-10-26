// Ground Zero

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <ctime>

using namespace std;

int main()
{
    long double pi = acos(-1);
    srand(time(0));
    std::setprecision(20);
    double R = 0;
    cout << "R = ";
    cin >> R;
    cout << "\n";

    // for (long R = 1 ; R < 200 ; R++) {
        double th = (pi*pi*R*R)/(2*8760);
        int T = 0;
        double dx = 2.0/R;
        long double B[500];
        for (int i = 0 ; i < 500 ; i++) {
            T = (int)rand()%2;
            double x = 0;
            double t = 0;
            while (x < (pi - (1.0/R))) {
                if (T == 0) {
                    x = x + dx;
                    if (x + dx > pi)
                        x = 2*pi - x;
                }
                else if (T == 1)
                    x = abs(x - dx);
                t = t + 1;
                T = (int)rand()%2;
            }
            B[i] = t*(1.0/8760)*2;
        }

        double sum = 0;
        for (int i = 0 ; i < 500 ; i++) {
            cout << B[i] << "\n";
            sum += B[i];
        }

        cout << "\nSimulated: " << sum/500 << "\nTheoretical: " << th << "\nError Percentage: " << abs(th - sum/500)/(0.01*th) << "\n";
    // }
}
