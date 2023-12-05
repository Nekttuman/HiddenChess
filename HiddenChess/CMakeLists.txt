cmake_minimum_required(VERSION 3.26)
project(HiddenChess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#set(CMAKE_PREFIX_PATH "D:/Zona_Downloads/Qt-1/5.15.2/vs_/msvc2019_64")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Network
        Multimedia
        WebSockets
        REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/Source/Widgets/ChatWidget)
include_directories(${CMAKE_SOURCE_DIR}/Source/Widgets/GameWidget)
include_directories(${CMAKE_SOURCE_DIR}/Source/Widgets/JoiningWidget)
include_directories(${CMAKE_SOURCE_DIR}/Source/Widgets/LoginWidget)
include_directories(${CMAKE_SOURCE_DIR}/Source/Widgets/MainWindow)
include_directories(${CMAKE_SOURCE_DIR}/Source/Widgets/MainMenuWidget)
include_directories(${CMAKE_SOURCE_DIR}/Source/Widgets/RoomsListWidget)
include_directories(${CMAKE_SOURCE_DIR}/Source/Widgets/RoomCreationWidget)
include_directories(${CMAKE_SOURCE_DIR}/Source/Widgets/SplashScreenWidget)
include_directories(${CMAKE_SOURCE_DIR}/Source/Widgets/SquareWidget)
include_directories(${CMAKE_SOURCE_DIR}/Source/Widgets/GameConfirmationWidget)
include_directories(${CMAKE_SOURCE_DIR}/Source/Widgets/FiguresDeckWidget)
include_directories(${CMAKE_SOURCE_DIR}/Source/Widgets/RegistrationWidget)

include_directories(${CMAKE_SOURCE_DIR}/Source/Classes/Client)
include_directories(${CMAKE_SOURCE_DIR}/Source/Classes/Figure)
include_directories(${CMAKE_SOURCE_DIR}/Source/Classes/RoomSettings)

set(UI_FILES
        Source/Widgets/SquareWidget/SquareWidget.ui
        Source/Widgets/MainWindow/MainWindow.ui
        Source/Widgets/GameWidget/GameWidget.ui
        Source/Widgets/JoiningWidget/JoiningWidget.ui
        Source/Widgets/LoginWidget/LoginWidget.ui
        Source/Widgets/MainMenuWidget/MainMenu.ui
        Source/Widgets/RoomCreationWidget/RoomCreationWidget.ui
        Source/Widgets/SplashScreenWidget/SplashScreenWidget.ui
        Source/Widgets/ChatWidget/ChatWidget.ui
        Source/Widgets/RoomsListWidget/RoomsListWidget.ui
        Source/Widgets/GameConfirmationWidget/GameConfirmationWidget.ui
        Source/Widgets/FiguresDeckWidget/FiguresDeckWidget.ui
        Source/Widgets/RegistrationWidget/RegistrationWidget.ui
)

qt5_add_resources(RESOURCES Assets/HiddenChess.qrc)
qt5_wrap_ui(UI_HEADERS ${UI_FILES})

add_executable(HiddenChess
        Source/main.cpp
        Source/Classes/Figure/Figure.cpp
        Source/Classes/RoomSettings/RoomSettings.cpp
        Source/Widgets/MainWindow/MainWindow.cpp
        Source/Widgets/ChatWidget/ChatWidget.cpp
        Source/Widgets/MainMenuWidget/MainMenu.cpp
        Source/Widgets/GameWidget/GameWidget.cpp
        Source/Widgets/JoiningWidget/JoiningWidget.cpp
        Source/Widgets/RoomCreationWidget/RoomCreationWidget.cpp
        Source/Widgets/SquareWidget/SquareWidget.cpp
        Source/Classes/Client/Client.cpp
        Source/Widgets/LoginWidget/loginwidget.cpp
        Source/Widgets/SplashScreenWidget/SplashScreenWidget.cpp
        Source/Widgets/RoomsListWidget/RoomsListWidget.cpp
        Source/Widgets/GameConfirmationWidget/GameConfirmationWidget.cpp
        Source/Widgets/FiguresDeckWidget/FiguresDeckWidget.cpp
        Source/Widgets/RegistrationWidget/RegistrationWidget.cpp
        ${RESOURCES}
        ${UI_FILES} ${UI_HEADERS}
)

target_link_libraries(HiddenChess
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        Qt5::Multimedia
        Qt5::WebSockets
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
