AirBnB Clone
AirBnB Clone is a project to replicate the functionality of the AirBnB website. The project provides a command line interface for managing objects like houses, apartments, rooms, etc.

Command Interpreter
The Command Interpreter is the main component of the AirBnB Clone project. It is a command line interface that allows users to interact with the objects in the system.

How to start it
To start the Command Interpreter, simply run the following command in your terminal:

javascript
./console.py

How to use it
The Command Interpreter provides a prompt where you can enter commands to interact with the objects in the system. The following are some of the supported commands:

create <class_name>: Creates a new object of the specified class and saves it to the system
show <class_name> <object_id>: Shows the information of the object with the specified id and class
destroy <class_name> <object_id>: Deletes the object with the specified id and class from the system
all: Shows all objects in the system
update <class_name> <object_id> <attribute_name> <attribute_value>: Updates the attribute of the object with the specified id and class
Examples
Here are some examples of using the Command Interpreter:

(hbnb) create BaseModel
d0c8e60f-f456-4a32-9c6e-06e7fad637e1
(hbnb) show BaseModel d0c8e60f-f456-4a32-9c6e-06e7fad637e1
[BaseModel] (d0c8e60f-f456-4a32-9c6e-06e7fad637e1) {'created_at': datetime.datetime(2023, 2, 6, 22, 41, 42, 998048), 'id': 'd0c8e60f-f456-4a32-9c6e-06e7fad637e1', 'updated_at': datetime.datetime(2023, 2, 6, 22, 41, 42, 998087)}
(hbnb) destroy BaseModel d0c8e60f-f456-4a32-9c6e-06e7fad637e1
(hbnb) all
[]'
