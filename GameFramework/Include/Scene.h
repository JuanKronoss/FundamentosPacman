#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"

/**
 * Forward declarations
 */

class Actor;

/**
 * @brief Represents a scene in the game, which contains actors and manages their lifecycle.
 */
class FRAMEWORK_EXPORT Scene
{
 public:

  Scene() = default;
  Scene(const String& _dataFile);
  ~Scene() = default;

  /**
   * @brief Loads the level data from a file, which may involve parsing the file and creating actors based on the data.
   * The file can contain information about the initial state of the scene, such as actor positions, types, and properties.
   * 
   * @param _dataFile The file path to the level data file. If not provided, it will use the default data path set in the constructor or previously loaded.
   */
  virtual void
  loadLevelFile(const String& _dataFile = "");

  /**
   * @brief Reloads the scene, which may involve reloading the level data, resetting actors to their initial states, and preparing the scene for a new game session.
   * This can be used to restart the current level or return to a known state after certain events, such as losing a life or restarting the game.
   */
  virtual void
  reload();

  /**
   * @brief Adds an actor to the scene.
   * 
   * @param actor A weak pointer to the actor to add to the scene.
   */
  void
  addActor(const WPtr<Actor>& actor);

  /**
   * @brief Removes an actor from the scene.
   * 
   * @param actor A weak pointer to the actor to remove from the scene.
   */
  void
  removeActor(const WPtr<Actor>& actor);

  /**
   * @brief Sets the visibility of all actors in the scene.
   * 
   * @param isVisible true to make all actors visible, false to make them invisible.
   */
  void
  setAllActorsVisibility(const bool isVisible);

  /**
   * @brief Gets the actors in the scene that are currently visible.
   * 
   * @return A vector of shared pointers to the actors in the scene that are currently visible.
   */
  Vector<SPtr<Actor>>
  getVisibleActors() const;

  /**
   * @brief Gets the actors in the scene sorted by their draw order.
   * 
   * @param onlyVisible If true, only returns actors that are currently visible. If false, returns all actors regardless of visibility.
   * @return A vector of shared pointers to the actors in the scene, sorted by their draw order.
   */
  Vector<SPtr<Actor>>
  getActorsInDrawingOrder(const bool onlyVisible = true) const;

  /**
   * @brief Gets the actors in the scene.
   */
  inline const Vector<SPtr<Actor>>&
  getActors() const
  {
    return m_pActors;
  }

  /**
   * @brief Gets an actor in the scene by its name.
   * 
   * @param name The name of the actor to find. Case sensitive.
   * @return A shared pointer to the actor with the specified name, or nullptr if no such actor exists in the scene.
   */
  SPtr<Actor>
  getActorByName(const String& name) const;

  /**
   * @brief Gets the actors in the scene that have a specific tag.
   * 
   * @param tag The tag to search for. Case sensitive.
   * @return A vector of shared pointers to the actors in the scene that have the specified tag. If no actors have the tag, returns an empty vector.
   */
  Vector<SPtr<Actor>>
  getActorsWithTag(const String& tag) const;

  /**
   * @brief Destroys all actors in the scene that are marked for destruction.
   * This should be called at the end of each frame to safely remove actors that have been marked for destruction during updates or collisions.
   */
  void
  destroyMarkedActors();

  /**
   * @brief Gets the file path to the scene data, which can be used for loading and saving the scene state.
   * @return The file path to the scene data.
   */
  inline const String&
  getDataPath() const
  {
    return m_dataPath;
  }

 private:

  String m_dataPath; // The file path to the scene data, which can be used for loading and saving the scene state
  Vector<SPtr<Actor>> m_pActors;
};
