### CMakeLists.txt --- PolytechRayTracing project
## 
## Author: Jean-Christophe Lombardo
## Copyright (C) 2011 - Jean-Christophe Lombardo, Inria
## Created: Thu Jun  9 10:33:56 2011
## Last-Updated:  Thu Jun  9 17:25:07 2011
##           By: Jean-Christophe Lombardo
##
######################################################################

project(appGui)

set(${PROJECT_NAME}_HEADERS
    Color.h
    Draughtboard.h
    Image.h
    LightModel.h
    LightSource.h
    Material.h
    ONB.h
    
    PhongModel.h
    Plane.h
    Ray.h
    RayTracer.h
    Rectangle.h
    Scene.h
    ScreenV2.h
    Set.h
    Shape.h
    Sphere.h
    stdint.h
    Timer.h
    Vector2.h
    Vector3.h
)

set(${PROJECT_NAME}_SOURCES
    Color.cpp
    Draughtboard.cpp
    Image.cpp
    LightModel.cpp
    LightSource.cpp
    Material.cpp
    ONB.cpp
    
    PhongModel.cpp
    Plane.cpp
    Ray.cpp
    RayTracer.cpp
    Rectangle.cpp
    Scene.cpp
    ScreenV2.cpp
    Shape.cpp
    Sphere.cpp
    Timer.cpp
    Vector2.cpp
    Vector3.cpp
)

#add_definitions(-std=c++0x)

add_executable(${PROJECT_NAME}
        appGui.cpp
        ${${PROJECT_NAME}_SOURCES}
        ${${PROJECT_NAME}_HEADERS}
    )
	
target_link_libraries(${PROJECT_NAME}
        ${SDL_LIBRARY}
        ${SDLIMAGE_LIBRARY}
        ${ITPP_LIBRARY}
)

## -*- tab-width: 4; indent-tabs-mode: nil c-basic-offset: 4 -*-
## vim:cindent:ts=4:sw=4:et:tw=80:sta:

