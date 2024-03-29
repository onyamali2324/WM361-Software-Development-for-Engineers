# FloorBot Commander | Compilation & Execution Instructions

## How to Run

To run the code just run the executable file located in the Build folder.


Alternatively:

In order to run the CLI application for FloorBot Commander, just run the code located in file "_RunMe.cpp" this will print in the terminal what you need. Alternatively if you do no have an IDE (such as VSCode) in a terminal move into the folder where all the files are located and run the following:

```
g++ _RunMe.cpp -o _RunMe && "absolute_path_to_folder"_Run
```

This is assuming you have g++ compiler available.

## How to use once running

### Account Login

Once the script has been started it will prompt to login, currently there is 3 different accounts with different access levels:

| Username | Password | Access Level |
| -------- | -------- | ------------ |
| user     | user     | 0            |
| owner    | owner    | 1            |
| admin    | admin    | 2            |

If there's an issue with the login, you will need to run the script again, following the stepsin the previous paragraph.

Once logged in it conjnects automatically to the robot.

### Command List

Once logged in you will now have access to a list of commands depending on your access level. There is two type of commands, the get commands which allow you to access information about the robot and set commands which allow for customisation on the robot.

Addtionally there is some movement commands that allow to move the robot when it has been moved to manual mode.

If the user is done, simply enter exit and the program will terminate.

To enter the commands just type it after the ">" in the terminal and press Enter, be mindful to not add spaces before or after your command as it will return an error and will prompt for a new command.

#### Get Commands

| Command          | Return                    | Minimum Access Level Required |
| ---------------- | ------------------------- | ----------------------------- |
| getrobotspeed    | Speed Mode                | 0                             |
| getrobotbattery  | Battery Percentage        | 0                             |
| getrobotpower    | Power Mode                | 0                             |
| getadvanceddata  | Advanced Data Structure   | 1                             |
| getbasicdata     | Basic Data Structure      | 0                             |
| getrobotstatus   | Robot Status              | 0                             |
| getrobotschedule | Latest Set Schedule       | 0                             |
| updatecli        | If CLI update available   | 2                             |
| updaterobot      | If robot update available | 2                             |

#### Set Commands

| Command          | Argument                              | Modified                      | Access Level required |
| ---------------- | ------------------------------------- | ----------------------------- | --------------------- |
| setrobotspeed    | {Low,Medium,High}, not case sensitive | Speed Mode                    | 1                     |
| setrobotpower    | {Low,Medium,High}, not case sensitive | Power Mode                    | 1                     |
| setrobotschedule | Integer                               | Next Scheduled Cleaningeaning | 1                     |
| setmanual        | NA                                    | Mode                          | 0                     |

#### Movement Commands

| Command | Movement Direction |
| ------- | ------------------ |
| w       | Forward            |
| a       | Left               |
| s       | Backward           |
| d       | Right              |
