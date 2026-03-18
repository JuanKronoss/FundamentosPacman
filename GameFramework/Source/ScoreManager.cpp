/**
 * Includes
 */

#include "ScoreManager.h"

ScoreManager::ScoreManager(const String& path)
{
  loadHighScoreFile(path); // Load the high score from the specified file path when the ScoreManager is initialized
}

void
ScoreManager::loadHighScoreFile(const String& path)
{
  // Check if the file has the correct extension
  if (path.substr(path.find_last_of('.')) != ".score") {
    throw std::invalid_argument("Invalid file extension for high score file: " + path + ". Expected .score");
  }
  // Read the binary file and set the high score
  
  IFStream file(path, std::ios::binary | std::ios::in);
  if (!file) {
    return; // If the file doesn't exist, we can just return and keep the default high score of 0
  }
  file.read(reinterpret_cast<char*>(&m_highScore), sizeof(m_highScore));

}

void
ScoreManager::saveHighScoreFile(const String& path) const
{
  // Check if the file has the correct extension
  if (path.substr(path.find_last_of('.')) != ".score") {
    throw std::invalid_argument("Invalid file extension for high score file: " + path + ". Expected .score");
  }
  // Write the high score to a binary file
  OFStream file(path, std::ios::binary | std::ios::out);
  if (!file) {
    throw std::runtime_error("Failed to open high score file for writing: " + path);
  }
  file.write(reinterpret_cast<const char*>(&m_highScore), sizeof(m_highScore));
}

void
ScoreManager::addPoints(uint64 points)
{
  m_currentScore += points;
  if (m_currentScore > m_highScore) {
    m_currentScore = std::min(m_currentScore, m_maxScore); // Ensure the current score does not exceed the maximum score limit
    m_highScore = m_currentScore; // Update the high score if the current score exceeds it
    m_gotHighScore = true; // Set the flag to indicate that the current score has surpassed the high score during this game session
  }
}
