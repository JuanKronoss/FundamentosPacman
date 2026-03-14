/**
 * Includes
 */

#include "SceneManager.h"
#include "Scene.h"

void
SceneManager::createScene(const String& _dataFile)
{
  SPtr<Scene> pScene = make_shared<Scene>(_dataFile);
  m_pScenes.push_back(pScene);
  if (!m_pActiveScene) {
    m_pActiveScene = pScene; // Set the first created scene as the active scene by default
  }
}

void
SceneManager::addScene(const SPtr<Scene>& scene, const bool makeActive)
{
  m_pScenes.push_back(scene);
  if (!m_pActiveScene || makeActive) {
    m_pActiveScene = scene; // Set the first added scene as the active scene by default
  }
}

void
SceneManager::setActiveScene(const WPtr<Scene>& scene, const bool reload)
{
  if (scene.expired()) {
    throw std::invalid_argument("Cannot set active scene: the provided scene pointer is expired.");
  }
  SPtr<Scene> spScene = scene.lock();
  auto it = std::find(m_pScenes.begin(), m_pScenes.end(), spScene);
  if (it == m_pScenes.end()) {
    throw std::invalid_argument("Cannot set active scene: the provided scene is not managed by this SceneManager.");
  }
  m_pActiveScene = spScene;
  if (reload) {
    m_pActiveScene->reload(); // Reload the active scene to reset its state when switching to it
  }
}

void
SceneManager::setActiveScene(const String& _dataFile, const bool reload)
{
  auto it = std::find_if(m_pScenes.begin(), m_pScenes.end(),
                         [&_dataFile](const SPtr<Scene>& scene) {
                           return scene->getDataPath() == _dataFile;
                         });
  if (it == m_pScenes.end()) {
    throw std::invalid_argument("Cannot set active scene: no scene with the specified data file was found.");
  }
  m_pActiveScene = *it;
  if (reload) {
    m_pActiveScene->reload(); // Reload the active scene to reset its state when switching to it
  }
}
