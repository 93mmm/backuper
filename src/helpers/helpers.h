#include <string>

int GetJSONPath(const std::string &action, std::string &path);
int SetJSONPath(const std::string &action, const std::string &path);
int GetAllJSONPaths(std::string &backup, std::string &restore);
