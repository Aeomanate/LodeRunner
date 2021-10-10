cmake_minimum_required(VERSION 3.13)
project(LodeRunner)

set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} \
        -Wno-unused-variable \
        -Wno-unused-parameter \
        -O0 \
        -std=gnu++2a \
        -pedantic \
        -Wall \
        -Wextra\
         \
        -Wconversion \
        -Wenum-compare \
        -Wfloat-equal \
        -Woverloaded-virtual \
        \
    "
    )

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Executable/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})

add_executable(${PROJECT_NAME}
    src/Main/main.cpp
    src/Main/Cell/Cell.cpp
    src/Main/Cell/Cell.hpp
    src/Tiles/Brick/Brick.cpp
    src/Tiles/Brick/Brick.hpp
    src/Main/Field/Field.cpp
    src/Main/Field/Field.hpp
    src/Characters/Player/Player.cpp
    src/Characters/Player/Player.hpp
    src/Characters/Enemy/Enemy.cpp
    src/Characters/Enemy/Enemy.hpp
    src/Characters/Character/CharacterMoveState.hpp
    src/Utility/Rand.hpp
    src/Utility/RingBuffer.hpp
    src/Characters/Character/States/CharacterIdle.cpp
    src/Characters/Character/States/CharacterIdle.hpp
    src/Characters/Character/States/CharacterJumpDown.cpp
    src/Characters/Character/States/CharacterJumpDown.hpp
    src/Tiles/Trap.cpp src/Tiles/Trap.hpp
    src/Tiles/Empty.cpp src/Tiles/Empty.hpp
    src/Tiles/Rope.cpp src/Tiles/Rope.hpp
    src/Tiles/Ladder.cpp src/Tiles/Ladder.hpp
    src/Tiles/Gold.cpp src/Tiles/Gold.hpp
    src/Tiles/Bedrock.cpp src/Tiles/Bedrock.hpp
    src/Characters/Character/States/CharacterOnBrick.cpp
    src/Characters/Character/States/CharacterOnBrick.hpp
    src/Characters/Character/States/CharacterOnRope.cpp
    src/Characters/Character/States/CharacterOnRope.hpp
    src/Main/EntityState.hpp
    src/Characters/Character/CharacterMoveState.cpp
    src/Main/Cell/Coord.hpp
    src/Main/Cell/Sprites.cpp
    src/Main/Cell/Sprites.hpp
    src/Main/Field/Drawer.cpp
    src/Main/Field/Drawer.hpp
    src/Main/Field/FieldParams.hpp
    src/Tiles/Brick/BreakingBrick.cpp
    src/Tiles/Brick/BreakingBrick.hpp
    src/Characters/Character/States/CharacterOnLadder.cpp
    src/Characters/Character/States/CharacterOnLadder.hpp
    src/Tiles/TransparentCell.cpp
    src/Tiles/TransparentCell.hpp
    src/Characters/Character/States/CharacterFall.cpp
    src/Characters/Character/States/CharacterFall.hpp
    src/Characters/Character/States/CharacterStuck.cpp
    src/Characters/Character/States/CharacterStuck.hpp
    src/Characters/Character/Character.cpp
    src/Characters/Character/Character.hpp
    src/Characters/Character/CharacterStateFactory.hpp
    src/Characters/Player/PlayerStateFactory.cpp
    src/Characters/Player/PlayerStateFactory.hpp
    src/Characters/Enemy/EnemyStateFactory.cpp
    src/Characters/Enemy/EnemyStateFactory.hpp
    src/Tiles/Brick/BrokenBrick.cpp
    src/Tiles/Brick/BrokenBrick.hpp
    src/Tiles/Brick/RecoveringBrick.cpp
    src/Tiles/Brick/RecoveringBrick.hpp
    src/Characters/Character/States/Fire/CharacterFireIdleLeft.cpp
    src/Characters/Character/States/Fire/CharacterFireIdleLeft.hpp
    src/Characters/Character/States/Fire/CharacterFireIdleRight.cpp
    src/Characters/Character/States/Fire/CharacterFireIdleRight.hpp
    src/Characters/Character/States/Fire/CharacterFireLadderLeft.cpp
    src/Characters/Character/States/Fire/CharacterFireLadderLeft.hpp
    src/Characters/Character/States/Fire/CharacterFireLadderRight.cpp
    src/Characters/Character/States/Fire/CharacterFireLadderRight.hpp
    src/Characters/Character/States/CharacterLose.cpp
    src/Characters/Character/States/CharacterLose.hpp
    src/Utility/Rand.cpp)

include_directories(src/Characters)
include_directories(src/Characters/Enemy)
include_directories(src/Characters/Player)
include_directories(src/Characters/Character)
include_directories(src/Characters/Character/States)
include_directories(src/Characters/Character/States/Fire)
include_directories(src/Main)
include_directories(src/Main/Cell)
include_directories(src/Main/Field)
include_directories(src/Utility)
include_directories(src/Tiles)

set(AEOLIB_ROOT "D:/Programms/ProgrammingEnvironment/Librares/AeoGameLib")
set(AEO_DLL ${AEOLIB_ROOT}/bin/libAeoGameFramework.dll)
include_directories(${AEOLIB_ROOT}/include)
install(FILES ${AEO_DLL} DESTINATION ${BUILD_DIR})
target_link_libraries(${PROJECT_NAME} ${AEO_DLL})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${BUILD_DIR})