project(binomial_world)

set(includes includes/)
set(sources src/binomial_world.cpp
            # src/ShortRateModel.cpp
            # src/ElementaryPrices.cpp
            # src/NewtonRaphson.cpp
            # src/CalibrationFunctionBDT.cpp
            # src/CalibrationProcess.cpp
            # src/BinomialDirections.cpp
            # src/BSDirections.cpp
            # src/BinomialRiskFreeRate.cpp
            # src/BinomialRiskNeutralProbability.cpp
            src/Spot.cpp
            src/Equities.cpp
            src/BinomialModel.cpp
            # src/BinomialModelEquities.cpp
            # src/BinomialModelFutures.cpp
            src/Options.cpp
            src/SingleStrikeOptions.cpp
            # src/Futures.cpp
            src/refactoring.cpp
            src/BinomialDynamic.cpp
            src/BinomialParameters.cpp
            src/InterestRates.cpp
            )


add_library(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC ${includes})
target_link_libraries(${PROJECT_NAME} PUBLIC GSL::gsl GSL::gslcblas Boost::boost Boost::date_time)
