#ifndef DUNGEONGENERATOR_CPP
#define DUNGEONGENERATOR_CPP

#include "Dungeongenerator.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

/****************************************
            Public
*****************************************/

Dungeongenerator::Dungeongenerator(): Dungeon()
{

    EraseDungeon();

    Visited = "0";

    //ctor
}

Dungeongenerator::~Dungeongenerator()
{
    EraseDungeon();
    //dtor
}


void Dungeongenerator::SaveDungeon(const std::string &Filename)
{

    if(DDim.Height > 0)
    {
        std::ofstream File(Filename.c_str());

        if(File.is_open())
        {
            for(int i = 0; i <= DDim.Height; ++i)
            {
                File << DDungeon.at(i) << std::endl;
            }

            File.close();
        }
        else
        {
            std::string Err = "Can't create File: " + Filename;
            throw std::runtime_error(Err);
        } // if(File.is_open()
    }

} // SaveDungeon

void Dungeongenerator::GenerateDungeon(const Position &Start)
{
    CreateRawDungeon();
    GenDungeon(Start.PosX, Start.PosY);
    TrimDungeon();
} // GenerateDungeon

/****************************************
            Private
*****************************************/

void Dungeongenerator::CreateRawDungeon()
{
    EraseDungeon();

    if((DDim.Width > 0) && (DDim.Height > 0))
    {
        std::string Dungeonline;

        for(int i = 0; i <= DDim.Width; ++i)
        {
            Dungeonline = Dungeonline + Elements.Wall;
        }

        for(int i = 0; i <= DDim.Height; ++i)
        {
            DDungeon.push_back(Dungeonline);
        }

        for(int i = 1; i <= DDim.Height; ++i)
        {
            if((i % 2) != 0)
            {
                for(int a = 1; a <= DDim.Width; ++a)
                {
                    if((a % 2) != 0)
                    {
                        DDungeon.at(i).at(a) = Elements.Floor.at(0);
                    } // if((a%2)
                } // for(int a)
            } // if((i%2)
        } // for(int i)
    } // if((DDim.Width)
} // CreateRawDungeon

void Dungeongenerator::GenDungeon(const int X, const int Y)
{
    if(CheckRange(X, Y))
    {
        DDungeon.at(Y).at(X) = Visited.at(0);

        int Direction;
        int DirCount = 1;

        //Direction = rand() % 4 + 1;
        Direction = GetRandom(1, 4);

        int NextX;
        int NextY;

        while(DirCount <= 4)
        {
            NextX = X;
            NextY = Y;

            switch(Direction)
            {
                case 1: // North
                    {
                        NextY = NextY - 2;
                        if(IsFloor(NextX, NextY))
                        {
                            DDungeon.at(NextY + 1).at(NextX) = Elements.Floor.at(0);
                            GenDungeon(NextX, NextY);
                        }
                        break;
                    } // case 1

                case 2: // East
                    {
                        NextX = NextX + 2;
                        if(IsFloor(NextX, NextY))
                        {
                            DDungeon.at(NextY).at(NextX - 1) = Elements.Floor.at(0);
                            GenDungeon(NextX, NextY);
                        }
                        break;
                    } // case 2

                case 3: // South
                    {
                        NextY = NextY + 2;
                        if(IsFloor(NextX, NextY))
                        {
                            DDungeon.at(NextY - 1).at(NextX) = Elements.Floor.at(0);
                            GenDungeon(NextX, NextY);
                        }
                        break;
                    } // case 3

                case 4: // West
                    {
                        NextX = NextX - 2;
                        if(IsFloor(NextX, NextY))
                        {
                            DDungeon.at(NextY).at(NextX + 1) = Elements.Floor.at(0);
                            GenDungeon(NextX, NextY);
                        }
                        break;
                    } // case 4

            } // switch(Direction)

            ++Direction;
            ++DirCount;
            CheckDirection(Direction);

        } // While(DirCount)
    } // if(CheckRange)
} // GenDungeon

void Dungeongenerator::CheckDirection(int &Dir)
{
    if(Dir > 4)
    {
        Dir = 1;
    }
    else
    {
        if(Dir < 1)
        {
            Dir = 4;
        }
    }
} // CheckDirection

bool Dungeongenerator::IsFloor(const int X, const int Y)
{
    if(CheckRange(X, Y))
    {

        std::string Floor;
        Floor = GetElement(X,Y);

        if(Elements.Floor.compare(Floor) == 0)
        {
            return true;
        }
    }

    return false;
} // IsFloor

void Dungeongenerator::TrimDungeon()
{
    std::string Visit;

    for(int Y = 1; Y <= DDim.Height; ++Y)
    {
        for(int X = 1; X <= DDim.Width; ++X)
        {
            Visit = DDungeon.at(Y).at(X);
            if(Visited.compare(Visit) == 0)
            {
                DDungeon.at(Y).at(X) = Elements.Floor.at(0);
            } // if(Visited)
        } // for(X)
    } // for(Y)
} // TrimDungeon

#endif
