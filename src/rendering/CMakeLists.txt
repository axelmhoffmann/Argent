add_library(renderer   "transform.h" "transform.cpp" "glm.h" "scene_builder.h" "render_object.h" "render_object.cpp" "scene_graph.h" "scene_builder.cpp" "mesh_handler.h")

add_subdirectory(ogl)

target_link_libraries(renderer PRIVATE log_print lib resources glfw ${ogl32lib} ${glew})