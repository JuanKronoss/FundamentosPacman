/**
 * Includes
 */

#include "FrameworkPrerequisites.h"

#include "Player.h"

typedef void (*ScriptFunction)(Actor* pActor);

struct DYNAMIC_LIBRARY_API ModInfo
{
  const char* targetActor{}; // The name of the target actor that this mod will be applied to, e.g., "Player"
  ScriptFunction scriptFunction{}; // The script function that defines the behavior of the mod, which will be executed by the ScriptComponent attached to the target actor
  bool executeOnlyOnce = true; // A flag indicating whether the mod's script function should be executed only once (true) or on every update (false)
};

extern "C" DYNAMIC_LIBRARY_API ModInfo loadMod()
{
  static ScriptFunction invincibilityModScript = [](Actor* pActor)
  {
    if (pActor) {
      auto pPlayer = dynamic_cast<Player*>(pActor); // Attempt to cast the actor to a Player type
      if (!pPlayer) {
        cout << "InvincibilityMod: Actor is not a Player, skipping invincibility.\n";
        return; // If the cast fails, the actor is not a player, so we skip applying the speed boost
      }
      pPlayer->setForeverInvincibility(true); // Set the player to be permanently invincible by calling the setForeverInvincibility function with true
    }
  };
  return ModInfo{ "Player", invincibilityModScript, true }; // Return the mod information, specifying that this mod targets the "Player" actor and uses the defined speed boost script
}
