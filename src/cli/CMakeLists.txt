# tool exectuable project
set(TARGET testCli)

add_executable(${TARGET}
    main.cpp
)

target_link_libraries(${TARGET}
  PRIVATE
    libtestaufgabe
)

set_target_properties(
    ${TARGET}
    PROPERTIES OUTPUT_NAME "${TARGET}"
)

install(TARGETS
    ${TARGET}
    DESTINATION ${PROJECT_BINARY_DIR}/bin
)