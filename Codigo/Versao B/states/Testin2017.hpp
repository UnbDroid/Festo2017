#ifndef TESTIN2017_HPP
#define TESTIN2017_HPP

#include "robotinostate.hpp"

class Testin2017: public RobotinoState
{
public:
    /** Singleton. */
    static Testin2017 *instance();

    /**
    * Called when entering the Testin2017 state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to Testin2017.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the Testin2017 state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    Testin2017();
    ~Testin2017();
};

#endif
