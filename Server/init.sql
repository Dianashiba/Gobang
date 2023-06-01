CREATE TABLE users(
	id int PRIMARY KEY auto_increment,
	mac VARCHAR(100) not NULL UNIQUE,
	username VARCHAR(100) NOT NULL
)
SELECT * from users;