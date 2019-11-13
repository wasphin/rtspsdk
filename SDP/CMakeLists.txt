# Module: RTSP
set(LIBNAME SDP)
set(POCO_LIBNAME "Poco${LIBNAME}")

set(LIB_HDRS
  include/Poco/SDP.h
  include/Poco/SDP/AddressRange.h
  include/Poco/SDP/AttributeField.h
  include/Poco/SDP/BandwidthField.h
  include/Poco/SDP/BandwidthModifiers.h
  include/Poco/SDP/Common.h
  include/Poco/SDP/ConnectionField.h
  include/Poco/SDP/EMailField.h
  include/Poco/SDP/EncryptionMethods.h
  include/Poco/SDP/Field.h
  include/Poco/SDP/FieldFactory.h
  include/Poco/SDP/InfoField.h
  include/Poco/SDP/KeyField.h
  include/Poco/SDP/MediaDescription.h
  include/Poco/SDP/MediaField.h
  include/Poco/SDP/MediaTypes.h
  include/Poco/SDP/NTPTime.h
  include/Poco/SDP/OriginField.h
  include/Poco/SDP/PhoneField.h
  include/Poco/SDP/PortRange.h
  include/Poco/SDP/RtpAvpConstants.h
  include/Poco/SDP/SDP.h
  include/Poco/SDP/SessionDescription.h
  include/Poco/SDP/SessionNameField.h
  include/Poco/SDP/TimeDescription.h
  include/Poco/SDP/TimeField.h
  include/Poco/SDP/TimeRepetitionField.h
  include/Poco/SDP/TimeZoneAdjustment.h
  include/Poco/SDP/TimeZoneAdjustmentField.h
  include/Poco/SDP/URIField.h
  include/Poco/SDP/VersionField.h)

set(LIB_SRCS
  src/AddressRange.cpp
  src/AttributeField.cpp
  src/BandwidthField.cpp
  src/BandwidthModifiers.cpp
  src/Common.cpp
  src/ConnectionField.cpp
  src/EMailField.cpp
  src/EncryptionMethods.cpp
  src/Field.cpp
  src/FieldFactory.cpp
  src/InfoField.cpp
  src/KeyField.cpp
  src/MediaDescription.cpp
  src/MediaField.cpp
  src/MediaTypes.cpp
  src/NTPTime.cpp
  src/OriginField.cpp
  src/PhoneField.cpp
  src/PortRange.cpp
  src/RtpAvpConstants.cpp
  src/SessionDescription.cpp
  src/SessionNameField.cpp
  src/TimeDescription.cpp
  src/TimeField.cpp
  src/TimeRepetitionField.cpp
  src/TimeZoneAdjustment.cpp
  src/TimeZoneAdjustmentField.cpp
  src/URIField.cpp
  src/VersionField.cpp)

add_library("${LIBNAME}" SHARED ${LIB_HDRS} ${LIB_SRCS})
add_library("${POCO_LIBNAME}" ALIAS "${LIBNAME}")
set_target_properties("${LIBNAME}"
  PROPERTIES
    VERSION ${PROJECT_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
    OUTPUT_NAME ${POCO_LIBNAME}
    DEFINE_SYMBOL SDP_EXPORTS)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories("${LIBNAME}"
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include
    $<INSTALL_INTERFACE:include>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries("${LIBNAME}" Poco::Foundation Poco::Net Poco::Util)

if(ENABLE_TESTS)
  add_subdirectory(samples)
  add_subdirectory(testsuite)
endif()
