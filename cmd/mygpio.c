#include <command.h>

static int do_mygpio(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[]) 
{
	printf("Hello world from cmd '%s'.\n", argv[0]);
	return 0;
}

U_BOOT_CMD(
	mygpio, 3, 1, do_mygpio,
	"output gpio register address for a given GPIO.",
	"usage: mygpio GPIO_INDEX GPIO_TAG:\n"
	" - GPIO_INDEX: index of GPIO group, 0 for GPIO0, 1 for GPIO1 and so on,\n"
	" - GPIO_TAG: tag of a GPIO in GPIO group, such as B4, A3 and so on\n");