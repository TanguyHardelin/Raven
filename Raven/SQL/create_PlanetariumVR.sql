USE raven;

CREATE TABLE planetariumVR(
    id INT UNSIGNED PRIMARY KEY AUTO_INCREMENT,
    mass TEXT,
    name TEXT,
    position TEXT,
    speed TEXT,
    radius TEXT,
    acceleration TEXT
);

INSERT INTO planetariumVR(name,mass,position,speed,acceleration,radius) VALUES ("Sun",'19891','0,0,0','0,0,0','0,0,0','696');
INSERT INTO planetariumVR(name,mass,position,speed,acceleration,radius) VALUES ("Mercury",'0.003','57,0,0','0,0,0','0,0,0','2');
INSERT INTO planetariumVR(name,mass,position,speed,acceleration,radius) VALUES ("Venus",'0.04','108,0,0','0,0,0','0,0,0','6');
INSERT INTO planetariumVR(name,mass,position,speed,acceleration,radius) VALUES ("Earth",'0.06','149,0,0','0,0,0','0,0,0','6');
INSERT INTO planetariumVR(name,mass,position,speed,acceleration,radius) VALUES ("Mars",'0.00006','249,0,0','0,0,0','0,0,0','3');
INSERT INTO planetariumVR(name,mass,position,speed,acceleration,radius) VALUES ("Jupiter",'18','816,0,0','0,0,0','0,0,0','71');
INSERT INTO planetariumVR(name,mass,position,speed,acceleration,radius) VALUES ("Saturn",'5','1503,0,0','0,0,0','0,0,0','60');
INSERT INTO planetariumVR(name,mass,position,speed,acceleration,radius) VALUES ("Uranus",'1','2870,0,0','0,0,0','0,0,0','25');
INSERT INTO planetariumVR(name,mass,position,speed,acceleration,radius) VALUES ("Neptune",'1','4498,0,0','0,0,0','0,0,0','24');