/* tuxctl-ioctl.c
 *
 * Driver (skeleton) for the mp2 tuxcontrollers for ECE391 at UIUC.
 *
 * Mark Murphy 2006
 * Andrew Ofisher 2007
 * Steve Lumetta 12-13 Sep 2009
 * Puskar Naha 2013
 */

#include <asm/current.h>
#include <asm/uaccess.h>

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/file.h>
#include <linux/miscdevice.h>
#include <linux/kdev_t.h>
#include <linux/tty.h>
#include <linux/spinlock.h>

#include "tuxctl-ld.h"
#include "tuxctl-ioctl.h"
#include "mtcp.h"

#define debug(str, ...) \
	printk(KERN_DEBUG "%s: " str, __FUNCTION__, ## __VA_ARGS__)

int a_flag;
int set_button(struct tty_struct* tty, unsigned long arg);
unsigned char button_packets [2];
unsigned char pre_state [6];
int tux_init(struct tty_struct* tty);
/************************ Protocol Implementation *************************/

/* tuxctl_handle_packet()
 * IMPORTANT : Read the header for tuxctl_ldisc_data_callback() in 
 * tuxctl-ld.c. It calls this function, so all warnings there apply 
 * here as well.
 */
void tuxctl_handle_packet (struct tty_struct* tty, unsigned char* packet)
{
    unsigned a, b, c;

    a = packet[0]; /* Avoid printk() sign extending the 8-bit */
    b = packet[1]; /* values when printing them. */
    c = packet[2];
	switch(a) {
		case MTCP_ACK:
            a_flag = 1; //set MTCP_ACK on
            break;
        case MTCP_RESET:
            tux_init(tty);
            tuxctl_ldisc_put(tty, pre_state, 6);
            break;
        case MTCP_BIOC_EVENT:
            button_packets[0] = b;
            button_packets[1] = c;
            break;
  		default:
            break;

    }

    /*printk("packet : %x %x %x\n", a, b, c); */
}

/******** IMPORTANT NOTE: READ THIS BEFORE IMPLEMENTING THE IOCTLS ************
 *                                                                            *
 * The ioctls should not spend any time waiting for responses to the commands *
 * they send to the controller. The data is sent over the serial line at      *
 * 9600 BAUD. At this rate, a byte takes approximately 1 millisecond to       *
 * transmit; this means that there will be about 9 milliseconds between       *
 * the time you request that the low-level serial driver send the             *
 * 6-byte SET_LEDS packet and the time the 3-byte ACK packet finishes         *
 * arriving. This is far too long a time for a system call to take. The       *
 * ioctls should return immediately with success if their parameters are      *
 * valid.                                                                     *
 *                                                                            *
 ******************************************************************************/




int tuxctl_ioctl (struct tty_struct* tty, struct file* file, 
	      unsigned cmd, unsigned long arg)
{
    switch (cmd) {
	case TUX_INIT:
		tux_init(tty);
		return 0;
	case TUX_BUTTONS:
		return set_button(tty, arg);
	case TUX_SET_LED:
		if (a_flag == 0){
			return 0;
		}
		a_flag = 0;
		return set_led(tty, arg);
	case TUX_LED_ACK:
		return 0;
	case TUX_LED_REQUEST:
		return 0;
	case TUX_READ_LED:
		return 0;
	default:
	    return -EINVAL;
    }
}



/*
 * tux_init
 *   DESCRIPTION: Takes no arguments. 
 * 		Initializes any variables associated with the driver and returns 0. 
 * 	Assume that any user-level code that interacts with your device will call 
 * 	this ioctl before any others.
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: 0
 *   SIDE EFFECTS: none
 */
int tux_init(struct tty_struct* tty){
	unsigned char temp[2];
	temp[0] = MTCP_BIOC_ON;
	temp[1] = MTCP_LED_USR;
	a_flag = 0;
	tuxctl_ldisc_put(tty, temp, 2);
	return 0;
	
}
/*
 * set_led
 *   DESCRIPTION: The argument is a 32-bit integer of the following form: The low 16-bits 
 * specify a number whose hexadecimal value is to be displayed on the 7-segment 
 * displays. The low 4 bits of the third byte specifies which LED’s should be turned on. 
 * The low 4 bits of the highest byte (bits 27:24) specify whether the corresponding decimal points should be turned on. This ioctl should return 0.
 *   INPUTS: arg: led information
 *   OUTPUTS: none
 *   RETURN VALUE: 0 (if success)
 *   SIDE EFFECTS: none
 */
int set_led(struct tty_struct* tty, unsigned long arg){
	//00000100 00001111 stands for 040f, second decimal point should be on
	//and all four led should works
	unsigned char output[6];
	int i;
	unsigned char number[11] = {0xE7, 0x06, 0xCB, 0x8F, 0x2E, 0xAD, 0xED, 0x86, 0xEF, 0xAF, 0x00};//0,1,2,3,4,5,6,7,8,9, NONE
	//the forth led won't be on if the minute is smaller than 10
	// if ((arg >> 12) & 0xF != 0){
	// 	output[1] = 0x0F;
	// }
	// else{
	// 	output[1] = 0x07;
	// }
	output[0] = MTCP_LED_SET;
	for (i = 0; i < 4; i++){
		unsigned char temp;
		int hnumber;
		temp = (arg >> (4*i)) & 0xF;
		hnumber = number[temp];
		if (i == 2){//in this case it's the third led, we need add a dot
			hnumber |= 0x10; //set dot
		}
		if ((i == 3)&&(temp == 0)){
			hnumber = number[10];
		}
		output[i+2] = hnumber;
	}
	output[1] = 0x0F; //should ask, why it's not working
	//reset case
	for (i=0; i < 6; i++){
		pre_state[i] = output[i];
	}


	tuxctl_ldisc_put(tty, output, 6);
	return 0;
}



/*
 * set_button
 *   DESCRIPTION: store the pressed button, rdlu cbas as final result
 *   INPUTS: arg -- pointer to user space
 *   OUTPUTS: none
 *   RETURN VALUE: 0 (if success), -EINVAL if pointer not valid
 *   SIDE EFFECTS: none
 */
int set_button(struct tty_struct* tty, unsigned long arg){

	//1xxxcbas
	//1xxxrdlu
	unsigned char cbas,rdlu,final,temp5,temp6;
	cbas = button_packets[0] & 0x0F; //get 0000cbas
	rdlu = button_packets[1] & 0x0F; //get 0000rdlu
	rdlu <<= 4; // get rdlu0000
	final = rdlu | cbas; //rdlucbas
	// we need rlducbas
	temp5 = final & 0x20;
	temp6 = final & 0x40;
	temp5 <<= 1;
	temp6 >>= 1;
	final &= 0x9F;
	final = final | temp5 | temp6;
	if (copy_to_user((void*)arg, &final ,sizeof(final)))
        return -EINVAL;
    else
        return 0;

}