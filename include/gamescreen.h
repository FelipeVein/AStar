#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "olcPixelGameEngine.h"
#include <vector>
#include "astar.h"


class AStarScreen : public olc::PixelGameEngine
{

public:

    std::vector<std::vector<AStarNode*>> nodes;
    AStarAlgorithm algo;
    int nNodeSize;
    int nNodeBorder;
    std::vector<AStarNode*> path;

	AStarScreen(AStarAlgorithm algo, std::vector<std::vector<AStarNode*>> nodes, std::vector<AStarNode*> path, int nNodeSize, int nNodeBorder)
    {
        this->nodes = nodes;
        this->algo = algo;
        this->path = path;
        this->nNodeSize = nNodeSize;
        this->nNodeBorder = nNodeBorder;
		sAppName = "A* Algorithm";
    };

private:

    
	virtual bool OnUserCreate(){ return true;};

    bool OnUserUpdate(float fElapsedTime);
};

#endif