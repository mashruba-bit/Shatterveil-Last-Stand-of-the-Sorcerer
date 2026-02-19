#include "constant.h"
#include "globals.h"
#include "iGraphics.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <mmsystem.h>
#include <windows.h>

#pragma comment(lib, "winmm.lib")

/* -------------------- GLOBAL VARIABLE DEFINITIONS -------------------- */
int bg1, bg2, bg41;
int bg5, bg6, bg7;   //--------------------------------my codes-------------------------------------------------------------
int currentBg = 1;

int btnNormal[NUM_BUTTONS];
int btnHover[NUM_BUTTONS];
bool btnIsHover[NUM_BUTTONS] = {false};

int backBtn, backBtnHover;
bool backHover = true;

int backSize = 60;
int backMargin = 20;
int backX = backMargin;
int backY = SCREEN_HEIGHT - backSize - backMargin;
int backW = backSize;
int backH = backSize;

int btnX = 30;
int btnW = 320;
int btnH = 100;
int btnStartY = 445;
int btnGap = 25;   //-----------------------------------------------------------------------------

int signpostImg;
int winFlagImg;
int winnerImg;
int hudLifeImg, hudPunchImg;
int tokenImg, treasureImg, tokenCount = 0, treasureCount = 0;
bool playerWon = false;
// Story sequence - ADD THESE THREE LINES
int storyImgs[7];
int storyIndex = 0;
bool inStorySequence = false;
Bridge bridges[] = {{290, 600, 160, 175, 165},   {890, 1090, 160, 180, 160},
                    {1085, 1212, 185, 195, 185}, {1200, 1250, 290, 300, 290},
                    {1170, 1290, 380, 390, 380}, {1320, 1650, 240, 250, 240},
                    {1684, 1770, 290, 300, 295}, {1684, 1790, 400, 420, 405},
                    {1760, 1900, 190, 200, 190}, {2290, 2400, 190, 200, 190}};
int numBridges = sizeof(bridges) / sizeof(bridges[0]);
Collectible collectibles[15];
int numCollectibles = 15;
bool swapEnemySprites = false;

int playerSide, playerSideLeft;
int playerSideM, playerSideLeftM;
int punchFistImg, punchHitImg;
int punchFistImgM, punchHitImgM;

int chargedPunchImg, chargedFistImg, chargedPunchImgSeq;
int chargedPunchImgM, chargedFistImgM, chargedPunchImgSeqM;
int chargeScrollImg;

int playerX = PLAYER_START_X_BG41;
int playerY = PLAYER_START_Y_BG41;

bool movingFront = true;
int animFrame = 0;
int punchState = 0;
int chargedHitWindow = 0;

bool punchJustLanded = false;

bool isJumping = false;
float jumpVelocity = 0;

bool gameStarted = true;
int punchVolume =
    700; // Range: 0 (silent) to 1000 (full). Adjust this to balance with music.
bool chargingPunch = false;
bool showChargeScroll = false;
bool chargeScrollShown = false;
bool chargeScrollDismissed = false;
bool chargedSequenceActive = false;
int chargedPunchState = 0;
int chargedUseCount = 0;
int chargedTimeCounter = 0;
bool chargedTimerRunning = false;

bool playerAlive = true;
int playerDeadImg;
int playerDeathY = 0;

bool killedByEnemy1 = false;    //----------------------------------------my codes---------------------------------------------------
bool killedByDragon = false;
bool killedByEnemy3 = false;
bool killedByEnemy4 = false;
bool killedByEnemy2 = false;

int playerLives = MAX_LIVES;
bool gameOverTriggered = false;
bool gameOverScreen = false;
int gameOverImg;
int gameOverDelayCounter = 0;
int deathDelayCounter = 0;
bool deathWaiting = false;

int cameraX = 0;

int enemy1Img;             //----------------------------------------my codes---------------------------------------------------
float enemy1FloatOffset = 0.0f;
float enemy1FloatSpeed = 0.08f;
float enemy1FloatRange = 6.0f;
bool enemy1Alive = true;
int enemy1HitCount = 0;
int enemy1DeadImg;
float enemy1DeadY = 0;
bool enemy1Falling = false;
float enemy1DeadVelocity = 0;

int enemy2LeftImg, enemy2RightImg;
bool enemy2MovingLeft = true;
float enemy2X = 600;
float enemy2Y = BG41_GROUND_Y + ENEMY2_FLOAT_HEIGHT;
float enemy2FloatOffset = 0.0f;
int enemy2HitCount = 0;
bool enemy2Dead = false;
float enemy2DeadY = 0;
bool enemy2Falling = false;
int enemy2DeadImg;
int enemy2BodyCollisionCount = 0;
bool enemy2WasColliding = false;

int enemy3IdleImg;
int enemy3WalkImg;
int enemy3FistImg;
int enemy3PunchImg;
bool enemy3Alive = true;
int enemy3IdleImgM;
int enemy3WalkImgM;
int enemy3FistImgM;
int enemy3PunchImgM;
float enemy3X = 0;
float enemy3Speed = 2.5f;
bool enemy3MovingLeft = true;
Enemy3State enemy3State = E3_WALKING;
float enemy3WalkOffset = 0.0f;
float enemy3WalkAmplitude = 2.0f;
float enemy3WalkSpeed = 0.1f;
int enemy3AnimFrame = 0;
int enemy3StateTimer = 0;
int enemy3PunchFrame = 0;
bool enemy3PunchToggle = false;
int enemy3HitCount = 0;
bool enemy3Falling = false;
float enemy3DeadY = 0;
float enemy3DeadVelocity = 0;
int enemy3DeadImg;
int enemy3PunchCount = 0;

int enemy4Img;
int enemy4DeadImg;
bool enemy4Alive = true;
int enemy4HitCount = 0;
float enemy4FloatOffset = 0.0f;
float enemy4FloatSpeed = 0.08f;
float enemy4FloatRange = 6.0f;
float enemy4DeadY = 0;                 //----------------------------------------end---------------------------------------------------

int dragonFrames[DRAGON_FRAME_COUNT];
int dragonFrameIndex = 0;
int dragonDeadImg;
bool dragonFireHitChecked = false;
bool dragonAlive = true;
int dragonHitCount = 0;
bool dragonFireActive = false;

void initCollectibles() {
  int tSize = 35;
  int trW = 80, trH = 80;
  int index = 0;

  // Bridge 1 (index 0) - More towards the left
  int leftX0 = bridges[0].minX + 60;
  collectibles[index++] = {leftX0, bridges[0].snapY + 45, false, false};
  collectibles[index++] = {leftX0 - tSize / 2 - 10, bridges[0].snapY + 10,
                           false, false};
  collectibles[index++] = {leftX0 + tSize / 2 + 10, bridges[0].snapY + 10,
                           false, false};

  // Bridge 2 (index 1)
  int midX1 = (bridges[1].minX + bridges[1].maxX) / 2;
  collectibles[index++] = {midX1 - tSize / 2, bridges[1].snapY + 45, false,
                           false};
  collectibles[index++] = {midX1 - tSize - 10, bridges[1].snapY + 10, false,
                           false};
  collectibles[index++] = {midX1 + 10, bridges[1].snapY + 10, false, false};

  // Bridge 4 (index 3)
  int midX3 = (bridges[3].minX + bridges[3].maxX) / 2;
  collectibles[index++] = {midX3 - tSize - 5, bridges[3].snapY + 10, false,
                           false};
  collectibles[index++] = {midX3 + 5, bridges[3].snapY + 10, false, false};

  // Bridge 7 (index 6)
  int midX6 = (bridges[6].minX + bridges[6].maxX) / 2;
  collectibles[index++] = {midX6 - tSize - 5, bridges[6].snapY + 10, false,
                           false};
  collectibles[index++] = {midX6 + 5, bridges[6].snapY + 10, false, false};

  // Bridge 9 (index 8)
  int midX8 = (bridges[8].minX + bridges[8].maxX) / 2;
  collectibles[index++] = {midX8 - tSize / 2, bridges[8].snapY + 45, false,
                           false};
  collectibles[index++] = {midX8 - tSize - 10, bridges[8].snapY + 10, false,
                           false};
  collectibles[index++] = {midX8 + 10, bridges[8].snapY + 10, false, false};

  // Bridge 5 (index 4)
  int midX4 = (bridges[4].minX + bridges[4].maxX) / 2;
  collectibles[index++] = {midX4 - trH / 2, bridges[4].snapY, false, true};

  // Bridge 8 (index 7)
  int midX7 = (bridges[7].minX + bridges[7].maxX) / 2;
  collectibles[index++] = {midX7 - trH / 2, bridges[7].snapY, false, true};
}

void checkCollectibleCollisions() {
  if (currentBg != 4 || !playerAlive)
    return;

  int tSize = 35;
  int trW = 80, trH = 80;

  for (int i = 0; i < numCollectibles; i++) {
    if (collectibles[i].collected)
      continue;

    int cW = collectibles[i].isTreasure ? trW : tSize;
    int cH = collectibles[i].isTreasure ? trH : tSize;

    if (playerX < collectibles[i].x + cW &&
        playerX + PLAYER_WIDTH > collectibles[i].x &&
        playerY < collectibles[i].y + cH &&
        playerY + PLAYER_HEIGHT > collectibles[i].y) {
      collectibles[i].collected = true;
      if (collectibles[i].isTreasure) {
        treasureCount++;
      } else {
        tokenCount++;
      }
    }
  }
}

// ---------------- FORWARD DECLARATIONS ----------------

void updateEnemy1Hit();       //----------------------------------------my codes---------------------------------------------------
void updateEnemy2Hit();
void updateEnemy4Hit();
void checkPlayerEnemy2Collision();
void checkPlayerEnemy4Collision();

void checkEnemy3Collision();
void updateEnemy3();
void updateEnemy3Hit();
void checkEnemy3BodyKill();

void handlePlayerDeath();
void updateGameOverDelay();

void shuffleEnemySprites();

void updateDragonHit() {
  if (currentBg != 4)
    return;

  Bridge &b = bridges[DRAGON_BRIDGE_INDEX];

  int dragonX = b.minX + DRAGON_X_OFFSET;
  int dragonY = b.snapY - 5; // slightly above ground

  // Dragon hitbox
  int dX1 = dragonX;
  int dX2 = dragonX + DRAGON_WIDTH;
  int dY1 = dragonY;
  int dY2 = dragonY + DRAGON_HEIGHT;

  bool invincible = (!dragonAlive) || (chargingPunch && chargeScrollDismissed);

  // -------- Normal Punch --------
  if (punchJustLanded) {
    int pX1 = playerX + (movingFront ? PLAYER_WIDTH : -10);
    int pX2 = playerX + (movingFront ? PLAYER_WIDTH + 40 : 10);
    int pY1 = playerY + 60;
    int pY2 = playerY + 140;

    bool overlapX = !(pX2 < dX1 || pX1 > dX2);
    bool overlapY = !(pY2 < dY1 || pY1 > dY2);

    if (overlapX && overlapY) {
      dragonHitCount++;
      punchJustLanded = false;
    }
  }

  // -------- Charged Punch (longer reach) --------
  if (chargedSequenceActive) {
    int reachExtra = 80; // extend punch reach
    int pX1 = playerX + (movingFront ? PLAYER_WIDTH : -10 - reachExtra);
    int pX2 = playerX + (movingFront ? PLAYER_WIDTH + 80 + reachExtra : 10);
    int pY1 = playerY + 40;
    int pY2 = playerY + PLAYER_HEIGHT;

    bool overlapX = !(pX2 < dX1 || pX1 > dX2);
    bool overlapY = !(pY2 < dY1 || pY1 > dY2);

    if (overlapX && overlapY) {
      dragonHitCount++;
    }
  }

  if (dragonHitCount >= DRAGON_HITS_TO_KILL + 1) {
    dragonAlive = false;
  }
}

void updateDragon() {
  dragonFrameIndex = (dragonFrameIndex + 1) % DRAGON_FRAME_COUNT;

  if (dragonFrameIndex >= 5 && dragonFrameIndex <= 10)
    dragonFireActive = true;
  else
    dragonFireActive = false;

  if (currentBg == 4 && playerAlive && dragonFireActive) {
    Bridge &b = bridges[DRAGON_BRIDGE_INDEX];

    int dragonX = b.minX + DRAGON_X_OFFSET;
    int dragonY = b.snapY - 5;

    int fireX1 = dragonX + 80;
    int fireX2 = dragonX + DRAGON_WIDTH + 40;
    int fireY1 = dragonY + 80;
    int fireY2 = dragonY + DRAGON_HEIGHT - 40;

    int pX1 = playerX;
    int pX2 = playerX + PLAYER_WIDTH;
    int pY1 = playerY;
    int pY2 = playerY + PLAYER_HEIGHT;

    bool overlapX = !(fireX2 < pX1 || fireX1 > pX2);
    bool overlapY = !(fireY2 < pY1 || fireY1 > pY2);
    bool invincible =
        (!dragonAlive) || (chargingPunch && chargeScrollDismissed);

    if (overlapX && overlapY && !invincible) {
      playerAlive = false;
      gameStarted = false;

      killedByDragon = true;
      killedByEnemy1 = false;

      // Snap dead body to dragon ground
      playerDeathY = b.snapY;
    }
  }
  updateDragonHit();
  updateEnemy1Hit();
  handlePlayerDeath();
}

void checkPlayerEnemy1Collision() {      //----------------------------------------my codes---------------------------------------------------
  if (!enemy1Alive)
    return; // enemy must be alive
  if (!playerAlive)
    return;
  if (currentBg != 4)
    return;

  Bridge &b = bridges[ENEMY1_BRIDGE_INDEX];

  // Enemy1 position exactly as drawn
  int enemyX = b.maxX - ENEMY1_WIDTH - 60;
  int enemyY;
  if (enemy1Alive) {
    enemyY = b.snapY + (int)(sin(enemy1FloatOffset) * enemy1FloatRange);
  } else if (enemy1Falling) {
    enemyY = (int)enemy1DeadY;
  } else {
    enemyY = b.snapY;
  }

  // Shrink hitbox to match visible body
  int eX1 = enemyX + 90; // a bit inside horizontally
  int eX2 = enemyX + ENEMY1_WIDTH - 10;
  int eY1 = enemyY + 10;                 // a bit above the bottom
  int eY2 = enemyY + ENEMY1_HEIGHT - 10; // a bit below the top

  // Player body hitbox
  int pX1 = playerX;
  int pX2 = playerX + PLAYER_WIDTH;
  int pY1 = playerY;
  int pY2 = playerY + PLAYER_HEIGHT;

  // Check overlap
  bool overlapX = !(pX2 < eX1 || pX1 > eX2);
  bool overlapY = !(pY2 < eY1 || pY1 > eY2);

  if (overlapX && overlapY) {
    playerAlive = false;
    gameStarted = false;

    killedByEnemy1 = true;
    killedByDragon = false;

    // Snap dead body to enemy1's Y
    playerDeathY = enemyY;
  }
}

void updateEnemy1() {
  enemy1FloatOffset += enemy1FloatSpeed;
  if (enemy1FloatOffset > 2 * 3.1416f)
    enemy1FloatOffset = 0;

  checkPlayerEnemy1Collision();
  checkEnemy3Collision();
  handlePlayerDeath();
}

void updateEnemy3() {
  if (currentBg != 4)
    return;

  Bridge &b = bridges[ENEMY3_BRIDGE_INDEX];

  // -------- DEAD FALL --------
  if (!enemy3Alive && enemy3Falling) {
    enemy3DeadVelocity -= 1.4f;
    enemy3DeadY += enemy3DeadVelocity;

    if (enemy3DeadY <= b.snapY) {
      enemy3DeadY = BG41_GROUND_Y;
      enemy3Falling = false;
    }
    return;
  }

  if (!enemy3Alive)
    return;

  // -------- PLAYER DEAD: FLOAT ONLY --------
  if (!playerAlive) {
    // float up and down slightly on bridge6
    enemy3WalkOffset += enemy3WalkSpeed;
    if (enemy3WalkOffset > 2 * 3.1416f)
      enemy3WalkOffset = 0;
    return; // skip attack logic
  }

  // -------- ATTACK LOGIC --------
  if (enemy3State == E3_ATTACKING) {
    enemy3StateTimer++;

    if (enemy3StateTimer >= ENEMY3_PUNCH_INTERVAL) {
      enemy3StateTimer = 0;
      enemy3PunchToggle ^= 1;

      if (!chargingPunch && !chargedSequenceActive) {
        enemy3PunchCount++;
        if (enemy3PunchCount >= ENEMY3_MAX_PUNCHES) {
          playerAlive = false;
          gameStarted = false;

          killedByEnemy3 = true;
          killedByEnemy1 = false;
          killedByDragon = false;
          playerDeathY = BG41_GROUND_Y;
        }
      }
    }
  }

  // -------- CHECK PLAYER PROXIMITY FOR ATTACK --------
  if (playerAlive) {
    int playerCenterX = playerX + PLAYER_WIDTH / 2;
    int enemyCenterX = enemy3X + ENEMY3_WIDTH / 2;
    int distX = abs(playerCenterX - enemyCenterX);
    bool sameBridge = abs(playerY - b.snapY) <= 6;

    if (sameBridge && distX <= ENEMY3_ATTACK_RANGE) {
      enemy3State = E3_ATTACKING;

      // Face the player before attacking
      if (playerCenterX < enemyCenterX)
        enemy3MovingLeft = true; // Player is on the left, face left
      else
        enemy3MovingLeft = false; // Player is on the right, face right
    } else
      enemy3State = E3_WALKING;
  }

  // -------- WALKING LOGIC --------
  if (enemy3State == E3_WALKING) {
    if (enemy3MovingLeft)
      enemy3X -= enemy3Speed;
    else
      enemy3X += enemy3Speed;

    enemy3WalkOffset += enemy3WalkSpeed;
    if (enemy3WalkOffset > 2 * 3.1416f)
      enemy3WalkOffset = 0;

    int leftBound = b.maxX;                          // Right edge of 9th bridge
    int rightBound = bridges[9].minX - ENEMY3_WIDTH; // Left edge of 10th bridge
    if (enemy3X <= leftBound) {
      enemy3X = leftBound;
      enemy3MovingLeft = false;
    } else if (enemy3X >= rightBound) {
      enemy3X = rightBound;
      enemy3MovingLeft = true;
    }
    enemy3StateTimer++;
    if (enemy3StateTimer > 20) {
      enemy3StateTimer = 0;
      enemy3AnimFrame ^= 1;
    }
  }
  updateEnemy3Hit();
  checkEnemy3BodyKill();
  handlePlayerDeath();
}

void checkEnemy3BodyKill() {
  if (!enemy3Alive)
    return;
  if (!playerAlive)
    return;
  if (currentBg != 4)
    return;

  // Player immunity during charged actions
  if ((chargingPunch && chargeScrollDismissed) || chargedSequenceActive)
    return;

  Bridge &b = bridges[ENEMY3_BRIDGE_INDEX];

  // Enemy3 body hitbox (LARGER for easier collision)
  int eX1 = enemy3X;
  int eX2 = enemy3X + ENEMY3_WIDTH;
  int eY1 = b.snapY;
  int eY2 = b.snapY + ENEMY3_HEIGHT;

  // Player body hitbox
  int pX1 = playerX;
  int pX2 = playerX + PLAYER_WIDTH;
  int pY1 = playerY;
  int pY2 = playerY + PLAYER_HEIGHT;

  bool overlapX = !(pX2 < eX1 || pX1 > eX2);
  bool overlapY = !(pY2 < eY1 || pY1 > eY2);

  if (overlapX && overlapY) {
    playerAlive = false;
    gameStarted = false;

    killedByEnemy3 = true;
    killedByEnemy1 = false;
    killedByDragon = false;
    killedByEnemy2 = false;
    killedByEnemy4 = false;

    playerDeathY = BG41_GROUND_Y;
  }
}
void checkEnemy3Collision() { return; }
void updateEnemy3Hit() {
  if (!enemy3Alive)
    return;
  if (currentBg != 4)
    return;

  Bridge &b = bridges[ENEMY3_BRIDGE_INDEX];

  // Enemy3 hitbox
  int eX1 = enemy3X;
  int eX2 = enemy3X + ENEMY3_WIDTH;
  int eY1 = b.snapY;
  int eY2 = b.snapY + ENEMY3_HEIGHT;

  // -------- NORMAL PUNCH --------
  if (punchJustLanded) {
    int pX1 = playerX + (movingFront ? PLAYER_WIDTH : -60);
    int pX2 = playerX + (movingFront ? PLAYER_WIDTH + 60 : 10);
    int pY1 = playerY + 60;
    int pY2 = playerY + 140;

    bool overlapX = !(pX2 < eX1 || pX1 > eX2);
    bool overlapY = !(pY2 < eY1 || pY1 > eY2);

    if (overlapX && overlapY) {
      enemy3HitCount++;
      punchJustLanded = false;
      // If normal punch count reaches 8, enemy3 dies
      if (enemy3HitCount >= ENEMY3_NORMAL_HITS_TO_KILL) {
        enemy3Alive = false;
        enemy3Falling = true;
        enemy3DeadVelocity = 0;
        enemy3DeadY = b.snapY + 250; // start ABOVE, for falling animation
      }
    }
  }

  // -------- CHARGED PUNCH --------
  if (chargedSequenceActive) {
    int pX1 = playerX + (movingFront ? PLAYER_WIDTH : -120);
    int pX2 = playerX + (movingFront ? PLAYER_WIDTH + 120 : 10);
    int pY1 = playerY + 40;
    int pY2 = playerY + PLAYER_HEIGHT;

    bool overlapX = !(pX2 < eX1 || pX1 > eX2);
    bool overlapY = !(pY2 < eY1 || pY1 > eY2);

    if (overlapX && overlapY) {
      enemy3Alive = false;
      enemy3Falling = true;
      enemy3DeadVelocity = 0;
      enemy3DeadY = b.snapY + 250; // start ABOVE, for falling animation
      return;
    }
  }

  // -------- DEATH CHECK --------
  if (enemy3HitCount >= ENEMY3_NORMAL_HITS_TO_KILL) {
    enemy3Alive = false;
    enemy3Falling = true;
    enemy3DeadVelocity = 0;
    enemy3DeadY = b.snapY + 250; // start ABOVE, for falling animation
  }
}

void updateChargedHitWindow() {
  if (chargedHitWindow > 0) {
    chargedHitWindow--;
    if (chargedHitWindow == 0)
      chargedSequenceActive = false;
  }
}

void updateEnemy1Hit() {
  if (!enemy1Alive)
    return;
  if (currentBg != 4)
    return;
  if (!punchJustLanded)
    return; // only count completed punches

  Bridge &b = bridges[ENEMY1_BRIDGE_INDEX];

  // Enemy1 position
  int enemyX = b.maxX - ENEMY1_WIDTH - 60;
  int enemyY = b.snapY + (int)(sin(enemy1FloatOffset) * enemy1FloatRange);

  // Enemy hitbox
  int eX1 = enemyX;
  int eX2 = enemyX + ENEMY1_WIDTH;
  int eY1 = enemyY;
  int eY2 = enemyY + ENEMY1_HEIGHT;

  // Player punch hitbox (NORMAL punch)
  int punchReach = 60; // extend reach to the left
  int pHeight = 80;    // vertical hitbox height
  int pY1 = playerY + 60;
  int pY2 = playerY + 60 + pHeight;

  int pX1, pX2;
  if (movingFront) {
    // Facing right: start hitbox slightly LEFT of player's right edge
    pX1 = playerX + PLAYER_WIDTH - 20;
    pX2 = playerX + PLAYER_WIDTH + punchReach;
  } else {
    // Facing left: hitbox slightly wider to left
    pX1 = playerX - punchReach;
    pX2 = playerX + 70;
  }

  // Check overlap
  bool overlapX = !(pX2 < eX1 || pX1 > eX2);
  bool overlapY = !(pY2 < eY1 || pY1 > eY2);

  if (overlapX && overlapY) {
    enemy1HitCount++;
    punchJustLanded = false; // consume hit

    if (enemy1HitCount >= ENEMY1_HITS_TO_KILL) {
      enemy1Alive = false;

      // Immediately place dead body on bridge1 at player position
      enemy1DeadY = bridges[ENEMY1_BRIDGE_INDEX].snapY; // exactly on bridge
    }
  }
}

void updateEnemy2() {
  if (currentBg != 4)
    return;

  // Fall if dead
  if (enemy2Dead && enemy2Falling) {
    enemy2DeadY -= 2; // Fall downward (negative because falling)
    if (enemy2DeadY <= BG41_GROUND_Y) {
      enemy2DeadY = BG41_GROUND_Y; // Make sure it touches the ground
      enemy2Falling = false;       // Stop falling when it reaches the ground
    }
    return; // EXIT early - don't run movement code below
  }

  // Only move if alive
  if (!enemy2Dead) {
    // Horizontal movement
    if (enemy2MovingLeft) {
      enemy2X -= ENEMY2_FLOAT_SPEED;    // Move left
      if (enemy2X <= bridges[0].maxX) { // If Enemy2 reaches Bridge 1
        enemy2MovingLeft = false;       // Change direction to right
      }
    } else {
      enemy2X += ENEMY2_FLOAT_SPEED; // Move right
      if (enemy2X >=
          bridges[1].minX - ENEMY2_WIDTH) { // If Enemy2 reaches Bridge 2
        enemy2MovingLeft = true;            // Change direction to left
      }
    }

    // Ensure enemy2 doesn't go off the screen (boundary check)
    if (enemy2X < bridges[0].maxX) {
      enemy2X =
          bridges[0].maxX; // Keep enemy2 within the left side of the screen
    }
    if (enemy2X > bridges[1].minX - ENEMY2_WIDTH) {
      enemy2X = bridges[1].minX -
                ENEMY2_WIDTH; // Keep enemy2 within the right side of the screen
    }

    // Floating effect (up and down)
    enemy2FloatOffset += 0.1f; // Adjust floating speed
    if (enemy2FloatOffset > 2 * 3.1416f) {
      enemy2FloatOffset = 0.0f; // Reset after a full cycle
    }
    enemy2Y = BG41_GROUND_Y + ENEMY2_FLOAT_HEIGHT +
              sin(enemy2FloatOffset) * 10; // Small floating bounce
  }

  updateEnemy2Hit();
  checkPlayerEnemy2Collision();
  handlePlayerDeath();
}

void updateEnemy4() {
  if (currentBg != 4)
    return;

  enemy4FloatOffset += enemy4FloatSpeed;
  if (enemy4FloatOffset > 2 * 3.1416f)
    enemy4FloatOffset = 0;

  // Update the position for Enemy 4 to the very right edge of Bridge 2
  Bridge &b = bridges[ENEMY4_BRIDGE_INDEX];
  int enemyX = b.maxX - ENEMY4_WIDTH; // Move to the right edge of Bridge 2

  updateEnemy4Hit();
  checkPlayerEnemy4Collision();
  handlePlayerDeath();
}

void updateEnemy4Hit() {
  if (!enemy4Alive)
    return;
  if (currentBg != 4)
    return;
  if (!punchJustLanded)
    return;

  Bridge &b = bridges[ENEMY4_BRIDGE_INDEX];

  // Enemy4 position (right edge of bridge)
  int enemy4X = b.minX + 100; // EXACT left edge of bridge
  int enemyY = b.snapY + ENEMY4_HEIGHT_OFFSET +
               (int)(sin(enemy4FloatOffset) * enemy4FloatRange);

  // Enemy hitbox
  int eX1 = enemy4X;
  int eX2 = enemy4X + ENEMY4_WIDTH;
  int eY1 = enemyY;
  int eY2 = enemyY + ENEMY4_HEIGHT;

  // Player punch hitbox (NORMAL punch)
  int punchReach = 60;
  int pHeight = 80;
  int pY1 = playerY + 60;
  int pY2 = playerY + 60 + pHeight;

  int pX1, pX2;
  if (movingFront) {
    pX1 = playerX + PLAYER_WIDTH - 20;
    pX2 = playerX + PLAYER_WIDTH + punchReach;
  } else {
    pX1 = playerX - punchReach;
    pX2 = playerX + 70;
  }

  // Check overlap
  bool overlapX = !(pX2 < eX1 || pX1 > eX2);
  bool overlapY = !(pY2 < eY1 || pY1 > eY2);

  if (overlapX && overlapY) {
    enemy4HitCount++;
    punchJustLanded = false; // consume hit

    if (enemy4HitCount >= ENEMY4_HITS_TO_KILL) {
      enemy4Alive = false;
      enemy4DeadY = bridges[ENEMY4_BRIDGE_INDEX].snapY;
    }
  }
}
void updateEnemy2Hit() {
  if (enemy2Dead)
    return;
  if (currentBg != 4)
    return;
  if (!punchJustLanded)
    return; // only check when punch just landed

  // Enemy2's hitbox (same as draw)
  int eX1 = enemy2X;
  int eX2 = enemy2X + ENEMY2_WIDTH;
  int eY1 = enemy2Y;
  int eY2 = enemy2Y + ENEMY2_HEIGHT;

  // Player punch hitbox (NORMAL punch)
  int punchReach = 60; // extend reach to the left
  int pHeight = 80;    // vertical hitbox height
  int pY1 = playerY + 60;
  int pY2 = playerY + 60 + pHeight;

  int pX1, pX2;
  if (movingFront) {
    // Facing right: start hitbox slightly LEFT of player's right edge
    pX1 = playerX + PLAYER_WIDTH - 20;
    pX2 = playerX + PLAYER_WIDTH + punchReach;
  } else {
    // Facing left: hitbox slightly wider to left
    pX1 = playerX - punchReach;
    pX2 = playerX + 70;
  }

  // Check overlap
  bool overlapX = !(pX2 < eX1 || pX1 > eX2);
  bool overlapY = !(pY2 < eY1 || pY1 > eY2);

  if (overlapX && overlapY) {
    enemy2HitCount++;
    punchJustLanded = false; // CONSUME the punch flag here

    if (enemy2HitCount >= ENEMY2_HITS_TO_KILL) {
      enemy2Dead = true;     // Mark Enemy2 as dead
      enemy2Falling = true;  // Start falling animation
      enemy2DeadY = enemy2Y; // Set the death position at current Y
    }
  }
}

void checkPlayerEnemy2Collision() {
  if (enemy2Dead)
    return;
  if (!playerAlive)
    return;
  if (currentBg != 4)
    return;
  if ((chargingPunch && chargeScrollDismissed) || chargedSequenceActive)
    return;
  if (punchState > 0)
    return;
  int drawW = (int)(ENEMY2_WIDTH * ENEMY2_SCALE);
  int drawH = (int)(ENEMY2_HEIGHT * ENEMY2_SCALE);

  int eX1 = enemy2X + (ENEMY2_WIDTH - drawW) / 2;
  int eY1 = enemy2Y + (ENEMY2_HEIGHT - drawH) / 2;

  int eX2 = eX1 + drawW;
  int eY2 = eY1 + drawH;

  int shrinkX = 20;
  int shrinkY = 20;

  eX1 += shrinkX;
  eX2 -= shrinkX;
  eY1 += shrinkY;
  eY2 -= shrinkY;

  int pX1 = playerX + 20;
  int pX2 = playerX + PLAYER_WIDTH - 20;
  int pY1 = playerY + 20;
  int pY2 = playerY + PLAYER_HEIGHT - 20;

  bool overlapX = !(pX2 < eX1 || pX1 > eX2);
  bool overlapY = !(pY2 < eY1 || pY1 > eY2);

  // Kill player IMMEDIATELY on ANY collision
  if (overlapX && overlapY) {
    playerAlive = false;
    gameStarted = false;

    killedByEnemy2 = true;
    killedByEnemy1 = false;
    killedByDragon = false;
    killedByEnemy3 = false;
    killedByEnemy4 = false;

    playerDeathY = BG41_GROUND_Y;
  }
}

void checkPlayerEnemy4Collision() {
  if (!enemy4Alive)
    return; // enemy must be alive
  if (!playerAlive)
    return;
  if (currentBg != 4)
    return;

  // Player immunity during charged actions
  if ((chargingPunch && chargeScrollDismissed) || chargedSequenceActive)
    return;

  Bridge &b = bridges[ENEMY4_BRIDGE_INDEX];

  // Enemy4 position exactly as drawn
  int enemy4X = b.minX + 100;
  int enemyY = b.snapY + ENEMY4_HEIGHT_OFFSET +
               (int)(sin(enemy4FloatOffset) * enemy4FloatRange);

  // Shrink hitbox to ensure REAL touching
  int eX1 = enemy4X + 90;
  int eX2 = enemy4X + ENEMY4_WIDTH - 30;
  int eY1 = enemyY + 20;
  int eY2 = enemyY + ENEMY4_HEIGHT - 20;

  // Player body hitbox (slightly reduced)
  int pX1 = playerX + 20;
  int pX2 = playerX + PLAYER_WIDTH - 20;
  int pY1 = playerY + 20;
  int pY2 = playerY + PLAYER_HEIGHT - 20;

  // Check overlap
  bool overlapX = !(pX2 < eX1 || pX1 > eX2);
  bool overlapY = !(pY2 < eY1 || pY1 > eY2);

  if (overlapX && overlapY) {
    playerAlive = false;
    gameStarted = false;

    killedByEnemy4 = true;
    killedByEnemy1 = false;
    killedByDragon = false;
    killedByEnemy3 = false;
    killedByEnemy2 = false;

    // Snap dead body to bridge2
    playerDeathY = b.snapY;
  }
}                        //----------------------------------------my codes---------------------------------------------------
void checkWinFlagCollision() {
  if (!playerAlive)
    return;
  if (currentBg != 4)
    return;
  if (playerWon)
    return; // Already won

  Bridge &bridge10 = bridges[9]; // Bridge 10
  int flagX = bridge10.maxX - WINFLAG_WIDTH + WINFLAG_X_OFFSET;
  int flagY = bridge10.snapY + WINFLAG_Y_OFFSET;

  // Win flag hitbox - SHRINK IT to require closer contact
  int shrinkX = 40; // Make hitbox smaller horizontally
  int shrinkY = 40; // Make hitbox smaller vertically

  int fX1 = flagX + shrinkX;
  int fX2 = flagX + WINFLAG_WIDTH - shrinkX;
  int fY1 = flagY + shrinkY;
  int fY2 = flagY + WINFLAG_HEIGHT - shrinkY;

  // Player hitbox - also shrink slightly
  int pX1 = playerX + 20;
  int pX2 = playerX + PLAYER_WIDTH - 20;
  int pY1 = playerY + 20;
  int pY2 = playerY + PLAYER_HEIGHT - 20;

  // Check overlap
  bool overlapX = !(pX2 < fX1 || pX1 > fX2);
  bool overlapY = !(pY2 < fY1 || pY1 > fY2);

  if (overlapX && overlapY) {
    playerWon = true;
    gameStarted = false;
  }
}
/* -------------------- HELPER -------------------- */
bool isInsideCircle(int mx, int my) {
  double cx = backX + backW / 2.0;
  double cy = backY + backH / 2.0;
  double r = backW / 2.0;
  double d = sqrt((mx - cx) * (mx - cx) + (my - cy) * (my - cy));
  return d <= r;
}

/* -------------------- CAMERA -------------------- */
void updateCamera() {
  if (currentBg != 4)
    return;
  if (!playerAlive)
    return; // CAMERA FREEZE ON DEATH

  cameraX = playerX - SCREEN_WIDTH / 2;
  if (cameraX < 0)
    cameraX = 0;
  if (cameraX > BG41_WIDTH - SCREEN_WIDTH)
    cameraX = BG41_WIDTH - SCREEN_WIDTH;
}

/* -------------------- BRIDGE HELPERS (ADD ONLY) -------------------- */
bool isOnBridge();                      //----------------------------------------my codes---------------------------------------------------
bool isBelowBridge();

bool isBelowBridge() {
  if (currentBg != 4)
    return false;
  if (isJumping)
    return false; // Allow movement while jumping
  if (isOnBridge())
    return false;

  int cx = playerX + PLAYER_WIDTH / 2;
  int nearestBridgeY = -1;
  int nearestBridgeIndex = -1;

  // Find the LOWEST bridge above the player
  for (int i = 0; i < numBridges; i++) {
    if (cx >= bridges[i].minX && cx <= bridges[i].maxX &&
        bridges[i].snapY > playerY) {
      if (nearestBridgeY == -1 || bridges[i].snapY < nearestBridgeY) {
        nearestBridgeY = bridges[i].snapY;
        nearestBridgeIndex = i;
      }
    }
  }

  // If no bridge above, don't block
  if (nearestBridgeY == -1)
    return false;
  if (nearestBridgeIndex == 3 ||
      nearestBridgeIndex == 4) // Bridge 4 or Bridge 5
  {
    // Check if player is horizontally between bridge 3 and bridge 6
    int bridge3End = bridges[2].maxX;   // End of bridge 3
    int bridge6Start = bridges[5].minX; // Start of bridge 6

    if (cx > bridge3End && cx < bridge6Start) {
      // Player is in the gap - allow movement
      return false;
    }
  }

  if (nearestBridgeIndex == 6 ||
      nearestBridgeIndex == 7) // Bridge 7 or Bridge 8
  {
    // Check if player is horizontally between bridge 6 and bridge 9
    int bridge6End = bridges[5].maxX;   // End of bridge 6
    int bridge9Start = bridges[8].minX; // Start of bridge 9

    if (cx > bridge6End && cx < bridge9Start) {
      // Player is in the gap - allow movement
      return false;
    }
  }

  // Block movement ONLY if player is clearly below the bridge
  if (playerY < nearestBridgeY - 20)
    return true;

  return false;
}

bool isOnBridge() {
  if (currentBg != 4)
    return false;

  int cx = playerX + PLAYER_WIDTH / 2;

  for (int i = 0; i < numBridges; i++) {
    if (cx >= bridges[i].minX && cx <= bridges[i].maxX &&
        abs(playerY - bridges[i].snapY) <= 6) {
      return true;
    }
  }
  return false;
}

void updateJump() {
  if (currentBg != 4)
    return;
  if (!playerAlive)
    return;

  int groundY = BG41_GROUND_Y;
  bool onBridge = false;
  float prevY = playerY;

  playerY += jumpVelocity;
  jumpVelocity -= GRAVITY;

  // -------- BRIDGE LANDING --------
  if (jumpVelocity < 0) {
    for (int i = 0; i < numBridges; i++) {
      int cx = playerX + PLAYER_WIDTH / 2;

      if (cx >= bridges[i].minX && cx <= bridges[i].maxX &&
          prevY >= bridges[i].snapY && playerY <= bridges[i].snapY) {
        playerY = bridges[i].snapY;
        isJumping = false;
        jumpVelocity = 0;
        onBridge = true;
        break;
      }
    }
  }

  // -------- LOCK PLAYER TO BRIDGE --------
  if (!isJumping) {
    int cx = playerX + PLAYER_WIDTH / 2;

    for (int i = 0; i < numBridges; i++) {
      if (cx >= bridges[i].minX && cx <= bridges[i].maxX &&
          abs(playerY - bridges[i].snapY) <= 6) {
        playerY = bridges[i].snapY;
        jumpVelocity = 0;
        break;
      }
    }
  }

  // -------- GROUND COLLISION --------
  if (playerY <= groundY) {
    playerY = groundY;
    isJumping = false;
    jumpVelocity = 0;
  }

  updateCamera();
  checkCollectibleCollisions();
}

/* -------------------- CHARGED TIMER -------------------- */
void updateChargedTimer() {
  if (!chargingPunch)
    return;
  chargedTimeCounter += 100;
  if (chargedTimeCounter >= CHARGED_TIME_LIMIT) {
    chargingPunch = false;
    chargedSequenceActive = false;
    chargedPunchState = 0;
    chargedTimeCounter = 0;
  }
}

/* -------------------- MUSIC -------------------- */
void playMusic() {                        //----------------------------------------my codes---------------------------------------------------
  mciSendString("stop music", NULL, 0, NULL);
  mciSendString("close music", NULL, 0, NULL);
  mciSendString("open \"Audios/music.mp3\" type mpegvideo alias music", NULL, 0,
                NULL);
  mciSendString("play music repeat", NULL, 0, NULL);
}

void restartMusic() {                   //----------------------------------------my codes---------------------------------------------------
  mciSendString("stop music", NULL, 0, NULL);
  mciSendString("seek music to start", NULL, 0, NULL);
  mciSendString("play music repeat", NULL, 0, NULL);
}
void initPunchSound() {
  mciSendString("close punch", NULL, 0, NULL);
  mciSendString("open \"Audios/punch.mp3\" type mpegvideo alias punch", NULL, 0,
                NULL);
}

void playPunchSound() {
  // Stop any currently playing punch sound, seek to start, play
  mciSendString("stop punch", NULL, 0, NULL);
  mciSendString("seek punch to start", NULL, 0, NULL);

  // Set volume (0-1000 scale)
  char volCmd[64];
  sprintf_s(volCmd, "setaudio punch volume to %d", punchVolume);
  mciSendString(volCmd, NULL, 0, NULL);

  mciSendString("play punch", NULL, 0,
                NULL); // no "repeat" - punch sound plays once
}

void drawHUD() {
  if (currentBg != 4 || playerWon)
    return;

  int hudW = 300; // Longer
  int hudH = 25;  // Thicker
  int margin = 20;
  int gap = 20;      // Increased gap for larger icons
  int iconSize = 45; // Bigger icons
  int startX = SCREEN_WIDTH - hudW - margin;
  int startY = SCREEN_HEIGHT - margin - hudH;

  // Icons (Heart/Life)
  iShowImage(startX - iconSize - 2, startY - (iconSize - hudH) / 2, iconSize,
             iconSize, hudLifeImg);

  // Background for Life Bar
  iSetColor(40, 40, 40);
  iFilledRectangle(startX, startY, hudW, hudH);

  // Life Bar (Deep Red)
  float lifeRatio = (float)playerLives / MAX_LIVES;
  if (lifeRatio > 1.0f)
    lifeRatio = 1.0f;
  if (lifeRatio > 0) {
    iSetColor(180, 0, 0); // Deep Red
    iFilledRectangle(startX, startY, (int)(hudW * lifeRatio), hudH);
  }

  // Border for Life bar (Black)
  iSetColor(0, 0, 0);
  iRectangle(startX, startY, hudW, hudH);

  // Background for Charged Punch Bar
  int punchY = startY - hudH - gap;

  // Icons (Punch)
  iShowImage(startX - iconSize - 2, punchY - (iconSize - hudH) / 2, iconSize,
             iconSize, hudPunchImg);

  iSetColor(40, 40, 40);
  iFilledRectangle(startX, punchY, hudW, hudH);

  // Charged Punch Bar (Deeper Blue)
  int remainingPunches = MAX_CHARGED_USES - chargedUseCount;
  if (remainingPunches < 0)
    remainingPunches = 0;
  float punchRatio = (float)remainingPunches / MAX_CHARGED_USES;
  if (punchRatio > 0) {
    iSetColor(0, 0, 120); // Deeper Blue
    iFilledRectangle(startX, punchY, (int)(hudW * punchRatio), hudH);
  }

  // Border for Punch bar (Black)
  iSetColor(0, 0, 0);
  iRectangle(startX, punchY, hudW, hudH);

  // ---------------- TOKEN BAR (TOP-LEFT CORNER) ----------------
  int tokenStartX = margin;
  int tokenStartY = SCREEN_HEIGHT - margin - hudH;
  int tokenIconSize = 35;

  // Background for Token Bar
  iSetColor(40, 40, 40);
  iFilledRectangle(tokenStartX, tokenStartY, hudW, hudH);

  // Token Bar (Black fill)
  float tokenRatio = (float)tokenCount / MAX_TOKENS;
  if (tokenRatio > 1.0f)
    tokenRatio = 1.0f;
  if (tokenRatio > 0) {
    iSetColor(0, 0, 0); // Black Bar
    iFilledRectangle(tokenStartX, tokenStartY, (int)(hudW * tokenRatio), hudH);
  }

  // Token Count Text (Centered in bar)
  char tokenStr[20];
  sprintf_s(tokenStr, "%d/%d", tokenCount, MAX_TOKENS);
  iSetColor(255, 255, 255);
  int textX = tokenStartX + (hudW - (int)strlen(tokenStr) * 10) / 2;
  int textY = tokenStartY + (hudH - 18) / 2;
  iText(textX, textY, tokenStr, GLUT_BITMAP_HELVETICA_18);

  // Border for Token bar (Black)
  iSetColor(0, 0, 0);
  iRectangle(tokenStartX, tokenStartY, hudW, hudH);

  // Icons (Token) - Now on the right side of the bar
  iShowImage(tokenStartX + hudW + 7, tokenStartY - (tokenIconSize - hudH) / 2,
             tokenIconSize, tokenIconSize, tokenImg);

  // ---------------- TREASURE BAR (BELOW TOKEN BAR) ----------------
  int treasureStartY = tokenStartY - hudH - gap;

  // Background for Treasure Bar
  iSetColor(40, 40, 40);
  iFilledRectangle(tokenStartX, treasureStartY, hudW, hudH);

  // Treasure Bar Fill (Deep Purple/Electric Purple)
  float treasureRatio = (float)treasureCount / MAX_TREASURES;
  if (treasureRatio > 1.0f)
    treasureRatio = 1.0f;
  if (treasureRatio > 0) {
    iSetColor(120, 0, 120); // Electric Purple
    iFilledRectangle(tokenStartX, treasureStartY, (int)(hudW * treasureRatio),
                     hudH);
  }

  // Treasure Count Text (Centered in bar)
  char treasureStr[20];
  sprintf_s(treasureStr, "%d/%d", treasureCount, MAX_TREASURES);
  iSetColor(255, 255, 255);
  int tTextX = tokenStartX + (hudW - (int)strlen(treasureStr) * 10) / 2;
  int tTextY = treasureStartY + (hudH - 18) / 2;
  iText(tTextX, tTextY, treasureStr, GLUT_BITMAP_HELVETICA_18);

  // Border for Treasure bar (Black)
  iSetColor(0, 0, 0);
  iRectangle(tokenStartX, treasureStartY, hudW, hudH);

  // Icons (Treasure) - Mirroring Token Bar style
  int treasureIconSize = 65;
  iShowImage(tokenStartX + hudW + 2,
             treasureStartY - (treasureIconSize - hudH) / 2, treasureIconSize,
             treasureIconSize, treasureImg);
}

/* -------------------- DRAW -------------------- */
void iDraw() {
  iClear();
  iSetColor(255, 255, 255);

  // ================= BACKGROUNDS (ADDED) =================
  if (currentBg == 1)
    iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg1);
  else if (currentBg == 3) {
    iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, storyImgs[storyIndex]);
  } else if (currentBg == 2) {
    iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg2);
    for (int i = 0; i < NUM_BUTTONS; i++) {
      int y = btnStartY - i * (btnH + btnGap);
      iShowImage(btnX, y, btnW, btnH,
                 btnIsHover[i] ? btnHover[i] : btnNormal[i]);
    }
  }

  else if (currentBg == 4)
    iShowImage(-cameraX, 0, BG41_WIDTH, BG41_HEIGHT, bg41);

  else if (currentBg == 5)                //----------------------------------------my codes---------------------------------------------------
    iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg5);

  else if (currentBg == 6)
    iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg6);

  else if (currentBg == 7)
    iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg7);
  else if (currentBg == 8) {
    iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gameOverImg);   //-------------------------------------------------------------
  }

  // ---------------- LEVEL COLLECTIBLES ----------------
  if (currentBg == 4) {
    int tSize = 35;
    int trW = 80, trH = 80;

    for (int i = 0; i < numCollectibles; i++) {
      if (!collectibles[i].collected) {
        int drawX = collectibles[i].x - cameraX;
        int drawY = collectibles[i].y;
        int img = collectibles[i].isTreasure ? treasureImg : tokenImg;
        int w = collectibles[i].isTreasure ? trW : tSize;
        int h = collectibles[i].isTreasure ? trH : tSize;

        iShowImage(drawX, drawY, w, h, img);
      }
    }
  }

  // ============ ADD SIGNPOST HERE (BEFORE ENEMIES) ============
  if (currentBg == 4) {
    Bridge &bridge6 = bridges[5];       // Bridge 6 is index 5 (0-based)
    int signpostX = bridge6.minX - 60;  // Left edge of bridge 6
    int signpostY = bridge6.snapY - 15; // On the bridge surface

    iShowImage(signpostX - cameraX, signpostY, SIGNPOST_WIDTH, SIGNPOST_HEIGHT,
               signpostImg);
  }
  // ============ DRAW WIN FLAG ON BRIDGE 10 ============
  if (currentBg == 4) {
    Bridge &bridge10 = bridges[9]; // Bridge 10 is index 9 (0-based)
    int flagX = bridge10.maxX - WINFLAG_WIDTH +
                WINFLAG_X_OFFSET;                  // Right edge of bridge 10
    int flagY = bridge10.snapY + WINFLAG_Y_OFFSET; // On the bridge surface

    iShowImage(flagX - cameraX, flagY, WINFLAG_WIDTH, WINFLAG_HEIGHT,
               winFlagImg);
  }

  // ---------------- ENEMY1 DRAW ----------------
  if (currentBg == 4) {                        //----------------------------------------my codes---------------------------------------------------
    Bridge &b = bridges[ENEMY1_BRIDGE_INDEX];
    int enemy1X = b.maxX - ENEMY1_WIDTH - 60;

    if (enemy1Alive) {
      // Float up and down using sin()
      int drawY = b.snapY + (int)(sin(enemy1FloatOffset) * enemy1FloatRange);
      iShowImage(enemy1X - cameraX, drawY, ENEMY1_WIDTH, ENEMY1_HEIGHT,
                 swapEnemySprites ? enemy4Img : enemy1Img);
    } else {
      // Dead enemy
      int drawY = enemy1DeadY - ENEMY1_HEIGHT + 140; // already set on bridge
      iShowImage(enemy1X - cameraX, drawY, ENEMY1_WIDTH, ENEMY1_HEIGHT,
                 swapEnemySprites ? enemy4DeadImg : enemy1DeadImg);
    }
  }

  // ---------------- ENEMY4 DRAW ----------------
  if (currentBg == 4) {
    Bridge &b = bridges[ENEMY4_BRIDGE_INDEX];
    int enemy4X = b.minX + 100; // EXACT left edge of bridge

    if (enemy4Alive) {
      // Float up and down using sin()
      int drawY = b.snapY + ENEMY4_HEIGHT_OFFSET +
                  (int)(sin(enemy4FloatOffset) * enemy4FloatRange);
      iShowImage(enemy4X - cameraX, drawY, ENEMY4_WIDTH, ENEMY4_HEIGHT,
                 swapEnemySprites ? enemy1Img : enemy4Img);
    } else {
      // Dead enemy - sits FLUSH on bridge
      int drawY = b.snapY - ENEMY4_HEIGHT +
                  130; // Adjust so bottom of image touches bridge
      iShowImage(enemy4X - cameraX, drawY, ENEMY4_WIDTH, ENEMY4_HEIGHT,
                 swapEnemySprites ? enemy1DeadImg : enemy4DeadImg);
    }
  }

  // ---------------- ENEMY3 DRAW ----------------
  if (currentBg == 4) {
    Bridge &b = bridges[ENEMY3_BRIDGE_INDEX];

    if (enemy3Alive) {
      int drawY =
          BG41_GROUND_Y + (int)(sin(enemy3WalkOffset) * enemy3WalkAmplitude);

      int img;

      if (enemy3State == E3_ATTACKING) {
        if (enemy3MovingLeft)
          img = enemy3PunchToggle ? enemy3PunchImg : enemy3FistImg;
        else
          img = enemy3PunchToggle ? enemy3PunchImgM : enemy3FistImgM;
      } else {
        if (enemy3MovingLeft)
          img = enemy3AnimFrame ? enemy3WalkImg : enemy3IdleImg;
        else
          img = enemy3AnimFrame ? enemy3WalkImgM : enemy3IdleImgM;
      }

      iShowImage(enemy3X - cameraX, drawY, ENEMY3_WIDTH, ENEMY3_HEIGHT, img);
    } else {
      // ---------------- ENEMY3 DEAD DRAW (FIXED SIZE) ----------------
      float widthScale = 2.7f;

      int deadW = (int)(ENEMY3_WIDTH * widthScale);
      int deadH = ENEMY3_HEIGHT + 5;

      int drawX = enemy3X - cameraX - (deadW - ENEMY3_WIDTH) / 2;
      int drawY = enemy3DeadY - 90; //  TOUCHES BRIDGE

      iShowImage(drawX, drawY, deadW, deadH, enemy3DeadImg);
    }
  }

  // ---------------- ENEMY2 DRAW ----------------
  if (currentBg == 4) {
    int drawW = (int)(ENEMY2_WIDTH * ENEMY2_SCALE);
    int drawH = (int)(ENEMY2_HEIGHT * ENEMY2_SCALE);

    // center scaling so it doesn't shift sideways
    int drawX = enemy2X - cameraX + (ENEMY2_WIDTH - drawW) / 2;
    int drawY = enemy2Y + (ENEMY2_HEIGHT - drawH) / 2;

    // Draw Enemy2 while alive
    if (!enemy2Dead) {
      iShowImage(drawX, drawY, drawW, drawH,
                 enemy2MovingLeft ? enemy2LeftImg : enemy2RightImg);
    } else {
      // Draw dead Enemy2 BIGGER
      float deadScale = 1.2f; // 120% size (increase this for even bigger)
      int deadW = (int)(ENEMY2_WIDTH * deadScale);
      int deadH = (int)(ENEMY2_HEIGHT * deadScale);

      // Center the dead body horizontally
      int deadDrawX = enemy2X - cameraX - (deadW - ENEMY2_WIDTH) / 2;

      // Position dead body lower on the ground
      int deadDrawY = enemy2DeadY - 90;

      iShowImage(deadDrawX, deadDrawY, deadW, deadH, enemy2DeadImg);
    }                                                       //---------------------------------------------------------------------
  }
  // ---------------- DRAGON DRAW (GROUND BETWEEN 9th and 10th BRIDGE)
  
  if (currentBg == 4) {
    Bridge &b = bridges[DRAGON_BRIDGE_INDEX];

    int dragonX = b.minX + DRAGON_X_OFFSET;
    int dragonY = b.snapY - 5;

    if (dragonAlive) {
      iShowImage(dragonX - cameraX, dragonY, DRAGON_WIDTH, DRAGON_HEIGHT,
                 dragonFrames[dragonFrameIndex]);
    } else {
      int deadOffsetY = -60;
      iShowImage(dragonX - cameraX, dragonY + deadOffsetY, DRAGON_WIDTH,
                 DRAGON_HEIGHT, dragonDeadImg);
    }
  }

  // ---------------- PLAYER DRAW ----------------
  if (!playerAlive && currentBg == 4) {
    int drawX = playerX - cameraX;

    int deadWidth = PLAYER_WIDTH + 40;
    int deadHeight = PLAYER_HEIGHT + 40;

    int drawY;
    if (killedByEnemy1)
      drawY = playerDeathY - 110;
    else if (killedByDragon)
      drawY = playerDeathY - 90;
    else if (killedByEnemy3)
      drawY = playerDeathY - 100; // Places bottom at ground level
    else if (killedByEnemy2)
      drawY = playerDeathY - 90;
    else if (killedByEnemy4)
      drawY = playerDeathY - 100;
    else
      drawY = BG41_GROUND_Y - 90;

    drawX -= (deadWidth - PLAYER_WIDTH) / 2;

    iShowImage(drawX, drawY, deadWidth, deadHeight, playerDeadImg);
  }

  else if (currentBg == 4) {
    int drawX = (currentBg == 4) ? playerX - cameraX : playerX;

    // Charged attack
    if (chargingPunch && chargeScrollDismissed) {
      if (chargedSequenceActive) {
        if (chargedPunchState == 0)
          iShowImage(drawX, playerY, PLAYER_WIDTH, PLAYER_HEIGHT,
                     movingFront ? chargedFistImg : chargedFistImgM);
        else
          iShowImage(drawX, playerY, PLAYER_WIDTH, PLAYER_HEIGHT,
                     movingFront ? chargedPunchImgSeq : chargedPunchImgSeqM);
      } else {
        iShowImage(drawX, playerY, PLAYER_WIDTH, PLAYER_HEIGHT,
                   movingFront ? chargedPunchImg : chargedPunchImgM);
      }
    }
    // Normal attack
    else {
      int img;
      if (punchState == 0)
        img = movingFront ? (animFrame ? playerSideLeft : playerSide)
                          : (animFrame ? playerSideLeftM : playerSideM);
      else if (punchState == 1)
        img = movingFront ? punchFistImg : punchFistImgM;
      else
        img = movingFront ? punchHitImg : punchHitImgM;

      iShowImage(drawX, playerY, PLAYER_WIDTH, PLAYER_HEIGHT, img);
    }
  }

  // ---------------- CHARGE SCROLL ----------------
  if (showChargeScroll && !chargeScrollDismissed) {
    iShowImage((SCREEN_WIDTH - 400) / 2, (SCREEN_HEIGHT - 400) / 2, 400, 300,
               chargeScrollImg);
  }

  // ---------------- BACK BUTTON (ADDED) ----------------
  if (currentBg == 5 || currentBg == 6 || currentBg == 7) {  //---------------------------------my codes---------------------------------
    iShowImage(backX, backY, backW, backH, backHover ? backBtnHover : backBtn);
  }
  // ============ DRAW WINNER SCREEN ============
  if (playerWon) {
    int scrollX = (SCREEN_WIDTH - WINNER_WIDTH) / 2;
    int scrollY = (SCREEN_HEIGHT - WINNER_HEIGHT) / 2;
    iShowImage(scrollX, scrollY, WINNER_WIDTH, WINNER_HEIGHT, winnerImg);
  }

  drawHUD();
}

void iKeyboard(unsigned char key) {
  if (playerWon)
    return;
  // --------------------- GAME OVER SCREEN CONTROLS ---------------------

  if (currentBg == 8) // Game Over screen             //---------------------------------my codes--------------------------------
  {
    if (key == 27) // ESC key - return to menu
    {
      currentBg = 2;
      gameStarted = false;
      gameOverScreen = false;
      gameOverTriggered = false;
      return;
    }

    if (key == 'y' || key == 'Y') // Y key - restart game with full lives
    {
      // Reset all game state
      currentBg = 4;
      gameStarted = true;
      gameOverScreen = false;
      gameOverTriggered = false;

      // Reset player
      playerX = PLAYER_START_X_BG41;
      playerY = PLAYER_START_Y_BG41;
      playerWon = false;
      cameraX = 0;
      movingFront = false;
      playerAlive = true;
      isJumping = false;
      punchState = 0;
      chargingPunch = false;
      chargedSequenceActive = false;
      chargedUseCount = 0;
      chargedTimeCounter = 0;

      // Reset lives system
      playerLives = MAX_LIVES;
      deathWaiting = false;
      deathDelayCounter = 0;
      gameOverDelayCounter = 0;

      // Reset all death flags
      killedByEnemy1 = false;
      killedByDragon = false;
      killedByEnemy3 = false;
      killedByEnemy2 = false;
      killedByEnemy4 = false;

      // Reset all enemies
      dragonAlive = true;
      dragonHitCount = 0;
      dragonFrameIndex = 0;

      enemy1Alive = true;
      enemy1HitCount = 0;
      enemy1Falling = false;
      enemy1FloatOffset = 0.0f;

      enemy2Dead = false;
      enemy2HitCount = 0;
      enemy2BodyCollisionCount = 0;
      enemy2Falling = false;
      enemy2X = 600;
      enemy2Y = BG41_GROUND_Y + ENEMY2_FLOAT_HEIGHT;
      enemy2MovingLeft = true;
      enemy2WasColliding = false;

      enemy3Alive = true;
      enemy3HitCount = 0;
      enemy3Falling = false;
      enemy3PunchCount = 0;
      enemy3State = E3_WALKING;
      enemy3X = bridges[ENEMY3_BRIDGE_INDEX].minX + 50;
      enemy3MovingLeft = true;

      enemy4Alive = true;
      enemy4HitCount = 0;
      enemy4FloatOffset = 0.0f;
      shuffleEnemySprites();

      initCollectibles();
      tokenCount = 0;
      treasureCount = 0;

      return;
    }
  }
                             //-----------------------------------------------------------------------------------------
  if (!playerAlive)
    return;

  // --------------------- MENU SHORTCUTS ---------------------
  if (currentBg == 1 && key == ' ') {
    currentBg = 2;
    return; // prevent falling into BG3/4 movement logic
  }
  // --------------------- STORY SEQUENCE ADVANCE ---------------------
  if (currentBg == 3 && key == ' ') {
    if (storyIndex < 6) {
      storyIndex++;
    } else {
      // Last slide (instruction) done — actually start the game
      inStorySequence = false;
      storyIndex = 0;
      currentBg = 4;
      gameStarted = true;
      shuffleEnemySprites();
      restartMusic(); // ← restart from beginning when game starts  //------------------------------------------------------------
    }
    return;
  }
  if (key == 27) // ESC key       //----------------------------------------my codes---------------------------------------------------
  {
    currentBg = 2;
    gameStarted = false;
    return;
  }

  // Do NOT have a generic space key change after this

  if (currentBg == 4) {

    // --------------------- NORMAL AND CHARGED PUNCH ---------------------
    if (key == 'f' || key == 'F') {
      if (chargingPunch && chargeScrollDismissed) {
        if (!chargedSequenceActive) {
          // First F press: go to FIST (state 0), start sequence
          chargedSequenceActive = true;
          chargedPunchState = 0; // 0 = fist
          chargedHitWindow = 6;
          playPunchSound();
        } else {
          // Toggle between fist (0) and punch (1)
          chargedPunchState ^= 1;
          if (chargedPunchState == 1) {
            chargedHitWindow = 6;
            playPunchSound();
          }
        }
      } else {
        if (punchState == 0) {
          punchState = 1;
          punchJustLanded = false;
        } else if (punchState == 1) {
          punchState = 2;         // SECOND PUNCH
          punchJustLanded = true; // REGISTER HIT ATTEMPT
          playPunchSound();
        } else if (punchState == 2) {
          punchState = 1;
          punchJustLanded = false;
        }
      }
    }
    // --------------------- START CHARGED FRONT ---------------------
    if ((key == 'p' || key == 'P') && chargedUseCount < MAX_CHARGED_USES) {
      if (!chargeScrollShown) {
        showChargeScroll = true;
        chargeScrollShown = true;
        chargeScrollDismissed = false;
        chargingPunch = false;
        chargedSequenceActive = false;
      } else {
        showChargeScroll = false;
        chargeScrollDismissed = true;
        chargingPunch = true;
        chargedSequenceActive = false;
        chargedPunchState = 0;

        chargedUseCount++;
        chargedTimeCounter = 0;
        chargedTimerRunning = true;
      }
    }

    // --------------------- DISMISS CHARGE SCROLL ---------------------
    if ((key == 'e' || key == 'E') && showChargeScroll) {
      showChargeScroll = false;
      chargeScrollDismissed = true;
      chargingPunch = true;
    }

    // --------------------- PLAYER MOVEMENT ---------------------
    if (currentBg == 4) {
      if (key == 'a') {
        if (!(currentBg == 4 && isBelowBridge())) {
          playerX -= 10;
          movingFront = true;
          punchState = 0;
          animFrame ^= 1; // toggle ONLY when player moves
        }
      }
      if (key == 'd') {
        if (!(currentBg == 4 && isBelowBridge())) {
          playerX += 10;
          movingFront = false;
          punchState = 0;
          animFrame ^= 1; // toggle ONLY when player moves
        }
      }
      if ((key == 'w' || key == 'W') && !isJumping) {
        isJumping = true;
        jumpVelocity = JUMP_POWER;
      }

      // Clamp player positions
      if (currentBg == 4) {
        if (playerX < 0)
          playerX = 0;
        if (playerX + PLAYER_WIDTH > BG41_WIDTH)
          playerX = BG41_WIDTH - PLAYER_WIDTH;
      }
    }
  }
}

/* -------------------- MOUSE -------------------- */
void iMouse(int button, int state, int mx, int my) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    // Check if btn1 is clicked                     //----------------------------------------my codes---------------------------------------
    int y = btnStartY - 0 * (btnH + btnGap); // btn1 index = 0
    if (mx >= btnX && mx <= btnX + btnW && my >= y && my <= y + btnH) {
      // Enter story sequence instead of jumping straight to game
      storyIndex = 0;
      inStorySequence = true;
      currentBg = 3;
      gameStarted = false;
      playerWon = false;

      // -------- RESET PLAYER STATE HERE --------
      playerX = PLAYER_START_X_BG41;
      playerY = PLAYER_START_Y_BG41;
      cameraX = 0;
      movingFront = false;
      playerAlive = true;
      dragonAlive = true;
      enemy1Alive = true;          //----------------------------------------my codes---------------------------------------------------
      enemy1HitCount = 0;
      enemy2Dead = false;
      enemy2HitCount = 0;
      enemy2BodyCollisionCount = 0;
      enemy3Alive = true;
      enemy3HitCount = 0;
      isJumping = false;
      punchState = 0;
      chargingPunch = false;
      chargedSequenceActive = false;
      killedByEnemy1 = false;
      killedByDragon = false;
      killedByEnemy3 = false;
      killedByEnemy2 = false;
      killedByEnemy4 = false;
      enemy4Alive = true;
      enemy4FloatOffset = 0.0f;
      enemy4HitCount = 0;
      shuffleEnemySprites();
      playerLives = MAX_LIVES;
      gameOverTriggered = false;
      gameOverScreen = false;
      deathWaiting = false;
      deathDelayCounter = 0;

      initCollectibles();
      tokenCount = 0;
      treasureCount = 0;
    }
  }

  // -------- CHARGE SCROLL DISMISS --------
  if (showChargeScroll) {
    int scrollX = (SCREEN_WIDTH - 400) / 2;
    int scrollY = (SCREEN_HEIGHT - 400) / 2;
    int scrollW = 400;
    int scrollH = 400;

    if (mx >= scrollX && mx <= scrollX + scrollW && my >= scrollY &&
        my <= scrollY + scrollH) {
      showChargeScroll = false;
      return;
    }
  }

  // -------- MENU BUTTON CLICKS (BG2) --------  //----------------------------------------my codes---------------------------------------------------
  if (currentBg == 2) {
    for (int i = 0; i < NUM_BUTTONS; i++) {
      int y = btnStartY - i * (btnH + btnGap);
      if (mx >= btnX && mx <= btnX + btnW && my >= y && my <= y + btnH) {
        if (i == 0)
          currentBg = 5;
        else if (i == 1)
          currentBg = 6;
        else if (i == 2)
          currentBg = 7;
        else
          exit(0);
        return;
      }
    }
  }

  // -------- BACK BUTTON CLICK --------
  if ((currentBg == 5 || currentBg == 6 || currentBg == 7) &&
      isInsideCircle(mx, my)) {
    currentBg = 2;
    return;
  }
}

void iMouseMove(int mx, int my) {}
void iSpecialKeyboard(unsigned char key) {}
void iPassiveMouseMove(int mx, int my) {
  if (currentBg == 2) {                    //----------------------------------------my codes---------------------------------------------------
    for (int i = 0; i < NUM_BUTTONS; i++) {
      int y = btnStartY - i * (btnH + btnGap);
      btnIsHover[i] =
          (mx >= btnX && mx <= btnX + btnW && my >= y && my <= y + btnH);
    }
  }

  if (currentBg == 5 || currentBg == 6 || currentBg == 7)
    backHover = isInsideCircle(mx, my);
}

/* -------------------- INIT -------------------- */
void loadButtons() {
  btnNormal[0] = iLoadImage("Images/btn1.png");
  btnNormal[1] = iLoadImage("Images/btn2.png");
  btnNormal[2] = iLoadImage("Images/btn3.png");
  btnNormal[3] = iLoadImage("Images/btn4.png");

  btnHover[0] = iLoadImage("Images/btn1_hover.png");
  btnHover[1] = iLoadImage("Images/btn2_hover.png");
  btnHover[2] = iLoadImage("Images/btn3_hover.png");
  btnHover[3] = iLoadImage("Images/btn4_hover.png");

  backBtn = iLoadImage("Images/back.png");
  backBtnHover = iLoadImage("Images/back_hover.png");
}
void initBackground() {
  bg1 = iLoadImage("Images/bg1.jpg");
  bg2 = iLoadImage("Images/bg2.jpg");
  bg41 = iLoadImage("Images/bg4.1.png");
  bg5 = iLoadImage("Images/bg5.png");
  bg6 = iLoadImage("Images/bg6.png");
  bg7 = iLoadImage("Images/bg7.png");
  // Story / instruction slides
  storyImgs[0] = iLoadImage("Images/story-1.png");
  storyImgs[1] = iLoadImage("Images/story-2.png");
  storyImgs[2] = iLoadImage("Images/story-3.png");
  storyImgs[3] = iLoadImage("Images/story-4.png");
  storyImgs[4] = iLoadImage("Images/story-5.png");
  storyImgs[5] = iLoadImage("Images/story-6.png");
  storyImgs[6] = iLoadImage("Images/instruction.png");
  gameOverImg = iLoadImage("Images/gameover.png");
  signpostImg = iLoadImage("Images/dangerpost.png");
  winFlagImg = iLoadImage("Images/win.png");
  winnerImg = iLoadImage("Images/winner.jfif");
  hudLifeImg = iLoadImage("Images/token/life.png");
  hudPunchImg = iLoadImage("Images/token/charged punch.png");
  tokenImg = iLoadImage("Images/token/token.png");
  treasureImg = iLoadImage("Images/token/treasure.png");
  // Player images
  playerSide = iLoadImage("Images/side.png");
  playerSideLeft = iLoadImage("Images/sideleft.png");
  playerSideM = iLoadImage("Images/sidem.png");
  playerSideLeftM = iLoadImage("Images/sideleftm.png");

  punchFistImg = iLoadImage("Images/fist.png");
  punchHitImg = iLoadImage("Images/punchf.png");
  punchFistImgM = iLoadImage("Images/fistm.png");
  punchHitImgM = iLoadImage("Images/punchff.png");

  chargedPunchImg = iLoadImage("Images/chargedfront.png");
  chargeScrollImg = iLoadImage("Images/chargescroll.png");

  chargedFistImg = iLoadImage("Images/chargedfist.png");
  chargedPunchImgSeq = iLoadImage("Images/chargedpunch.png");

  chargedPunchImgM = iLoadImage("Images/chargedfrontm.png");
  chargedFistImgM = iLoadImage("Images/chargedfistm.png");
  chargedPunchImgSeqM = iLoadImage("Images/chargedpunchm.png");

  playerDeadImg = iLoadImage("Images/player_dead.png");

  loadButtons(); // calling

  enemy1Img = iLoadImage("Images/enemy1.png");
  enemy1DeadImg = iLoadImage("Images/enemy1_dead.png");

  enemy2LeftImg = iLoadImage("Images/enemy2_left.png");
  enemy2RightImg = iLoadImage("Images/enemy2_right.png");
  enemy2DeadImg = iLoadImage("Images/enemy2_dead.png");

  enemy3IdleImg = iLoadImage("Images/enemy3.png");
  enemy3WalkImg = iLoadImage("Images/enemy3_walk.png");
  enemy3FistImg = iLoadImage("Images/enemy3_fist.png");
  enemy3PunchImg = iLoadImage("Images/enemy3_punch.png");
  enemy3IdleImgM = iLoadImage("Images/enemy3m.png");
  enemy3WalkImgM = iLoadImage("Images/enemy3_walkm.png");
  enemy3FistImgM = iLoadImage("Images/enemy3_fistm.png");
  enemy3PunchImgM = iLoadImage("Images/enemy3_punchm.png");
  enemy3DeadImg = iLoadImage("Images/enemy3_dead.png");

  enemy4Img = iLoadImage("Images/enemy4.png");
  enemy4DeadImg = iLoadImage("Images/enemy4_dead.png");

  // -------- LOAD DRAGON FRAMES --------
  char dpath[64];
  for (int i = 0; i < DRAGON_FRAME_COUNT; i++) {
    // dr1.png ... dr12.png
    sprintf_s(dpath, "Images/dragon/dr%d.png", i + 1);
    dragonFrames[i] = iLoadImage(dpath);
    dragonDeadImg = iLoadImage("Images/dragon/dr_dead.png");
  }

  // Timers
  iSetTimer(16, updateJump);
  iSetTimer(100, updateChargedTimer);
  iSetTimer(220, updateDragon); // dragon animation timer
  iSetTimer(60, updateEnemy1);
  iSetTimer(40, updateEnemy3);
  iSetTimer(40, updateChargedHitWindow);
  iSetTimer(40, updateEnemy2);
  iSetTimer(60, updateEnemy4);
  iSetTimer(100, updateGameOverDelay);
  iSetTimer(40, checkWinFlagCollision);
  // -------- INIT ENEMY3 POSITION --------
  Bridge &b9 = bridges[ENEMY3_BRIDGE_INDEX]; // 9th bridge
  // Position enemy3 AFTER the 9th bridge (ground between 9th and 10th)
  enemy3X = b9.maxX + 50; // Start 50 pixels to the right of 9th bridge

  // -------- START BACKGROUND MUSIC --------   //----------------------------------------my codes---------------------------------------------------
  initCollectibles();
  playMusic();
  initPunchSound();
}

void respawnPlayer() {              //----------------------------------------my codes---------------------------------------------------
  playerX = PLAYER_START_X_BG41;
  playerY = PLAYER_START_Y_BG41;
  cameraX = 0;

  playerAlive = true;
  gameStarted = true;

  isJumping = false;
  jumpVelocity = 0;

  punchState = 0;
  chargingPunch = false;
  chargedSequenceActive = false;

  killedByEnemy1 = false;
  killedByEnemy2 = false;
  killedByEnemy3 = false;
  killedByEnemy4 = false;
  killedByDragon = false;
  enemy2BodyCollisionCount = 0;
  enemy2WasColliding = false;
}

void shuffleEnemySprites() {
  swapEnemySprites = (rand() % 2 == 0); // 50/50 chance each run
}

void handlePlayerDeath() {
  if (!playerAlive && !deathWaiting && !gameOverTriggered) {
    deathWaiting = true;
    deathDelayCounter = 0;
  }
}

void updateGameOverDelay() {
  if (deathWaiting && !gameOverTriggered) {
    deathDelayCounter++;

    if (deathDelayCounter >= DEATH_DELAY_TIME) {
      int livesToLose = 1;

      if (killedByEnemy3 || killedByDragon)
        livesToLose = 2;

      playerLives -= livesToLose;

      if (playerLives < 0)
        playerLives = 0;

      if (playerLives > 0) {
        deathWaiting = false;
        respawnPlayer();
      } else {
        gameOverTriggered = true;
        gameOverDelayCounter = 0;
      }
    }
  }
  if (gameOverTriggered && !gameOverScreen) {
    gameOverDelayCounter++;

    if (gameOverDelayCounter >= 15) {
      gameOverScreen = true;
      currentBg = 8;
    }
  }
}

/* -------------------- MAIN -------------------- */
int main() {
  srand(time(NULL));
  iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Menu + Game");
  initBackground();
  iStart();
  return 0;
}