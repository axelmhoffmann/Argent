#include "World.h"

void ag::World::AddArchetype(ag::ArchetypeCollection* arch)
{
    archetypes.push_back(std::shared_ptr<ag::ArchetypeCollection>(arch));
    archetypeIDMap[arch->GetID()] = arch;
    for (ag::IQuery* q : queries)
    {
        q->AddIfMatch(std::shared_ptr<ag::ArchetypeCollection>(arch));
    }
}

void ag::World::InitialiseQuery(ag::IQuery* query)
{
    queries.push_back(query);
    for (std::shared_ptr<ArchetypeCollection> arch : archetypes)
    {
        query->AddIfMatch(arch);
    }
}

ag::World::~World()
{

}