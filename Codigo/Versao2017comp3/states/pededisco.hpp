#ifndef PedeDisco_HPP
#define PedeDisco_HPP

#include "robotinostate.hpp"

class PedeDisco: public RobotinoState
{
public:
    /** Singleton. */
    static PedeDisco *instance();

    /**
    * Called when entering the PedeDisco state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to PedeDisco.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the PedeDisco state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    PedeDisco();
    ~PedeDisco();
};

#endif