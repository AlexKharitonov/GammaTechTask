include(FetchContent)

set(FLATBUFFERS_GIT_URL "https://github.com/google/flatbuffers.git")
set(FLATBUFFERS_VERSION v23.1.21)

message(STATUS "flatbuffers setup...")
FetchContent_Declare(
  flatbuffers
  GIT_REPOSITORY ${FLATBUFFERS_GIT_URL}
  GIT_TAG        ${FLATBUFFERS_VERSION}
)

FetchContent_MakeAvailable(flatbuffers)

FetchContent_GetProperties(flatbuffers)
if(NOT flatbuffers_POPULATED)
  FetchContent_Populate(flatbuffers)
  add_subdirectory(${flatbuffers_SOURCE_DIR} ${flatbuffers_BINARY_DIR})
endif()

# Get the path to the flatc executable
set(FLATC "${flatbuffers_BINARY_DIR}/${CMAKE_BUILD_TYPE}/flatc")

# The program requires Qt to be installed, it's to big to pull it here.
set(QT_MAJOR_REQUIRED 6)
set(QT_MINOR_REQUIRED 4)
set(QT_PATCH_REQUIRED 3)

#set(QT_PATH "C:/Qt")
if(NOT QT_PATH)
  message(FATAL_ERROR "QT_PATH is not set but required, Ex. -DQT_PATH=C:/Qt")
endif()

set(QT_MIN_REQUIRED_VERSION ${QT_MAJOR_REQUIRED}.${QT_MINOR_REQUIRED}.${QT_PATCH_REQUIRED})
set(QT_VERSION_PATH "${QT_PATH}/${QT_MIN_REQUIRED_VERSION}")
set(QT_MSVC_PATH "${QT_VERSION_PATH}/msvc2019_64")
SET(QT_WINDEPLOY_PATH "${QT_MSVC_PATH}/bin/windeployqt.exe")

list(APPEND CMAKE_PREFIX_PATH "${QT_MSVC_PATH}/lib/cmake/Qt${QT_MAJOR_REQUIRED}")