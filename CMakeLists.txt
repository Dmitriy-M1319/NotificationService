cmake_minimum_required(VERSION 3.20)
project(NotifyService)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20 REQUIRED)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost)
find_package(SQLite3)
find_package(nlohmann_json)

include_directories (SYSTEM ${Boost_INCLUDE_DIR})

set(HEADERS utils/SqlException.h
    Note.h
    INotificationRepository.h
    NotificationRepository.h
    TimerService.h
    INotifier.h
    GNotifier.h
    ISerializer.h
    Serializer.h
    MessageReceiver.h
)

add_executable(${PROJECT_NAME}
    utils/SqlException.cpp
    Note.cpp
    NotificationRepository.cpp
    TimerService.cpp
    GNotifier.cpp
    Serializer.cpp
    MessageReceiver.cpp
    main.cpp
)

add_executable(sender sender.cpp)

target_link_libraries(${PROJECT_NAME} 
    ${BOOST_LIBRARIES} 
    ${SQLITE3_LIBRARIES} 
    vsqlitepp
    nlohmann_json::nlohmann_json
)
target_link_libraries(sender ${BOOST_LIBRARIES})

