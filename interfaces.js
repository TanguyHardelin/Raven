// This file was generated by Raven
const Plugin = require('./Plugins/Kernel/Plugin')

class FrontApps extends Plugin{
	constructor(){
		super()
		this.params = {};
	}

}

class SQL_BDD extends Plugin{
	constructor(){
		super()
		this.params = {"host":"localhost","user":"raven","password":"4VXQgAyhnB$","database":"raven"};
	}

	userLogin(data,cb){}
	addUser(data,cb){}
	runSQLCommand(command,cb){}
}

class Secure extends Plugin{
	constructor(){
		super()
		this.params = {"authorisationList":{"BONAPP":1,"EUREKART":2,"TANGUY_WEBSITE":4,"RAVENBOT_USER":8,"RAVENBOT_ADMIN":16,"OPTION_5":32,"OPTION_6":64,"OPTION_7":128,"OPTION_8":256,"OPTION_9":512,"OPTION_10":1024,"OPTION_11":2048,"OPTION_12":4096,"OPTION_13":8192,"OPTION_14":16384,"OPTION_15":32768,"OPTION_16":65536,"OPTION_17":131072,"OPTION_18":262144,"OPTION_19":524288,"OPTION_20":1048576,"OPTION_21":2097152,"OPTION_22":4194304,"OPTION_23":8388608,"OPTION_24":16777216,"OPTION_25":33554432,"OPTION_26":67108864,"OPTION_27":134217728,"ADD_USER":268435456,"MESSAGES_AUTHORISATION":536870912,"ADMIN_AUTHORISATION":1073741824,"SUPER_ADMIN_AUTHORISATION":2147483648},"url":"192.168.0.122","ravenLoginPagePath":"/RavenApp/ravenLogin/","ravenLoginPageName":"ravenLogin"};
	}

	get(URL,cb,authorisation){}
	post(URL,cb,authorisation){}
	addApplication(name,applicationPath,authorisation){}
	getAllUsersConnected(){}
	getAuthorisationList(){}
}

class WebAPI extends Plugin{
	constructor(){
		super()
		this.params = {"url":["http://192.168.0.122","http://www.192.168.0.122"],"ravenPort":5000,"clientPort":5000};
	}

	addApplication(name,applicationPath){}
	add(URL,cb){}
	get(URL,cb){}
	post(URL,cb){}
	getExpressServer(){}
}

class WebSocket extends Plugin{
	constructor(){
		super()
		this.params = {"needReadyMessage":true,"readyMessage":"ready"};
	}

	createSocketIOServer(expressServer){}
	getSocketIO(){}
	sendToAllClient(evt,msg){}
	addSocketAPI(evt,cb){}
	handleNewConnection(cb){}
}


class BonApp extends Plugin{
	constructor(){
		super()
		this.params = {};
	}

}

class Empty extends Plugin{
	constructor(){
		super()
		this.params = {};
	}

}

class GmailBot extends Plugin{
	constructor(){
		super()
		this.params = {};
	}

}

class Hackaton extends Plugin{
	constructor(){
		super()
		this.params = {};
	}

}

class RavenAdministrationPanel extends Plugin{
	constructor(){
		super()
		this.params = {};
	}

}

class ResumeWebsite extends Plugin{
	constructor(){
		super()
		this.params = {};
	}

}

class Interfaces extends Plugin{
	constructor(){
		super()
		this.FrontApps= new FrontApps();
		this.SQL_BDD= new SQL_BDD();
		this.Secure= new Secure();
		this.WebAPI= new WebAPI();
		this.WebSocket= new WebSocket();
		this.BonApp= new BonApp();
		this.Empty= new Empty();
		this.GmailBot= new GmailBot();
		this.Hackaton= new Hackaton();
		this.RavenAdministrationPanel= new RavenAdministrationPanel();
		this.ResumeWebsite= new ResumeWebsite();
	}
}
module.exports = Interfaces