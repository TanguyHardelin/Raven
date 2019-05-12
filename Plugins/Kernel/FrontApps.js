const Plugin= require('./Plugin');


class FrontApps extends Plugin{
    constructor(params){
        super(params);
        this.addDependencies('webAPI')
        this.addDependencies('Secure')

        this.bindAllFunction(this);
    }

    __buildApp__(appName){
        const exec = require('child_process').execSync;
        console.log("cd Raven/App/"+appName +" && npm run build && cd ../..")
        exec("cd Raven/App/"+appName +" && ls && npm run build && cd ../..",(e,d,r)=>console.log(d));
    }
    __installApp__(appName){
        const exec = require('child_process').execSync;
        console.log("cd Raven/App/"+appName +" && npm install && cd ../..")
        exec("cd Raven/App/"+appName +" && ls && npm install && cd ../..",(e,d,r)=>console.log(d));
    }
    __ejectApp__(appName){
        const exec = require('child_process').execSync;
        console.log("cd Raven/App/"+appName +" && npm run eject && cd ../..")
        exec("cd Raven/App/"+appName +" && ls && npm run eject && cd ../..",(e,d,r)=>console.log(d));
    }
    
    
    __start__(){
        let self=this;
        
        return new Promise((resolve,err)=>{
            //TODO: construire ça en fonction des parametres
            //self.plugins.Secure.addApplication("ravenBot","/RavenApp/ravenBot/",0x0);
            //self.plugins.Secure.addApplication("resumeMonitor","/RavenApp/resumeMonitor/",0x0);
            self.plugins.WebAPI.addApplication("/","/Raven/App/CV/");
            self.plugins.WebAPI.addApplication("planetariumvr","/Raven/App/PlanetariumVR")
            self.plugins.WebAPI.addApplication("hackaton","/Raven/App/Hackaton")
            
            resolve();
        })
    }
}

module.exports = FrontApps;