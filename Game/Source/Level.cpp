/**
 * Includes
 */

#include "Level.h"
#include "Game.h"
#include "Actor.h"
#include "SpriteRendererComponent.h"
#include "BoxColliderComponent.h"
#include "Player.h"
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

  SPtr<Player> pPlayer = make_shared<Player>("Player", m_windowWidth, m_windowHeight);
  pPlayer->addTag("Player");
  pPlayer->setPosition(windowWidthF * 0.5f, windowHeightF * 0.5f);
  pPlayer->addComponent<SpriteRendererComponent>(resourceMan.getTexture("PacMan"));
  pPlayer->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(60.0f, 60.0f));

  addActor(pPlayer);

  SPtr<Ghost> pRedGhost = make_shared<Ghost>(GhostType::Red);
  pRedGhost->addTag("Enemy");
  pRedGhost->addComponent<SpriteRendererComponent>(resourceMan.getTexture("Ghosts"));
  pRedGhost->setProperSprite();
  pRedGhost->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(60.0f, 60.0f));
  pRedGhost->setPosition(windowWidthF * 0.5f, windowHeightF * 0.25f);

  addActor(pRedGhost);

  SPtr<Ghost> pOrangeGhost = make_shared<Ghost>(GhostType::Orange);
  pOrangeGhost->addTag("Enemy");
  pOrangeGhost->addComponent<SpriteRendererComponent>(resourceMan.getTexture("Ghosts"));
  pOrangeGhost->setProperSprite();
  pOrangeGhost->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(60.0f, 60.0f));
  pOrangeGhost->setPosition(windowWidthF * 0.25f, windowHeightF * 0.25f);

  addActor(pOrangeGhost);


  SPtr<PacDot> pPacDot = make_shared<PacDot>();
  pPacDot->addTag("PacDot");
  pPacDot->setPosition(windowWidthF * 0.5f, windowHeightF * 0.75f);
  pPacDot->addComponent<SpriteRendererComponent>(resourceMan.getTexture("PacDot"));
  pPacDot->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(15.0f, 15.0f));
  pPacDot->getComponent<SpriteRendererComponent>().lock()->setDrawOrder(-1);

  addActor(pPacDot);


  SPtr<PacDot> pPowerPellet = make_shared<PacDot>(50);
  pPowerPellet->addTag("PacDot");
  pPowerPellet->addTag("PowerPellet");
  pPowerPellet->setPosition(windowWidthF * 0.75f, windowHeightF * 0.75f);
  pPowerPellet->addComponent<SpriteRendererComponent>(resourceMan.getTexture("PowerPellet"));
  pPowerPellet->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(33.0f, 33.0f));
  pPowerPellet->getComponent<SpriteRendererComponent>().lock()->setDrawOrder(-1);

  addActor(pPowerPellet);

  SPtr<Actor> pWall1 = make_shared<Actor>();
  pWall1->addTag("Wall");
  pWall1->setPosition(windowWidthF * 0.25f, windowHeightF * 0.5f);
  pWall1->addComponent<SpriteRendererComponent>(resourceMan.getTexture("Wall"));
  pWall1->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(32.0f, 32.0f));

  addActor(pWall1);

  scoreMan.loadHighScoreFile();
  hud.updateScore(scoreMan.getCurrentScore(), scoreMan.getHighScore()); // Initialize the HUD with the current score and high score

  pPlayer->onScoreChange.subscribe(
    [&](uint64 scoreValue)
    {
      scoreMan.addPoints(scoreValue); // Update the score in the Score Manager when the player scores points
      hud.updateScore(scoreMan.getCurrentScore(), scoreMan.getHighScore()); // Notify the HUD to update the displayed score and high score
    });

  pPlayer->onInvincibilityChanged.subscribe(
    [=](bool isInvincible)
    {
      // Toggle the vulnerability of the ghosts when the player's invincibility state changes
      pRedGhost->toggleVulnerability(isInvincible);
      pOrangeGhost->toggleVulnerability(isInvincible);
    });

}

