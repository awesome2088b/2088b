#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}


 //* Runs the user autonomous code. This function will be started in its own task
 //* with the default priority and stack size whenever the robot is enabled via
// * the Field Management System or the VEX Competition Switch in the autonomous
//  * mode. Alternatively, this function may be called in initialize or opcontrol
//  * for non-competition testing purposes.
//  *
//  * If the robot is disabled or communications is lost, the autonomous task
//  * will be stopped. Re-enabling the robot will restart the task, not re-start it
//  * from where it left off.
//  */


//highest for movement is 127
void autonomouskill() {
    intaker(200);
    forward(170);
    left(210);
    pros::c::delay(500);
    clampPiston.set_value(true);
    pros::c::delay(1000);
    backward(450);
    pros::c::delay(800);
    clampPiston.set_value(false);
    right(110);
    backward(600);
    pros::c::delay(500);
    clampPiston.set_value(true);
    forward(100);
    left(50);
    forward(2000);

    // clampPiston.set_value(true);
    // right(180);
    // pros::delay(50);
    // backward(1000);
    // pros::delay(50);
    // clampPiston.set_value(false);
    // intaker(2000);
    // right(90);
    // pros::delay(50);
    // forward(3000);
    // intaker(2000);
    // pros::delay(30);
    // right(90);
    // pros::delay(30);
    // forward(2000);
    // intaker(2000);
    // pros::delay(30);
    // right(90);
    // forward(1000);
    // intaker(2000);
    // pros::delay(200);
    // intaker(5000);
    // forward(500);
    // pros::delay(100);
    // left(180);
    // intaker(3000);
    // forward(200);
    // pros::delay(20);
    // backward(300);
    // clampPiston.setValue(true);
}

void autonomous() {

    clampPiston.set_value(true);
    backward(350);
    pros::delay(550);
    clampPiston.set_value(false);
    pros::delay(500);
    intaker(1000);
    left(370);
    pros::delay(300);
    forward(220);
    intaker(2000);
    pros::delay(200);
    left(220);
    forward(170);
    pros::delay(500);
    intaker(2000);
    pros::delay(700);
    left(280);
    forward(1000);
}


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.CONTROLLER_MASTER
 */



void opcontrol() {
    pros::Controller master(pros::E_CONTROLLER_MASTER);
    pros::Motor left_mtr_front(-20);
    pros::Motor left_mtr_back(-15);
    pros::Motor left_mtr_middle(-18);
    pros::Motor right_mtr_front(19);
    pros::Motor right_mtr_back(16);
    pros::Motor right_mtr_middle(17);
    pros::Motor intake(-7);


    pros::ADIAnalogOut clampPiston('A');


//drivetrain

    int left;
    int right;


    int forward;
    int turning;

    bool clampToggle = false;

    while (true) {
        forward = master.get_analog(ANALOG_RIGHT_X);
        turning = master.get_analog(ANALOG_LEFT_Y);

        right = forward - turning;
        left = forward + turning;

        left_mtr_front.move(left);
        left_mtr_back.move(left);
        left_mtr_middle.move(left);
        right_mtr_back.move(-right);
        right_mtr_front.move(-right);
        right_mtr_middle.move(-right);

        
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
        intake.move_voltage(120000.8);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
            intake.move_voltage(-120000.8);
        } else {
            intake.move_voltage(0);
            } 
        }
    }

void forward (int timedrive) {
    left_mtr_back.move(127);
    left_mtr_back.move(127);
    left_mtr_middle.move(127);
    right_mtr_front.move(127);
    right_mtr_back.move(127);
    right_mtr_middle.move(127);

    pros::delay(timedrive);
    left_mtr_back.move(0);
    left_mtr_back.move(0);
    left_mtr_middle.move(0);
    right_mtr_front.move(0);
    right_mtr_back.move(0);
    right_mtr_middle.move(0);
}
void backward (int timedrive) {
    left_mtr_back.move(-127);
    left_mtr_back.move(-127);
    left_mtr_middle.move(-127);
    right_mtr_front.move(-127);
    right_mtr_back.move(-127);
    right_mtr_middle.move(-127);

    pros::delay(timedrive);
    left_mtr_back.move(0);
    left_mtr_back.move(0);
    left_mtr_middle.move(0);
    right_mtr_front.move(0);
    right_mtr_back.move(0);
    right_mtr_middle.move(0);
}

void right(int timedrive) {
    left_mtr_back.move(127);
    left_mtr_back.move(127);
    left_mtr_middle.move(127);
    right_mtr_front.move(-127);
    right_mtr_back.move(-127);
    right_mtr_middle.move(-127);

    pros::delay(timedrive);
    left_mtr_back.move(0);
    left_mtr_back.move(0);
    left_mtr_middle.move(0);
    right_mtr_front.move(0);
    right_mtr_back.move(0);
    right_mtr_middle.move(0);

}

void left(int timedrive) {
    left_mtr_back.move(-127);
    left_mtr_back.move(-127);
    left_mtr_middle.move(-127);
    right_mtr_front.move(127);
    right_mtr_back.move(127);
    right_mtr_middle.move(127);

    pros::delay(timedrive);

    left_mtr_back.move(0);
    left_mtr_back.move(0);
    left_mtr_middle.move(0);
    right_mtr_front.move(0);
    right_mtr_back.move(0);
    right_mtr_middle.move(0);
}

void intaker(int timeSpin) {
intake.move_voltage(12000);
pros::delay(timeSpin);
intake.move_voltage(0);
}






// 	pros::Controller master(pros::E_CONTROLLER_MASTER);
//     // pros:: radio_port({11});
//     pros::Motor intake_port({15}); //i dunno i think this is actually a conveyor belt port, but it might not work
// 	pros::MotorGroup left_mg({16, -17, 18});    // changed middle from negitive to positive. change back if any errors occur
// 	pros::MotorGroup right_mg({-12, -13, -14});  // swtich ports with left_mg if does not work.

// //ncooking!!!!


// 	while (true) {
// 		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
// 						(pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
// 		                (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);  // Prints status of the emulated screen LCDs

// 		// Arcade control scheme
// 		int dir = master.get_analog(ANALOG_LEFT_Y);    // amount forward/backward from left joystick
// 		int turn = master.get_analog(ANALOG_RIGHT_X);  // turn left/right from right g
// 		left_mg.move(dir - turn);                      // left motor voltage
// 		right_mg.move(dir + turn);                     // right motor voltage
// 		pros::delay(20); 
// 		pros::motor_brake_mode_e_t driver_preference_brake = MOTOR_BRAKE_COAST;

// 	pros::Controller master(pros::E_CONTROLLER_MASTER);
//     pros::Motor left_mtr_front(-20);
//     pros::Motor left_mtr_back(-15);
//     pros::Motor left_mtr_middle (-18);
//     pros::Motor right_mtr_front(19);
//     pros::Motor right_mtr_back(-16);
//     pros::Motor right_mtr_middle(17);
//     pros::Motor intake(-7);
    



//     pros::adi::DigitalOut clampPiston('a'); 

// //drivetrain

//     int left;
//     int right;

//     int forward;
//     int turning;

//     bool clampToggle = false;

//     while (true) {

//         forward = master.get_analog(ANALOG_RIGHT_X);
//         turning = master.get_analog(ANALOG_LEFT_Y);

//         right = forward - turning;
//         left = forward + turning;

//         left_mtr_front.move(left);
//         left_mtr_back.move(left);
//         left_mtr_middle.move(left);
//         right_mtr_front.move(-right);
//         right_mtr_back.move(-right);
//         right_mtr_middle.move(-right);

//         if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
//             intake.move_voltage(120000.8);
//         } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
//             intake.move_voltage(-120000.8);
//         } else {
//             intake.move_voltage(0);
//         }

//         if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
//             clampToggle = !clampToggle;
//             clampPiston.set_value(clampToggle);
//         }
//     }

// 	}                              // Run for 20 ms then update
// 		}

 //i changed .8 to .9 on line 136 and 138s, change back if any problems occur 
