#include <vector>
#include "astarnode.h"
#include <algorithm>

class AStarAlgorithm{
    public: 
    
            // constructor and destructor
            AStarAlgorithm() {};
            ~AStarAlgorithm() {};
    
            // variables
            std::vector<AStarNode*> openList;
            std::vector<AStarNode*> closedList;
    
            // functions
            std::vector<AStarNode *> findPath(AStarNode* startNode, AStarNode* goalNode);
            std::vector<AStarNode *> reconstructPath(AStarNode* startNode, AStarNode* goalNode);
            void sortOpenList() { std::sort(openList.begin(), openList.end(), [](AStarNode* a, AStarNode* b) { return a->getGlobalCost() + a->getHeuristicCost() < b->getGlobalCost() + b->getHeuristicCost(); });};
            void insertOpenList(AStarNode* node);
};