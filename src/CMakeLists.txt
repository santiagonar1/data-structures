set(SOURCE_LIST
        dummy.cpp)

set(HEADER_LIST
        "${ds_SOURCE_DIR}/include/contiguous_iterator.hpp"
        "${ds_SOURCE_DIR}/include/type_definitions.hpp"
        "${ds_SOURCE_DIR}/include/vector.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(ds ${SOURCE_LIST}
        ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(ds PUBLIC "${ds_SOURCE_DIR}/include")