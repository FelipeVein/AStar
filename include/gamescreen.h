#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <vector>
#include "astar.h"


class AStarScreen : public olc::PixelGameEngine
{
private:

    
	virtual bool OnUserCreate()
	{
        return true;
    }

    bool OnUserUpdate(float fElapsedTime);
    
public:

    std::vector<std::vector<AStarNode*>> nodes;
    AStarAlgorithm *algo;
	int nMapWidth = 16;
	int nMapHeight = 16;
    int nNodeSize = 9;
    int nNodeBorder = 2;

	AStarScreen(AStarAlgorithm *algo, std::vector<std::vector<AStarNode*>> nodes)
    {
        this->nodes = nodes;
        this->algo = algo;
		sAppName = "A* Algorithm";
    };

};