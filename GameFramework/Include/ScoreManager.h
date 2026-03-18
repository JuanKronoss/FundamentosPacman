#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"
#include "Module.h"

/**
 * @brief Manages the player's score and high score, including loading and saving the high score to a file,
 * updating the current score, and providing access to the current score and high score for display in the HUD.
 */
class ScoreManager : public Module<ScoreManager>
{
 public:

  ScoreManager(const String& path = SCORE_FILE_PATH + "HighScore.score");
  ~ScoreManager() = default;

  /**
   * @brief Loads the high score from a file. If the file does not exist, it initializes the high score to 0.
   * @param path The path to the high score file. Defaults to SCORE_FILE_PATH + "HighScore.score".
   */
  void
  loadHighScoreFile(const String& path = SCORE_FILE_PATH + "HighScore.score");

  /**
   * @brief Saves the current high score to a file.
   * @param path The path to the high score file. Defaults to SCORE_FILE_PATH + "HighScore.score".
   */
  void
  saveHighScoreFile(const String& path = SCORE_FILE_PATH + "HighScore.score") const;

  /**
   * @brief Gets the current score.
   * @return The current score.
   */
  inline uint64
  getCurrentScore() const
  {
    return m_currentScore;
  }

  /**
   * @brief Gets the high score.
   * @return The high score.
   */
  inline uint64
  getHighScore() const
  {
    return m_highScore;
  }

  /**
   * @brief Adds points to the current score and updates the high score if necessary.
   * @param points The number of points to add to the current score.
   */
  void
  addPoints(uint64 points);

  /**
   * @brief Checks if the current score has surpassed the high score during the current game session.
   * @return true if the current score has surpassed the high score, false otherwise.
   */
  inline bool
  hasGotHighScore() const
  {
    return m_gotHighScore;
  }

  /**
   * @brief Resets the current score to 0 and resets the flag for surpassing the high score for a new game session.
   */
  inline void
  resetCurrentScore()
  {
    m_currentScore = 0; // Reset the current score to 0 for a new game session
    m_gotHighScore = false; // Reset the flag for surpassing high score for the new game session
  }

  /**
   * @brief Gets the maximum score that can be displayed in the HUD.
   * @return The maximum score that can be displayed in the HUD.
   */
  uint64
  getMaxScore() const
  {
    return m_maxScore;
  }

 private:

  uint64 m_currentScore = 0; // The current score of the player
  uint64 m_highScore = 0; // The highest score achieved by the player
  uint64 m_maxScore = 9999999999999999999; // Maximum score that can be displayed in the HUD, set to a very large number to prevent overflow
  bool m_gotHighScore = false; // Flag to indicate if the current score has surpassed the high score during the current game session
};
