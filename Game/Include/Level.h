#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"
#include "Scene.h"

/**
 * Forward declarations
 */
class Actor;

/**
 * @brief Represents a level in the game, which is a specific type of scene that contains the layout and actors for a particular stage of the game.
 * The Level class is responsible for loading the level data from a file, creating actors based on the level layout, and managing the level's state during gameplay.
 */
class Level: public Scene
{
 public:

   struct Elements
   {
     static const char wall = '#';
     static const char pacDot = '.';
     static const char powerPellet = 'o';
     static const char emptySpace = 'e';
     static const char player = 'P';
     static const char redGhost = 'R';
     static const char pinkGhost = 'I';
     static const char cyanGhost = 'C';
     static const char orangeGhost = 'O';

  };

  Level(const String& _dataFile, uint32 windowWidth, uint32 windowHeight);
  ~Level() = default;

  void
  loadLevelFile(const String& _dataFile = "") override;

 private:

  //void
  //processWalls(IFStream& levelFile, const String& line, uint32 rowIndex, Vector<SPtr<Actor>> _vpActors);

  uint32 m_windowWidth;
  uint32 m_windowHeight;
  float m_iniYPos = 68.0f; // Initial Y position for the top row of the level, adjusted to account for the HUD height and centering on the tile grid
  float m_tileSize = 38.0f; // Assuming each tile in the level corresponds to a 32x32 pixel area
  float m_halfTileSize = m_tileSize * 0.5f; // Calculate half the tile size for centering actors on the grid
  float m_pacDotSize = 8.0f;
  float m_powerPelletSize = 22.0f;
};
