#ifndef testeAlinhaFrente_HPP
#define testeAlinhaFrente_HPP

#include "robotinostate.hpp"

class testeAlinhaFrente: public RobotinoState
{
public:
    /** Singleton. */
    static testeAlinhaFrente *instance();

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
    testeAlinhaFrente();
    ~testeAlinhaFrente();
};

#endif