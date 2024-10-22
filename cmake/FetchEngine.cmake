function(fetch_latebit version system_name)
  message(STATUS "Fetching latebit ${version} for ${system_name}")

  execute_process(
    COMMAND ${CMAKE_C_COMPILER} -dumpmachine
    RESULT_VARIABLE result
    OUTPUT_VARIABLE arch
    ERROR_QUIET
  )
  if (result)
    message(FATAL_ERROR "Failed to determine target architecture triplet: ${result}")
  endif()
  string(REGEX MATCH "([^-]+).*" arch_match ${arch})
  if (NOT CMAKE_MATCH_1 OR NOT arch_match)
    message(FATAL_ERROR "Failed to match the target architecture triplet: ${arch}")
  endif()
  set(arch ${CMAKE_MATCH_1})

  include(FetchContent)
  FetchContent_Declare(
    latebit
    URL https://github.com/latebit/latebit-engine/releases/download/${version}/latebit-${version}-${arch}-${system_name}.tar.gz
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