#ifndef CAMERA_H
#define CAMERA_H

#include <json/json.h>

#include <atomic>
#include <iostream>
#include <thread>

#include "opencv2/opencv.hpp"

class CameraThread {
 public:
  CameraThread();
  ~CameraThread();

  bool init(const Json::Value &camData);
  void start();
  void stop();

 private:
  cv::VideoCapture cap_outer_;
  cv::VideoWriter writer_;
  void event_loop();
};
#endif /* CAMERA_H */
