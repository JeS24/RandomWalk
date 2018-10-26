// "Half the randomness"
// No STDEV implemented

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <ctime>

using namespace std;

int main()
{
    long double pi = acos(-1);
    srand(time(0));
    std::setprecision(20);
    // double R = 0;
    // cout << "R = ";
    // cin >> R;
    // cout << "\n";

    ofstream file;
    file.open("plot4.csv");
    file << "Radius,Simulated,Theoretical\n";

    for (long R = 1 ; R < 500 ; R++) {
        long double th = pow((pi*R - (1.0/R)), 2)/(2*8760);
        int T = 0;
        double dx = 2.0/R;
        long double B[200];
        // cout << "\u0020" << R;
        for (int i = 0 ; i < 200 ; i++) {
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
        for (int i = 0 ; i < 200 ; i++) {
            // cout << B[i] << "\n";
            sum += B[i];
        }
        double sim = sum/200;

        // Writing to a file
        file << R << "," << sim << "," << th << "\n";

        // cout << "\nSimulated: " << sim << "\nTheoretical: " << th << "\nError Percentage: " << abs(th - sim)/(0.01*th) << "\n";
    }
    file.close();
}
