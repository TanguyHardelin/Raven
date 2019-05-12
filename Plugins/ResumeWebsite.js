const Plugin= require('./Kernel/Plugin');
const iplocation = require("iplocation").default;

class ResumeWebsite extends Plugin{
    constructor(params){
        super(params);
        this.addDependencies('webAPI')
        this.addDependencies('SQL_BDD')
    }


    __get_current_date_in_sql_format__(){
        let date;
        date = new Date();
        date = date.getUTCFullYear() + '-' +
            ('00' + (date.getUTCMonth()+1)).slice(-2) + '-' +
            ('00' + date.getUTCDate()).slice(-2) + ' ' + 
            ('00' + date.getUTCHours()).slice(-2) + ':' + 
            ('00' + date.getUTCMinutes()).slice(-2) + ':' + 
            ('00' + date.getUTCSeconds()).slice(-2);

           return date;
    }

    __start__(){
        let self=this;
        return new Promise((resolve,err)=>{
            self.plugins.WebAPI.get('/tracker/:action/:value',(req,res)=>{
                //Get ip
                let ip = req.headers['x-forwarded-for'] || req.connection.remoteAddress;
                ip=ip.split(`:`).pop();

                //Get date
                let date=self.__get_current_date_in_sql_format__();

                //Log it
                self.log("new action IP = "+ip+" action= "+req.params.action+" date= "+date);

                //If new insert ip in IP tables
                self.plugins.SQL_BDD.runSQLCommand("SELECT id FROM CV_IP_List WHERE ip='"+ip+"'",(d)=>{
                    if(d.length==0){
                        self.plugins.SQL_BDD.runSQLCommand("INSERT INTO CV_IP_List(ip,seen) VALUES ('"+ip+"',FALSE)",()=>{});

                        self.plugins.SQL_BDD.runSQLCommand("SELECT id FROM CV_IP_List WHERE ip='"+ip+"'",(data)=>{
                            //Insert it to action table:
                            self.plugins.SQL_BDD.runSQLCommand("INSERT INTO CV_IP_Actions(ip_id,action_type,action_value,action_date) VALUES ("+data[0].id+",'"+req.params.action+"','"+req.params.value+"','"+date+"')",()=>{});
                        });
                    }
                    else{
                    self.plugins.SQL_BDD.runSQLCommand("UPDATE CV_IP_List SET seen = FALSE WHERE ip='"+ip+"'",()=>{});
                        self.plugins.SQL_BDD.runSQLCommand("INSERT INTO CV_IP_Actions(ip_id,action_type,action_value,action_date) VALUES ("+d[0].id+",'"+req.params.action+"','"+req.params.value+"','"+date+"')",()=>{});
                    }
                    
                });
                res.json({error:"none"});
            });

            self.plugins.Secure.get('/getAllTracker',(req,res)=>{
                //Get ip
                let ip = req.headers['x-forwarded-for'] || req.connection.remoteAddress;
                ip=ip.split(`:`).pop();

                //Get date
                let date=self.__get_current_date_in_sql_format__();

                //Log it
                self.log("new action IP = "+ip+" action= "+req.params.action+" date= "+date);

                //If new insert ip in IP tables
                self.plugins.SQL_BDD.runSQLCommand("SELECT id FROM CV_IP_List",(data)=>{
                    /*
                    let r={};
                    self.plugins.SQL_BDD.runSQLCommand("SELECT ip,seen,action_type,action_value,action_date FROM CV_IP_Actions INNER JOIN CV_IP_List ON CV_IP_List.id=CV_IP_Actions.ip_id",(data)=>{
                        for(let i=0;i<data.length;i++){
                            if( r[data[i].ip] == undefined) r[data[i].ip]=[]
                            r[data[i].ip].push({action_type:data[i].action_type,action_date:data[i].action_date,action_value:data[i].action_value,seen:data[i].seen})
                        }
                        res.json({error:false,result:r})
                    });
                    */
                    let r=[]
                    self.plugins.SQL_BDD.runSQLCommand("SELECT ip,seen,action_type,action_value,action_date FROM CV_IP_Actions INNER JOIN CV_IP_List ON CV_IP_List.id=CV_IP_Actions.ip_id",(data)=>{
                        for(let i=0;i<data.length;i++){
                            if(r[data[i].ip] === undefined){
                                r.push({})
                                r["ip"] = data[i].ip
                                r["name"] = data[i].ip
                                r["notifications"] = []
                            }
                            r["notifications"].push(data[i].action_type)
                        }
                        res.json({error:false,result:r})
                        
                    });

                });                
            });

            self.plugins.Secure.get('/markTrackerAsSeen/:ip',(req,res)=>{
                self.plugins.SQL_BDD.runSQLCommand("UPDATE CV_IP_List SET seen = TRUE WHERE ip='"+req.params.ip+"'",()=>{});       
            });
            self.plugins.Secure.get('/markTrackerAsUnSeen/:ip',(req,res)=>{
                self.plugins.SQL_BDD.runSQLCommand("UPDATE CV_IP_List SET seen = FALSE WHERE ip='"+req.params.ip+"'",()=>{});       
            });

            self.plugins.Secure.get('/getIPInfo/:ip',(req,res)=>{
                iplocation(req.params.ip, [], (error, result) => {
                    res.json(result);
                });
            });

            self.plugins.WebAPI.get('/sendEmail/:email/:name/:enterprise/:object/:content',(req,res)=>{
                let data={};
                data["userEmail"]=this.params["emailTanguy"];
                data["subject"]="[Raven][SiteWeb] "+req.params.object;
                
                data["text"]=req.params.name+" ("+req.params.email+")"+" de l'entreprise "+req.params.enterprise+" vous a laissé le message suivant: \n"+req.params.content.toString();

                self.plugins.GmailBot.sendEmail(data,(success)=>{
                    if(success){
                        res.json({error:false})
                    }
                    else{
                        res.json({error:true})
                    }
                });
                
            });
            
            resolve();
        })
    }
}

module.exports = ResumeWebsite;