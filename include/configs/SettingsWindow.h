#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QValidator>

#include "Configuration.h"
#include "ConfigurationChain.h"

/**
 * @class SettingsWindow
 * @brief A window for viewing and changing application settings.
 *
 * The window contains a form with spin boxes for each setting.
 * The settings are grouped into categories, and each category has its own group box.
 * The window also contains "Save" and "Cancel" buttons.
 * The settings are loaded from a JSON file when the window is shown, and saved to the JSON file when the "Save" button is clicked.
 * The "Cancel" button closes the window without saving the changes.
 */
class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param configChain The ConfigurationChain object for loading and saving configurations.
     * @param config The Configuration object for getting and setting configuration values.
     * @param parent The parent widget.
     */
    explicit SettingsWindow(ConfigurationChain &configChain, Configuration *config, QWidget *parent = nullptr);

    /**
     * @brief Event handler for the show event.
     * @param event The show event.
     *
     * This function is called when the window is shown.
     * It loads the settings from the JSON file and sets the values of the spin boxes.
     */
    void showEvent(QShowEvent *event) override;

private slots:

    /**
     * @brief Slot for the "Save" button clicked signal.
     *
     * This function is called when the "Save" button is clicked.
     * It gets the values of the spin boxes and saves the settings to the JSON file.
     */
    void saveSettings();

private:
    ConfigurationChain &configChain_; ///< The ConfigurationChain object for loading and saving configurations.
    Configuration *config;            ///< The Configuration object for getting and setting configuration values.

    QSpinBox *kCellSizeBox_;
    QSpinBox *kFpsBox_;
    QSpinBox *kViewPaddingBox_;
    QSpinBox *kStartingCellCountBox_;
    QSpinBox *kEnvironmentWidthBox_;
    QSpinBox *kEnvironmentHeightBox_;
    QSpinBox *kMaxEnergyBox_;
    QSpinBox *kMinEnergyBox_;
    QSpinBox *kStepsBox_;
    QSpinBox *kMoveCostBox_;
    QSpinBox *kPhotosynthesisAddBox_;
    QDoubleSpinBox *kAttackCoefficientBox_;
    QDoubleSpinBox *kAttackCostBox_;
    QSpinBox *kDuplicationCostBox_;
    QSpinBox *kPriseBox_;
    QSpinBox *kMovesToDeathBox_;
    QSpinBox *kMinDamageBox_;
    QSpinBox *kDelayBox_;
    QPushButton *saveButton_;
};

#endif // SETTINGSWINDOW_H
