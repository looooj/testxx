

include_directories(/home/lpr/prjs /home/lpr/dep/include)



add_executable(testweb testweb.cpp  ../common/mongoose.c  ../common/exithandler.cpp ../common/mgserver.cpp ../common/mysleep.cpp )

target_link_libraries(testweb pthread)            



            