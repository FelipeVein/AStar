#include "gamescreen.h"


bool AStarScreen::OnUserUpdate(float fElapsedTime)
{
    // Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

    // Draw Map
    // First, we will draw connections between nodes
    for (int x = 0; x < nMapWidth; x++)
        for (int y = 0; y < nMapHeight; y++)
        {
            for (auto& n : nodes[x][y]->getNeighbors())
            {
                int x1 = x * nNodeSize + nNodeSize / 2;
                int y1 = y * nNodeSize + nNodeSize / 2;
                int x2 = n->x * nNodeSize + nNodeSize / 2;
                int y2 = n->y * nNodeSize + nNodeSize / 2;
                DrawLine(x1, y1, x2, y2, olc::Pixel(255, 255, 255));
            }
        }
    return true;
};