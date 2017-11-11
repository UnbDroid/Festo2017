#ifndef AlinhaFrenteParede_HPP
#define AlinhaFrenteParede_HPP

#include "robotinostate.hpp"

class AlinhaFrenteParede: public RobotinoState
{
public:
    /** Singleton. */
    static AlinhaFrenteParede *instance();

    /**
    * Called when entering the AlinhaFrenteParede state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to AlinhaFrenteParede.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the AlinhaFrenteParede state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    AlinhaFrenteParede();
    ~AlinhaFrenteParede();
};

#endif