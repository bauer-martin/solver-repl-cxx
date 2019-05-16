target_sources(core
  PRIVATE
    ${CMAKE_SOURCE_DIR}/include/option_coding/AbstractOptionCoding.h AbstractOptionCoding.cpp
    ${CMAKE_SOURCE_DIR}/include/option_coding/OptionCoding.h OptionCoding.cpp
    ${CMAKE_SOURCE_DIR}/include/option_coding/OptionNameOptionCoding.h OptionNameOptionCoding.cpp
    ${CMAKE_SOURCE_DIR}/include/option_coding/VariabilityModelIndexOptionCoding.h VariabilityModelIndexOptionCoding.cpp
)
