target_sources(tests PRIVATE "World_ITest.cpp" 
							 "System_UTest.cpp" 
							 "Archetype_UTest.cpp" 
							 "Component_UTest.cpp" 
							 "EntityRef_ITest.cpp" 
							 "EventManager_ITest.cpp"
							 "ECS_Mock.h"
							 "new_archetype_UTest.cpp")
target_link_libraries(tests ecs)