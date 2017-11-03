#ifndef ROBOTINOControleRemoto_HPP
#define ROBOTINOControleRemoto_HPP

#include "robotinostate.hpp"

class ControleRemoto: public RobotinoState
{
public:
    /** Singleton. */
    static ControleRemoto *instance();

    /**
    * Called when entering the ControleRemoto state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to ControleRemoto.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the ControleRemoto state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    ControleRemoto();
    ~ControleRemoto();
};

#endif