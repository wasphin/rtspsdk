# Module: RTSP
set(LIBNAME RTSP)
set(POCO_LIBNAME "Poco${LIBNAME}")

set(LIB_HDRS
  include/Poco/RTSP.h
  include/Poco/RTSP/RTSP.h
  include/Poco/RTSP/RTSPBasicStreamBuf.h
  include/Poco/RTSP/RTSPClientSession.h
  include/Poco/RTSP/RTSPFixedLengthStream.h
  include/Poco/RTSP/RTSPHeaderStream.h
  include/Poco/RTSP/RTSPMessage.h
  include/Poco/RTSP/RTSPRequest.h
  include/Poco/RTSP/RTSPResponse.h
  include/Poco/RTSP/RTSPSessionFactory.h
  include/Poco/RTSP/RTSPSession.h
  include/Poco/RTSP/RTSPSessionInstantiator.h
  include/Poco/RTSP/RTSPStream.h)

set(LIB_SRCS
  src/RTSPClientSession.cpp
  src/RTSPFixedLengthStream.cpp
  src/RTSPHeaderStream.cpp
  src/RTSPMessage.cpp
  src/RTSPRequest.cpp
  src/RTSPResponse.cpp
  src/RTSPSession.cpp
  src/RTSPSessionFactory.cpp
  src/RTSPSessionInstantiator.cpp
  src/RTSPStream.cpp)

add_library("${LIBNAME}" SHARED ${LIB_HDRS} ${LIB_SRCS})
add_library("${POCO_LIBNAME}" ALIAS "${LIBNAME}")
set_target_properties("${LIBNAME}"
  PROPERTIES
    VERSION ${PROJECT_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
    OUTPUT_NAME ${POCO_LIBNAME}
    DEFINE_SYMBOL RTSP_EXPORTS)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories("${LIBNAME}"
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include
    $<INSTALL_INTERFACE:include>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries("${LIBNAME}" Poco::Foundation Poco::Net)

if(ENABLE_TESTS)
  add_subdirectory(samples)
  add_subdirectory(testsuite)
endif()
