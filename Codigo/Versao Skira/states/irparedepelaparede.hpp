<<<<<<< HEAD
#ifndef IRPAREDEPELAPAREDE_HPP
=======
#ifndef IRPARADEPELAPAREDE_HPP
>>>>>>> 2ab142e143f7a5275d43ec3494c4c49516242b3a
#define IRPAREDEPELAPAREDE_HPP

#include "robotinostate.hpp"

class IrParedePelaParede: public RobotinoState
{
public:
    /** Singleton. */
    static IrParedePelaParede *instance();

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
    IrParedePelaParede();
    ~IrParedePelaParede();
};

#endif