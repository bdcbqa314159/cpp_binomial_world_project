project(binomial_world)

set(includes includes/)
set(sources src/binomial_world.cpp
            src/ShortRateModel.cpp
            src/ElementaryPrices.cpp
            src/NewtonRaphson.cpp
            src/CalibrationFunctionBDT.cpp
            src/CalibrationProcess.cpp
            src/BinomialDirections.cpp
            src/BinomialRiskFreeRate.cpp
            src/BinomialRiskNeutralProbability.cpp
            src/Spot.cpp
            src/BinomialModel.cpp
            src/Options.cpp
            src/SingleStrikeOptions.cpp
            src/Futures.cpp
            src/refactoring_2.cpp
            src/refactoring_3.cpp
            src/refactoring_4.cpp
            src/refactoring_5.cpp
            src/refactoring_6.cpp
            src/refactoring_8.cpp
            src/refactoring_9.cpp
            src/refactoring_10.cpp
            src/refactoring_11.cpp
            src/refactoring_12.cpp
            src/refactoring_13.cpp)


add_library(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC ${includes})
target_link_libraries(${PROJECT_NAME} PUBLIC GSL::gsl GSL::gslcblas Boost::boost Boost::date_time)
