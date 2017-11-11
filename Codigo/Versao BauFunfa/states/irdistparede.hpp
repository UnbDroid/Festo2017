#ifndef IrDistPelaParede_HPP
#define IrDistPelaParede_HPP

#include "robotinostate.hpp"

class IrDistPelaParede: public RobotinoState
{
public:
    /** Singleton. */
    static IrDistPelaParede *instance();

    /**
    * Called when entering the IrDistPelaParede state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to IrDistPelaParede.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the IrDistPelaParede state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    IrDistPelaParede();
    ~IrDistPelaParede();
};

#endif