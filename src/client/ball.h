#ifndef BALL_H
#define BALL_H

class Ball{
    public:
        friend class World;
        float x_position;
        float y_position;
        Ball();

        ~Ball();
};

#endif