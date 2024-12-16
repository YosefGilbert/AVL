#include <iostream>
#include "AVL.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
bool isValidID(string ID);
bool isValidName(string name);
bool isValidName(string name){
    for (unsigned int i = 0; i < name.size(); i++){
        if (!isalpha(name[i]))
        {
            return false;
        }
    }
    return true;
}
bool isValidID(string ID){
    for (unsigned int i = 0; i < ID.size(); i++){
        if (!isdigit(ID[i]))
        {
            return false;
        }
        if (ID.size() != 8)
        {
            return false;
        }
    }
    return true;
}

int main(){
    Tree tree;
    string numCommands;
    string line;
    getline(cin, numCommands);
    for (int i = 0; i < stoi(numCommands); i++)
    {
        string name;
        string ID;

        getline(cin, line);
        istringstream in(line);
        string command;
        getline(in, command, ' ');
        if (command == "insert")
        {
            getline(in, name, '"'); //skips over the space
            getline(in, name, '"');

            getline(in, ID,  ' '); // skips over the space
            getline(in, ID,  ' ');
            if (isValidID(ID) and isValidName(name)){
                tree.insert(ID, name);
                cout << "successful" << endl;
            } else{
                cout <<"unsuccessful" << endl;
            }

        }
        if (command == "remove")
        {
            getline(in, ID,  ' '); // skips over the space
            getline(in, ID,  ' ');
            if (isValidID(ID)){
                tree.remove(ID);
            } else{
                cout <<"unsuccessful" << endl;
            }
        }
        if (command == "search")
        {
            getline(in, name, '"'); //skips over the space
            getline(in, name, '"');
            if (isValidName(name))
            {
                tree.searchName(name);
            }
            if (isValidID(name))
            {
                if (!tree.searchID(name).empty()){
                    cout << tree.searchID(name) << endl;
                } else{
                    cout << "unsuccessful" << endl;
                }
            }
            if (!isValidID(name) and !isValidName(name))
            {
                cout << "unsuccessful" << endl;
            }
        }
        if (command == "printInorder")
        {
            vector<string> names = tree.printInorder();
            tree.printVector(names);
        }
        if (command == "printPreorder")
        {
            vector<string> names = tree.printPreorder();
            tree.printVector(names);
        }
        if (command == "printPostorder")
        {
            vector<string> names = tree.printPostorder();
            tree.printVector(names);
        }
        if (command == "printLevelCount")
        {
            tree.printLevelCount();
        }
        if (command == "removeInorder")
        {
            string N;
            getline(in, N,  ' '); // skips over the space
            getline(in, N,  ' ');
            tree.removeInorder(stoi(N));
        }
    }
//    tree.printHeights();
	return 0;
}
