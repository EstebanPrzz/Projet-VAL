# CMakeList.txt : projet CMake pour Projet VAL, incluez la source et définissez
# la logique spécifique au projet ici.
#
Project(Test)

if(MSVC)
  set(SFML_DIR "C:/Program Files/SFML/lib/cmake/SFML")
  set(SFML_STATIC_LIBRARIES TRUE)
  add_compile_options(
    $<$<CONFIG:>:/MT> #---------|
    $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
    $<$<CONFIG:Release>:/MT> #--|
  )
endif()


find_package(SFML 2.6.1 COMPONENTS window system graphics REQUIRED)
link_libraries(sfml-graphics sfml-window)
# Ajoutez une source à l'exécutable de ce projet.
add_executable (CMakeTarget "Projet VAL.cpp" "Projet VAL.h" "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
