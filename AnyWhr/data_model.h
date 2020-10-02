#ifndef data_model_h
#define data_model_h
#include <iostream>
#include <vector>
#include <map>
#define ll long long
#define ld long double
#define mp make_pair
#define pb push_back
#define vll vector<ll>
#define pll pair<ll,ll>
#define vvll vector<vll>
#define vpll vector<pll>
#define fr(i,a,b) for(ll i=a;i<b;++i)
#define frb(i,a,b) for(ll i=a;i>b;--i)
#define endl '\n'
#define INF 99999999
#define MOD 1000000007
using namespace std;


ll const side = 5;
vll neighbour_edge_mapping = { 3, 4, 5, 0, 1, 2 };

class metaData {
public:
    metaData() {
        tryDelete = false;
        visited = false;
    }
    bool tryDelete;
    bool visited;
};

class node {
public:
    node(string name) {
        center = mp(-1, -1);
        this->name = name;
        neighbours = vector<node*>(6, NULL);
        data = new metaData();
    }
    pll center;
    string name;
    vector<node*> neighbours;
    metaData* data;
};

#endif