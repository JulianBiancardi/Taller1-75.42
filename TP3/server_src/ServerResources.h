#ifndef __SERVER_RESOURCE_H__
#define __SERVER_RESOURCE_H__

#include <map>
#include <mutex>
#include <string>

//--------------------------------------------------------------------------------------
class ServerResources {
 private:
  std::mutex mutex;
  std::map<std::string, std::string> resources;

 public:
  explicit ServerResources(const std::string& template_root);

  /*Agrega un recurso con su cuerpo asociado. Si el recurso es "/" no dará un
   * error debido a que no podemos modificar el root.*/
  void addResource(const std::string& resource, const std::string& body);
  /*Obtiene el cuerpo del recurso solicitado*/
  std::string getBody(const std::string& resource);

  ~ServerResources();
};

#endif  // __SERVER_RESOURCE_H__
//--------------------------------------------------------------------------------------
