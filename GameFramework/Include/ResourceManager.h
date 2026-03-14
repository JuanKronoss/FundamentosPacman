#pragma once

#include "FrameworkPrerequisites.h"
#include "Module.h"

#include <SFML/Graphics.hpp>

/**
 * @brief Manages game resources such as textures, ensuring that they are loaded and accessed efficiently throughout the game.
 */
class ResourceManager : public Module<ResourceManager>
{
 public:
 
  ResourceManager() = default;
  ~ResourceManager() = default;
 
  /**
   * @brief Loads a texture if not already loaded
   */
  void
  loadTexture(const String& key, const String& path);
 
  /**
   * @brief Gets a texture resource by name.
   * @param name The name of the texture resource to retrieve.
   * @return A reference to the requested texture resource.
   */
  const sf::Texture&
  getTexture(const String& name) const;
 
 private:
 
   UMap<String, sf::Texture> m_umTextures; // A map of texture resources, indexed by their names
};
