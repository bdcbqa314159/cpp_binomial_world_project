project(binomial_world)

set(includes includes/)
set(sources src/binomial_world.cpp
            src/ShortRateModel.cpp
            src/ElementaryPrices.cpp)

add_library(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC ${includes})
target_link_libraries(${PROJECT_NAME} PUBLIC GSL::gsl GSL::gslcblas Boost::boost Boost::date_time)
