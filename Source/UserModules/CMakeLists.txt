set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(MinimalModule)
add_subdirectory(MyModule)
add_subdirectory(EyeModule)
add_subdirectory(PupilModule)
add_subdirectory(HeadMovementModule)
add_subdirectory(DecisionModule)
add_subdirectory(MouthModule)



set(SOURCE ${SOURCE} PARENT_SCOPE)
set(MODULES_INCLUDS ${MODULES_INCLUDS} PARENT_SCOPE)
set(MODULES_LIBS ${MODULES_LIBS} PARENT_SCOPE)
