function(fetch_latebit_kiosk version public_dir)
  message(STATUS "Fetching latebit-kiosk ${version}")
  include(FetchContent)
  FetchContent_Declare(
    latebit_kiosk
    URL https://github.com/latebit/latebit-kiosk/archive/refs/tags/${version}.tar.gz
  )
  FetchContent_GetProperties(latebit_kiosk)

  if(NOT latebit_kiosk_POPULATED)
  FetchContent_MakeAvailable(latebit_kiosk)
    
    # Makes the project name human readable (my_game -> my game
    # TODO: this should ideally be read from the configuration
    string(REGEX REPLACE "_([a-z])" " \\1" temp "${PROJECT_NAME}")
    set(TITLE "${temp}")
    
    # Template variables
    configure_file(${latebit_kiosk_SOURCE_DIR}/index.html ${public_dir}/index.html @ONLY)
    
    file(GLOB KIOSK_FILES "${latebit_kiosk_SOURCE_DIR}/*")
    # Exclude dot files
    list(FILTER KIOSK_FILES EXCLUDE REGEX "/\\.[^/]*$")
    foreach(file ${KIOSK_FILES})
      file(COPY ${file} DESTINATION ${public_dir})
    endforeach()
  endif()

  message(STATUS "Fetching latebit-kiosk ${version} - done")
endfunction()