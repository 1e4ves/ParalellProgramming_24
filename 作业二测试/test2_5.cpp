#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <omp.h>

using namespace std;

int main(int argc, char** argv) {

    std::default_random_engine e;
    std::uniform_int_distribution<int> u(2,20); // 左闭右闭区间
    e.seed(time(0));
    
    vector<vector<int> > a(110, vector<int>(110, 0));
    vector<vector<int> > b(110, vector<int>(110, 0));
    
    for (int i = 1; i <= 100; i++) {    
        for (int j = 1; j <= 100; j++) {
            a[i][j] = u(e);
        }
    }
    
    b = a;
    cout << (a == b ? "Yes" : "No") << endl;
    for (int i = 1; i <= 100; i++) {    
        for (int j = 4; j <= 100; j++) {        
            a[i][j] = a[i - 1][j + 1];
        }
    }

    #pragma omp parallel for
    for (int i = 1; i <= 100; i++) {      
        for (int j = 4; j <= 100; j++) {
            b[i][j] = b[i - 1][j + 1];
        }
    }
    cout << (a == b ? "Yes" : "No") << endl;
}

