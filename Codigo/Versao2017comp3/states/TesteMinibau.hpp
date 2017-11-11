#ifndef TesteMinibau_HPP
#define TesteMinibau_HPP

#include "robotinostate.hpp"

class TesteMinibau: public RobotinoState
{
public:
    /** Singleton. */
    static TesteMinibau *instance();

    /**
    * Called when entering the TesteMinibau state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to TesteMinibau.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the TesteMinibau state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    TesteMinibau();
    ~TesteMinibau();
};

#endif