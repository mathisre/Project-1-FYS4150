#include <iostream>
#include <armadillo>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <string>
#include <time.h>

using namespace arma;
using namespace std;
ofstream ofile;

int main(int argc, char* argv[])
{
    if (argc <= 2){
        cout << "Bad usage, should be file then n in command line" << endl;
        exit(1);
    }
    string filename;
    filename = argv[1]; //input filename and n from command line
    int n = atoi(argv[2]);
    ofile.open(filename);
    ofile << n << endl; //print n to file for plotting
    double h = 1./(n+1);
    vec d(n);
    vec x = linspace<vec>(0, 1, n+1);
    vec f =100*exp(-10*x)*pow(h,2);
    vec u(n+2);
    vec fd(n);
    fd(0) = 0;
    clock_t start, finish;
    for (int i = 0;i<n; i++){
        d(i) = (i+2)*pow(i+1,-1);
    }
    start = clock();
    for (int i = 1;i<n; i++){
        fd(i) = f(i) +fd(i-1)/d(i-1);

    }
    u(n)=fd(n-1)/d(n-1); u(n+1) = 0; u(0)=0;
    for (int i = n-1 ; i>0; i--){
        u(i) = (fd(i) + u(i+1))/d(i);

    }
    finish = clock();
    for (int i=0; i<=n+1; i++){
        ofile << left << setw(12) << f[i] << " "
              << right << setw(7) << u[i] <<endl;

    }
    ofile.close();
    double ftime = double (finish-start)/CLOCKS_PER_SEC;
    cout << "Time = "<< ftime << endl;
    return 0;
}
