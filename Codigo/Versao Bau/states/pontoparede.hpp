#ifndef PONTOPAREDE_HPP
#define PONTOPAREDE_HPP

#include "robotinostate.hpp"

class PontoParede: public RobotinoState
{
public:
    /** Singleton. */
    static PontoParede *instance();

    /**
    * Called when entering the IrParaParede state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to IrParaParede.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the IrParaParede state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    PontoParede();
    ~PontoParede();
};

#endif