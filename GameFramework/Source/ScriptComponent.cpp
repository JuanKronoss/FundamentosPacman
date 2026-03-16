/**
 * Includes
 */

#include "ScriptComponent.h"

ScriptComponent::ScriptComponent(ScriptFunction _scriptFunction, const bool _executeOnlyOnce)
  : m_scriptFunction(_scriptFunction), m_executeOnlyOnce(_executeOnlyOnce)
{}

void
ScriptComponent::update(const float /*deltaTime*/)
{
  if (m_executeOnlyOnce && m_hasExecuted) {
    return; // If the script should only
  }
  if (m_scriptFunction && m_pOwner) {
    m_scriptFunction(m_pOwner); // Execute the script function, passing the owner actor as an argument
    m_hasExecuted = true; // Mark the script as executed to prevent it from running again if it should only execute once
  }
}