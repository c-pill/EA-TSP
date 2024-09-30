#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string.h>
#include <time.h>
#include <vector>

using namespace std;

// keeps track of best individual and its fitness
int * best_individual;
int best_fit = INT_MAX;

// keeps track of number of nodes in problem
int num_nodes;

// keeps track of number of iterations
int iterations = 0;
// keeps track of number of iterations without improvement
int stale_iter = 0;


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
     
        // function displays an individual based on position in population
        void printIndividual(int pos) {
            cout << "Individual " << pos+1 << ':' << endl;
            for (auto i = 0; i < num_nodes; i++)
                cout << population[pos][i] << ' ';
            cout << endl << "Fitness " << fitness[pos] << endl;
        }

        // function displays new individual
        void printNew(int * individual) {
            cout << "New Individual:" << endl;
            for (auto i = 0; i < num_nodes; i++)
                cout << individual[i] << ' ';
        }

        // function displays the population
        void print() {
            for (auto i = 0; i < size; i++)
                printIndividual(i);
        } 

        // parent selection is uniform random
        // mating function uses order crossover and returns the child
        int * MATE() {
            int pos_1 = rand() % size;
            int pos_2 = rand() % size;
            while (pos_1 == pos_2)
                pos_2 = rand() % size;

            int * parent_1 = population[pos_1]; 
            int * parent_2 = population[pos_2];
            int * child = new int[num_nodes];

            pos_1 = rand() % num_nodes;
            pos_2 = rand() % num_nodes;
            while (pos_1 == pos_2)
                pos_2 = rand() % num_nodes;
            if (pos_1 > pos_2) {
                int tmp = pos_1;
                pos_1 = pos_2;
                pos_2 = tmp;
            }
            for (auto i = 0; i < num_nodes; i++) {
                if (i >= pos_1 && i <= pos_2)
                    child[i] = parent_1[i];
                else
                    child[i] = parent_2[i];
            }
            //printNew(child);
            return child;
        }

        // function evaluates an individual's fitness using Euclidean distance
        int EVALUATE(int coords[][2], int * individual) {
            double fit = 0;
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
       
        void SELECT() {

        }

        // constructor takes in size of each population to create random generation
        // and takes the data of nodes to evaluate each individual
        Generation(int coords[][2], int s) {
            size = s;
            population = new int*[size];
            fitness = new int[size];
            for (auto i = 0; i < size; i++) {
                population[i] = generatePermutation();
                fitness[i] = EVALUATE(coords, population[i]);
            }
        }

        Generation() {}
        
        ~Generation() {}
};

class Children : public Generation {
        
    public:
        // keeps track of how many individuals have been added to the children's set
        int individuals_set;

        // function used to add individuals to generation
        void addIndividual(int * individual) {
            population[individuals_set] = individual;
            individuals_set++;
        }

        // function that performs scramble mutation on child
        void MUTATE() {
            
        }

        Children() {}
        
        // constructor takes size to create shell for children set
        Children(int s) {
            size = s;
            population = new int*[size];
            fitness = new int[size];
            individuals_set = 0;
        }
        
        ~Children() {}
};

int main() {
    srand(time(0));
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
    const int size = 4*num_nodes;

    Generation generation(coords, size);

    cout << "First generation intialized successfully." << endl << endl;

    //generation.print();

    //while (stale_iter < 5000 && iterations < 10000) {
        // create new children set
        Children children(size);
        
        // perform MATE function size/4 times
        for (auto i = 0; i < size; i++)
            children.addIndividual(generation.MATE());
        
        children.print();

        // recombine pairs of parents

        // mutate offspring
        // evauluate new candidates
        // select individuals for the next generation
    //}


    return 0;
}