const Plugin= require('./Kernel/Plugin');
const ejs=require('ejs')
const randomstring = require("randomstring");

//TODO: supprimer ce merdier pas propre
let BONAP_AUTHORISATION=0x1;
let EUREKART_AUTHORISATION=0x1<<1;
let TANGUY_WEBSITE_AUTHORISATION=0x1<<2;


let ADD_USER_AUTHORISATION=0x1<<28;
let MESSAGES_AUTHORISATION=0x1<<29;
let ADMIN_AUTHORISATION=0x1<<30;
let SUPER_ADMIN_AUTHORISATION=0x1<<31;

class RavenAdministrationPanel extends Plugin{
    constructor(params){
        super(params);
        this.addDependencies('webAPI')
        this.addDependencies('Secure')
        
    }
    __start__(){
        let self=this;
        return new Promise((resolve,err)=>{
            //No secure API:
            
            // *addSignUpRequest* 
            // **Ne nécéssite pas un quelconque connexion**
            // Ajoute une requette d'inscription
            this.plugins.WebAPI.get('/addSignUpRequest/:email/:name/:text',(req,res)=>{
                let username=req.params.name;
                let email=req.params.email;
                let text=req.params.text

                username=this.stringToSQLString(username)
                email=this.stringToSQLString(email)
                text=this.stringToSQLString(text)
                

                let self=this;
                self.plugins.SQL_BDD.runSQLCommand('INSERT INTO Request VALUES (NULL,"'+email+'","'+username+'","'+text+'",false,false,"NONE")',()=>{
                    res.json({error:false});
                });
            });

            //Secure API:

            // *getAuthorizations* 
            // **Fonction lié au login de l'utilisateur**
            // Retourne toute les authorisations qu'a l'utilisateur
            this.plugins.Secure.get('/getAuthorizations',(req,res)=>{
                let self=this;
                let sessionID=req.cookies.sessionID;
                let authorisation=self.plugins.Secure.getAllUsersConnected()[sessionID].getAuthorisation();
                res.json(authorisation);
            });

            // *getAllUserConnected* 
            // **Nécéssite une authorisation admin ou super admin**
            // Retourne tous les utilisateurs connectés
            this.plugins.Secure.get('/getAllUserConnected',(req,res)=>{
                let self=this;
                let t={};
                t.users=new Array();
                for(let key in self.plugins.Secure.getAllUsersConnected()){
                    t.users.push({'sessionID':self.plugins.Secure.getAllUsersConnected()[key].user.getSessionID(),'username':self.plugins.Secure.getAllUsersConnected()[key].user.getUsername(),'authorisation':self.plugins.Secure.getAllUsersConnected()[key].user.getAuthorisation()})
                }
                res.json(t);
            
            },ADMIN_AUTHORISATION);

            // *getAllSignUpRequest* 
            // **Nécéssite une authorisation admin ou super admin**
            // Retourne toutes les requettes d'inscriptions saisis par l'utilisateur
            this.plugins.WebAPI.get('/getAllSignUpRequest',(req,res)=>{
                let self=this;
                self.plugins.SQL_BDD.runSQLCommand("SELECT * FROM Request",(data)=>{
                    res.json({all_request:data})
                });
            },ADMIN_AUTHORISATION||SUPER_ADMIN_AUTHORISATION);

            // *deleteRequestFromId* 
            // **Nécéssite une authorisation admin ou super admin**
            // Supprime une requette d'inscription grace à son ID
            this.plugins.WebAPI.get('/deleteRequestFromId/:id',(req,res)=>{
                let self=this;
                self.plugins.SQL_BDD.runSQLCommand("DELETE FROM Request WHERE id="+req.params.id,(data)=>{
                    res.json({error:false})
                });
            },ADMIN_AUTHORISATION||SUPER_ADMIN_AUTHORISATION);

            // *addUser* 
            // **Nécéssite une authorisation admin ou super admin**
            // Ajoute un utilisateur avec son authorisation associée
            this.plugins.Secure.get('/addUser/:authorisation',(rq,rs)=>{
                //TODO: securiser tout ça

                let APIKey=randomstring.generate(25);
                self.plugins.SQL_BDD.runSQLCommand("INSERT INTO SignUpURL VALUES (NULL,'"+APIKey+"',"+parseInt(rq.params.authorisation)+",'"+Date.now()+"')",(data)=>{ });
                this.plugins.WebAPI.get('/'+APIKey,(req,res)=>{
                    res.render('../EJS/createAccount.ejs',{APIKey:APIKey});
                })
                
                this.plugins.WebAPI.get('/'+APIKey+'/:username/:email/:password',(req,res)=>{
                    self.plugins.SQL_BDD.runSQLCommand("INSERT INTO Users(id,username,password,authorisation) VALUES (NULL,'"+req.params.username+"','"+req.params.password+"','"+parseInt(rq.params.authorisation)+"')",(data)=>{
                        self.valid('User '+req.params.username+" was added with "+rq.params.authorisation+" authorisation");
                        res.json({error:false});
                    });
                   
                });
                rs.json({url:APIKey});

            },ADD_USER_AUTHORISATION||ADMIN_AUTHORISATION||SUPER_ADMIN_AUTHORISATION);

            // *disconnectFromID* 
            // **Nécéssite une authorisation admin ou super admin**
            // Déconnecte un utilisateur grace à son ID
            this.plugins.Secure.get('/disconnectFromID/:sessionID',(req,res)=>{
                let sessionID=req.params.sessionID;
                delete self.plugins.Secure.getAllUsersConnected()[sessionID];

                res.json({error:false})
            },ADMIN_AUTHORISATION||SUPER_ADMIN_AUTHORISATION);

            resolve();
        })
    }   
}

module.exports = RavenAdministrationPanel;