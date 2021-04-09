#include "ServerResources.h"

#include <fstream>
#include <iostream>
#include <sstream>  //std::stringstream
#include <stdexcept>

#define ROOT "/"

//--------------------------------------------------------------------------------------
ServerResources::ServerResources(const std::string& template_root) {
  std::fstream file;
  file.open(template_root);
  if (!file.is_open()) {
    throw std::runtime_error("No such file exist in the directory");
  }

  std::stringstream strStream;
  strStream << file.rdbuf();  // read the file
  std::string root_content = strStream.str();

  resources[ROOT] = root_content;
}

void ServerResources::addResource(const std::string& resource,
                                  const std::string& body) {
  std::lock_guard<std::mutex> lock(mutex);
  if (resource == ROOT) {
    throw std::runtime_error(
        "Error in function addResource, the root can not be modified");
  }
  resources[resource] = body;
}

std::string ServerResources::getBody(const std::string& resource) {
  std::lock_guard<std::mutex> lock(mutex);
  std::string body;
  body = resources.at(resource);
  return body;
}

ServerResources::~ServerResources() {}
//--------------------------------------------------------------------------------------
