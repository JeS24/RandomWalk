// "Half the randomness"
// STDEV implemented -  which, probably, is incorrect.

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
    file.open("plot-stdev.csv");
    file << "Radius,Simulated,Theoretical,STDEV\n";

    for (long R = 1 ; R < 1000 ; R++) {
        double stdev = 0;
        long double th = pow((pi*R - (1.0/R)), 2)/(2*8760);
        int T = 0;
        double dx = 2.0/R;
        long double B[400];
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
            B[i] = t*(1.0/8760)*2; // Removed the squaring part
        }

        double diff = 0, sum = 0, sumD = 0;
        for (int i = 0 ; i < 200 ; i++)
            sum += B[i];

        double mean = sum/200;
        
        double sim = mean;
        
        for (int i = 1 ; i < 200 ; i++) {
            diff = B[i] - mean;
            sumD += diff*diff;
        }

        stdev = sqrt(sumD/198);

        // Writing to a file
        file << R << "," << sim << "," << th << "," << stdev << "\n";

        // cout << "\nSimulated: " << sim << "\nTheoretical: " << th << "\nError Percentage: " << abs(th - sim)/(0.01*th) << "\n";
    }
    file.close();
}
