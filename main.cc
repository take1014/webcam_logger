#include <filesystem>
#include <fstream>

#include "camera.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "you must set config.json path" << std::endl;
    return 0;
  }

  std::string config_path = std::string(argv[1]);
  if (!std::filesystem::exists(config_path)) {
    std::cerr << "do not exists config.json path: " << config_path << std::endl;
    return 0;
  }

  std::ifstream config_file(config_path);
  Json::Value root;
  config_file >> root;

  if (!root.isMember("CAMERAD")) {
    std::cerr << "Error: 'CAMERAD' key not found in JSON." << std::endl;
    return 0;
  }

  Json::Value camData = root["CAMERAD"];
  // cam_outer: HD Pro Webcam C920
  // check v4l2-ctl --list-devices
  CameraThread cam;
  bool isInitCam = cam.init(camData);
  if (isInitCam) {
    cam.start();
  } else {
    std::cerr << "Do not open camera" << std::endl;
  }
}
