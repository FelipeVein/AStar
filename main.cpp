#define OLC_PGE_APPLICATION
#include <iostream>
#include "astar.h"
#include <chrono>
#include <cmath>
#include "gamescreen.h"
// #include "olcPixelGameEngine.h"


void test1() {
    // create a 10 x 10 grid using AStarNodes
    const int size = 10;
    AStarNode* grid[size][size];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j] = new AStarNode(i, j);
        }
    }

    // add neighbors to each node - this is a 4-way grid
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i > 0) {
                grid[i][j]->addNeighbor(grid[i-1][j]);
            }
            if (i < size-1) {
                grid[i][j]->addNeighbor(grid[i+1][j]);
            }
            if (j > 0) {
                grid[i][j]->addNeighbor(grid[i][j-1]);
            }
            if (j < size-1) {
                grid[i][j]->addNeighbor(grid[i][j+1]);
            }
        }
    }

    // // print the grid
    // for (int j = 0; j < 10; j++) {
    //     for (int i = 0; i < 10; i++) {
    //         std::cout << *grid[i][j]<< " ";
    //     }
    //     std::cout << std::endl;
    // }

    // // create an AStarAlgorithm object
    AStarAlgorithm aStar;

    // // find a path from the top left to the bottom right

    std::vector<AStarNode *> path = aStar.findPath(grid[0][0], grid[size-1][size-1]);

    // print the path
    for (int i = 0; i < path.size(); i++) {
        std::cout << *path[i] << std::endl;
    }
}



void test2(){
    
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<AStarNode*>> talhao;
    int scale_x = 1;
    int scale_y = 1;

    int n_rows = 2000/scale_x;
    int n_nodes = 300/scale_y;

    int row_robot =100/scale_x, node_robot = 50/scale_y;
    int row_goal = 500/scale_x, node_goal = 50/scale_y;

    // create 2000 rows of 200 nodes and add them to talhao
    for (int i = 0; i < n_rows; i++) {
        std::vector<AStarNode*> row;
        for (int j = 0; j < n_nodes; j++) {
            row.push_back(new AStarNode(i*0.45, j*3));
        }
        talhao.push_back(row);
    }


    for(int i = 0; i < n_rows; i ++){
        for(int j= 0; j < n_nodes; j++){
            if(j > 0){
                if(j == n_nodes-1){
                    talhao[i][j]->addNeighbor(talhao[i][j-1], 1000*abs(row_goal - i));
                }
                else{
                    talhao[i][j]->addNeighbor(talhao[i][j-1]);
                }
            }
            if(j < n_nodes-1){
                if(j == 0){
                    talhao[i][j]->addNeighbor(talhao[i][j+1], 1000*abs(row_goal - i));
                }
                else{
                    talhao[i][j]->addNeighbor(talhao[i][j+1]);
                }
            }
        }
        if(i < n_rows-1){
            talhao[i][0]->addNeighbor(talhao[i+1][0]);
            talhao[i][n_nodes-1]->addNeighbor(talhao[i+1][n_nodes-1]);
        }
        if(i > 0){
            talhao[i][0]->addNeighbor(talhao[i-1][0]);
            talhao[i][n_nodes-1]->addNeighbor(talhao[i-1][n_nodes-1]);
        }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Tempo para criar o talhao: " << elapsed.count() << "s" << std::endl;
    // create an AStarAlgorithm object
    AStarAlgorithm aStar;

    AStarNode * robot_position = talhao[row_robot][node_robot];
    AStarNode * goal_position = talhao[row_goal][node_goal];

    std::cout << "Encontrando um caminho entre os pontos "<< *robot_position << " e " << *goal_position << std::endl;

    // find a path from the top left to the bottom right
    start = std::chrono::high_resolution_clock::now();
    std::vector<AStarNode *> path = aStar.findPath(robot_position, goal_position);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "Tempo para encontrar o caminho: " << elapsed.count() << " s" << std::endl;
    // print the path

    for (int i = 0; i < path.size(); i++) {
        std::cout << *path[i];
    }
    
}


void test3(){
    
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<AStarNode*>> talhao;
    int scale_x = 1;
    int scale_y = 1;

    int n_rows = 2000/scale_x;
    int n_nodes = 300/scale_y;

    int row_robot =0/scale_x, node_robot = 0/scale_y;
    int row_goal = 2000/scale_x - 1, node_goal = 300/scale_y - 1;

    // create 2000 rows of 200 nodes and add them to talhao
    for (int i = 0; i < n_rows; i++) {
        std::vector<AStarNode*> row;
        for (int j = 0; j < n_nodes; j++) {
            row.push_back(new AStarNode(i*0.45, j*3));
        }
        talhao.push_back(row);
    }


    for(int i = 0; i < n_rows; i ++){
        for(int j= 0; j < n_nodes; j++){
            if(j > 0){
                if(j == n_nodes-1){
                    talhao[i][j]->addNeighbor(talhao[i][j-1]);
                }
                else{
                    talhao[i][j]->addNeighbor(talhao[i][j-1]);
                }
            }
            if(j < n_nodes-1){
                if(j == 0){
                    talhao[i][j]->addNeighbor(talhao[i][j+1]);
                }
                else{
                    talhao[i][j]->addNeighbor(talhao[i][j+1]);
                }
            }
        }
        if(i < n_rows-1){
            talhao[i][0]->addNeighbor(talhao[i+1][0]);
            talhao[i][n_nodes-1]->addNeighbor(talhao[i+1][n_nodes-1]);
        }
        if(i > 0){
            talhao[i][0]->addNeighbor(talhao[i-1][0]);
            talhao[i][n_nodes-1]->addNeighbor(talhao[i-1][n_nodes-1]);
        }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Tempo para criar o talhao: " << elapsed.count() << "s" << std::endl;
    // create an AStarAlgorithm object
    AStarAlgorithm aStar;

    AStarNode * robot_position = talhao[row_robot][node_robot];
    AStarNode * goal_position = talhao[row_goal][node_goal];

    std::cout << "Encontrando um caminho entre os pontos "<< *robot_position << " e " << *goal_position << std::endl;

    // find a path from the top left to the bottom right
    start = std::chrono::high_resolution_clock::now();
    std::vector<AStarNode *> path = aStar.findPath(robot_position, goal_position);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "Tempo para encontrar o caminho: " << elapsed.count() << " s" << std::endl;
    // print the path

    for (int i = 0; i < path.size(); i++) {
        std::cout << *path[i];
    }
    
}







int main() {

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<AStarNode*>> talhao;
    int scale_x = 10;
    int scale_y = 2;

    int n_rows = 2000/scale_x;
    int n_nodes = 300/scale_y;

    int row_robot = 0/scale_x, node_robot = 0/scale_y;
    int row_goal = 2000/scale_x - 1, node_goal = 300/scale_y - 1;

    std::cout << "Tamanho do talhao: " << n_rows << " x " << n_nodes << std::endl;

    // create 2000 rows of 200 nodes and add them to talhao
    for (int i = 0; i < n_rows; i++) {
        std::vector<AStarNode*> row;
        for (int j = 0; j < n_nodes; j++) {
            // row.push_back(new AStarNode(i*0.45, j*3));
            row.push_back(new AStarNode(i, j));
        }
        talhao.push_back(row);
    }


    for(int i = 0; i < n_rows; i ++){
        for(int j= 0; j < n_nodes; j++){
            if(j > 0){
                if(j == n_nodes-1){
                    talhao[i][j]->addNeighbor(talhao[i][j-1]);
                    // talhao[i][j]->addNeighbor(talhao[i][j-1], 1000*abs(row_goal - i));
                }
                else{
                    talhao[i][j]->addNeighbor(talhao[i][j-1]);
                }
            }
            if(j < n_nodes-1){
                if(j == 0){
                    talhao[i][j]->addNeighbor(talhao[i][j+1]);
                    // talhao[i][j]->addNeighbor(talhao[i][j+1], 1000*abs(row_goal - i));
                }
                else{
                    talhao[i][j]->addNeighbor(talhao[i][j+1]);
                }
            }
        }
        if(i < n_rows-1){
            talhao[i][0]->addNeighbor(talhao[i+1][0]);
            talhao[i][n_nodes-1]->addNeighbor(talhao[i+1][n_nodes-1]);
        }
        if(i > 0){
            talhao[i][0]->addNeighbor(talhao[i-1][0]);
            talhao[i][n_nodes-1]->addNeighbor(talhao[i-1][n_nodes-1]);
        }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Tempo para criar o talhao: " << elapsed.count() << "s" << std::endl;
    // create an AStarAlgorithm object
    AStarAlgorithm aStar;

    AStarNode * robot_position = talhao[row_robot][node_robot];
    AStarNode * goal_position = talhao[row_goal][node_goal];

    std::cout << "Encontrando um caminho entre os pontos "<< *robot_position << " e " << *goal_position << std::endl;

    // find a path from the top left to the bottom right
    start = std::chrono::high_resolution_clock::now();
    std::vector<AStarNode *> path = aStar.findPath(robot_position, goal_position);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "Tempo para encontrar o caminho: " << elapsed.count() << " s" << std::endl;
    // print the path

    // for (int i = 0; i < path.size(); i++) {
    //     std::cout << *path[i];
    // }

    int nodeSize = 10;
    int nodeBorder = 2;

    AStarScreen gameScreen = AStarScreen(aStar, talhao, path, nodeSize, nodeBorder);

    int pixel_size = 1;
    int screen_width = n_rows*nodeSize;
    int screen_height = n_nodes*nodeSize;
	if (gameScreen.Construct(screen_width, screen_height, pixel_size, pixel_size))
		gameScreen.Start();

    
    return 0;
}