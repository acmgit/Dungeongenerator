#include <iostream>
#include "Dungeongenerator.hpp"

using namespace std;

int main()
{
    Dungeongenerator *MyDungeon = NULL;
    MyDungeon = new Dungeongenerator();

    if(!MyDungeon)
    {
        std::cout << "Problem to create Dungeongenerator ..." << std::endl;
        return -1;
    }

    // Sets the Dimension of the Maze.
    Dungeongenerator::Dimension MyDim;
    MyDim.Width = 40;
    MyDim.Height = 30;

    MyDungeon->SetDimension(MyDim);

    // Sets the Startposition of the Maze.
    Dungeongenerator::Position StartPosition;

    StartPosition.PosX = 5;
    StartPosition.PosY = 1;

    // Ok, now we can generate an Maze.
    MyDungeon->GenerateDungeon(StartPosition);

    #ifdef Debug
    MyDungeon->PrintDungeon();
    #endif // Debug

    try
    {
        MyDungeon->SaveDungeon("Dungeon.txt");
    }
    catch(std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        if(MyDungeon)
        {
            delete MyDungeon;
            MyDungeon = NULL;
            return -1;
        }
    }


    if(MyDungeon)
    {
        delete MyDungeon;
        MyDungeon = NULL;
    }

    return 0;
}
