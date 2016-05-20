/*
* Copyright (c) 2016, Wind River Systems, Inc.
*
* Redistribution and use in source and binary forms, with or without modification, are
* permitted provided that the following conditions are met:
*
* 1) Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
*
* 2) Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* 3) Neither the name of Wind River Systems nor the names of its contributors may be
* used to endorse or promote products derived from this software without specific
* prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


/*
 * DESCRIPTION
 * A sample application to blink the LED on the Intel Galileo Gen2 board.
 *
 * The LED is located between the USB host and device ports, on the same side
 * of the board as the Ethernet connector.  Internally, it is connected to
 * GPIO Pin 7 which is also broken out on IO13 of the Arduino header.
 *
 * The program will set up the required GPIO pins and then toggle the LED
 * 10 times with a 1 second delay in between.
 */


#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#include "gpioutils.h"

/*******************************************************************************
* err_exit - Called when an error condition occurs.
*
* De-allocates all the GPIO pins the program uses and calls exit(-1)
*/

static void err_exit(void)
{
    (void)gpio_dealloc(30);
    (void)gpio_dealloc(46);
    (void)gpio_dealloc(7);

    exit (-1);
}

/*******************************************************************************
* main - User application entry function
*
* This the the entry point for a VxWorks User Mode application
*/

int main(int argc, char *argv[])
{
    int i;

    /*
     * Create the required GPIO pins and reserve them
     */

    if (gpio_alloc(30))   /* Create /sys/class/gpio/gpio30 (Internal MUX) */
        err_exit();

    if (gpio_alloc(46))   /* Create /sys/class/gpio/gpio46 (Internal MUX) */
        err_exit();

    if (gpio_alloc(7))    /* Create /sys/class/gpio/gpio7  (Arduino IO13) */
        err_exit();

    /*
     * Setup GPIO30. Output and LOW
     */

    if (gpio_set_direction(30, "out"))
        err_exit();

    if (gpio_write_pin(30, "0"))
        err_exit();


    /*
     * Set up GPIO 46. Output and LOW
     */

    if (gpio_set_direction(46, "out"))
        err_exit();

    if (gpio_write_pin(46, "0"))
        err_exit();


    /*
     * Setup GPIO7. Output. GPIO7 is connected to the LED
     */

    if (gpio_set_direction(7, "out"))
        err_exit();

    /*
     * Flash the LED 10 times with ~1 second delay in between
     */
    for (i=0; i < 10; i++)
        {
        if (gpio_write_pin(7, "0"))    /* Turn the LED off */
            err_exit();

        sleep(1);                      /* Wait ~1 second */

        if (gpio_write_pin(7, "1"))    /* Turn the LED on */
            err_exit();

        sleep(1);
        }


    /*
     * Clean up
     */
    if (gpio_write_pin(7, "0"))       /* Turn the LED off */
            err_exit();

    if (gpio_dealloc(30))   /* Unreserve /sys/class/gpio/gpio30 (Internal MUX) */
        err_exit();

    if (gpio_dealloc(46))    /* Unreserve /sys/class/gpio/gpio46 (Internal MUX) */
        err_exit();

    if (gpio_dealloc(7))    /* Unreserve /sys/class/gpio/gpio7  (Arduino IO13) */
        err_exit();

    return(0);
}
