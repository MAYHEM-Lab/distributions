cmake_minimum_required(VERSION 3.13)
project(distributions)

add_library(distributions normal.c)

install(TARGETS distributions EXPORT distributions DESTINATION lib)
install(EXPORT distributions DESTINATION lib/cmake/distributions)

file(GLOB distributions_headers "*.h")
install(FILES ${distributions_headers} DESTINATION include)
install(FILES distributions-config.cmake DESTINATION lib/cmake/distributions)
