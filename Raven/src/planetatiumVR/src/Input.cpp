#include "Input.h"

using namespace std;

Command Input::getCommandFromCommandLine(QString commandLine){
    Command result;

    QStringList command_list=commandLine.split(" ");
    result.commandName = command_list[0];

    for(int i=1;i<command_list.count();i+=2){
        result.arguments.insert(command_list[i],command_list[i+1]);
    }

    return result;
}

//Check if all arguments are presents
bool Input::isCommandCorrect(Command command){
    QString commandName = command.commandName;
    QMap<QString,QString> commandArguments = command.arguments;
    if(commandName == CMD_EXIT) return true;
    else if(commandName == CMD_CREATE){
        if(commandArguments.contains("mass")&&commandArguments.contains("position")&&commandArguments.contains("speed")&&commandArguments.contains("acceleration")&&commandArguments.contains("name"))
            return true;
        else 
            return false;
    }
    else if(commandName == CMD_MODIFY){
        if(commandArguments.contains("mass")||commandArguments.contains("position")||commandArguments.contains("speed")||commandArguments.contains("acceleration")||commandArguments.contains("name"))
            return true;
        else 
            return false;
    }
    else if(commandName == CMD_SIMULATE){
        if(commandArguments.contains("value"))
            return true;
        else 
            return false;
    }
    else{
        return false;
    }
}