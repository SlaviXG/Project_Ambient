#ifndef CONFIGURATION_HANDLER_H_
#define CONFIGURATION_HANDLER_H_

#include "Configuration.h"

class ConfigurationHandler {
public:
    virtual void loadConfiguration(Configuration& config) = 0;
    virtual void saveConfiguration(Configuration& config) = 0;
};


#endif  