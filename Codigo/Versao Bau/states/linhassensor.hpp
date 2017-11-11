#ifndef LINHASSENSOR_HPP
#define LINHASSENSOR_HPP

#include "robotinostate.hpp"

class LinhasSensor: public RobotinoState
{
public:
    /** Singleton. */
    static LinhasSensor *instance();

    /**
    * Called when entering the LinhasSensor state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to LinhasSensor.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the LinhasSensor state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    LinhasSensor();
    ~LinhasSensor();
};

#endif