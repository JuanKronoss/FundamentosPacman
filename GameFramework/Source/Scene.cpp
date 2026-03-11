/**
 * Includes
 */

#include "Scene.h"
#include "Actor.h"
#include "SpriteRendererComponent.h"

void Scene::addActor(const WPtr<Actor>& actor)
{
  if (actor.expired()) {
    return; // Do not add expired actors
  }
  m_pActors.push_back(actor.lock());
}

void Scene::removeActor(const WPtr<Actor>& actor)
{
  if (actor.expired()) {
    return; // Do not attempt to remove expired actors
  }
  auto it = find(m_pActors.begin(), m_pActors.end(), actor.lock());
  if (it != m_pActors.end()) {
    m_pActors.erase(it);
  }
}

Vector<SPtr<Actor>>&
Scene::getActorsInDrawingOrder() const
{
  Vector<SPtr<Actor>> sortedActors = m_pActors;
  // Sort the actors by their draw order before returning them
  sort(sortedActors.begin(), sortedActors.end(),
       [](const SPtr<Actor>& a, const SPtr<Actor>& b) {
         WPtr<SpriteRendererComponent> spriteRendererA = a->getComponent<SpriteRendererComponent>();
         WPtr<SpriteRendererComponent> spriteRendererB = b->getComponent<SpriteRendererComponent>();
         int32 drawOrderA = spriteRendererA.expired() ? 0 : spriteRendererA.lock()->getDrawOrder();
         int32 drawOrderB = spriteRendererB.expired() ? 0 : spriteRendererB.lock()->getDrawOrder();
         return drawOrderA < drawOrderB;
       });
  return sortedActors;
}