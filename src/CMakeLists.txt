
project(zmqserver)
add_executable(server ${PROJECT_SOURCE_DIR}/server.cpp)
target_link_libraries(server PRIVATE cppzmq)

project(zmqclient)
add_executable(client ${PROJECT_SOURCE_DIR}/client.cpp)
target_link_libraries(client PRIVATE cppzmq)

