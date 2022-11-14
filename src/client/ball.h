#ifndef BALL_H
#define BALL_H

class Ball{
    private:
        friend class World;
        float x_position;
        float y_position;
    public:
        Ball();

        ~Ball();
};

#endif