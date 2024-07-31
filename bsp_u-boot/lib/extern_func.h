/************************************************/
/*						*/
/*	extern_func.h				*/	
/*						*/
/************************************************/

#ifndef _EXTERN_FUNC_H_
#define _EXTERN_FUNC_H_


extern int printf(const char* fmt, ...);
extern int usb_init(void);
extern int usb_stor_scan(int mode);
extern int usb_host_eth_scan(int mode);
extern int usb_stop(void);
extern void* memcpy(void*, const void*, size_t);
extern void app_startup(char * const *);
extern int do_fat_fswrite(cmd_tbl_t *cmdtp, int flag,int argc, char * const argv[]);
extern int do_fat_fsload(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
extern void *malloc(size_t);
extern int sprintf(char *buf, const char *fmt, ...)
                __attribute__ ((format (__printf__, 2, 3)));
extern size_t strlen(const char * s);
extern char * strcat(char * dest, const char * src);
extern struct usb_device *usb_get_dev_index(int index);

//GPIO
extern int gpio_request(unsigned gpio, const char *label);
extern int gpio_free(unsigned gpio);
extern int gpio_direction_input(unsigned gpio);
extern int gpio_direction_output(unsigned gpio, int value);
extern int gpio_get_value(unsigned gpio);
extern int gpio_set_value(unsigned gpio, int value);


#endif  /* EXTERN_FUNC_H_ */

