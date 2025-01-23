# Electric MicroVan

The electric microvan features a compact design (3m long, 1m wide, 1.35m high). The roof (3m long, 1m wide) is covered with solar panels. It has four tubeless 20 by 4-inch fat tires, with the two rear wheels equipped with motors.

Inside, the space is divided horizontally into two main areas: the front cabin (1m x 1m x 1.35m) and the rear space (2m x 1m x 1.35m). The rear space is further divided vertically into two sections: the upper sleeping area (2m x 1m x 1m) and the lower storage area (2m x 1m x 35cm).

## Cabin

The cabin measures 1m by 1m and is 1.35m high. The cabin has two doors, each measuring 1.25m high and 55cm wide, located on each side at the rear part of the cabin. It front window located at the top measures 1m x 60cm.

The cabin can easily switch between three functions: driving cabin, working space, and kitchen.The main components of the cabin are detachable, leaving nearly the entire cabin space available for all purposes.


#### Detachable components

* **Steering:** The steering wheel and its column.
* **Seat:** The seat assembly measures 90cm x 40cm. It has a 5cm foam padding, and leather-like upholstery. It is mounted at the rear of the cabin, at 50cm high. It can be detached or folded downwards.
* **Table:** The table is a 1cm thick sheet of wood measuring 90cm by 55cm. The table can be hanged at the front side of the cabin, at 70cm height.

#### Fixed components

* **Shelves:**
* **Control panel:**


## Sleeping Area

## Storage Area

The lower storage area measures 2m by 1m and is 35cm high. It is divided into four separate cells (each measuring 1m by 50cm). The cells are accessible via four doors (measuring 90cm x 30cm), with two on each side.


# Subsystems

## Lighting Subsystem

This subsystem controls the light, and consists of:

*   **Board:** Arduino One v3 (ATmega328P)
*   **Input:**  One rotary encoder with push button, with a knob named "LEVEL"
*   **Output:** One neopixel LED (ws2812b)

At initialization, the light is off. Pressing the button toggles the light. Rotating the knob clockwise increases the intensity of the light, rotating it counter-clockwise decreases it.

## Weather Subsystem

This subsystem measures and records the weather, and consists of:

* **Board:** WeAct Studio STM32F405
* **Motion sensor** mpu6050
* **Pressure sensor:**  bmp280
* **Magnetic sensor:**  qmc5883l
* **GPS**:** neo6m

