#ifndef Modulo3_2017_HPP
#define Modulo3_2017_HPP

#include "robotinostate.hpp"

class Modulo3_2017: public RobotinoState
{
public:
    /** Singleton. */
    static Modulo3_2017 *instance();

    /**
    * Called when entering the Modulo3_2017 state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to Modulo3_2017.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the Modulo3_2017 state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    Modulo3_2017();
    ~Modulo3_2017();
};

#endif
