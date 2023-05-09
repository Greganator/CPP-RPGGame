# CMakeList.txt : CMake project for AtticsAndAngels, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.5)
project(AtticsAndAngels CXX)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
add_subdirectory(thirdparty/raylib thirdparty/raylib/bin)
set(BUILD_RAYGUI_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build raygui examples
add_subdirectory(thirdparty/raygui/projects/CMake)
file(COPY "resources" DESTINATION "/")

set(SOURCES
    AtticsAndAngels.cpp   
    Screens/screen_title.cpp  
    Screens/screen_options.cpp 
    Screens/screem_logo.cpp
    Screens/screen_ending.cpp 
    Screens/screen_gameplay.cpp 
    Screens/screens.h 
    thirdparty/nlohmann/json.hpp
    Screens/UIHelpers.h
     "Stats.h" "Stats.cpp" "Weapon.h" "Weapon.cpp" "Melee.h" "Melee.cpp" "Ranged.h" "Ranged.cpp" "Magic.h" "Magic.cpp" "Character.h" "Character.cpp" "Class.h" "Class.cpp" "Damage.h" "Damage.cpp" "Vault.h" "JsonSaveLoad.h" "Screens/screen_teamCreation.cpp" "PlayerTeam.h" "PlayerTeam.cpp" "Player.h" "Player.cpp" "AIEnimy.h" "AIEnimy.cpp"  "Vault.cpp" "CharacterAnimator.h" "CharacterAnimator.cpp" "AIController.h" "AIController.cpp" "InitiativeController.h" "InitiativeController.cpp")


add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} raylib raygui)