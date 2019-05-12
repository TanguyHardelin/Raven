const Plugin= require('./Kernel/Plugin');


class BonApp extends Plugin{
    constructor(params){
        super(params);
        this.addDependencies('webAPI')
        this.addDependencies('Secure')
        this.addDependencies('JsonBDD')
    }
    __start__(){
        let self=this;
        return new Promise((resolve,err)=>{
            this.addSecureWebAPI('/bonApp/getRecipeByID/:id',(req,res)=>{
                
            },0x2);
            resolve();
        })
    }
    __get_recipe_by_id__(id){
        if(parseInt(id)!= NaN)
            this.runSQLCommand("SELECT * FROM recette WHERE id="+id);
        else
            this.error('[getRecipeByID] try to run unexpected command '+id);
    }
}

module.exports = BonApp;