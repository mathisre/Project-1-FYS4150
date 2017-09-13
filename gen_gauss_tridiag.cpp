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
    filename = argv[1]; //read filename and n from command line
    int n = atoi(argv[2]);
    ofile.open(filename);
    ofile << n << endl; //print n to command line for plotting
    double h = 1./(n+1);
    clock_t start, finish;
    vec x = linspace<vec>(0, 1, n+1);
    vec a = -1*ones(n); //initializing diagonal elements
    vec d = 2* ones(n+1);
    vec c = -1*ones(n);
    vec f =100*exp(-10*x)*pow(h,2);
    vec u(n+2); //u has more elements because we need to input boundary conditions
    vec fd(n+1);
    start = clock();
    fd(0) = 0;
    for (int i=1; i<=n; i++){
        d(i) = d(i) - c(i-1)*a(i-1)/d(i-1); //note that a is of length n not n+1, and that a_1 is in the 2nd row
        fd(i) = f(i) -fd(i-1)*a(i-1)/d(i-1);
    }
    u(n+1)=0; u(0)=0; u(n)= fd(n)/d(n);
    for (int i=n-1; i>0; i--){
        u(i) = (fd(i) - c(i)*u(i+1))*pow(d(i),-1); //solution
    }
    finish = clock();
    for (int i=0; i<=n+1; i++){
        ofile << left << setw(12) << fd[i] << " " //printing solution (and f~to file)
              << right << setw(7) << u[i] <<endl;
    }
    double ftime = double (finish-start)/CLOCKS_PER_SEC;
    cout << ftime << endl;
    ofile.close();
    return 0;
}
