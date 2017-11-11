#ifndef IRDISTPELAPAREDE2_HPP
#define IRDISTPELAPAREDE2_HPP

#include "robotinostate.hpp"

class IrDistPelaParede2: public RobotinoState
{
public:
    /** Singleton. */
    static IrDistPelaParede2 *instance();

    /**
    * Called when entering the IrParedePelaParede state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to IrParedePelaParede.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the IrParedePelaParede state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    IrDistPelaParede2();
    ~IrDistPelaParede2();
};

#endif