#include "Engine.h"
#include "SpaceObject.h"
#include <QDebug>

using namespace std;

static std::mutex _lock_all_unread_command;

Engine::Engine(){
    _continue=true;
    _run_logic_simulation = false;
}

void Engine::updateInput(){
    for (string line; std::getline(std::cin, line);) {
        //Create command structure
        Command command = Input::getCommandFromCommandLine(line.c_str());

        if(Input::isCommandCorrect(command)){
            //Write all_unread_commands:
            _lock_all_unread_command.lock();
            _all_unread_command.push_back(command);
            _lock_all_unread_command.unlock();

        }
        
        //Handle exit:
        if(command.commandName==CMD_EXIT) break;
    }

   

}
void Engine::updateOutput(){
    QJsonArray array;
    for(unsigned i=0;i<_all_space_object.size();i++){
        QJsonObject item;

        item.insert("name",_all_space_object[i]->getName());
        item.insert("mass",_all_space_object[i]->getMass());

     
        QJsonArray array_position;
        array_position.push_back(_all_space_object[i]->getPosition().getX());
        array_position.push_back(_all_space_object[i]->getPosition().getY());
        array_position.push_back(_all_space_object[i]->getPosition().getZ());

        QJsonArray array_speed;
        array_speed.push_back(_all_space_object[i]->getSpeed().getX());
        array_speed.push_back(_all_space_object[i]->getSpeed().getY());
        array_speed.push_back(_all_space_object[i]->getSpeed().getZ());
        

        QJsonArray array_acceleration;
        array_acceleration.push_back(_all_space_object[i]->getAcceleration().getX());
        array_acceleration.push_back(_all_space_object[i]->getAcceleration().getY());
        array_acceleration.push_back(_all_space_object[i]->getAcceleration().getZ());


        item.insert("position",array_position);
        item.insert("speed",array_speed);
        item.insert("acceleration",array_acceleration);
        
        array.push_back(item);
    }

    QJsonObject result;
    result.insert("objects",array);

    QJsonDocument doc(result);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    //qDebug()<<strJson;
    cout<<strJson.toStdString()<<endl;

}
void Engine::updateLogic(){
    //Start the clock for the gameloop:
    static auto last_time_of_gameloop = std::chrono::high_resolution_clock::now();

    for(unsigned i=0;i<_all_space_object.size();i++){
        for(unsigned j=0;j<_all_space_object.size();j++){
            if(i!=j){
                //Check if object is continue simulation
                if(_all_space_object[j]->isContinue() && _all_space_object[i]->isContinue()){
                    double distance = (_all_space_object[i]->getPosition()-_all_space_object[j]->getPosition()).norm();

                    if(distance>0){
                        Vector3D direction = (_all_space_object[j]->getPosition()-_all_space_object[i]->getPosition()).normalize();

                        double G = 6.67408e-11;
                        double force = G * (_all_space_object[i]->getMass()*_all_space_object[j]->getMass()) / (distance * distance);

                        _all_space_object[i]->addForce(direction*force);

                        //Detect collision:
                        if(distance<_all_space_object[j]->getRadius()){
                            _all_space_object[j]->stopSimulation();
                        }
                    }
                    else{
                        _all_space_object[i]->addForce(Vector3D(0,0,0));
                    }

                    
                }
            }
        }
    }
    //Stop the clock and make constant frame:
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - last_time_of_gameloop;
    last_time_of_gameloop = finish;

   
    for(unsigned i=0;i<_all_space_object.size();i++){
        _all_space_object[i]->compute(elapsed.count() * 1000000);
    }
}

void Engine::run(){
    _input_thread = std::thread(&Engine::updateInput,this);
   
    while(_continue){
        
        //Handle command:
        _lock_all_unread_command.lock();
        if(_all_unread_command.size()>0){
            for(unsigned i=0;i<_all_unread_command.size();i++){
                Command command = _all_unread_command[i];
                QString commandName = command.commandName;
                QMap<QString,QString> commandArguments = command.arguments;
                
                if(commandName == CMD_EXIT) _continue = false;
                else if(commandName == CMD_CREATE){
                    
                    QString name = commandArguments["name"];
                    double  mass = commandArguments["mass"].toDouble();

                    QStringList positionTMP = commandArguments["position"].split(",");
                    Vector3D position (positionTMP[0].toDouble(),positionTMP[1].toDouble(),positionTMP[2].toDouble());

                    QStringList speedTMP = commandArguments["speed"].split(",");
                    Vector3D speed (speedTMP[0].toDouble(),speedTMP[1].toDouble(),speedTMP[2].toDouble());

                    QStringList accelerationTMP = commandArguments["acceleration"].split(",");
                    Vector3D acceleration (accelerationTMP[0].toDouble(),accelerationTMP[1].toDouble(),accelerationTMP[2].toDouble());

                    double  radius = commandArguments["radius"].toDouble();

                    //Check if already contain object:
                    bool contain = false;
                    for(unsigned i=0;i<_all_space_object.size();i++){
                        if(_all_space_object[i]->getName() == name){
                            contain = true;
                        }
                    }

                    if(!contain){
                        //cout<<"Create new object with name= "<<name.toStdString()<<" mass= "<< commandArguments["mass"].toStdString()<< " position= "<<position.toString()<<" speed= "<<speed.toString()<<" acceleration= "<<acceleration.toString()<<endl;
                    
                        _all_space_object.push_back(new SpaceObject(name,mass,position,speed,acceleration,radius));
                    }
                    
                }
                else if(commandName == CMD_MODIFY){
                    //TODO: Implement !
                }
                else if(commandName == CMD_SIMULATE){
                    if(commandArguments["value"] == "true")
                        _run_logic_simulation = true;
                    else
                        _run_logic_simulation = false;
                }
            }
            while(_all_unread_command.size()>0){
                _all_unread_command.pop_back();
            }
        }
        _lock_all_unread_command.unlock();
        

        //UpdateLogic:
        updateLogic();
        //updateOutput:
        updateOutput();

        //Sleep:
        //TODO: attendre de maniere a avoir un FPS regulier
        usleep(1000000);
        
    }
    _input_thread.join();
}

Engine::~Engine(){
    for(unsigned i=0;i<_all_space_object.size();i++){
        delete _all_space_object[i];
    }
}