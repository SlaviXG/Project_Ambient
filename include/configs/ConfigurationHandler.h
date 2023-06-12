#ifndef CONFIGURATION_HANDLER_H_
#define CONFIGURATION_HANDLER_H_

#include "Configuration.h"

/**
 * @class ConfigurationHandler
 * @brief Interface for classes that need to load and save configurations.
 */
class ConfigurationHandler {
public:
    /**
     * @brief Load configurations from a Configuration object.
     * @param config The Configuration object.
     */
    virtual void loadConfiguration(Configuration& config) = 0;

    /**
     * @brief Save configurations to a Configuration object.
     * @param config The Configuration object.
     */
    virtual void saveConfiguration(Configuration& config) const = 0;
};


#endif  