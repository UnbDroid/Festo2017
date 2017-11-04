#ifndef teste002IrAtePonto_HPP
#define teste002IrAtePonto_HPP

#include "robotinostate.hpp"

class teste002IrAtePonto: public RobotinoState
{
public:
    /** Singleton. */
    static teste002IrAtePonto *instance();

    /**
    * Called when entering the teste002IrAtePonto state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to teste002IrAtePonto.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the teste002IrAtePonto state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    teste002IrAtePonto();
    ~teste002IrAtePonto();
};

#endif