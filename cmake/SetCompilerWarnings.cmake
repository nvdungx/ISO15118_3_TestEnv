# Compiler warnings

# Store origin compile flags
set(CMAKE_C_FLAGS_ORIGIN ${CMAKE_C_FLAGS})
set(CMAKE_CXX_FLAGS_ORIGIN ${CMAKE_CXX_FLAGS})

# Create custom compile flags
set(CMAKE_C_FLAGS_CUSTOM ${CMAKE_C_FLAGS})
set(CMAKE_CXX_FLAGS_CUSTOM ${CMAKE_CXX_FLAGS})

if(MSVC)

  # Set warnings level 4
  if(CMAKE_C_FLAGS_CUSTOM MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W3" CMAKE_C_FLAGS_CUSTOM ${CMAKE_C_FLAGS_CUSTOM})
  else()
    set(CMAKE_C_FLAGS_CUSTOM "${CMAKE_C_FLAGS_CUSTOM} /W4")
  endif()
  if(CMAKE_CXX_FLAGS_CUSTOM MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS_CUSTOM ${CMAKE_CXX_FLAGS_CUSTOM})
  else()
    set(CMAKE_CXX_FLAGS_CUSTOM "${CMAKE_CXX_FLAGS_CUSTOM} /W3")
  endif()

  # Make all warnings into errors and increases the number of sections that an object file can contain
  set(CMAKE_C_FLAGS_CUSTOM "${CMAKE_C_FLAGS_CUSTOM} /WX /bigobj")
  set(CMAKE_CXX_FLAGS_CUSTOM "${CMAKE_CXX_FLAGS_CUSTOM} /WX /bigobj")

else()

  # Make all warnings into errors
  set(CMAKE_C_FLAGS_CUSTOM "${CMAKE_C_FLAGS_CUSTOM} -W -Wall")
  set(CMAKE_CXX_FLAGS_CUSTOM "${CMAKE_CXX_FLAGS_CUSTOM} -W -Wall")

endif()

# Update compile flags
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS_CUSTOM})
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS_CUSTOM})
