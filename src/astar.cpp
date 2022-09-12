
#include "astar.h"
#include <algorithm>
#include <chrono>


std::vector<AStarNode *> AStarAlgorithm::findPath(AStarNode* startNode, AStarNode* goalNode){
    this->openList.push_back(startNode);
    std::vector<AStarNode *> path;
    startNode->setGlobalCost(0);
    startNode->setHeuristicCost(startNode->getEuclidianDistance(goalNode));
    int iterations = 0;
    std::chrono::time_point<std::chrono::system_clock> start, tmp_time;
    start = std::chrono::system_clock::now();
    while(!openList.empty()) {
        // sortOpenList();
        // remove the first element from the open list and add it to the closed list and to the path
        AStarNode* currentNode = openList[0];
        // closedList.push_back(currentNode);
        tmp_time = std::chrono::system_clock::now();
        openList.erase(openList.begin());
        // std::cout << "Time to erase: " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - tmp_time).count()<< " microseconds"<< std::endl;
        if(currentNode == goalNode) {
            std::cout << "Caminho encontrado em " << iterations << " iterações" << std::endl;
            tmp_time = std::chrono::system_clock::now();
            path = reconstructPath(startNode, goalNode);
            // std::cout << "Time to reconstruct: " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - tmp_time).count()<< " microseconds"<< std::endl;
            return path;
        }

        for(int i = 0; i < currentNode->getNeighbors().size(); i++) {
            tmp_time = std::chrono::system_clock::now();
            float gScore = currentNode->getGlobalCost() + currentNode->getCostToNeighbor(currentNode->getNeighbors()[i]); //currentNode->getDistance(currentNode->getNeighbors()[i]);
            // print the elapsed time in seconds
            // std::cout << "Time to get cost: " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - tmp_time).count()<< " microseconds"<< std::endl;

            if(gScore < currentNode->getNeighbors()[i]->getGlobalCost()) {
                currentNode->getNeighbors()[i]->setParent(currentNode);
                currentNode->getNeighbors()[i]->setGlobalCost(gScore);
                if(currentNode->getNeighbors()[i] != goalNode) {
                    tmp_time = std::chrono::system_clock::now();
                    currentNode->getNeighbors()[i]->setHeuristicCost(currentNode->getNeighbors()[i]->getManhattanDistance(goalNode));
                    // std::cout << "Time to calculate heuristic: " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - tmp_time).count()<< " microseconds"<< std::endl;
                }
                // if(std::find(openList.begin(), openList.end(), currentNode->getNeighbors()[i]) == openList.end() && std::find(closedList.begin(), closedList.end(), currentNode->getNeighbors()[i]) == closedList.end()) {
                //     // openList.push_back(currentNode->getNeighbors()[i]);
                //     tmp_time = std::chrono::system_clock::now();
                //     insertOpenList(currentNode->getNeighbors()[i]);
                //     // std::cout << "Time to insert: " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - tmp_time).count()<< " microseconds"<< std::endl;
                // }
                
                insertOpenList(currentNode->getNeighbors()[i]);
            }
        }
        iterations++;
        if(iterations % 10000 == 0) {
            std::cout << "Iteração " << iterations << std::endl;
            std::cout << "Tempo para as últimas 10000 iterações: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << "ms" << std::endl;
            start = std::chrono::system_clock::now();
            std::cout << "Tamanho da open list: " << openList.size() << std::endl;
            // std::cout << "Tamanho da closed list: " << closedList.size() << std::endl;

        }

    }

    return path;
}


std::vector<AStarNode *> AStarAlgorithm::reconstructPath(AStarNode* startNode, AStarNode* goalNode){
    std::vector<AStarNode *> path;
    AStarNode * currentNode = goalNode;
    while(currentNode != startNode){
        path.push_back(currentNode);
        currentNode = currentNode->getParent();
    }
    path.push_back(startNode);
    std::reverse(path.begin(), path.end());
    std::cout << "Distance: " << goalNode->getGlobalCost() << std::endl;
    return path;
}

void AStarAlgorithm::insertOpenList(AStarNode* node){
    // insert the node in the open list, but keep the list sorted by the global cost using binary search
    if(openList.empty()) {
        openList.push_back(node);
        return;
    }
    std::vector<AStarNode *>::iterator lowerbound = openList.begin();
    std::vector<AStarNode *>::iterator upperbound = openList.end();
    std::vector<AStarNode *>::iterator middle;
    
    while(upperbound > lowerbound) {
        middle = lowerbound + (int)(upperbound - lowerbound)/2;
        if(node->getGlobalCost() + node->getHeuristicCost() < (*middle)->getGlobalCost() + (*middle)->getHeuristicCost()) {
            upperbound = middle-1;
        } else {
            lowerbound = middle+1;
        }
    }
    middle = lowerbound + (int)(upperbound - lowerbound)/2;
    
    this->openList.insert(middle, node);
}
