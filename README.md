# SNES_ControllerPort_Bitbanger

WIRING ---------

SNES Latch ---> GPIO 6
SNES clk ---> GPIO 7
SNES Data ---> GPIO 8

-------------------

BUG{ 

The pulses on the data line for the controller port are lagging which causes ghosting for the buttons.

}
