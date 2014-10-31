#ifndef DUNGEON_CPP
#define DUNGEON_CPP

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <time.h>

#include "Dungeon.hpp"

/****************************************
            Public
*****************************************/

Dungeon::Dungeon()
{
    time_t t;
    time(&t);
    std::srand(t);

    Elements.Wall = "#";
    Elements.Floor = " ";
    //ctor
}

Dungeon::~Dungeon()
{

}

void Dungeon::SetDimension(const Dimension &Dim)
{
    DDim.Width = Dim.Width;
    DDim.Height = Dim.Height;
} // SetDimension

void Dungeon::SetElement(const Element &Ele)
{
    Elements.Floor = Ele.Floor;
    Elements.Wall = Ele.Wall;
} // SetElement

bool Dungeon::CheckRange(const int X, const int Y)
{
    if(
       (X > 0) && (X <= DDim.Width - 1) &&
       (Y > 0) && (Y <= DDim.Height - 1)
      )
    {
        return true;
    }

    return false;
} // CheckRange

void Dungeon::LoadDungeon(const std::string &Filename)
{
    Erase(DDungeon);
    ClearDimension();
    DDim = Load(Filename);

} // LoadDungeon

void Dungeon::LoadLevel(const std::string &Filename)
{
    Load(Filename);
} // LoadLevel

void Dungeon::ClearDimension()
{
    DDim.Width = 0;
    DDim.Height = 0;
} // ClearDimension

void Dungeon::EraseDungeon()
{
    Erase(DDungeon);
} // EraseDungeon

void Dungeon::EraseLevel()
{
    Entry.clear();
    Exit.clear();
    Room.clear();
    TreasureRoom.clear();
    UpStair.clear();
    DownStair.clear();
}
std::string Dungeon::GetElement(const int X, const int Y)
{
    std::string MyElement = "";

    if(CheckRange(X,Y))
    {
        MyElement = DDungeon.at(Y).at(X);
    }

    return MyElement;
} // GetElement

int Dungeon::GetRandom(const int MinValue, const int MaxValue)
{
    return rand() % MaxValue + MinValue;
} // GetRandom

#ifdef Debug

void Dungeon::PrintDungeon()
{
    Print(DDungeon);
} // PrintDungeon

#endif // Debug

/****************************************
            Protected
*****************************************/

Dungeon::Dimension Dungeon::Load(const std::string &Filename)
{
    std::ifstream File(Filename.c_str());
    Dimension Dim;

    if(File.is_open())
    {
        std::string Dungeonline;

        Dim.Height = 0;

        while(File.good())
        {
            std::getline(File, Dungeonline);

            if(Dungeonline.length()>0)
            {
                ++Dim.Height;
                DDungeon.push_back(Dungeonline);
            }
        }

        --Dim.Height;
        File.close();

        Dim.Width = DDungeon.at(0).length()-1;
    }
    else
    {
        std::string Err = "Can't open File: " + Filename;
        throw std::runtime_error(Err);
    } // if(File.is_open()

    return Dim;
} // Load

void Dungeon::Erase(std::vector<std::string> &Typ)
{
    Typ.clear();
} // Erase

#ifdef Debug

void Dungeon::Print(std::vector<std::string> &Typ)
{
    std::cout << std::endl << "Width = " << DDim.Width << std::endl;
    std::cout << "Height = " << DDim.Height << std::endl << std::endl;
    for(int i = 0; i <= DDim.Height; ++i)
    {
        std::cout << Typ.at(i) << std::endl;
    }
} // Print

#endif // Debug

#endif
