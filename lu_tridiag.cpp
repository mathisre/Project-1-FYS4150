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
    filename = argv[1]; //importing filename and n from command line
    int n = atoi(argv[2]);
    ofile.open(filename);
    ofile << n << endl; //printing n to file to use when plotting
    double h = 1./(n+1);
    clock_t start, finish;
    mat A = zeros<mat>(n,n); //initializing variables
    vec x = linspace<vec>(0, 1, n);
    vec f =100*exp(-10*x)*pow(h,2);
    for (int i=0; i<n; i++){ //Creating matrix A
        if(i!=n-1){
            A(i,i) = 2;
            A(i,i+1) = -1;
        }
        if (i !=0 ){
            A(i,i)=2;
            A(i,i-1) = -1;
        }
    }
    start = clock();
    vec solution = solve(A,f); //Solving for u
    finish = clock();
    ofile << 0 << endl; //boundary condition
    ofile << solution;
    double ftime = double (finish-start)/CLOCKS_PER_SEC;
    cout << "time = " << ftime<<endl;
    ofile.close();
    return 0;
}
