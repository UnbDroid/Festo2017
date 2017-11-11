#ifndef Modulo3_2017v2_HPP
#define Modulo3_2017v2_HPP

#include "robotinostate.hpp"

class Modulo3_2017v2: public RobotinoState
{
public:
    /** Singleton. */
    static Modulo3_2017v2 *instance();

    /**
    * Called when entering the Modulo3_2017v2 state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to Modulo3_2017v2.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the Modulo3_2017v2 state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    Modulo3_2017v2();
    ~Modulo3_2017v2();
};

#endif
