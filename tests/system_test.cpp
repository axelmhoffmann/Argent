#include "TestFramework.h"
#include "../src/ecs/ECS.h"
#include "../src/ecs/System.h"

#include <vector>


struct ComponentA
{
    int value;
    ComponentA(int val)
    {
        value = val;
    }
};

struct ComponentB { };

class TestSystem : public ag::System
{
public:
    void Init() override
    {

    }
    void Update(double dt) override
    {

    }
    void FrameUpdate(double dt) override {}
private:
    static ag::System::SystemRegister<TestSystem> reg;
};

ag::System::SystemRegister<TestSystem> TestSystem::reg = ag::System::SystemRegister<TestSystem>();


void initialisation()
{
    size_t systemCount = ag::System::Systems().size();
    ag_expect(systemCount == 1, "Expected 1 registered system, instead found {}", systemCount);

    std::unique_ptr<ag::System> sys = ag::System::Systems().at(0)();
}

int main()
{
    Test::Name("Systems");

    Test::Case("Initialisation", initialisation);


    Test::Run();
}