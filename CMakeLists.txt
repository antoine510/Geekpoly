cmake_minimum_required(VERSION 3.5)
project(Monopoly)

option (ENABLE_32_BITS "Enable 32 bits compilation" OFF)

include_directories("./" "SDL/include/")

if(WIN32)
	if(CMAKE_GENERATOR MATCHES "Win64")
		if(ENABLE_32_BITS)
			message( FATAL_ERROR "Win64 compiler incompatible with 32 bits option." )
		else()
			link_directories("SDL/lib/x64")
		endif()
	else()
		link_directories("SDL/lib/Win32")
		if(NOT ENABLE_32_BITS)
			message( STATUS "Win32 compiler chosen, enabling 32 bits.")
		endif()
	endif()
	add_definitions(-DWIN32_LEAN_AND_MEAN -D_CRT_SECURE_NO_WARNINGS)
elseif (APPLE)
else()
	add_definitions()
	link_directories()
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

