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

node* create_node() {
    string name;
    cout << "Enter name: ";
    cin >> name;
    return new node(name);
}

pll get_center_coordinates(pll center, ll edge) {
    switch (edge) {
    case 0: {//up
        return mp(center.first, center.second + 2 * side);
    }
          break;
    case 1: {//up-right
        return mp(center.first + 2 * side, center.second + side);
    }
          break;
    case 2: {//down-right
        return mp(center.first + 2 * side, center.second - side);
    }
          break;
    case 3: {//down
        return mp(center.first, center.second - 2 * side);
    }
          break;
    case 4: {//down-left
        return mp(center.first - 2 * side, center.second - side);
    }
          break;
    case 5: {//up-left
        return mp(center.first - 2 * side, center.second + side);
    }
          break;
    }
}

void update_neighbours(node* temp, map<pll, node*>& grid, bool remove_node) {
    fr(i, 0, 6) {
        map<pll, node*>::iterator it = grid.find(get_center_coordinates(temp->center, i));
        if (it != grid.end()) {
            temp->neighbours[i] = remove_node ? NULL : it->second;
            it->second->neighbours[neighbour_edge_mapping[i]] = remove_node ? NULL : temp;
        }
    }
}

void add_neighbour(map<string, pll>& grid_nodes, map<pll, node*>& grid) {
    string name;
    cout << "Enter existing node name: ";
    cin >> name;
    map<string, pll>::iterator it = grid_nodes.find(name);
    if (it != grid_nodes.end()) {//node found
        node* curr = grid[it->second];
        ll edge;
        cout << "Enter the edge to add neighbour to: ";
        cin >> edge;
        if (edge < 6 && curr->neighbours[edge] == NULL) {//can add neighbour
            node* temp = create_node();
            pll cood = get_center_coordinates(it->second, edge);//center coordinates of new node
            temp->center = cood;
            grid_nodes.insert(mp(temp->name, cood));
            grid.insert(mp(cood, temp));
            update_neighbours(temp, grid, false);
        }
        else {
            cout << "Cannot add neighbour here.\n";
        }
    }
    else {
        cout << "Node does not exist.\n";
    }
}

void print_neighbours(string name, map<string, pll>& grid_nodes, map<pll, node*>& grid) {
    map<string, pll>::iterator it = grid_nodes.find(name);
    if (it == grid_nodes.end()) {
        cout << "Node doesn't exit.\n";
    }
    else {
        node* temp = grid[it->second];
        fr(i, 0, 6) {
            if (temp->neighbours[i] != NULL) {
                cout << i << "->" << temp->neighbours[i]->name << endl;
            }
        }
    }
}

node* get_next_neighbour(node* temp) {
    fr(i, 0, 6) {
        if (temp->neighbours[i] != NULL) return temp->neighbours[i];
    }
    return NULL;
}

ll get_count(node* curr) {
    ll count = 1;
    curr->data->visited = 1;
    fr(i, 0, 6) {
        if (curr->neighbours[i] != NULL) {
            node* neigh = curr->neighbours[i];
            if (neigh->data->visited == false && neigh->data->tryDelete == false)count += get_count(neigh);
        }
    }
    return count;
}

void delete_node(map<string, pll>& grid_nodes, map<pll, node*>& grid) {
    string name;
    cout << "Enter the node to be deleted: ";
    cin >> name;
    map<string, pll>::iterator it = grid_nodes.find(name);
    if (it == grid_nodes.end()) {
        cout << "Node doesn't exit.\n";
    }
    else {
        node* curr = grid[it->second];
        node* neigh = get_next_neighbour(curr);
        if (neigh != NULL) {
            curr->data->tryDelete = true;
            ll count = get_count(neigh);//count all nodes reachable from neigh
            if (count == grid.size() - 1) {//can delete node
                update_neighbours(curr, grid, true);
                //delete from maps
                grid.erase(grid.find(it->second));
                grid_nodes.erase(it);
                //delete node
                delete curr;
            }
            else {
                cout << "Cannot delete node as it is a bridge.\n";
            }
        }
        else {
            grid.erase(grid.find(it->second));
            grid_nodes.erase(it);
            delete curr;
        }
    }
}

void reset_data(map<pll, node*>& grid) {
    for (map<pll, node*>::iterator it = grid.begin(); it != grid.end(); ++it) {
        it->second->data->visited = false;
        it->second->data->tryDelete = false;
    }
}

void show_options() {
    cout << "Press \n";
    cout << "1 to Create start node.\n";
    cout << "2 to Create and connect new node to an existing node.\n";
    cout << "3 to Delete existing node.\n";
    cout << "4 to Get neighbours of existing node.\n";
    cout << "5 to Exit.\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    map<string, pll> grid_nodes;//grid_nodes[name] = coordinates
    map<pll, node*> grid;//grid[co-ordinate] = node*
    ll option;
    string name;
    do {
        show_options();
        cin >> option;
        switch (option) {
        case 1: {//Create
            node* temp;
            if (grid.size() == 0) {
                temp = create_node();
                temp->center.first = temp->center.second = 0;//start node co-ordinates (0,0)
                grid_nodes.insert(mp(temp->name, temp->center));
                grid.insert(mp(temp->center, temp));
                //cout<<temp->name<<endl;
            }
            else {
                cout << "Start node already exists.\n";
            }
        }
              break;
        case 2: {//Add neighbour
            if (grid.size() == 0) {
                cout << "Cannot add node to cluster as no node exits.\n";
                break;
            }
            add_neighbour(grid_nodes, grid);
        }
              break;
        case 3: {//Delete
            if (grid.size() == 0) {
                cout << "Cannot delete node as no node exits.\n";
                break;
            }
            delete_node(grid_nodes, grid);
            reset_data(grid);
        }
              break;
        case 4: {//Get neighbours
            if (grid.size() == 0) {
                cout << "No node exits.\n";
                break;
            }
            string name;
            cout << "Enter node name: ";
            cin >> name;
            print_neighbours(name, grid_nodes, grid);
        }
              break;
        case 5:
            cout << "Bye.\n";
            break;
        default:
            cout << "Invalid entry.\n";
        }

    } while (option != 5);

    return 0;
}
