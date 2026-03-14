#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"
#include "Scene.h"


class Level: public Scene
{
 public:

  Level(const String& _dataFile, uint32 windowWidth, uint32 windowHeight);
  ~Level() = default;

  void
  loadLevelFile(const String& _dataFile = "") override;

 private:

  uint32 m_windowWidth;
  uint32 m_windowHeight;

};
