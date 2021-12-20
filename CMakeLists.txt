cmake_minimum_required(VERSION 3.5)
project(Monopoly)

include_directories("./" "SDL2-2.0.18/include/")

if(WIN32)
	link_directories("SDL2-2.0.18/lib/x64")
	add_definitions(-DWIN32_LEAN_AND_MEAN -D_CRT_SECURE_NO_WARNINGS)
else()
	message(FATAL "Unsuported configuration")
endif ()

file(GLOB SRC_FILES
	"*.c"
	"*.h"
)
	
file(GLOB SRC_CARD
	"Card/*.c"
	"Card/*.h"
)

file(GLOB SRC_FORMS
	"Forms/*.c"
	"Forms/*.h"
)

file(GLOB SRC_GAME
	"Game/*.c"
	"Game/*.h"
)

file(GLOB SRC_GRAPHICS
	"Graphics/*.c"
	"Graphics/*.h"
)

file(GLOB SRC_UI
	"UI/*.c"
	"UI/*.h"
)

add_executable(Monopoly ${SRC_FILES} ${SRC_CARD} ${SRC_FORMS} ${SRC_GAME} ${SRC_GRAPHICS} ${SRC_UI})

source_group(Common					FILES ${SRC_FILES})
source_group(Card					FILES ${SRC_CARD})
source_group(Forms					FILES ${SRC_FORMS})
source_group(Game					FILES ${SRC_GAME})
source_group(Graphics				FILES ${SRC_GRAPHICS})
source_group(UI						FILES ${SRC_UI})

target_link_libraries(Monopoly "SDL2" "SDL2main" "SDL2_ttf")


set_target_properties(Monopoly
    PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY_RELEASE 			"${CMAKE_SOURCE_DIR}/Binary"
	RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO 	"${CMAKE_SOURCE_DIR}/Binary"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG 				"${CMAKE_SOURCE_DIR}/Binary"
)

