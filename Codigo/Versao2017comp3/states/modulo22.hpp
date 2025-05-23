#ifndef MODULO22_HPP
#define MODULO22_HPP

#include "robotinostate.hpp"

class Modulo22: public RobotinoState
{
public:
    /** Singleton. */
    static Modulo22 *instance();

    /**
    * Called when entering the Test state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to Test.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the Test state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    Modulo22();
    ~Modulo22();
};

#endif
