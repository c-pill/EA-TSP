#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string.h>
#include <time.h>
#include <vector>

using namespace std;

int num_nodes;
int number = 0;

// function displays individual
void indPrint(int * ind) {
    for (auto i = 0; i < num_nodes; i++)
        cout << ind[i] << ' ';
    cout << endl << endl;
}

// fitness function calculates the Euclidean distance between two nodes
int fitness(int * node1, int * node2) {
    int euc_dist = pow(node1[0]-node2[0],2) + pow(node1[1]-node2[1],2);
    return sqrt(euc_dist);
}

// function calculates an individual's fitness
int indFitness(int ** coords, int * ind) {
    int fit = 0;
    for (int i = 0, j = 1; j <= num_nodes; i++)
        fit += fitness(coords[ind[i]], coords[ind[j]]);
    return fit;
}

int* generatePermutation() {
    int* ind = new int[num_nodes];
    int pos;
    vector<int> used;
    for (auto i = 0; i < num_nodes; i++) 
        used.push_back(i);

    for (auto i = 0; i < num_nodes; i++) {
        pos = rand() % used.size();
        ind[i] = used[pos];
        used.erase(used.begin() + pos);
    }
    return ind;
}

// function generates initial population
int** generatePopulation(int size) {
    // individuals stored in [0], fitness stored in [1]
    int** pop = new int*[size];
    for (auto i = 0; i < size; i++) {
        pop[i] = generatePermutation();
    }
        
    return pop;
}

// deletes population once program is complete
void deletePopulation(int ** pop, int size) {
    for (auto i = 0; i < size; i++) {
        delete(pop[i]);
    }
    delete(pop);
}

int main() {
    // code intializing the process: collect data and generate first
    // population

    ifstream file("TSPDATA.txt", ios::in);
    if (!file.is_open()) {
        cerr << "Error accessing file";
        return 1;
    }
    string s;
    int node, x_coord, y_coord;

    for (auto i = 0; i < 2; i++, file >> s);
    file >> num_nodes;
    for (auto i = 0; i < 3; i++, file >> s);

    // nodes start at 1 but are stored starting at 0
    int coords[num_nodes][2];

    for (auto i = 0; file >> node; i++) {
        file >> x_coord;
        file >> y_coord;
        coords[i][0] = x_coord;
        coords[i][1] = y_coord;
    }
    const int size = 4*num_nodes;
    srand(time(0));

    int ** pop = generatePopulation(size); 
    indPrint(pop[0]);
    // code for beginning the 

    deletePopulation(pop, size);
    return 0;
}