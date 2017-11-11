#ifndef Modulo1Tunado_HPP
#define Modulo1Tunado_HPP

#include "robotinostate.hpp"

class Modulo1Tunado: public RobotinoState
{
public:
    /** Singleton. */
    static Modulo1Tunado *instance();

    /**
    * Called when entering the Modulo1Tunado state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to Modulo1Tunado.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the Modulo1Tunado state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    Modulo1Tunado();
    ~Modulo1Tunado();
};

#endif
