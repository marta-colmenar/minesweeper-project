
if (NOT EXISTS "C:/Users/marta/Documents/AIM/3rd_semester/C++/Exercises/build-glfw-3.3.8-Desktop_Qt_5_15_2_MSVC2019_64bit-Debug/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: \"C:/Users/marta/Documents/AIM/3rd_semester/C++/Exercises/build-glfw-3.3.8-Desktop_Qt_5_15_2_MSVC2019_64bit-Debug/install_manifest.txt\"")
endif()

file(READ "C:/Users/marta/Documents/AIM/3rd_semester/C++/Exercises/build-glfw-3.3.8-Desktop_Qt_5_15_2_MSVC2019_64bit-Debug/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")

foreach (file ${files})
  message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  if (EXISTS "$ENV{DESTDIR}${file}")
    exec_program("C:/Qt/Tools/CMake_64/bin/cmake.exe" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif()
  elseif (IS_SYMLINK "$ENV{DESTDIR}${file}")
    EXEC_PROGRAM("C:/Qt/Tools/CMake_64/bin/cmake.exe" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing symlink \"$ENV{DESTDIR}${file}\"")
    endif()
  else()
    message(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  endif()
endforeach()

