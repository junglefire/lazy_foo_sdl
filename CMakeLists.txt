PROJECT(playboy)

CMAKE_MINIMUM_REQUIRED(VERSION 3.25)

SET(CMAKE_C_FLAGS_DEBUG "-O0 -Wall -g -ggdb")
SET(CMAKE_C_FLAGS_RELEASE "-O3 -Wall")
SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall")

SET(CMAKE_BUILD_TYPE Release)
SET(EXECUTABLE_OUTPUT_PATH bin)
SET(LIBRARY_OUTPUT_PATH lib)

ADD_DEFINITIONS(-DSIMPLE_MESSAGE)
ADD_DEFINITIONS(-w)

INCLUDE_DIRECTORIES(aurora)

# [Note] MacOS SDL2
# brew install sdl2
INCLUDE_DIRECTORIES(/usr/local/include/SDL2)
LINK_DIRECTORIES(/usr/local/opt/sdl2/lib/)
LINK_DIRECTORIES(/usr/local/lib/)


###############################################################################
###########################   application  ####################################
###############################################################################

SET(EX02 ex/ex02.cpp)
ADD_EXECUTABLE(ex02 ${EX02})
TARGET_LINK_LIBRARIES(ex02 SDL2)

SET(EX04 ex/ex04.cpp)
ADD_EXECUTABLE(ex04 ${EX04})
TARGET_LINK_LIBRARIES(ex04 SDL2)

SET(EX05 ex/ex05.cpp)
ADD_EXECUTABLE(ex05 ${EX05})
TARGET_LINK_LIBRARIES(ex05 SDL2)

SET(EX06 ex/ex06.cpp)
ADD_EXECUTABLE(ex06 ${EX06})
TARGET_LINK_LIBRARIES(ex06 SDL2 SDL2_image)

SET(EX14 ex/ex14.cpp)
ADD_EXECUTABLE(ex14 ${EX14})
TARGET_LINK_LIBRARIES(ex14 SDL2 SDL2_image)








