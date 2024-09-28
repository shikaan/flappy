function(fetch_latebit version system_name)
  message(STATUS "Fetching latebit ${version} for ${system_name}")
  include(FetchContent)
  FetchContent_Declare(
    latebit
    URL https://github.com/latebit/latebit-engine/releases/download/${version}/latebit-${version}-${system_name}.tar.gz
  )
  FetchContent_GetProperties(latebit)

  if(NOT latebit_POPULATED)
    FetchContent_Populate(latebit)
    add_library(latebit UNKNOWN IMPORTED)
    file(GLOB LIB_FILES "${latebit_SOURCE_DIR}/lib/liblatebit.*")
    set_target_properties(latebit PROPERTIES
      IMPORTED_LOCATION ${LIB_FILES}
      INTERFACE_INCLUDE_DIRECTORIES ${latebit_SOURCE_DIR}/include
    )
  endif()
  add_definitions(-DLATEBIT_VERSION="${version}")
  message(STATUS "Fetching latebit ${version} for ${system_name} - done")
endfunction()