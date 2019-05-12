#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <vector>
#include <string>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <thread>
#include <mutex>
#include <chrono>
#include <unistd.h>

#include "Input.h"
#include "SpaceObject.h"

#define SIMULATION_RATE 30

class Engine{
    public:
        Engine();
        void updateInput();
        void updateOutput();
        void updateLogic();

        void run();

        ~Engine();
    protected:
        std::vector<Command>    _all_unread_command;
        std::thread             _input_thread;
        std::thread             _logic_thread;

        bool                    _continue;
        bool                    _run_logic_simulation;
        
        //All objects:
        std::vector<SpaceObject *> _all_space_object;
       //std::vector<command> _all_commands;
};


#endif