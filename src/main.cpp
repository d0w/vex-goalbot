#include "main.h"
#define LEFT_WHEELS_PORT 6
#define RIGHT_WHEELS_PORT 8
#define ARM_PORT 12

#define FRONT_BUMPER_PORT 'a'
#define UPPER_LIMIT_SWITCH_PORT 'h'
#define LOWER_LIMIT_SWITCH_PORT 'i'
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

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

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
 * task, not resume it from where it left off.
 */
void opcontrol() {
	// construction
  pros::Motor left_wheels (LEFT_WHEELS_PORT);
  pros::Motor right_wheels (RIGHT_WHEELS_PORT, true);
	pros::Motor arm(ARM_PORT, MOTOR_GEARSET_36); // arm motor has 100 rpm (red) gearset
  pros::Controller master (CONTROLLER_MASTER);

	pros::ADIDigitalIn claw_bumper(FRONT_BUMPER_PORT);
	pros::ADIDigitalIn lower_limit(LOWER_LIMIT_SWITCH_PORT);
	pros::ADIDigitalIn upper_limit(UPPER_LIMIT_SWITCH_PORT);

  while (true) {
		// arcade driving
    int power = master.get_analog(ANALOG_LEFT_Y);
    int turn = master.get_analog(ANALOG_RIGHT_X);
    int left = power + turn;
    int right = power - turn;
    left_wheels.move(left);
    right_wheels.move(right);

		// bumper
		if (claw_bumper.get_value()) {
			// while the upper limit switch is not pressed, move the arm upwards
			while (!upper_limit.get_value()) {
					arm.move_velocity(100);
			}
		}

		// arm movement
		if (master.get_digital(DIGITAL_R1)) {
			arm.move_velocity(100); // this is going up
		}
		else if (master.get_digital(DIGITAL_R2) && !lower_limit.get_value()) {
			arm.move_velocity(-100); // this is going down
		}
		else {
			arm.move_velocity(0);
		}


    pros::delay(2);
  }
}
