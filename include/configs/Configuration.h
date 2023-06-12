#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <fstream>

#include "../../libs/json/json.hpp"

/**
 * @class Configuration
 * @brief Class for managing configurations stored in a JSON file.
 */
class Configuration {
public:
    /**
     * @brief Constructor that loads configurations from a JSON file.
     * @param filename The name of the JSON file.
     */
    Configuration(const std::string& filename) : filename_(filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            file >> config_;
            file.close();
        }
    }

    /**
     * @brief Get a configuration value.
     * @param key The configuration key.
     * @param default_value The default value to return if the key is not found.
     * @return The configuration value.
     */
    template<typename T>
    T get(const std::string& key, const T& default_value) {
        if (config_.contains(key)) {
            return config_[key].get<T>();
        }
        return default_value;
    }

    /**
     * @brief Set a configuration value.
     * @param key The configuration key.
     * @param value The configuration value.
     */
    template<typename T>
    void set(const std::string& key, const T& value) {
        config_[key] = value;
    }

    /**
     * @brief Save the configurations to the JSON file.
     */
    void save() {
        std::ofstream file(filename_);
        if (file.is_open()) {
            file << config_;
            file.close();
        }
    }

private:
    std::string filename_;
    nlohmann::json config_;
};

#endif