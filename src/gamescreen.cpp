#include "gamescreen.h"

bool AStarScreen::OnUserUpdate(float fElapsedTime)
{
    // Draw Map
    // First, we will draw connections between nodes
    for (int x = 0; x < nodes.size(); x++)
        for (int y = 0; y < nodes[x].size(); y++)
        {
            for (auto& n : nodes[x][y]->getNeighbors())
            {
                int x1 = x * nNodeSize + (nNodeSize - nNodeBorder) / 2;
                int y1 = y * nNodeSize + (nNodeSize - nNodeBorder) / 2;
                int x2 = n->x * nNodeSize + (nNodeSize - nNodeBorder) / 2;
                int y2 = n->y * nNodeSize + (nNodeSize - nNodeBorder) / 2;
                DrawLine(x1, y1, x2, y2, olc::Pixel(255, 255, 255));
            }
        }
    
    // Next, we will draw the nodes themselves
    for (int x = 0; x < nodes.size(); x++)
        for (int y = 0; y < nodes[x].size(); y++)
        {
            int x1 = x * nNodeSize + nNodeSize / 2;
            int y1 = y * nNodeSize + nNodeSize / 2;
            FillRect(x1 - nNodeSize / 2, y1 - nNodeSize / 2, nNodeSize - nNodeBorder, nNodeSize - nNodeBorder, olc::Pixel(255, 255, 255));
        }

    // Draw the beginning and end nodes of the path
    // The beginning node is green
    int x1 = path[0]->x * nNodeSize + nNodeSize / 2;
    int y1 = path[0]->y * nNodeSize + nNodeSize / 2;
    FillRect(x1 - nNodeSize / 2, y1 - nNodeSize / 2, nNodeSize - nNodeBorder, nNodeSize - nNodeBorder, olc::Pixel(0, 255, 0));
    
    // The end node is blue
    x1 = path[path.size() - 1]->x * nNodeSize + nNodeSize / 2;
    y1 = path[path.size() - 1]->y * nNodeSize + nNodeSize / 2;
    FillRect(x1 - nNodeSize / 2, y1 - nNodeSize / 2, nNodeSize - nNodeBorder, nNodeSize - nNodeBorder, olc::Pixel(0, 0, 255));

    // Draw Path from start to finish
    // the path is going to be a series of filled rectangles that are drawn on top of the nodes, except for the start and end nodes
    for (int i = 1; i < path.size() - 1; i++)
    {
        int x1 = path[i]->x * nNodeSize + nNodeSize / 2;
        int y1 = path[i]->y * nNodeSize + nNodeSize / 2;
        FillRect(x1 - nNodeSize / 2, y1 - nNodeSize / 2, nNodeSize - nNodeBorder, nNodeSize - nNodeBorder, olc::Pixel(255, 0, 0));
    }
    




    return true;
}
