#ifndef testeSkira001_HPP
#define testeSkira001_HPP

#include "robotinostate.hpp"

class testeSkira001: public RobotinoState
{
public:
    /** Singleton. */
    static testeSkira001 *instance();

    /**
    * Called when entering the testeSkira001 state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to testeSkira001.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the testeSkira001 state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    testeSkira001();
    ~testeSkira001();
};

#endif