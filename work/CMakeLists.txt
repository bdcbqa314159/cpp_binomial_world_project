project(work)

set(includes ./ ../binomial_world/)

add_executable(my_test my_test.cpp)
target_include_directories(my_test PUBLIC ${includes})
target_link_libraries(my_test binomial_world)

add_executable(excel_verifications excel_verifications.cpp)
target_include_directories(excel_verifications PUBLIC ${includes})
target_link_libraries(excel_verifications binomial_world)

# add_executable(ShortRates ShortRates.cpp)
# target_include_directories(ShortRates PUBLIC ${includes})
# target_link_libraries(ShortRates binomial_world)

# add_executable(my_new_test new_test.cpp)
# target_include_directories(my_new_test PUBLIC ${includes})
# target_link_libraries(my_new_test binomial_world)

# add_executable(work main.cpp)
# target_include_directories(work PUBLIC ${includes})
# target_link_libraries(work binomial_world)

# add_executable(coding_bits coding.cpp)
# target_include_directories(coding_bits PUBLIC ${includes})
# target_link_libraries(coding_bits binomial_world)

# add_executable(bdt BDT.cpp)
# target_include_directories(bdt PUBLIC ${includes})
# target_link_libraries(bdt binomial_world)

# add_executable(calibration_issue calibration.cpp)
# target_include_directories(calibration_issue PUBLIC ${includes})
# target_link_libraries(calibration_issue binomial_world)

# add_executable(binomial_test binomial.cpp)
# target_include_directories(binomial_test PUBLIC ${includes})
# target_link_libraries(binomial_test binomial_world)
