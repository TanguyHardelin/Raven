DROP DATABASE IF EXISTS raven;
CREATE DATABASE raven;
USE raven;

CREATE TABLE Users(
    id INT UNSIGNED PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(256) UNIQUE NOT NULL,
    password VARCHAR(256) NOT NULL,
    authorisation BIGINT
);

CREATE TABLE Request (
    id INT UNSIGNED PRIMARY KEY AUTO_INCREMENT,
    email CHAR(255),
    request TEXT
);


CREATE TABLE Inventory(
    id INT UNSIGNED PRIMARY KEY AUTO_INCREMENT,
    user_id INT UNSIGNED,
    ingredient VARCHAR(256),
    is_to_buy BOOLEAN,
    CONSTRAINT user_id FOREIGN KEY (user_id) REFERENCES Users(id)
);

CREATE TABLE Recipe(
    id INT UNSIGNED PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(1000),
    image VARCHAR(1000),
    link VARCHAR(256),
    time_of_preparation INT,
    time_of_backing INT,
    time_of_cooking INT,
    difficulty SMALLINT,
    cost SMALLINT,
    number_person SMALLINT,
    ingredient_0 VARCHAR(256),
    ingredient_1 VARCHAR(256),
    ingredient_2 VARCHAR(256),
    ingredient_3 VARCHAR(256),
    ingredient_4 VARCHAR(256),
    ingredient_5 VARCHAR(256),
    ingredient_6 VARCHAR(256),
    ingredient_7 VARCHAR(256),
    ingredient_8 VARCHAR(256),
    ingredient_9 VARCHAR(256),
    ingredient_10 VARCHAR(256),
    ingredient_11 VARCHAR(256),
    ingredient_12 VARCHAR(256),
    ingredient_13 VARCHAR(256),
    ingredient_14 VARCHAR(256),
    ingredient_15 VARCHAR(256),
    ingredient_16 VARCHAR(256),
    ingredient_17 VARCHAR(256),
    ingredient_18 VARCHAR(256),
    ingredient_19 VARCHAR(256),
    ingredient_20 VARCHAR(256),
    ingredient_21 VARCHAR(256),
    ingredient_22 VARCHAR(256),
    ingredient_23 VARCHAR(256),
    ingredient_24 VARCHAR(256),
    ingredient_25 VARCHAR(256),
    ingredient_26 VARCHAR(256),
    ingredient_27 VARCHAR(256),
    ingredient_28 VARCHAR(256),
    ingredient_29 VARCHAR(256),
    ingredient_quantity_0 SMALLINT,
    ingredient_quantity_1 SMALLINT,
    ingredient_quantity_2 SMALLINT,
    ingredient_quantity_3 SMALLINT,
    ingredient_quantity_4 SMALLINT,
    ingredient_quantity_5 SMALLINT,
    ingredient_quantity_6 SMALLINT,
    ingredient_quantity_7 SMALLINT,
    ingredient_quantity_8 SMALLINT,
    ingredient_quantity_9 SMALLINT,
    ingredient_quantity_10 SMALLINT,
    ingredient_quantity_11 SMALLINT,
    ingredient_quantity_12 SMALLINT,
    ingredient_quantity_13 SMALLINT,
    ingredient_quantity_14 SMALLINT,
    ingredient_quantity_15 SMALLINT,
    ingredient_quantity_16 SMALLINT,
    ingredient_quantity_17 SMALLINT,
    ingredient_quantity_18 SMALLINT,
    ingredient_quantity_19 SMALLINT,
    ingredient_quantity_20 SMALLINT,
    ingredient_quantity_21 SMALLINT,
    ingredient_quantity_22 SMALLINT,
    ingredient_quantity_23 SMALLINT,
    ingredient_quantity_24 SMALLINT,
    ingredient_quantity_25 SMALLINT,
    ingredient_quantity_26 SMALLINT,
    ingredient_quantity_27 SMALLINT,
    ingredient_quantity_28 SMALLINT,
    ingredient_quantity_29 SMALLINT,
    instruction_0 VARCHAR(256),
    instruction_1 VARCHAR(256),
    instruction_2 VARCHAR(256),
    instruction_3 VARCHAR(256),
    instruction_4 VARCHAR(256),
    instruction_5 VARCHAR(256),
    instruction_6 VARCHAR(256),
    instruction_7 VARCHAR(256),
    instruction_8 VARCHAR(256),
    instruction_9 VARCHAR(256),
    instruction_10 VARCHAR(256),
    instruction_11 VARCHAR(256),
    instruction_12 VARCHAR(256),
    instruction_13 VARCHAR(256),
    instruction_14 VARCHAR(256),
    instruction_15 VARCHAR(256),
    instruction_16 VARCHAR(256),
    instruction_17 VARCHAR(256),
    instruction_18 VARCHAR(256),
    instruction_19 VARCHAR(256),
    instruction_20 VARCHAR(256),
    instruction_21 VARCHAR(256),
    instruction_22 VARCHAR(256),
    instruction_23 VARCHAR(256),
    instruction_24 VARCHAR(256),
    instruction_25 VARCHAR(256),
    instruction_26 VARCHAR(256),
    instruction_27 VARCHAR(256),
    instruction_28 VARCHAR(256),
    instruction_29 VARCHAR(256)
);

CREATE TABLE List_of_recipe(
    id INT UNSIGNED PRIMARY KEY AUTO_INCREMENT,
    recipe_id INT UNSIGNED,
    date_of_recipe DATE,
    CONSTRAINT recipe_id FOREIGN KEY (recipe_id) REFERENCES Recipe(id)
);
INSERT INTO Users VALUES(1,'tanguy','1234',0xFFFFFFFF);