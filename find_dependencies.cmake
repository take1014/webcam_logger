set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# you must install dependencies.
# ========== JSONCPP ==========
# git clone https://github.com/open-source-parsers/jsoncpp.git
# ========== ZEROMQ ==========
# git clone https://github.com/zeromq/libzmq.git
# git clone https://github.com/zeromq/cppzmq.git
include_directories("/usr/local/include")
link_directories("/usr/local/lib")

find_package(Threads REQUIRED)