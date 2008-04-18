/*
 * Implementation file for NovInt Falcon FindFalcon Example Program
 *
 * Copyright (c) 2007 Kyle Machulis <kyle@nonpolynomial.com> http://www.nonpolynomial.com
 *
 * Sourceforge project @ http://www.sourceforge.net/projects/libnifalcon
 *
 * This library is covered by the MIT License, read LICENSE for details.
 */

#include "nifalcon_test_fw.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define PACKET_TIMEOUT 1000

falcon_device dev;

void sigproc()
{
	printf("closing falcon and quitting\n");
	nifalcon_close(&dev);
	exit(0);
}

int main(int argc, char** argv)
{
	int num_falcons, status, i;
	unsigned int count;
	unsigned char input[17] = "<AAAAAAAAAAAAAA>";
	unsigned char output[17];	
	falcon_packet input_packet, output_packet;

	
	signal(SIGINT, sigproc);
	signal(SIGQUIT, sigproc);
	
	nifalcon_init(&dev);
	
	num_falcons = nifalcon_get_count(&dev);
	
	count = 0;
	input[16] = output[16] = 0;

	printf("Falcons found: %d\n", num_falcons);

	printf("Opening falcon\n");
	if((status = nifalcon_open(&dev, 0)) < 0)
	{
		printf ("Cannot open falcon! Error: %s\n", nifalcon_get_error_string(&dev));
		return 1;
	}
	printf("Opened falcon\n");
	printf("Loading firmware\n");
	for(i = 0; i < 5; ++i)
	{
		if((status = nifalcon_load_firmware(&dev, "test_firmware.bin")) == 0) break;
		printf("Firmware not loaded! Error: %d %s\nRetrying...\n", dev.falcon_error_code, nifalcon_get_error_string(&dev));
	}
	if(i == 5)
	{
		printf("Cannot load firmware! Bailing...\n");
		return 1;
	}
	printf("Firmware loaded\n");

	printf("Send Raw: %s\n", input);
	if(nifalcon_test_fw_send_raw(&dev, input) < 0)
	{
		printf("Write error: %s\n", nifalcon_get_error_string(&dev));
		return 1;
	}
	printf("Receive Raw: %s\n", output);
	if(nifalcon_test_fw_receive_raw(&dev, output, PACKET_TIMEOUT) < 0)
	{
		printf("Read error: %s\n", nifalcon_get_error_string(&dev));
		return 1;
	}
	

	nifalcon_test_fw_init_packet(&input_packet);
	nifalcon_test_fw_init_packet(&output_packet);
	while(1)
	{
		input_packet.info = NOVINT_TEST_FW_HOMING_MODE;
		if(!(output_packet.info & (NOVINT_TEST_FW_HOMED_AXIS1 | NOVINT_TEST_FW_HOMED_AXIS2 | NOVINT_TEST_FW_HOMED_AXIS3)))
		{
			input_packet.info |= NOVINT_TEST_FW_LED_RED;
		}
		else
		{
			input_packet.info |= NOVINT_TEST_FW_LED_GREEN;
		}
		printf("Writing %d\n", count);
		if(nifalcon_test_fw_send_struct(&dev, &input_packet) < 0)
		{
			printf("Write error: %s\n", nifalcon_get_error_string(&dev));
			return 1;
		}
		printf("reading %d\n", count);
		if(nifalcon_test_fw_receive_struct(&dev, &output_packet, PACKET_TIMEOUT) < 0)
		{
			printf("Read error: %s\n", nifalcon_get_error_string(&dev));
			return 1;
		}
		printf("%x %x %x %x\n", output_packet.motor[0], output_packet.motor[1], output_packet.motor[2], output_packet.info);
		++count;
	}

	nifalcon_close(&dev);
	return 0;
}
