#include <iostream>
#include <mpi.h>
#include <vector>
#include <ctime>
#include <random>

using namespace std;

int main(int argc, char** argv) {
    std::default_random_engine e;
    std::uniform_int_distribution<int> u(1, 100); 
    e.seed(time(0));
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    
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

    for (int j = 4; j <= 100; j++) {    
        for (int i = 1; i <= 100; i++) {
            b[i][j] = b[i - 1][j + 1];
        }
    }

    cout << (a == b ? "Yes" : "No") << endl;
    MPI_Finalize();
}
