#include "camera.h"

// timestamp
std::string getTimestampedFilename() {
    std::time_t t = std::time(nullptr);
    std::tm tm;
    localtime_r(&t, &tm); // Linux/macOS 用。Windows は localtime_s を使用

    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(4) << tm.tm_year + 1900
        << std::setw(2) << tm.tm_mon + 1
        << std::setw(2) << tm.tm_mday
        << std::setw(2) << tm.tm_hour
        << std::setw(2) << tm.tm_min
        << std::setw(2) << tm.tm_sec
        << "_cap.avi";
    return oss.str();
}

// constructor
CameraThread::CameraThread() {}

// destructor
CameraThread::~CameraThread() { stop(); }

bool CameraThread::init(const Json::Value &camData) {
  cap_outer_.open(camData["DEVICE"].asString());
  if (!cap_outer_.isOpened()) {
    std::cerr << "ERROR: Unable to OUTER camera." << std::endl;
    return false;
  }
  cap_outer_.set(cv::CAP_PROP_FRAME_WIDTH, camData["IMG_WIDTH"].asInt());
  cap_outer_.set(cv::CAP_PROP_FRAME_HEIGHT, camData["IMG_HEIGHT"].asInt());
  cap_outer_.set(cv::CAP_PROP_FPS, camData["FPS"].asInt());

  std::string filename = getTimestampedFilename();
  writer_.open(
            filename,
            cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), // H.264 (FFmpeg必須)
            // cv::VideoWriter::fourcc('X', '2', '6', '4'), // H.264 (FFmpeg必須)
            camData["FPS"].asInt(),
            cv::Size(camData["IMG_WIDTH"].asInt(), camData["IMG_HEIGHT"].asInt())
        );

  if (!writer_.isOpened()) {
      std::cerr << "VideoWriterを開けません（H.264コーデックがOpenCVに組み込まれているか確認）" << std::endl;
      return -1;
  }
  return true;
}

void CameraThread::event_loop() {
  while (true) {
    cv::Mat frame_outer;
    cap_outer_ >> frame_outer;

    if (!frame_outer.empty()) {
      cv::flip(frame_outer, frame_outer, 0);
      writer_.write(frame_outer);
    } else {
      std::cout << "do not capture a image" << std::endl;
    }
  }
}

void CameraThread::start() {
  std::cout << "CAMERA thread start." << std::endl;
  event_loop();
}

void CameraThread::stop() {
  writer_.release();
  cap_outer_.release();
}
