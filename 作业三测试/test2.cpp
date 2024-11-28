#include <iostream>
#include <string>
#include <vector>
#include <omp.h>
#include <random>
#include <ctime>
#include <stdlib.h>
using namespace std;

int main() {
    omp_set_num_threads(4);
    vector<int> x(220, 0);
    vector<int> y(220, 0);
    vector<vector<int> > a(110, vector<int>(110, 0));
    vector<vector<int> > c(110, vector<int>(110, 0));
    vector<int > b(110, 0);
    std::default_random_engine e;
    uniform_int_distribution<int> u(2, 20);
    e.seed(0);


    //init
    for (int i = 1; i <= 109; i++) {
        for (int j = 1; j <= 109; j++) {        
            a[i][j] = u(e);
            b[i] = u(e);
        }
    }
    auto a_ = a;
    auto b_ = b;
    for (int i = 1; i <= 109; i++) {
        for (int j = 1; j <= 109; j++) {
            c[i][j] = u(e);
        }
    }

    cout << endl;
    cout << endl;


    //修改n
    int n = 103;


    auto c_ = c;


    //benchmark
    for (int i = 1; i <= 100; i++) {
        x[i] = y[i] + 10;
        for (int j = 1; j <= 100; j++) {
            b[j] = a[j][n] + (i + j) % 17;
            for (int k = 1; k <= 100; k++) {
                a[j + 1][k] = b[j] + c[j][k];
            }
           y[i + j] = a[j + 1][n]; 
        }
    }


    vector<int> t(220, 0);
    
    a = a_;
    b = b_;
    c = c_;

    
    // ********************************
    // n < 100
    // ********************************

    // for (int i = 1; i <= 100; i++) {
    //     for (int j = 1; j <= 100; j++) {
    //         b[j] = a[j][n] + (i + j) % 17;
    //         #pragma omp parallel for 
    //         for (int k = 1; k <= 100; k++) {
    //             a[j + 1][k] = b[j] + c[j][k];
    //         } 

    //     }
    //     #pragma omp parallel for
    //     for (int j = 1; j <= 100; j++) {
    //         y[i + j] = a[j + 1][n];
    //     }
    // }
 
    // #pragma omp parallel for
    // for (int i = 1; i <= 100; i++) {
    //     t[i] = y[i] + 10;
    // }


    // #pragma omp parallel for
    // for (int i = 1; i <= 100; i++) {
    //     #pragma omp parallel for
    //     for (int j = 1; j <= 100; j++) {
    //         b[j] = a[j][n] + (i + j) % 17; 
    //     }

    // }

    // ********************************
    // n > 100
    // ********************************

    // #pragma omp parallel for
    // for (int i = 1; i <= 100; i++) {
    //     #pragma omp parallel for
    //     for (int j = 1; j <= 100; j++) {
    //         #pragma omp parallel for 
    //         for (int k = 1; k <= 100; k++) {
    //             a[j + 1][k] = b[j] + c[j][k];
    //         }  
    //     } 
    // }
    // // #pragma omp parallel for
    // for (int i = 1; i <= 100; i++) {
    //     #pragma omp parallel for
    //     for (int j = 1; j <= 100; j++) {
    //         y[i + j] = a[j + 1][n];
    //     }
    // }
       
    // #pragma omp parallel for
    // for (int i = 1; i <= 100; i++) {
    //     t[i] = y[i] + 10;
    // }


    for (int i = 0; i <= 109; i++) {
        if (x[i] != t[i]) 
            cout << x[i] << " " << t[i] << endl;
    }   
    std::cout << (int) (x == t) << std::endl;
}

