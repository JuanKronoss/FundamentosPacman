#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"
#include "Module.h"

/**
 * Forward declarations
 */
class Scene;

/**
 * @brief Manages the different scenes in the game, allowing for scene creation, switching, and retrieval of the active scene.
 */
class SceneManager : public Module<SceneManager>
{
 public:

  SceneManager() = default;
  ~SceneManager() = default;

  /**
   * @brief Creates a new scene and adds it to the scene manager.
   */
  void
  createScene(const String& _dataFile);

  /**
   * @brief Adds an existing scene to the scene manager.
   * @param scene A shared pointer to the scene to add to the scene manager.
   * @param makeActive If true, the added scene will be set as the active scene. Defaults to true.
   */
  void
  addScene(const SPtr<Scene>& scene, const bool makeActive = true);

  /**
   * @brief Gets the currently active scene.
   * @return A shared pointer to the currently active scene.
   */
  inline SPtr<Scene>
  getActiveScene() const
  {
    return m_pActiveScene;
  }

  /**
   * @brief Sets the active scene to the specified scene.
   * @param scene A weak pointer to the scene to set as the active scene.
   * @param reload If true, the active scene will be reloaded after switching. This can be used to reset the scene state when switching to a new scene. Defaults to true.
   */
  void
  setActiveScene(const WPtr<Scene>& scene, const bool reload = true);

  /**
   * @brief Sets the active scene to the scene that corresponds to the specified data file.
   * @param _dataFile The file path to the scene data file. The scene manager will search for a scene that was created with this data file and set it as the active scene.
   * @param reload If true, the active scene will be reloaded after switching. This can be used to reset the scene state when switching to a new scene. Defaults to true.
   */
  void
  setActiveScene(const String& _dataFile, const bool reload = true);

 private:
 
  Vector<SPtr<Scene>> m_pScenes; // A vector of shared pointers to all scenes managed by the scene manager
  SPtr<Scene> m_pActiveScene; // A shared pointer to the currently active scene

};
