file (GLOB TYPE_TRAITS_HEADERS "*.hpp")
message(STATUS "header files:" ${TYPE_TRAITS_HEADERS})

source_group("headers" FILES ${TYPE_TRAITS_HEADERS})

include_directories (.)

add_library(type_traits INTERFACE)
add_custom_target(type_traits_header SOURCES ${TYPE_TRAITS_HEADERS})
target_include_directories(type_traits INTERFACE  ".")

set_property(TARGET type_traits_header PROPERTY FOLDER ${PRJECT_LIBRARIES_DIR})



install (TARGETS type_traits
         PUBLIC_HEADER DESTINATION ${PROJECT_SOURCE_DIR}/_install/include
)
