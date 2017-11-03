#ifndef teste004Circuito_HPP
#define teste004Circuito_HPP

#include "robotinostate.hpp"

class teste004Circuito: public RobotinoState
{
public:
    /** Singleton. */
    static teste004Circuito *instance();

    /**
    * Called when entering the teste003Locomocao state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to teste003Locomocao.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the teste003Locomocao state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    teste004Circuito();
    ~teste004Circuito();
};

#endif