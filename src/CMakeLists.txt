cmake_minimum_required(VERSION 3.14)

project(SampleClientServerCommunicationWithSSL LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

add_executable(SampleClientServerCommunicationWithSSL
  main.cpp
  myserver.h myserver.cpp
  certificates/server.key certificates/server.csr certificates/server.crt certificates/ca.key certificates/ca.crt
)
target_link_libraries(SampleClientServerCommunicationWithSSL Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(SampleClientServerCommunicationWithSSL Qt${QT_VERSION_MAJOR}::Network)

include(GNUInstallDirs)
install(TARGETS SampleClientServerCommunicationWithSSL
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
