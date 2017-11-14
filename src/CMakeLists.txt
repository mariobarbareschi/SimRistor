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
                           

add_library(fblccontroller
            FBLCController.cpp
            )
target_link_libraries(fblccontroller PRIVATE xbar)
target_include_directories(fblccontroller 
                           PRIVATE ${CMAKE_SOURCE_DIR}/inc
                           )

add_library(fblcrun
            FBLCRun.cpp
            )
target_link_libraries(fblcrun PRIVATE fblccontroller)
target_include_directories(fblcrun 
                           PRIVATE ${CMAKE_SOURCE_DIR}/inc
                           )
                           