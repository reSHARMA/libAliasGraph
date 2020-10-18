#ifndef ALIASGRAPH_H
#define ALIASGRAPH_H

#include "iostream"
#include "map"
#include "set"

namespace AliasGraphUtil {
template <class AliasNode>

class AliasGraph {
   private:
    std::map<AliasNode*, std::set<AliasNode*>> Graph;

   public:
    bool hasEdgeBetween(AliasNode*, AliasNode*);
    void insert(AliasNode*, AliasNode*, int, int);
    bool insert(AliasNode*, AliasNode*);
    std::set<AliasNode*> getPointee(AliasNode*);
    template <class Node>
    friend std::ostream& operator<<(std::ostream& OS,
                                    const AliasGraph<Node>& G);
};

/** Implementation ---- **/

/// hasEdgeBetween - Returns true if there is a edge between \p Src and \p Dest
template <class AliasNode>
bool AliasGraph<AliasNode>::hasEdgeBetween(AliasNode* Src, AliasNode* Dest) {
    if (Graph.find(Src) == Graph.end()) return false;
    return this->getPointee(Src).find(Dest) != this->getPointee(Src).end();
}

/// insert - Inserts an edge between \p Src and \p Dest based on \p Left and \p
/// Right. \p Left and \p Right denotes the level of redirection in LHS and RHS
/// respectively example a = b is denoted by (1, 1) and a = &b by (1, 0).
/// Only a = b, a = &b, a = *b and *a = b supported right now, TODO support more
template <class AliasNode>
void AliasGraph<AliasNode>::insert(AliasNode* Src, AliasNode* Dest, int Left,
                                   int Right) {
    if (Left == 1 && Right == 1) {
        for (auto Alias : this->getPointee(Dest)) {
            this->insert(Src, Alias);
        }
    } else if (Left == 2 && Right == 1) {
        for (auto AliasSrc : this->getPointee(Src)) {
            for (auto AliasDest : this->getPointee(Dest)) {
                this->insert(AliasSrc, AliasDest);
            }
        }
    } else if (Left == 1 && Right == 0) {
        this->insert(Src, Dest);
    } else if (Left == 1 && Right == 2) {
        for (auto AliasDest : this->getPointee(Dest)) {
            for (auto AliasDestDest : this->getPointee(AliasDest)) {
                this->insert(Src, AliasDestDest);
            }
        }
    }
}

/// insert - Inserts an direct edge between \p Src andp Dest. Returns false if
/// the edge already existed
template <class AliasNode>
bool AliasGraph<AliasNode>::insert(AliasNode* Src, AliasNode* Dest) {
    if (this->hasEdgeBetween(Src, Dest)) return false;
    this->Graph[Src].insert(Dest);
    return true;
}

/// getPointee - Returns a set of pointee for a given \p Node. Retuns an empty
/// set if \p Node does not point to anyone
template <class AliasNode>
std::set<AliasNode*> AliasGraph<AliasNode>::getPointee(AliasNode* Node) {
    std::set<AliasNode*> PointeeSet;
    if (this->Graph.find(Node) != this->Graph.end())
        PointeeSet = this->Graph[Node];
    return PointeeSet;
}

template <class AliasNode>
std::ostream& operator<<(std::ostream& OS, const AliasGraph<AliasNode> &G){
    for(auto X : G.Graph){
        OS << *(X.first) << " -> {";
        for(auto Y : X.second){
            OS << *(Y) << ", ";
        }
        OS << "}\n";
    }
    return OS;
}

}  // namespace AliasGraphUtil
#endif
