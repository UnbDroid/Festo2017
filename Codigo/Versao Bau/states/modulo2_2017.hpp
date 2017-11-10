#ifndef MODULO2_2017_HPP
#define MODULO2_2017_HPP

#include "robotinostate.hpp"

class Modulo2_2017: public RobotinoState
{
public:
    /** Singleton. */
    static Modulo2_2017 *instance();

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
    Modulo2_2017();
    ~Modulo2_2017();
};

#endif
