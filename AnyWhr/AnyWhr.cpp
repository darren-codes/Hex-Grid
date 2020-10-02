#include "neighbour_functions.h"

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
