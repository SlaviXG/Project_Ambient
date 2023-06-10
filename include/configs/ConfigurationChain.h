#ifndef CONFIGURATION_CHAIN_H_
#define CONFIGURATION_CHAIN_H_

#include <vector>

#include "Configuration.h"
#include "ConfigurationHandler.h"


class ConfigurationChain {
public:
    void addHandler(ConfigurationHandler* handler) {
        handlers_.push_back(handler);
    }

    void loadConfiguration(Configuration& config) {
        for (auto handler : handlers_) {
            handler->loadConfiguration(config);
        }
    }

    void saveConfiguration(Configuration& config) {
        for (auto handler : handlers_) {
            handler->saveConfiguration(config);
        }
    }

private:
    std::vector<ConfigurationHandler*> handlers_;
};


#endif  