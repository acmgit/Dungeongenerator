#ifndef DUNGEON_HPP
#define DUNGEON_HPP

#include <string>
#include <vector>

class Dungeon
{
    public:
        struct Dimension
        {
            int Width;
            int Height;
        };

        struct Position
        {
            int PosX;
            int PosY;
        };

        struct Element
        {
            std::string Wall;
            std::string Floor;
        };

        Dungeon();
        virtual ~Dungeon();

        void SetDimension(const Dimension &Dim);                                // Set's the Dimension of an Dungeon
        void SetElement(const Element &Ele);                                    // Set's the Tilesets of an Dungeon


        bool CheckRange(const int X, const int Y);                              // Is the Value int the Area of the Dungeon?

/****************************************************************************
LoadDungeon(Filename):

Opens the File - throw an (Runtime-)Exception, if unable to open the file
Clear the Dimension
Erase the Dungeon
Load the named File
Set's the Dimension new
*****************************************************************************/
        void LoadDungeon(const std::string &Filename);

/****************************************************************************
LoadLevel(Filename):

Opens the File - throw an (Runtime-)Exception, if unable to open the file
Erase the Dungeon
Load the named File
*****************************************************************************/
        void LoadLevel(const std::string &Filename);

        void ClearDimension();                                                  // Set's the Dimension of an Dungeon to 0
        void EraseDungeon();                                                    // Deletes a Dungeon
        void EraseLevel();                                                      // Deletes a Levelmap

        std::string GetElement(const int X, const int Y);                       // Get's the Tile at X and Y from the Dungeon
        int GetRandom(const int MinValue, const int MaxValue);                  // Get's a Randomvalue between MinValue and MaxValue

#ifdef Debug
        void PrintDungeon();                                                    // Print's the Dungeon on the Console
        //void PrintLevel();
#endif // Debug

    protected:

        Dimension Load(const std::string &Filename);
        void Erase(std::vector<std::string> &Typ);

        std::vector<std::string> DDungeon;

        std::vector<Position> Entry;
        std::vector<Position> Exit;
        std::vector<Position> Room;
        std::vector<Position> TreasureRoom;
        std::vector<Position> UpStair;
        std::vector<Position> DownStair;

        Dimension DDim;
        Element Elements;

        int Level;
        std::string Levelname;

#ifdef Debug
        void Print(std::vector<std::string> &Typ);
#endif // Debug

};

#endif // DUNGEON_H
