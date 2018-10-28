// Ground Zero

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <curand_kernel.h> // **

using namespace std;

__global__
void loop(double* array,  long N, long R, double pi, double x, double t)
{

    int index = threadIdx.x;
    // int stride = blockDim.x;

    // int tId = index + (blockIdx.x * stride);
    curandState state;
    // "index" alone works for us - no need for "grid-stride" loops, as we are limiting to just 512 elements in the array
    // And, each element is handled by individual thread (ideally) -- Nope, not working as intended
    curand_init((unsigned long long)clock(), index, 1, &state); // ** Set offset = 1
    double dx = 2.0/R;
    
    int T = (int)(10*curand_uniform(&state))%4;

    // __syncthreads(); // Did not help
    while (x < (pi - (1.0/R))) {
        if (T == 0) {
            x += dx;
            if (x + dx > pi)
                x = 2*pi - x;
        }
        else if (T == 1)
            x = fabs(x - dx);
        t = t + 1;
        T = (int)(10*curand_uniform(&state))%4;
    }
    // __syncthreads(); // Did not help
    
    // for (int i = index; i < N; i += stride)
        array[index] = t*(1.0/8760);
}

int main()
{
    double pi = acos(-1);

    long rand_size = 1<<9; // 2^9 = 512 - Number of times, the walk shall be simulated, per "R" value - size of the "store" array
    double *store; // Array for storing the output, from each simulation, per "R" value
    cudaMallocManaged(&store, rand_size*sizeof(double)); // Allocating memory in "Unified Storage" for "store"

    std::setprecision(20);
    
    // Input Radius
    double R = 0;
    cout << "\nR = ";
    cin >> R;
    cout << "\n";

    // Theoretical Value
    long double th = pow((pi*R - (1.0/R)), 2)/(2*8760);

    // Calling the kernel - 1 Block * 512 Threads = 512 Threads
    // Each thread shall simulate the Random Walk once, for a total of 512 outputs to the array
    loop<<<1, 512>>>(store, rand_size, R, pi, 0, 0);
    cudaDeviceSynchronize(); // Waiting for GPU to finish

    // Summing the terms in the array is trivial and fast on the CPU
    double sum = 0;
    for (int i = 0 ; i < rand_size ; i++) {
        cout << store[i] << "\n";
        sum += store[i];
    }

    // Value, from the simulation
    double sim = sum/rand_size;

    // Output the values
    cout << "\nSimulated: " << sim << "\nTheoretical: " << th << "\nError Percentage: " << fabs(th - sim)/(0.01*th) << "\n";
    cudaFree(store);

    return 0; // Have to check, if this is really important to keep
}
