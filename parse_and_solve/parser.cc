#include <utility>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
using namespace std;

struct node
{
        string value;
        int childs;
        node**children;
};

struct node* newNode(string value, int childs){
        struct node* temp = new struct node();
        temp->value = value;
        temp->childs = childs;
        temp->children = new node*[childs];
        return temp;
}

void preorderPrint(node * nod){
        if(nod == NULL){
                return;
        }

        cout << nod->value << endl;

        for(int y = 0; y < nod->childs; y++){
                preorderPrint(nod->children[y]);
        }
        delete[] nod->children;
        delete nod;
}

void del(node * nod){
        for(int u = 0; u < nod->childs; u++){
                del(nod->children[u]);
                                }
       delete[] nod->children;
       delete nod;
}

int main() {
        ifstream myfile("math.lr");
        vector<string> terms;
        vector<string> non;
        vector<string> lprods;
        stack<int> stateStack;
        stack<node*> symStack;
        map<pair<int, string>, int> reduce;
        map<pair<int, string>, int> shift;
        int length, nlength;
        string start;

        // Read in terminals
        myfile >> length;
        for( int i = 0; i < length; ++i){
                string temp;
                myfile >> temp;
                terms.push_back(temp);
        }

        // Non terminals
        myfile >> nlength;
        for( int k = 0; k < nlength; ++k){
                string temp;
                myfile >> temp;
                non.push_back(temp);
        }

        //Start state
        myfile >> start;

        // Productions
        int nProds;
        myfile >> nProds;
        string temp1;
        getline(myfile, temp1);
        vector<vector<string>> rprods(nProds, vector<string>(0));
        for(int j = 0; j < nProds; j++){
                string lhs, rhs;
                getline(myfile, temp1);
                istringstream is(temp1);
                is >> lhs;
                lprods.push_back(lhs);
                while(is >> rhs){
                        rprods[j].push_back(rhs);
                }
        }

        // Actions
        int st = 0;
        int act = 0;
        // Num of states and num of actions
        myfile >> st >> act;
        string state1, line;
        getline(myfile, line);
        for(int j = 0; j < act; j++){
                getline(myfile, line);
                istringstream iss(line);
                int state1 = 0;
                int stateRule = 0;
                string symbol = "";
                string redShift = "";
                iss >> state1 >> symbol >> redShift >> stateRule;
                if(redShift == "reduce"){
                        reduce[make_pair(state1, symbol)] = stateRule;
                        continue;
                }
                shift[make_pair(state1, symbol)] = stateRule;
        }

        myfile.close();
        string var, lex;
        vector<pair<string, string>> read;
        int iteration = -1;
        stateStack.push(0);
        read.push_back(make_pair("BOF", "BOF"));
        while(cin >> var && cin >> lex){
                read.push_back(make_pair(var, lex));
        }
        read.push_back(make_pair("EOF", "EOF"));

        for(int a = 0; a < read.size(); a++){ // for each symbol a in |- x -|
                iteration++;
                // while a reduction exists between current state and a
                while(reduce[make_pair(stateStack.top(), read[a].first)] != 0){
                        // remove rhs of production
                        int red = reduce[make_pair(stateStack.top(), read[a].first)];
                        string right = "";
                        for( int g = 0; g < rprods[red].size(); g++){
                                right = right + " " + rprods[red][g];
                        }
                        node* out = newNode(lprods[red] + right, rprods[red].size());
                        for(int l = rprods[red].size() - 1; l >= 0; l--){
                                out->children[l] = symStack.top();
                                symStack.pop();
                                stateStack.pop();
                        }
                        // insert rhs of production
                        symStack.push(out);
                        stateStack.push(shift[make_pair(stateStack.top(), lprods[red])]);
                }
                // push symbol and state and reject if next state is undefined
                symStack.push(newNode(read[a].first + " " + read[a].second, 0));
                if(shift.count(make_pair(stateStack.top(), read[a].first)) == 0){
                        cerr << "ERROR at " << iteration << endl;
                        for( int g = 0; g < symStack.size();){
                                        del(symStack.top());
                                        symStack.pop();
                                        }
                        return 0;
                }
                stateStack.push(shift[(make_pair(stateStack.top(), read[a].first))]); // delta(StateStack.top, a);
        }
        int red = reduce[make_pair(stateStack.top(), "EOF")];
        string right = "";
        for( int g = 0; g < rprods[red].size(); g++){
                right = right + " " + rprods[red][g];
        }
        node* out = newNode(lprods[red] + right, rprods[red].size());
        for(int l = rprods[red].size() - 1; l >= 0; l--){
                out->children[l] = symStack.top();
                symStack.pop();
                stateStack.pop();
        }
        preorderPrint(out);
}
