#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"

class ScoreManager
{
 public:

  ScoreManager() = default;
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
  inline uint32
  getCurrentScore() const
  {
    return m_currentScore;
  }

  /**
   * @brief Gets the high score.
   * @return The high score.
   */
  inline uint32
  getHighScore() const
  {
    return m_highScore;
  }

  /**
   * @brief Adds points to the current score and updates the high score if necessary.
   * @param points The number of points to add to the current score.
   */
  void
  addPoints(uint32 points);

  /**
   * @brief Checks if the current score has surpassed the high score during the current game session.
   * @return true if the current score has surpassed the high score, false otherwise.
   */
  inline bool
  hasGotHighScore() const
  {
    return m_gotHighScore;
  }

 private:

  uint32 m_currentScore = 0; // The current score of the player
  uint32 m_highScore = 0; // The highest score achieved by the player
  bool m_gotHighScore = false; // Flag to indicate if the current score has surpassed the high score during the current game session

};
