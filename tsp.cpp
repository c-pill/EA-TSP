#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string.h>
#include <time.h>
#include <vector>

using namespace std;

double best_fit;
int * best_ind;
int num_nodes;
int number = 0;

// each Generation stores the population and each individuals fitness
class Generation {
    public:
        int ** population;
        int * fitness;
        int size;

        int* generatePermutation() {
            int* individual = new int[num_nodes];
            int pos;
            vector<int> used;
            for (auto i = 0; i < num_nodes; i++) 
                used.push_back(i);
            for (auto i = 0; i < num_nodes; i++) {
                pos = rand() % used.size();
                individual[i] = used[pos];
                used.erase(used.begin() + pos);
            }
            return individual;
        }

        // function calculates an individual's fitness using Euclidean distance
        int calculateFitness(int coords[][2], int pos) {
            double fit = 0;
            int * individual = population[pos];
            for (int i = 0, j = 1; j < num_nodes; i++, j++) {
                fit += sqrt(
                    pow(coords[individual[i]][0]-coords[individual[j]][0], 2) +
                    pow(coords[individual[i]][1]-coords[individual[j]][1], 2)); 
            }
            fit += sqrt(
                pow(coords[individual[0]][0]-coords[individual[num_nodes-1]][0], 2) +
                pow(coords[individual[0]][1]-coords[individual[num_nodes-1]][1], 2));

            return (int)fit;
        }
            
        // function displays an individual
        void printIndividual(int pos) {
            cout << "Individual " << pos+1 << ':' << endl;
            for (auto i = 0; i < num_nodes; i++)
                cout << population[pos][i] << ' ';
            cout << endl << "Fitness " << fitness[pos] << endl;
        }

        // function displays the population
        void print() {
            for (auto i = 0; i < size; i++)
                printIndividual(i);
        } 
        
        // constructor takes in size of each population to create generation
        Generation(int coords[][2], int s) {
            size = s;
            population = new int*[size];
            fitness = new int[size];
            srand(time(0));
            for (auto i = 0; i < size; i++) {
                population[i] = generatePermutation();
                fitness[i] = calculateFitness(coords, i);
            }
        }

        ~Generation() {
            cout << "Kill" << endl;
        }
};

int main() {
    cout << "Accessing file ..." << endl;
    // reads data from file and creates initial generation
    ifstream file("TSPDATA.txt", ios::in);
    if (!file.is_open()) {
        cerr << "Error accessing file.";
        return 1;
    }
    string s;
    int node, x_coord, y_coord;
    
    cout << "Reading data from file ... " << endl;

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

    cout << "Data from file stored. Creating first generation ..." << endl;

    // population size 4 times the number of nodes
    Generation parent(coords, 4*num_nodes);
    
    parent.print();
    cout << "Intialization Complete." << endl;

    return 0;
}