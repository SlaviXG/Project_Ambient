#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <fstream>

#include "../../libs/json/json.hpp"


class Configuration {
public:
    Configuration(const std::string& filename) : filename(filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            file >> config;
            file.close();
        }
    }

    template<typename T>
    T get(const std::string& key, const T& default_value) {
        if (config.contains(key)) {
            return config[key].get<T>();
        }
        return default_value;
    }

    template<typename T>
    void set(const std::string& key, const T& value) {
        config[key] = value;
    }

    void save() {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << config;
            file.close();
        }
    }

private:
    std::string filename;
    nlohmann::json config;
};

#endif