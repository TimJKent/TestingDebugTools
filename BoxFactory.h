#pragma once

#include <StateMachine.h>
#include <chrono>

class BoxFactory : public StateMachine
{
public:
    enum BOXFACTORY_STATE
    {
        IDLE = 0,
        CREATE_BOX
    };

    BoxFactory(const std::string& factoryName) : StateMachine()
    {
        this->factoryName = factoryName;

        AddState(std::make_unique<IdleState>(IDLE, this));
        AddState(std::make_unique<CreateBoxState>(CREATE_BOX, this));
    }

    class IdleState : public State
    {
        public:
            IdleState(StateID stateID, BoxFactory* context) : State(stateID){ factoryContext = context;}
            ~IdleState() = default;
            void OnStateEnter () override 
            { 
                idleStartTime = std::chrono::high_resolution_clock::now();
                idleCurrentTime = std::chrono::high_resolution_clock::now();
                std::cout << factoryContext->factoryName << ": Enter Idle\n"; 
            }
            void OnStateUpdate() override 
            { 
                idleCurrentTime = std::chrono::high_resolution_clock::now();
                std::chrono::seconds idleDurationSeconds = std::chrono::duration_cast<std::chrono::seconds>(idleCurrentTime - idleStartTime);
                std::cout << factoryContext->factoryName << "Idle (" << idleDurationSeconds.count() <<")\n"; 
            }
            void OnStateExit  () override { std::cout << factoryContext->factoryName << ": Exit Idle\n"; }
            
            StateID GetNextState() override 
            {
                std::chrono::seconds idleDurationSeconds = std::chrono::duration_cast<std::chrono::seconds>(idleCurrentTime - idleStartTime);
                if(idleDurationSeconds > std::chrono::seconds(5))
                {
                    return CREATE_BOX;
                }
                return IDLE;
            } 
        private:
            BoxFactory* factoryContext;
            std::chrono::time_point<std::chrono::high_resolution_clock> idleStartTime;
            std::chrono::time_point<std::chrono::high_resolution_clock> idleCurrentTime;
    };

    class CreateBoxState : public State
    {
        public:
            CreateBoxState(StateID stateID, BoxFactory* context) : State(stateID){ factoryContext = context;}
             ~CreateBoxState() = default;
            void OnStateEnter () override { boxCount = 0; }
            void OnStateUpdate() override { std::cout << "Making Box["<< boxCount++ <<"]\n";}
            void OnStateExit  () override { std::cout << "Made " << boxCount << " boxes!\n";}  

            StateID GetNextState() override 
            {
                if(boxCount >= 100000)
                {
                    return IDLE;
                }
                return stateID; 
            } 
        private:
            BoxFactory* factoryContext;
        private:
            int boxCount = 0;
    };

private:
    std::string factoryName;
};