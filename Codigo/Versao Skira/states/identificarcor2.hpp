#ifndef IDENTIFICARCOR2_HPP
#define IDENTIFICARCOR2_HPP

#include "robotinostate.hpp"

class IdentificarCor2: public RobotinoState
{
public:
    /** Singleton. */
    static IdentificarCor2 *instance();

    /**
    * Called when entering the IdentificarCor state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to IdentificarCor.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the IdentificarCor state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    IdentificarCor2();
    ~IdentificarCor2();
};

#endif