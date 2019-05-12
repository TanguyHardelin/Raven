const Plugin= require('./Kernel/Plugin');



class Hackaton extends Plugin{
    constructor(params){
        super(params);
        this.addDependencies('webAPI')
        this.addDependencies('Secure')
        //this.addDependencies('JsonBDD')
    }
    
    example(data){

    }


    __start__(){
        let self=this;
        return new Promise((resolve,err)=>{

            
            resolve();
        })
    }
}

module.exports = Hackaton;