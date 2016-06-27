#include <string>
#include <vector>

class FsSync
{
  void removeOrphanedFiles(std::string destination, std::string path,
    std::vector<std::string>& sources);

  void removeOrphanedDirectories(std::string destination,
    std::string path, std::vector<std::string>& sources);

  void createMissingDirectories(std::string destination,
    std::string path, std::vector<std::string>& sources);

  void copyRequiredFiles(std::string destination,
    std::string path, std::vector<std::string>& sources);

public:
  void sync(std::string destination, std::vector<std::string>& sources);

};
