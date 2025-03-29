project(binomial_world)

set(includes includes/)
set(sources src/Binomial_World.cpp
            src/BinomialDirections.cpp
            src/Equities.cpp
            src/Options.cpp
            src/SingleStrikeOptions.cpp
            src/BinomialDynamic.cpp
            src/InterestRates.cpp
            src/BinomialVolGrid.cpp
            src/Utils.cpp
            src/VolGridAdapter.cpp
            src/Numeric.cpp
            src/CouponParameters.cpp
            src/CouponPayment.cpp
            # src/ShortRateModel.cpp
            # src/ElementaryPrices.cpp
            # src/NewtonRaphson.cpp
            # src/CalibrationFunctionBDT.cpp
            # src/CalibrationProcess.cpp
            
            # src/BSDirections.cpp
            # src/BinomialRiskFreeRate.cpp
            # src/BinomialRiskNeutralProbability.cpp
            # src/Spot.cpp
            
            # src/BinomialModel.cpp
            # src/BinomialModelEquities.cpp
            # src/BinomialModelFutures.cpp
            
            # src/Futures.cpp
            # src/refactoring.cpp
            
            # src/BinomialParameters.cpp
            
            # src/RiskFreeRateTermStructure.cpp
            # src/ZeroCouponBondDynamic.cpp
            # src/BinomialValues.cpp
            # src/refactoring_bis.cpp
            # src/refactoring_ter.cpp
            
            )


add_library(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC ${includes})
target_link_libraries(${PROJECT_NAME} PUBLIC GSL::gsl GSL::gslcblas Boost::boost Boost::date_time)
