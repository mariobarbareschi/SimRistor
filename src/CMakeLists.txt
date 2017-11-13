add_library(memristor
            memristor.cpp
            )
target_include_directories(memristor 
                           PRIVATE ${CMAKE_SOURCE_DIR}/inc
                           )
                           
add_library(xbar
            xbar.cpp
            )
target_link_libraries(xbar PRIVATE memristor)
target_include_directories(xbar 
                           PRIVATE ${CMAKE_SOURCE_DIR}/inc
                           )
                           

add_library(xbarcontroller
            xbarcontroller.cpp
            )
target_link_libraries(xbarcontroller PRIVATE xbar)
target_include_directories(xbarcontroller 
                           PRIVATE ${CMAKE_SOURCE_DIR}/inc
                           )

add_library(xbarrun
            xbarrun.cpp
            )
target_link_libraries(xbarrun PRIVATE xbarcontroller)
target_include_directories(xbarrun 
                           PRIVATE ${CMAKE_SOURCE_DIR}/inc
                           )
                           