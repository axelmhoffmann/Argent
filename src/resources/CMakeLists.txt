add_library(resources "Resource.cpp" "Mesh.cpp" "Texture.cpp" "Material.h" "Material.cpp" "AssetManager.h" "AssetManager.cpp" "Shader.h" "Shader.cpp" "Blueprint.cpp" "Blueprint.h" "AudioClip.h" "AudioClip.cpp" 
						"v2/resources.h" "v2/resrc_manager.cpp" "v2/resrc_manager.h" "v2/resrc_handle.h" "v2/resrc_specifier.h" "v2/material.h" "v2/texture.h" "v2/packer/agpk.cpp")

target_link_libraries(resources PRIVATE rv2 nlohmann_json::nlohmann_json)
target_include_directories(resources PRIVATE ${Stb_INCLUDE_DIR})

add_subdirectory(v2)