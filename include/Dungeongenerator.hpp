#ifndef DUNGEONGENERATOR_HPP
#define DUNGEONGENERATOR_HPP

#include <string>
#include <vector>
#include "Dungeon.hpp"

class Dungeongenerator: public Dungeon
{
    public:
        Dungeongenerator();
        ~Dungeongenerator();

/*
SaveDungeon:
Trys to save a Dungeon from Memory to Disk, throw a (Runtime-)Exception,
if unable to open the File.
*/
        void SaveDungeon(const std::string &Filename);

/*
GenerateDungeon:
Clears the Dungeon.
Creates a new Rawdungeon.
Generates the new Dungeon with Deepsearch.
Trims the Visited Tiles to Floortiles.
*/
        void GenerateDungeon(const Position &Start);                         // Creates from a raw Dungeon an visitable Dungeon

        void GenerateEntry(const int Number);

    private:

        void CreateRawDungeon();                                                // Creates a raw Dungeon for Generating
        void GenDungeon(const int X, const int Y);                              // Generates a Dungeon with Deepsearch
        void CheckDirection(int &Dir);
        bool IsFloor(const int X, const int Y);
        void TrimDungeon();                                                     // Converts all visited Tiles to Floortiles

        std::string Visited;

};

#endif // DUNGEONGENERATOR_H
