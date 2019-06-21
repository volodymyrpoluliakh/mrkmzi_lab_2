cmake_minimum_required(VERSION 2.8)

<<<<<<< HEAD
project(el_gamal)

add_executable(${PROJECT_NAME}
    main.cpp
    el_gamal.hpp
    el_gamal.cpp
    )

#target_include_directories(${})
#
target_link_libraries(${PROJECT_NAME} gmp.a boost_program_options.a libstdc++.a)
=======
project(lab2)
add_executable(${PROJECT_NAME} "main.cpp" big_int.cpp big_int.h functions.cpp functions.h)


target_link_libraries(${PROJECT_NAME} boost_program_options.a)
>>>>>>> 10408cc69aa5950e15fd0a62ac85c89b9c4594da
