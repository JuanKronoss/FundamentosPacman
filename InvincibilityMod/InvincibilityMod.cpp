/**
 * Includes
 */

#include "FrameworkPrerequisites.h"
#include "ModInfo.h"

#include "PlayerBase.h"

extern "C" DYNAMIC_LIB_EXPORT ModInfo loadMod()
{
  static ScriptFunction invincibilityModScript = [](Actor* pActor)
  {
    if (pActor) {
      auto pPlayer = dynamic_cast<PlayerBase*>(pActor); // Attempt to cast the actor to a Player type
      if (!pPlayer) {
        cout << "InvincibilityMod: Actor is not a PlayerBase, skipping invincibility.\n";
        return; // If the cast fails, the actor is not a player, so we skip applying the speed boost
      }
      pPlayer->setForeverInvincibility(true); // Set the player to be permanently invincible by calling the setForeverInvincibility function with true
    }
  };
  return ModInfo{ "Player", invincibilityModScript, true }; // Return the mod information, specifying that this mod targets the "Player" actor and uses the defined speed boost script
}
