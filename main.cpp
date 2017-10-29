/*
 * File:   DFSOrder.h
 * Author: Cuisenaire
 * Labo 2
 * Created on 3. novembre 2014, 08:23
 */


#include <cstdlib>
#include <iostream>
#include "DiGraph.h"
#include "TopologicalSort.h"

// vous devez reutiliser celui du labo 1, ex 2 (cf. donnee)
#include "Util.h"
#include "SymbolGraph.h"

using namespace std;

//methode permettant de verifier le graphe trie par rapport au fichier d'entree
bool checkOrder(const std::vector<int>& order,
                const SymbolGraph<DiGraph>& SG,
                const std::string& filename,
                char delim) {

    std::vector<int> positionInOrder(order.size());
    for( size_t i = 0; i < order.size(); ++i )
        positionInOrder[order[i]] = int(i);
    
    bool ok = true;
    
    std::string line;
    
    std::ifstream s(filename);
    while (std::getline(s, line))
    {
        auto names = split(line,delim);
        
        for(size_t i = 1; i < names.size(); ++i) {
         
            int v = SG.index(names[0]); // module
            int w = SG.index(names[i]); // ieme prerequis
            
            if ( positionInOrder[ v ] < positionInOrder [ w ]) {
                cout << "Erreur d'ordre : " << names[0] << " avant " << names[i] << endl;
                ok = false;
            } 
        }
    }
    s.close();
    
    return ok;
}



int main(int argc, const char * argv[]) {

    string fileName1 = "prerequis.txt";
    string fileName2 = "prerequis2.txt";
    
    /* TEST FILE 1*/
    SymbolGraph<DiGraph> g1(fileName1, ',');
    
    DirectedCycle<SymbolGraph<DiGraph>> dc1(g1);
    
    cout << "Does file 1 have a cycle ? : " << dc1.HasCycle() << endl;
  
    cout << "The cycle is : " << endl;
    std::list<int> cycle1 = dc1.Cycle();
    
    for(auto i = cycle1.begin(); i != cycle1.end(); i++){
        cout << "(" << *i << ") ";
    }
    cout << endl;
    
    /* TEST FILE 2 */
    SymbolGraph<DiGraph> g2(fileName2,',');
    
    DirectedCycle<SymbolGraph<DiGraph>> dc2(g2);
    cout << "Does file 2 have a cycle ? : " << dc2.HasCycle() << endl;
  
    cout << "The cycle is : " << endl;
    std::list<int> cycle2 = dc2.Cycle();
    
    for(auto i = cycle2.begin(); i != cycle2.end(); i++){
        cout << "(" << g2.name(*i) << ") ";
    }
    cout << endl;
    return EXIT_SUCCESS;
}
