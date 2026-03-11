#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"
#include "Transform.h"

/**
 * Forward declarations
 */

class Component;

/**
 * @brief Base class for all actors in the game.
 */
class Actor
{
 public:
  
  Actor() = default;
  virtual ~Actor() = default;

  /**
   * @brief Adds a tag to the actor if. Case sensitive.
   * 
   * @param tag The tag to add.
   */
  void
  addTag(const String& tag);

  /**
   * @brief Removes a tag from the actor. Case sensitive.
   * 
   * @param tag The tag to remove.
   */
  void
  removeTag(const String& tag);

  /**
   * @brief Sets the draw order of the actor. Actors with lower draw orders are drawn first.
   * @param drawOrder The new draw order for the actor.
   */
  void
  setDrawOrder(const int32 drawOrder) const;

  /**
   * @brief Checks if the actor has a specific tag. Case sensitive.
   * 
   * @param tag The tag to check for.
   * @return true if the actor has the tag, false otherwise.
   */
  bool
  hasTag(const String& tag) const;

  /**
   * @brief Updates the actor and its components.
   * 
   * @param deltaTime The time elapsed since the last update, in seconds.
   */
  virtual
  void update(const float deltaTime);

  /**
   * @brief Sets the position of the actor.
   * 
   * @param x The x-coordinate of the new position.
   * @param y The y-coordinate of the new position.
   */
  void
  setPosition(const float x, const float y);

  /**
   * @brief Moves the actor by the specified amounts.
   * 
   * @param deltaX The amount to move the actor along the x-axis.
   * @param deltaY The amount to move the actor along the y-axis.
   */
  void
  move(const float deltaX, const float deltaY);

  /**
   * @brief Gets the transform of the actor.
   * 
   * @return A reference to the actor's transform.
   */
  Transform
  getTransform() const
  {
    return m_transform;
  }

  /**
   * @brief Called when the actor collides with another actor.
   * 
   * @param other The other actor involved in the collision.
   * @param intersection The intersection rectangle of the collision.
   */
  virtual void
  onCollision(const WPtr<Actor> other, const sf::FloatRect& intersection);

  inline bool
  isDirty() const
  {
    return m_isDirty;
  }

  /**
   * @brief Adds a component to the actor.
   * 
   * @tparam T The type of the component to add.
   * @param args The arguments to forward to the component's constructor.
   * @return A weak pointer to the added component.
   */
  template <typename T = Component, typename... Args>
  WPtr<T>
  addComponent(Args&&... args)
  {
    static_assert(IsBaseOf<Component, T>::value, "T must be a subclass of Component");
    SPtr<T> component = make_shared<T>(forward<Args>(args)...);
    m_components.push_back(component);
    component->setOwner(this);
    return component;
  }

  /**
   * @brief Gets a component of the specified type.
   * 
   * @tparam T The type of the component to get.
   * @return A weak pointer to the component, or an empty weak pointer if not found.
   */
  template <typename T = Component>
  WPtr<T>
  getComponent() const
  {
    static_assert(IsBaseOf<Component, T>::value, "T must be a subclass of Component");
    for (const auto& component : m_components) {
      SPtr<T> castedComponent = dynamic_pointer_cast<T>(component);
      if (castedComponent) {
        return castedComponent;
      }
    }
    return WPtr<T>();
  }

 protected:
  
  Transform m_transform;
  Vector<SPtr<Component>> m_components;
  Vector<String> m_tags;
  bool m_isDirty = false;
};
