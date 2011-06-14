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
    Image.h
    Intersection.h
    LightModel.h
    LightSource.h
    Material.h
    ONB.h
    ParamSurf.h
    PhongModel.h
    Ray.h
    RayTracer.h
    Rectangle.h
    Scene.h
    Screen.h
    Set.h
    Shape.h
    Sphere.h
    stdint.h
    Vector2.h
    Vector3.h
    ScreenV2.h
)

set(${PROJECT_NAME}_SOURCES
    Color.cpp
    Image.cpp
    Intersection.cpp
    LightModel.cpp
    LightSource.cpp
    Material.cpp
    ONB.cpp
    ParamSurf.cpp
    PhongModel.cpp
    Ray.cpp
    RayTracer.cpp
    Rectangle.cpp
    Scene.cpp
    Screen.cpp
    Shape.cpp
    Sphere.cpp
    Vector2.cpp
    Vector3.cpp
    ScreenV2.cpp
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

