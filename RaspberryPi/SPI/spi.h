/*
 * SPI testing utility (using spidev driver)
 *
 * Copyright (c) 2007  MontaVista Software, Inc.
 * Copyright (c) 2007  Anton Vorontsov <avorontsov@ru.mvista.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * Cross-compile with cross-gcc -I/path/to/cross-kernel/include
 */
 /*
  * SPI (format : uint8)
  * Copyright  : Dongwoon <wdk1121@naver.com>
  * 
  * static void transfer(int fd,uint8_t* tx,uint8_t* rx,uint32_t Array_size)
  * Array_size 크기에 맞는 tx, rx buffer 안에 Data를 SPI_Full_Duplex_Line
  *  
  */
#ifndef __SPI_H
#define __SPI_H
 
#include <stdint.h> //int format define
#include <unistd.h> //process control
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h> //control file
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
/*Basic ErrorPrint in Console*/

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
static void pabort(const char *s)
{
	perror(s);
	abort();
}

static const char *device = "/dev/spidev0.0";
static uint8_t mode;
static uint8_t bits = 8;
static uint32_t speed = 500000;
static uint16_t delay;
 
static void transfer(int fd,uint8_t* tx,uint8_t* rx,uint32_t Array_size)
{
	int ret;
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx,
		.rx_buf = (unsigned long)rx,
		.len = (uint32_t)Array_size,//.len = ARRAY_SIZE(tx),//
		.speed_hz = speed,
		.delay_usecs = delay,
		.bits_per_word = bits,
	};
	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
		pabort("can't send spi message");
	for (ret = 0; ret < (int)Array_size; ret++) {
		if (!(ret % Array_size))
			puts("");
		printf("%.2X ", rx[ret]);
	}
	puts("");
}
/*SPI 모드설정 Print*/
/*
static void print_usage(const char *prog)
{
	printf("Usage: %s [-DsbdlHOLC3]\n", prog);
	puts("  -D --device   device to use (default /dev/spidev1.1)\n"
	     "  -s --speed    max speed (Hz)\n"
	     "  -d --delay    delay (usec)\n"
	     "  -b --bpw      bits per word \n"
	     "  -l --loop     loopback\n"
	     "  -H --cpha     clock phase\n"
	     "  -O --cpol     clock polarity\n"
	     "  -L --lsb      least significant bit first\n"
	     "  -C --cs-high  chip select active high\n"
	     "  -3 --3wire    SI/SO signals shared\n");
	exit(1);
}

//SPI 모드설정

static void parse_opts(int argc, char *argv[])
{
	while (1) {
		static const struct option lopts[] = {
			{ "device",  1, 0, 'D' },
			{ "speed",   1, 0, 's' },
			{ "delay",   1, 0, 'd' },
			{ "bpw",     1, 0, 'b' },
			{ "loop",    0, 0, 'l' },
			{ "cpha",    0, 0, 'H' },
			{ "cpol",    0, 0, 'O' },
			{ "lsb",     0, 0, 'L' },
			{ "cs-high", 0, 0, 'C' },
			{ "3wire",   0, 0, '3' },
			{ "no-cs",   0, 0, 'N' },
			{ "ready",   0, 0, 'R' },
			{ NULL, 0, 0, 0 },
		};
		int c;
		//Option Check
		c = getopt_long(argc, argv, "D:s:d:b:lHOLC3NR", lopts, NULL);
 
		if (c == -1)
			break;
 
		switch (c) {
		case 'D':
			device = optarg;
			break;
		case 's':
			speed = atoi(optarg);
			break;
		case 'd':
			delay = atoi(optarg);
			break;
		case 'b':
			bits = atoi(optarg);
			break;
		case 'l':
			mode |= SPI_LOOP;
			break;
		case 'H':
			mode |= SPI_CPHA;
			break;
		case 'O':
			mode |= SPI_CPOL;
			break;
		case 'L':
			mode |= SPI_LSB_FIRST;
			break;
		case 'C':
			mode |= SPI_CS_HIGH;
			break;
		case '3':
			mode |= SPI_3WIRE;
			break;
		case 'N':
			mode |= SPI_NO_CS;
			break;
		case 'R':
			mode |= SPI_READY;
			break;
		default:
			print_usage(argv[0]);
			break;
		}
	}
}*/
 
void spi_main(uint8_t* tx,uint8_t* rx,uint32_t Array_size)
{
	
	int ret = 0;
	int fd;
	//SPI 모드 설정
	//parse_opts(argc, &argv);
	
	fd = open(device, O_RDWR);
	if (fd < 0)
		pabort("can't open device");

	/*
	 * spi mode
	 */
	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1)
		pabort("can't set spi mode");
 
	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
	if (ret == -1)
		pabort("can't get spi mode");
 
	/*
	 * bits per word
	 */
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1)
		pabort("can't set bits per word");
 
	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret == -1)
		pabort("can't get bits per word");
 
	/*
	 * max speed hz
	 */
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		pabort("can't set max speed hz");
 
	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		pabort("can't get max speed hz");
 
	printf("spi mode: %d\n", mode);
	printf("bits per word: %d\n", bits);
	printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);
	transfer(fd,tx,rx,Array_size);
	close(fd);
 
	//return ret;
}

#endif /* __SPI_H */
