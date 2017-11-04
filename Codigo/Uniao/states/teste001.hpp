#ifndef teste001_HPP
#define teste001_HPP

#include "robotinostate.hpp"

class teste001: public RobotinoState
{
public:
    /** Singleton. */
    static teste001 *instance();

    /**
    * Called when entering the teste001 state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to teste001.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the teste001 state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    teste001();
    ~teste001();
};

#endif