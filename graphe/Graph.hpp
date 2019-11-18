#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <vector>
#include <utility>
#include <algorithm>
#include <mutex>
#include <thread>
#include <fstream>
#include <utility> 
#include <random>
#include <chrono>

using namespace std;
typedef struct noued{
    int val;
    float x,y;
    bool voiture;
    vector<int> autre;	
}noued;
vector<noued> Graph;

default_random_engine generator;
uniform_int_distribution<int> distribution;
vector<pair<thread,int>> Thread;
bool Prog;

int mainA();
void affiche();
void charger(string name);
void ajouter_arrete(int val1,int val2);
void init_aleatoire(int val);
void ajouter_arrete_double(int val1,int val2);
void init_voiture(int);
void erase_all_point_null();
int element(int val);