#include "helpers.h"
#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream>
#include <CoreFoundation/CFBundle.h>

std::string ConfigPath() {
  CFURLRef resourceURL = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
  char resourcePath[PATH_MAX];
  if (CFURLGetFileSystemRepresentation(resourceURL, true, (UInt8 *)resourcePath, PATH_MAX)) {
    if (resourceURL != NULL) {
      CFRelease(resourceURL);
    }
    return (std::string)resourcePath + "/config.json";
  }
  return "";
}

int ReadJSON(const std::string &filename, nlohmann::json &json_data) {
  std::ifstream file(filename);
  if (not file.is_open()) {
    return 1;
  }
  json_data = nlohmann::json::parse(file);
  file.close();
  return 0;
}

int WriteJSON(const std::string &filename, const nlohmann::json &json_data) {
  std::ofstream file(filename);
  if (not file.is_open()) {
    return 1;
  }

  file << json_data;
  file.close();

  return 0;
}

int GetJSONPath(const std::string &action, std::string &path) {
  nlohmann::json config;

  if (ReadJSON(ConfigPath(), config)) {
    return 1;
  }

  path = config[action + "_path"];
  return 0;
}

int SetJSONPath(const std::string &action, const std::string &path) {
  std::string config_path = ConfigPath();
  nlohmann::json config;

  if (ReadJSON(config_path, config)) {
    return 1;
  }

  config[action + "_path"] = path;

  if (WriteJSON(config_path, config)) {
    return 1;
  }

  std::cout << config.dump(2) << std::endl;
  return 0;
}
