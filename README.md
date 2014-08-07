encoder_independent
===================

each encoder its own Arduino


When the interrupts for the encoder were attached to the same Arduino which controlls the stepper motors, weird things happened, e.g. at times the motor wouldn't run smoothly or the encoder output would suddenly rush and give tons of output even thoug the motor was still or the encoder output would make jumps. 
The idea was, that the interrupt service routines from the encoder interferes with the normal workflow of the motor control as the amount of data handeled by the interrupts was a lot. To make both motor and encoder work smoothly, the code was split up and put onto one Arduino which now controlls only the motor(s) (see stepper_motor_control) and one that controls only a single encoder per Arduino (encoder_independent). 
So far, the weird behaviour described above didn't occur.
