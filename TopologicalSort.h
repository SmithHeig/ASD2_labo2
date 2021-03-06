/*
 * File:   TopologicalSort.h
 * Author: Olivier Cuisenaire
 * 
 * Modified by: Alleman Adrien, Chatillon Jérémie and Smith James
 * Modified the: 29.10.2017
 *
 * Created on 08. octobre 2014, 14:07
 *
 * A implementer
 * Classe permettant le tri topologique d'un graphe oriente
 */

#ifndef ASD2_TopologicalSort_h
#define ASD2_TopologicalSort_h

#include "DirectedCycle.h"
#include <list>
#include <vector>
#include <exception>


template <typename GraphType>
class TopologicalSort {
private:
    std::vector<int> postOrder;
    
public:    
    //constructeur, Attends un SymbolGraph<DiGraph>
    TopologicalSort(const GraphType & g) {
        /* A IMPLEMENTER */  
        
        //détection de cycle
        DirectedCycle<GraphType> dcg = DirectedCycle<GraphType>(g);
        if(dcg.HasCycle()){
            throw(GraphNotDAGException(dcg.Cycle()));
        }
        
        //DiGraph dg = g.G().reverse();
        DFS<GraphType> dfs = DFS<GraphType>(g);
        
        //parcours DFS du graphe inversé
        dfs.visitGraph([](int){}, [&](int v){postOrder.push_back(v);});
    }
    
    //tableau contenant l'ordre de parcours des indexes des sommets dans le graphe
    const std::vector<int>& Order() {
        return postOrder;
    }
    
    //exception si le graphe n'est pas un DAG (Directed Acyclic Graph)
    class GraphNotDAGException : public std::exception {
        
    private:
        //indexes des sommets du cycle qui empeche le tris topologique
        const std::list<int> cycle;
        
    public:
        GraphNotDAGException(const std::list<int> cycle) noexcept : exception(), cycle(cycle) {
        }
        
        virtual const char* what() const noexcept {
            return "Topological sort impossible : the graph is not a DAG";
        }
        
            const std::list<int>& Cycle() const noexcept {
            return cycle;
        }
    };
};


#endif
