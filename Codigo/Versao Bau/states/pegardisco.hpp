#ifndef PEGARDISCO_HPP
#define PEGARDISCO_HPP

#include "robotinostate.hpp"

class PegarDisco: public RobotinoState
{
public:
    /** Singleton. */
    static PegarDisco *instance();

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
    PegarDisco();
    ~PegarDisco();
};

#endif