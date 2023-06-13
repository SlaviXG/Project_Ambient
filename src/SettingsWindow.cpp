#include "../include/configs/SettingsWindow.h"

SettingsWindow::SettingsWindow(ConfigurationChain &configChain, Configuration *config, QWidget *parent)
    : QDialog(parent), configChain_(configChain), config(config)
{
    setWindowTitle("Settings");
    setMinimumWidth(400); // Set minimum dialog width

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Create a group box for each category of settings
    QGroupBox *gameSettingsBox = new QGroupBox("Game Settings", this);
    QGroupBox *environmentSettingsBox = new QGroupBox("Environment Settings", this);
    QGroupBox *energySettingsBox = new QGroupBox("Energy Settings", this);
    QGroupBox *actionSettingsBox = new QGroupBox("Action Settings", this);

    // Create form layouts for each group box
    QFormLayout *gameSettingsLayout = new QFormLayout(gameSettingsBox);
    QFormLayout *environmentSettingsLayout = new QFormLayout(environmentSettingsBox);
    QFormLayout *energySettingsLayout = new QFormLayout(energySettingsBox);
    QFormLayout *actionSettingsLayout = new QFormLayout(actionSettingsBox);

    // Create spin boxes for each setting
    kCellSizeBox_ = new QSpinBox(this);
    kCellSizeBox_->setRange(1, 100); // Set range and default value
    kCellSizeBox_->setValue(4);
    gameSettingsLayout->addRow("Cell Size", kCellSizeBox_);

    kFpsBox_ = new QSpinBox(this);
    kFpsBox_->setRange(1, 1000);
    kFpsBox_->setValue(10);
    gameSettingsLayout->addRow("FPS", kFpsBox_);

    kViewPaddingBox_ = new QSpinBox(this);
    kViewPaddingBox_->setRange(1, 1000);
    kViewPaddingBox_->setValue(2);
    gameSettingsLayout->addRow("View Padding", kViewPaddingBox_);

    kStartingCellCountBox_ = new QSpinBox(this);
    kStartingCellCountBox_->setRange(1, 1000000000);
    kStartingCellCountBox_->setValue(200);
    gameSettingsLayout->addRow("Starting Cell Count", kStartingCellCountBox_);

    kEnvironmentWidthBox_ = new QSpinBox(this);
    kEnvironmentWidthBox_->setRange(1, 100000000);
    kEnvironmentWidthBox_->setValue(1000);
    environmentSettingsLayout->addRow("Environment Width", kEnvironmentWidthBox_);

    kEnvironmentHeightBox_ = new QSpinBox(this);
    kEnvironmentHeightBox_->setRange(1, 100000000);
    kEnvironmentHeightBox_->setValue(1000);
    environmentSettingsLayout->addRow("Environment Height", kEnvironmentHeightBox_);

    kMaxEnergyBox_ = new QSpinBox(this);
    kMaxEnergyBox_->setRange(1, 1000000);
    kMaxEnergyBox_->setValue(2000);
    energySettingsLayout->addRow("Max Energy", kMaxEnergyBox_);

    kMinEnergyBox_ = new QSpinBox(this);
    kMinEnergyBox_->setRange(1, 10000);
    kMinEnergyBox_->setValue(1600);
    energySettingsLayout->addRow("Min Energy", kMinEnergyBox_);

    kStepsBox_ = new QSpinBox(this);
    kStepsBox_->setRange(1, 10000);
    kStepsBox_->setValue(5);
    actionSettingsLayout->addRow("Steps", kStepsBox_);

    kMoveCostBox_ = new QSpinBox(this);
    kMoveCostBox_->setRange(1, 100000);
    kMoveCostBox_->setValue(5);
    actionSettingsLayout->addRow("Move Cost", kMoveCostBox_);

    kPhotosynthesisAddBox_ = new QSpinBox(this);
    kPhotosynthesisAddBox_->setRange(1, 1000000);
    kPhotosynthesisAddBox_->setValue(25);
    actionSettingsLayout->addRow("Photosynthesis Add", kPhotosynthesisAddBox_);

    kAttackCoefficientBox_ = new QDoubleSpinBox(this);
    kAttackCoefficientBox_->setRange(0.0, 1.0);
    kAttackCoefficientBox_->setSingleStep(0.1);
    kAttackCoefficientBox_->setValue(0.5);
    actionSettingsLayout->addRow("Attack Coefficient", kAttackCoefficientBox_);

    kAttackCostBox_ = new QDoubleSpinBox(this);
    kAttackCostBox_->setRange(0.0, 1.0);
    kAttackCostBox_->setSingleStep(0.01);
    kAttackCostBox_->setValue(0.01);
    actionSettingsLayout->addRow("Attack Cost", kAttackCostBox_);

    kDuplicationCostBox_ = new QSpinBox(this);
    kDuplicationCostBox_->setRange(1, 10000);
    kDuplicationCostBox_->setValue(1200);
    actionSettingsLayout->addRow("Duplication Cost", kDuplicationCostBox_);

    kPriseBox_ = new QSpinBox(this);
    kPriseBox_->setRange(1, 10000);
    kPriseBox_->setValue(500);
    actionSettingsLayout->addRow("Prise", kPriseBox_);

    kMovesToDeathBox_ = new QSpinBox(this);
    kMovesToDeathBox_->setRange(1, 100000);
    kMovesToDeathBox_->setValue(800);
    actionSettingsLayout->addRow("Moves To Death", kMovesToDeathBox_);

    kMinDamageBox_ = new QSpinBox(this);
    kMinDamageBox_->setRange(1, 1000000);
    kMinDamageBox_->setValue(1000);
    actionSettingsLayout->addRow("Min Damage", kMinDamageBox_);

    kDelayBox_ = new QSpinBox(this);
    kDelayBox_->setRange(1, 10000);
    kDelayBox_->setValue(10);
    actionSettingsLayout->addRow("Delay", kDelayBox_);

    // Add group boxes to main layout
    mainLayout->addWidget(gameSettingsBox);
    mainLayout->addWidget(environmentSettingsBox);
    mainLayout->addWidget(energySettingsBox);
    mainLayout->addWidget(actionSettingsBox);

    // Create buttons
    saveButton_ = new QPushButton("Save", this);
    connect(saveButton_, &QPushButton::clicked, this, &SettingsWindow::saveSettings);
    QPushButton *cancelButton = new QPushButton("Cancel", this);
    connect(cancelButton, &QPushButton::clicked, this, &SettingsWindow::close);

    // Add buttons to main layout
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(saveButton_);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);
}

void SettingsWindow::showEvent(QShowEvent *event)
{
    // Load settings when window is shown
    this->configChain_.saveConfiguration(*config);

    kCellSizeBox_->setValue(config->get<int>("kCellSize", 3));
    kFpsBox_->setValue(config->get<int>("kFps", 10));
    kViewPaddingBox_->setValue(config->get<int>("kViewPadding", 2));
    kStartingCellCountBox_->setValue(config->get<int>("kStartingCellCount", 200));
    kEnvironmentWidthBox_->setValue(config->get<int>("kEnvironmentWidth", 1000));
    kEnvironmentHeightBox_->setValue(config->get<int>("kEnvironmentHeight", 1000));
    kMaxEnergyBox_->setValue(config->get<int>("kMaxEnergy", 2000));
    kMinEnergyBox_->setValue(config->get<int>("kMinEnergy", 1600));
    kStepsBox_->setValue(config->get<int>("kSteps", 5));
    kMoveCostBox_->setValue(config->get<int>("kMoveCost", 5));
    kPhotosynthesisAddBox_->setValue(config->get<int>("kPhotosynthesisAdd", 25));
    kAttackCoefficientBox_->setValue(config->get<float>("kAttackCoefficient", 0.5));
    kAttackCostBox_->setValue(config->get<float>("kAttackCost", 0.01));
    kDuplicationCostBox_->setValue(config->get<int>("kDuplicationCost", 1200));
    kPriseBox_->setValue(config->get<int>("kPrise", 500));
    kMovesToDeathBox_->setValue(config->get<int>("kMovesToDeath", 800));
    kMinDamageBox_->setValue(config->get<int>("kMinDamage", 1000));
    kDelayBox_->setValue(config->get<int>("kDelay", 10));
}

void SettingsWindow::saveSettings()
{
    // Save settings when save button is clicked

    config->set<int>("kCellSize", kCellSizeBox_->value());
    config->set<int>("kFps", kFpsBox_->value());
    config->set<int>("kViewPadding", kViewPaddingBox_->value());
    config->set<int>("kStartingCellCount", kStartingCellCountBox_->value());
    config->set<int>("kEnvironmentWidth", kEnvironmentWidthBox_->value());
    config->set<int>("kEnvironmentHeight", kEnvironmentHeightBox_->value());
    config->set<int>("kMaxEnergy", kMaxEnergyBox_->value());
    config->set<int>("kMinEnergy", kMinEnergyBox_->value());
    config->set<int>("kSteps", kStepsBox_->value());
    config->set<int>("kMoveCost", kMoveCostBox_->value());
    config->set<int>("kPhotosynthesisAdd", kPhotosynthesisAddBox_->value());
    config->set<float>("kAttackCoefficient", kAttackCoefficientBox_->value());
    config->set<float>("kAttackCost", kAttackCostBox_->value());
    config->set<int>("kDuplicationCost", kDuplicationCostBox_->value());
    config->set<int>("kPrise", kPriseBox_->value());
    config->set<int>("kMovesToDeath", kMovesToDeathBox_->value());
    config->set<int>("kMinDamage", kMinDamageBox_->value());
    config->set<int>("kDelay", kDelayBox_->value());

    configChain_.loadConfiguration(*config);
}
