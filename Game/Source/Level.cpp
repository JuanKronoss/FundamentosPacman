/**
 * Includes
 */

#include "Level.h"
#include "Game.h"
#include "Actor.h"
#include "SpriteRendererComponent.h"
#include "BoxColliderComponent.h"
#include "PlayerPacMan.h"
#include "Ghost.h"
#include "PacDot.h"
#include "ResourceManager.h"
#include "ScoreManager.h"
#include "HUD.h"

Level::Level(const String& _dataFile, uint32 windowWidth, uint32 windowHeight)
  : Scene(_dataFile), m_windowWidth(windowWidth), m_windowHeight(windowHeight)
{
  loadLevelFile(_dataFile);
}

void
Level::loadLevelFile(const String & _dataFile)
{
  Scene::loadLevelFile(_dataFile);

  ResourceManager& resourceMan = ResourceManager::instance();
  ScoreManager& scoreMan = ScoreManager::instance();
  HUD& hud = HUD::instance();

  float windowWidthF = static_cast<float>(m_windowWidth);
  float windowHeightF = static_cast<float>(m_windowHeight);

  IFStream levelFile(_dataFile);
  if (!levelFile.is_open()) {
    throw std::runtime_error("Failed to open level file: " + _dataFile);
  }

  // Read the level file line by line and create actors based on the characters in the file
  SPtr<PlayerPacMan> pPlayer;
  Vector<SPtr<Ghost>> vpGhosts;

  String line;
  uint32 rowIndex = 0;
  while (std::getline(levelFile, line)) {
    for (uint32 colIndex = 0; colIndex < line.length(); ++colIndex) {
      char element = line[colIndex];
      float xPos = colIndex * m_tileSize + m_halfTileSize; // Calculate the x position based on the column index and tile size, and add half the tile size to center the actor on the grid
      float yPos = m_iniYPos + rowIndex * m_tileSize + m_halfTileSize; // Calculate the y position based on the row index and tile size, and add half the tile size to center the actor on the grid
      switch (element) {
        case Elements::wall: {
          SPtr<Actor> pWall = make_shared<Actor>();
          pWall->addTag("Wall");
          pWall->setPosition(xPos, yPos);
          pWall->addComponent<SpriteRendererComponent>(resourceMan.getTexture("Wall"));
          pWall->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(m_tileSize - 2.0f, m_tileSize - 2.0f));
          pWall->getComponent<SpriteRendererComponent>().lock()->setDrawOrder(-2);
          addActor(pWall);
          break;
        }
        case Elements::pacDot: {
          SPtr<PacDot> pPacDot = make_shared<PacDot>();
          pPacDot->addTag("PacDot");
          pPacDot->setPosition(xPos, yPos);
          pPacDot->addComponent<SpriteRendererComponent>(resourceMan.getTexture("PacDot"));
          pPacDot->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(m_pacDotSize, m_pacDotSize));
          pPacDot->getComponent<SpriteRendererComponent>().lock()->setDrawOrder(-1);
          addActor(pPacDot);
          break;
        }
        case Elements::powerPellet: {
          SPtr<PacDot> pPowerPellet = make_shared<PacDot>(50);
          pPowerPellet->addTag("PacDot");
          pPowerPellet->addTag("PowerPellet");
          pPowerPellet->setPosition(xPos, yPos);
          pPowerPellet->addComponent<SpriteRendererComponent>(resourceMan.getTexture("PowerPellet"));
          pPowerPellet->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(m_powerPelletSize, m_powerPelletSize));
          pPowerPellet->getComponent<SpriteRendererComponent>().lock()->setDrawOrder(-1);
          addActor(pPowerPellet);
          break;
        }
        case Elements::player: {
          pPlayer = make_shared<PlayerPacMan>("Player", m_windowWidth, m_windowHeight);
          pPlayer->addTag("Player");
          pPlayer->setPosition(xPos, yPos);
          pPlayer->addComponent<SpriteRendererComponent>(resourceMan.getTexture("PacMan"));
          pPlayer->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(m_tileSize - 2.0f, m_tileSize - 2.0f));
          addActor(pPlayer);
          break;
        }
        case Elements::redGhost: {
          SPtr<Ghost> pRedGhost = make_shared<Ghost>(GhostType::Red);
          pRedGhost->addTag("Enemy");
          pRedGhost->addComponent<SpriteRendererComponent>(resourceMan.getTexture("Ghosts"));
          pRedGhost->setProperSprite();
          pRedGhost->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(m_tileSize, m_tileSize));
          pRedGhost->setPosition(xPos, yPos);
          addActor(pRedGhost);
          vpGhosts.push_back(pRedGhost);
          break;
        }
        case Elements::pinkGhost: {
          SPtr<Ghost> pPinkGhost = make_shared<Ghost>(GhostType::Pink);
          pPinkGhost->addTag("Enemy");
          pPinkGhost->addComponent<SpriteRendererComponent>(resourceMan.getTexture("Ghosts"));
          pPinkGhost->setProperSprite();
          pPinkGhost->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(m_tileSize, m_tileSize));
          pPinkGhost->setPosition(xPos, yPos);
          addActor(pPinkGhost);
          vpGhosts.push_back(pPinkGhost);
          break;
        }
        case Elements::cyanGhost: {
          SPtr<Ghost> pBlueGhost = make_shared<Ghost>(GhostType::Blue);
          pBlueGhost->addTag("Enemy");
          pBlueGhost->addComponent<SpriteRendererComponent>(resourceMan.getTexture("Ghosts"));
          pBlueGhost->setProperSprite();
          pBlueGhost->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(m_tileSize, m_tileSize));
          pBlueGhost->setPosition(xPos, yPos);
          addActor(pBlueGhost);
          vpGhosts.push_back(pBlueGhost);
          break;
        }
        case Elements::orangeGhost: {
          SPtr<Ghost> pOrangeGhost = make_shared<Ghost>(GhostType::Orange);
          pOrangeGhost->addTag("Enemy");
          pOrangeGhost->addComponent<SpriteRendererComponent>(resourceMan.getTexture("Ghosts"));
          pOrangeGhost->setProperSprite();
          pOrangeGhost->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(m_tileSize, m_tileSize));
          pOrangeGhost->setPosition(xPos, yPos);
          addActor(pOrangeGhost);
          vpGhosts.push_back(pOrangeGhost);
          break;
        }
      } // End of switch statement for level file elements
    } // End of loop through characters in the line
    ++rowIndex;
  } // End of loop through lines in the level file

  pPlayer->onScoreChange.subscribe(
    [&](uint64 scoreValue)
    {
      scoreMan.addPoints(scoreValue); // Update the score in the Score Manager when the player scores points
      hud.updateScore(scoreMan.getCurrentScore(), scoreMan.getHighScore()); // Notify the HUD to update the displayed score and high score
    });
  hud.updateScore(scoreMan.getCurrentScore(), scoreMan.getHighScore()); // Update the HUD with the initial score and high score when the level is loaded

  pPlayer->onInvincibilityChanged.subscribe(
    [=](bool isInvincible)
    {
      // Toggle the vulnerability of the ghosts when the player's invincibility state changes
      for (auto& pGhost : vpGhosts) {
        pGhost->toggleVulnerability(isInvincible);
      }
    });

  pPlayer->onForeverInvincibilitySet.subscribe(
    [=](bool isForeverInvincible)
    {
      // Set the ghosts to be permanently vulnerable if the player is set to be permanently invincible, and vice versa
      for (auto& pGhost : vpGhosts) {
        pGhost->setIsForeverVulnerable(isForeverInvincible);
      }
    });



}
