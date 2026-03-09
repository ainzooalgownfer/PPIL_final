# CMakeList.txt : CMake project for PPIL, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (PPIL "PPIL.cpp" "PPIL.h" "header/vecteur2D.h" "header/Forme.h" "header/Segement.h" "header/Cercle.h" "header/Polygone.h" "header/VisiteurForme.h" "header/Group.h" "header/VisiteurSauvegardeTexte.h" "src/VisiteurSauvegardeTexte.cpp" "src/Forme.cpp" "header/ChargeurFrome.h" "header/Connexion_m.h" "header/ChargeurCercle.h"  "header/ChargeurPolygone.h" "header/ChargeurSegment.h" "header/ChargeurGroup.h"
        header/VisiteurDessin.h
        src/ConnexionManager.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PPIL PROPERTY CXX_STANDARD 20)
endif()

# --- Liaison des bibliothèques pour windows ---
if(WIN32)
    # Windows : Winsock2
    target_link_libraries(PPIL ws2_32)
endif()

# TODO: Add tests and install targets if needed.
