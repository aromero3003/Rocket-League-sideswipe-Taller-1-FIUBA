#ifndef COMMAND_H
#define COMMAND_H

#define PRESS_RIGHT 65
#define PRESS_LEFT 66
#define PRESS_SPACE 67

#define RELEASE_RIGHT 68
#define RELEASE_LEFT 69
#define RELEASE_SPACE 70

class Command{
    private:
        int id;
        int command_num;
    public:
        Command(int i, int command_num);

        int get_command();

        ~Command();
};

#endif