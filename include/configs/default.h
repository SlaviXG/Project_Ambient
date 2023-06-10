#ifndef DEFAULT_H_
#define DEFAULT_H_

constexpr int kCellSize = 4;               ///< Default size of a cell
constexpr int kFps = 10;                   ///< Frames per second of the game update
constexpr int kViewPadding = 2;            ///< Padding around the view
constexpr size_t kStartingCellCount = 200; ///< Initial cell count when the game starts

constexpr int kMaxEnergy = 2000;
constexpr int kMinEnergy = 1600;

constexpr int kSteps = 5;                 //
constexpr int kMoveCost = 5;              // count of energy, that cell will loose after move
constexpr int kPhotosynthesisAdd = 25;    // count of energy, that cell will recieve after Photosynthes
constexpr float kAttackCoefficient = 0.5; // opponent energy -= currentEnergy * kAC + minDamage
constexpr float kAttackCost = 0.01;       // 1/10 * currentEnergy
constexpr int kDuplicationCost = 1200;
constexpr int kPrise = 500;       // + energy after killing
constexpr int movesToDeath = 800; // every cell can make at max 250 actions
constexpr int minDamage = 1000;
constexpr int kDelay = 10;

#endif