/**
 * Includes
 */

#include "FrameworkPrerequisites.h"
#include "ModInfo.h"

#include "PlayerBase.h"

extern "C" DYNAMIC_LIB_EXPORT ModInfo loadMod()
{
  static ScriptFunction speedBoostScript = [](Actor* pActor)
  {
    if (pActor) {
      auto pPlayer = dynamic_cast<PlayerBase*>(pActor); // Attempt to cast the actor to a Player type
      if (!pPlayer) {
        cout << "SpeedBoostMod: Actor is not a PlayerBase, skipping speed boost.\n";
        return; // If the cast fails, the actor is not a player, so we skip applying the speed boost
      }
      pPlayer->setSpeed(pPlayer->getSpeed() * 10.0f); // Double the player's speed by multiplying the current speed by 2
    }
  };
  return ModInfo{ "Player", speedBoostScript, true }; // Return the mod information, specifying that this mod targets the "Player" actor and uses the defined speed boost script
}
