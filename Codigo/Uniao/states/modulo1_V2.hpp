#ifndef MODULO1_V2_HPP
#define MODULO1_V2_HPP

#include "robotinostate.hpp"

class Modulo1_V2: public RobotinoState
{
public:
    /** Singleton. */
    static Modulo1_V2 *instance();

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
    Modulo1_V2();
    ~Modulo1_V2();
};

#endif
