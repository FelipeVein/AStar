#ifndef ASTARNODE_H
#define ASTARNODE_H


#include <vector>
#include <cmath>
#include <map>
#include <iostream>

class AStarNode {
    public: 

        // constructor and destructor
        AStarNode(float x, float y) { this->x = x; this->y = y; };
        AStarNode(float x, float y, AStarNode* parent, float globalCostUntilSelf) { this->x = x; this->y = y; this->parent = parent; this->globalCostUntilSelf = globalCostUntilSelf; };
        ~AStarNode();

        // variables
        float x;
        float y;
        float globalCostUntilSelf = INFINITY;
        float heuristicCostUntilGoal = 0;
        std::vector<AStarNode*> neighbors;
        std::map<AStarNode*, float> neighborCosts;
        AStarNode* parent = nullptr;


        // getters and setters
        float getGlobalCost() { return globalCostUntilSelf;};
        float getHeuristicCost() { return heuristicCostUntilGoal;};
        void setParent(AStarNode* parent) { this->parent = parent;};
        AStarNode* getParent() { return parent;};
        void setGlobalCost(float globalCostUntilSelf) { this->globalCostUntilSelf = globalCostUntilSelf;};
        void setHeuristicCost(float heuristicCostUntilGoal) { this->heuristicCostUntilGoal = heuristicCostUntilGoal;};
        void addNeighbor(AStarNode* neighbor) { neighbors.push_back(neighbor); neighborCosts[neighbor] = getManhattanDistance(neighbor);};
        void addNeighbor(AStarNode* neighbor, float cost) { neighbors.push_back(neighbor); neighborCosts[neighbor] = getManhattanDistance(neighbor)+cost;};
        std::vector<AStarNode*> getNeighbors() { return neighbors;};
        void removeNeighbor(AStarNode* neighbor) {
            for (int i = 0; i < neighbors.size(); i++) {
                if (neighbors[i] == neighbor) {
                    neighbors.erase(neighbors.begin() + i);
                }
            }
        };
        void clearNeighbors() { neighbors.clear();};


        // functions
        float getManhattanDistance(AStarNode* node) { return std::abs(x-node->x) + std::abs(y-node->y);}; //{return abs(x-node->x) + abs(y-node->y);};
        float getEuclidianDistance(AStarNode* node) { return sqrt(pow(node->x - x, 2) + pow(node->y - y, 2));}; 
        
        float getCostToNeighbor(AStarNode* neighbor) { return neighborCosts[neighbor];};
        float getRowCost(AStarNode* node) { return std::abs(y - node->y);};

        // cout operator
        friend std::ostream& operator<<(std::ostream& os, const AStarNode& node) {
            os << "NODE<<"<< "x: " << node.x << " y: " << node.y << ">>";
            return os;
        }
        

            
};

// bool operator<(const AStarNode& p1, const AStarNode& p2)
// {

//     return (p1.globalCostUntilSelf + p1.heuristicCostUntilGoal) < (p2.globalCostUntilSelf + p2.heuristicCostUntilGoal);
// }

#endif