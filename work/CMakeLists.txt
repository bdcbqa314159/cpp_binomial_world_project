project(work)

set(includes ./ ../binomial_world/)

add_executable(work main.cpp)
add_executable(test test.cpp)


add_executable(coding_bits coding.cpp)
target_include_directories(coding_bits PUBLIC ${includes})
target_link_libraries(coding_bits binomial_world)
