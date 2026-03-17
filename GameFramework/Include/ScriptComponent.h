#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"

#include "Component.h"

typedef void (*ScriptFunction)(Actor* pActor);

/**
 * @brief A component that allows attaching custom script behavior to an actor.
 * The script function is executed during the update phase of the component, allowing for dynamic behavior defined at runtime.
 */
class FRAMEWORK_EXPORT ScriptComponent: public Component
{
 public:

  ScriptComponent(ScriptFunction _scriptFunction, const bool _executeOnlyOnce);
  virtual ~ScriptComponent() = default;

  /**
   * @brief Updates the script component, executing any custom behavior defined in derived classes.
   * 
   * @param deltaTime The time elapsed since the last update, in seconds.
   */
  void
  update(const float deltaTime) override;

protected:

  ScriptFunction m_scriptFunction; // The script function to execute during the update
  bool m_executeOnlyOnce = false; // A flag to indicate whether the script function should only be executed once, which can be set based on the mod information when the ScriptComponent is created
  bool m_hasExecuted = false; // A flag to track whether the script function has been executed, which can be used for mods that should only execute once
};
