# Function to create header-only lib tests
#
# Usage:
# add_header_test(<testname>
#     SOURCES <source list>
#     INCLUDEDIR <header dir>
#     DEPENDS <libraries to link>)
#
function (add_header_test testname)
  cmake_parse_arguments(ARG "" "" "SOURCES;INCLUDEDIR;DEPENDS" ${ARGN})
    
    # create an exectuable in which the tests will be stored
    add_executable (${testname})
    target_sources (${testname} PRIVATE ${ARG_SOURCES})
    
    if(ARG_DEPENDS)
      target_link_libraries(${testname} PUBLIC ${ARG_DEPENDS})
    endif()

    target_compile_features(${testname} PRIVATE cxx_std_17)
    if (MSVC)
      target_compile_options(${testname} PRIVATE "/Zc:__cplusplus")
    endif ()
    target_include_directories (${testname}
      PRIVATE
        ${ARG_INCLUDEDIR} 
    )
    add_test(NAME ${testname} COMMAND ${testname} -s)
endfunction ()

set(TESTS "")
set (TESTCODES 
  InCircle
  InSphere
  Orient2d
  Orient3d
  Robustness
)
foreach(TESTCODE ${TESTCODES})
  set (TESTNAME "Test${TESTCODE}")
  add_header_test (${TESTNAME}
      SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/${TESTNAME}.cpp"
      INCLUDEDIR
        "${CMAKE_CURRENT_LIST_DIR}"
      DEPENDS 
        ${PROJECT_NAME}::${PROJECT_NAME}
    )
  list(APPEND TESTUTILITIES ${TESTNAME})
  set_target_properties (${TESTNAME} PROPERTIES FOLDER TestUtility)
endforeach()