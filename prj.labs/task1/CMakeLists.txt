project(task1)
add_executable(task1 task.cpp)
target_link_libraries(task1 ${OpenCV_LIBS})

file(READ task.cpp cpp_source)
configure_file(task.report.md.in.txt ${CMAKE_CURRENT_BINARY_DIR}/task.report.md @ONLY)
add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/task.report.md" "$<TARGET_FILE_DIR:${PROJECT_NAME}>")