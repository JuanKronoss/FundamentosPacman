#pragma once

/**
 * Includes
 */

#include "Actor.h"
#include "ScriptComponent.h"

struct ModInfo
{
  const char* targetActor{}; // The name of the target actor that this mod will be applied to, e.g., "Player"
  ScriptFunction scriptFunction{}; // The script function that defines the behavior of the mod, which will be executed by the ScriptComponent attached to the target actor
  bool executeOnlyOnce = true; // A flag indicating whether the mod's script function should be executed only once (true) or on every update (false)
};