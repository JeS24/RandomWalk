// Theoretically most accurate, so far
// Has a timer to gauge the runtime
// And, stdev - which, probably, is incorrect.

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    long double pi = acos(-1);
    srand(time(0));
    std::setprecision(20);

    ofstream file;
    file.open("plot-latest.csv");
    file << "Radius,Simulated,Theoretical,STDEV\n";

    for (long R = 1 ; R < 100 ; R++) {
        // double stdev = 0;
        long double th = pow((pi*R - (1.0/R)), 2)/(2*8760);
        int T = 0;
        double dx = 2.0/R;
        long double B[200];
        // cout << "\u0020" << R;
        for (int i = 0 ; i < 200 ; i++) {
            T = (int)rand()%4;
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
                T = (int)rand()%4;
            }
            B[i] = t*(1.0/8760); // Removed the factor, 2
        }

        double diff = 0, sum = 0, sumD = 0;
        for (int i = 0 ; i < 200 ; i++)
            sum += B[i];

        double mean = sum/200;
        
        double sim = mean;
        
        // for (int i = 0 ; i < 400 ; i++) {
        //     diff = B[i] - mean;
        //     sumD += diff*diff;
        // }

        // stdev = sqrt(sumD/399);

        // Writing to a file
        file << R << "," << sim << "," << th << ","  << "\n"; // Removed the stdev part

        // cout << "\nSimulated: " << sim << "\nTheoretical: " << th << "\nError Percentage: " << abs(th - sim)/(0.01*th) << "\n";
    }
    file.close();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<seconds>(t2 - t1).count();

    cout << "\nProcess completed.\nTotal Runtime: " << duration << " s\n";
}
