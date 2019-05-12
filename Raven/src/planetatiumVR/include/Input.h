#ifndef INPUT_H
#define INPUT_H

#include <QString>
#include <iostream>
#include <QStringList>
#include <QMap>

//Deffinition de toute les commandes
const QString CMD_EXIT      = "EXIT";
const QString CMD_CREATE    = "CREATE";
const QString CMD_MODIFY    = "MODIFY";
const QString CMD_SIMULATE  = "SIMULATE";

typedef struct{
    QString commandName;
    QMap<QString,QString> arguments;
} Command;

class Input{
    public:
        static Command getCommandFromCommandLine(QString commandLine);
        static bool    isCommandCorrect(Command command);
};


#endif