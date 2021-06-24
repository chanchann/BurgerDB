# set(DB_SRCS
#     chatservice.cc
#     chatserver.cc
#     main.cc
# )

# add_executable(chatserver ${SERVER_SRCS})

# target_link_libraries(chatserver burger_base burger_net chat_model pthread rt)


add_subdirectory(tests)