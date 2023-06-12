/**
 * @file default.h
 * @author Yarik Kishchuk (kshchuk@gmail.com)
 * @brief The file stores the default settings that are used when the configs json file is missing.
 * @version 0.1
 * @date 2023-06-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef DEFAULT_H_
#define DEFAULT_H_

#include "Configuration.h"
#include "ConfigurationHandler.h"

static int kCellSize = 4;               ///< Default size of a cell
static int kFps = 10;                   ///< Frames per second of the game update
static int kViewPadding = 2;            ///< Padding around the view
static size_t kStartingCellCount = 200; ///< Initial cell count when the game starts

static int kMaxEnergy = 2000;
static int kMinEnergy = 1600;

static int kSteps = 5;                 //
static int kMoveCost = 5;              // count of energy, that cell will loose after move
static int kPhotosynthesisAdd = 25;    // count of energy, that cell will recieve after Photosynthes
static float kAttackCoefficient = 0.5; // opponent energy -= currentEnergy * kAC + minDamage
static float kAttackCost = 0.01;       // 1/10 * currentEnergy
static int kDuplicationCost = 1200;
static int kPrise = 500;        // + energy after killing
static int kMovesToDeath = 800; // every cell can make at max 250 actions
static int kMinDamage = 1000;
static int kDelay = 10;

/**
 * @brief The Defaults class
 *
 * Used for loading and storing default values to json file
 *
 */
class Defaults : public ConfigurationHandler
{
public:
    /**
     * @brief Load configurations from a Configuration object.
     * @param config The Configuration object.
     */
    void loadConfiguration(Configuration &config) override
    {
        static const int kCellSize = config.get<int>("kCellSize", kCellSize);
        kFps = config.get<int>("kFps", kFps);
        kViewPadding = config.get<int>("kViewPadding", kViewPadding);
        kStartingCellCount = config.get<size_t>("kStartingCellCount", kStartingCellCount);

        kMaxEnergy = config.get<int>("kMaxEnergy", kMaxEnergy);
        kMinEnergy = config.get<int>("kMinEnergy", kMinEnergy);

        kSteps = config.get<int>("kSteps", kSteps);
        kMoveCost = config.get<int>("kMoveCost", kMoveCost);
        kPhotosynthesisAdd = config.get<int>("kPhotosynthesisAdd", kPhotosynthesisAdd);
        kAttackCoefficient = config.get<float>("kAttackCoefficient", kAttackCoefficient);
        kAttackCost = config.get<float>("kAttackCost", kAttackCost);
        kDuplicationCost = config.get<int>("kDuplicationCost", kDuplicationCost);
        kPrise = config.get<int>("kPrise", kPrise);
        kMovesToDeath = config.get<int>("kMovesToDeath", kMovesToDeath);
        kMinDamage = config.get<int>("kMinDamage", kMinDamage);
        kDelay = config.get<int>("kDelay", kDelay);
    }

    /**
     * @brief Save configurations to a Configuration object.
     * @param config The Configuration object.
     */
    void saveConfiguration(Configuration &config) const override
    {
        config.set<int>("kCellSize", kCellSize);
        config.set<int>("kFps", kFps);
        config.set<int>("kViewPadding", kViewPadding);
        config.set<size_t>("kStartingCellCount", kStartingCellCount);

        config.set<int>("kMaxEnergy", kMaxEnergy);
        config.set<int>("kMinEnergy", kMinEnergy);

        config.set<int>("kSteps", kSteps);
        config.set<int>("kMoveCost", kMoveCost);
        config.set<int>("kPhotosynthesisAdd", kPhotosynthesisAdd);
        config.set<float>("kAttackCoefficient", kAttackCoefficient);
        config.set<float>("kAttackCost", kAttackCost);
        config.set<int>("kDuplicationCost", kDuplicationCost);
        config.set<int>("kPrise", kPrise);
        config.set<int>("kMovesToDeath", kMovesToDeath);
        config.set<int>("kMinDamage", kMinDamage);
        config.set<int>("kDelay", kDelay);
    }
};

#endif
