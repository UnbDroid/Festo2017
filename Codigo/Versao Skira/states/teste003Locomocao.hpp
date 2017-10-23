#ifndef teste003Locomocao_HPP
#define teste003Locomocao_HPP

#include "robotinostate.hpp"

class teste003Locomocao: public RobotinoState
{
public:
    /** Singleton. */
    static teste003Locomocao *instance();

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
    teste003Locomocao();
    ~teste003Locomocao();
};

#endif