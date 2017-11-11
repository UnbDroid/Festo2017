#ifndef PedeCor_HPP
#define PedeCor_HPP

#include "robotinostate.hpp"

class PedeCor: public RobotinoState
{
public:
    /** Singleton. */
    static PedeCor *instance();

    /**
    * Called when entering the PedeCor state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to PedeCor.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the PedeCor state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    PedeCor();
    ~PedeCor();
};

#endif