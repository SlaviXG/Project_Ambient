#ifndef CONFIGURATION_CHAIN_H_
#define CONFIGURATION_CHAIN_H_

#include <vector>

#include "Configuration.h"
#include "ConfigurationHandler.h"


/**
 * @class ConfigurationChain
 * @brief Class for managing a chain of ConfigurationHandlers.
 */
class ConfigurationChain {
public:
    /**
     * @brief Add a ConfigurationHandler to the chain.
     * @param handler The ConfigurationHandler.
     */
    void addHandler(ConfigurationHandler* handler) {
        handlers_.push_back(handler);
    }

    /**
     * @brief Load configurations for all handlers in the chain.
     * @param config The Configuration object.
     */
    void loadConfiguration(Configuration& config) {
        for (auto handler : handlers_) {
            handler->loadConfiguration(config);
        }
    }

    /**
     * @brief Save configurations for all handlers in the chain.
     * @param config The Configuration object.
     */
    void saveConfiguration(Configuration& config) {
        for (auto handler : handlers_) {
            handler->saveConfiguration(config);
        }
    }

private:
    std::vector<ConfigurationHandler*> handlers_;
};


#endif  