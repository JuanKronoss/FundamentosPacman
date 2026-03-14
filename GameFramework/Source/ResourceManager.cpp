/**
 * Includes
 */

#include "ResourceManager.h"

void
ResourceManager::loadTexture(const String& key, const String& path)
{
  if (m_umTextures.find(path) != m_umTextures.end()) {
    return; // If the texture is already loaded, we can just return
  }
  sf::Texture texture;
  if (!texture.loadFromFile(path)) {
    throw std::runtime_error("Failed to load texture from file: " + path);
  }
  m_umTextures[key] = texture; // Store the loaded texture in the map
}

const
sf::Texture&
ResourceManager::getTexture(const String& name) const
{
  auto it = m_umTextures.find(name);
  if (it == m_umTextures.end()) {
    throw std::runtime_error("Texture not found: " + name);
  }
  return it->second; // Return a reference to the requested texture
}
