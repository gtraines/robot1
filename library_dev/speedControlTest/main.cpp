#include <iostream>
#include "SpeedControl.h"
#include <exception>


/*
 * Test Scenarios:
 * - Attach, move forward from stop, Should add move forward operations
 * - Attach, move backward from stop, should add change direction and move backward operations
 * - Attach, move forward from stop, move backward, should add move forward operations, change directions (move backward operations), add move backward operations
 * - Attach, move backward from stop, move forward
 */
int testScenario_moveForwardFromStop_checkOperations() {
    int loopUnavailableForCommand = 0;
    int commandSpeed = 3;
    auto tazer = SpeedControl();
    auto speedControlServo = Servo();

    int incrementMillis = 50;

    tazer.attach(speedControlServo, incrementMillis);

    auto command = new SpeedControlCommand(commandSpeed);
    tazer.commandMove(*command);

    auto operationCount = tazer._operationsQueue.size();

    auto remainingTime = tazer.incrementTimeStep();

    auto operationCountAfterIncrement = tazer._operationsQueue.size();

    if (operationCountAfterIncrement != (operationCount - 1)) {
        throw std::exception();
    }

    return remainingTime;

}

int testScenario(int startingSpeed, int endingSpeed, int incrementMillis) {
    int loopUnavailableForCommand = 0;
    int commandSpeed = startingSpeed;
    auto* tazer = new SpeedControl();
    auto* speedControlServo = new Servo();

    tazer->attach(*speedControlServo, incrementMillis);

    for (int incrementLoop = 0; incrementLoop < 100; incrementLoop++) {
        try {

            if (tazer->availableToReceiveCommand()) {

                auto* command = new SpeedControlCommand(commandSpeed);
                tazer->commandMove(*command);
                commandSpeed++;
            }
            else {
                loopUnavailableForCommand++;
            }

            tazer->incrementTimeStep();
            int lastRecvd = speedControlServo->getLastWrote();
            std::cout << lastRecvd << std::endl;

        }
        catch (std::exception &exception) {
            std::cout << exception.what() << std::endl;
            return -1;
        }
    }

    std::cout << loopUnavailableForCommand << std::endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

int main() {

    auto resultOfScenario1 = testScenario_moveForwardFromStop_checkOperations();
    std::cout << resultOfScenario1 << std::endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}