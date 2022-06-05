set(DB_SRCS
    main.cc
    Cursor.cc 
    DB.cc 
    DbClient.cc 
    InputBuffer.cc  
    MetaCmd.cc 
    Pager.cc 
    Row.cc 
    Statement.cc 
    Table.cc 
    BTree.cc
)

add_executable(burgerdb ${DB_SRCS})

# target_link_libraries(burgerdb pthread rt)
# add_subdirectory(tests)