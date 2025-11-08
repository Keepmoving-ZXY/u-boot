#include <command.h>

static int do_mygpio(struct cmd_tbl *cmdtp, int flag, int argc,
		     char *const argv[])
{
	static uint64_t gpio_base_addr[5] = { 0xFDD60000, 0xFE740000,
					      0xFE750000, 0xFE760000,
					      0xFE770000 };

	uint8_t target_bit = 0;
	uint32_t dr_reg_addr = 0;
	uint32_t ddr_reg_addr = 0;
	uint32_t ext_reg_addr = 0;
	uint16_t reg_val_high = 0;
	uint16_t reg_val_low = 0;
	uint32_t reg_val = 0;

	const char *ddr_reg_name = NULL;
	const char *ddr_reg_high_name = "GPIO_SWPORT_DDR_H";
	const char *ddr_reg_low_name = "GPIO_SWPORT_DDR_L";
	const char *dr_reg_name = NULL;
	const char *dr_reg_high_name = "GPIO_SWPORT_DR_H";
	const char *dr_reg_low_name = "GPIO_SWPORT_DR_L";

	uint8_t index = argv[1][0] - '0';
	ext_reg_addr = gpio_base_addr[index] + 0x70;

	target_bit = argv[2][1] - '0';
	ddr_reg_addr = gpio_base_addr[index];
	if (argv[2][0] == 'C' || argv[2][0] == 'D') {
		ddr_reg_addr += 0xc;
		ddr_reg_name = ddr_reg_high_name;
		if (argv[2][0] == 'D')
			target_bit += 0x8;
	} else {
		ddr_reg_addr += 0x8;
		ddr_reg_name = ddr_reg_low_name;
		if (argv[2][0] == 'B')
			target_bit += 0x8;
	}

	printf("Port Data Direction Register for GPIO%s %s:\n", argv[1],
	       argv[2]);
	printf("\t%s: 0x%08x\n", ddr_reg_name, ddr_reg_addr);
	printf("\tvalue:\n");

	reg_val_low = 1 << target_bit;
	reg_val_high = 1 << target_bit;
	reg_val = (uint32_t)(reg_val_high << 16) | reg_val_low;
	printf("\t\tout: 0x%x\n", reg_val);

	reg_val_low = 0;
	reg_val_high = 1 << target_bit;
	reg_val = (uint32_t)(reg_val_high << 16) | reg_val_low;
	printf("\t\tin: 0x%x\n", reg_val);

	printf("\n");

	target_bit = argv[2][1] - '0';
	dr_reg_addr = gpio_base_addr[index];
	if (argv[2][0] == 'C' || argv[2][0] == 'D') {
		dr_reg_addr += 0x4;
		dr_reg_name = dr_reg_high_name;
		if (argv[2][0] == 'D')
			target_bit += 0x8;
	} else {
		dr_reg_name = dr_reg_low_name;
		if (argv[2][0] == 'B')
			target_bit += 0x8;
	}

	printf("Port Data Register for GPIO%s %s:\n", argv[1], argv[2]);
	printf("\t%s: 0x%08x\n", dr_reg_name, dr_reg_addr);
	printf("\tvalue:\n");

	reg_val_low = 1 << target_bit;
	reg_val_high = 1 << target_bit;
	reg_val = (uint32_t)(reg_val_high << 16) | reg_val_low;
	printf("\t\tpull-up: 0x%x\n", reg_val);

	reg_val_low = 0;
	reg_val_high = 1 << target_bit;
	reg_val = (uint32_t)(reg_val_high << 16) | reg_val_low;
	printf("\t\tpull-down: 0x%x\n", reg_val);

	return 0;
}

U_BOOT_CMD(
	mygpio, 3, 1, do_mygpio,
	"output gpio register address for a given GPIO.",
	"usage: mygpio GPIO_INDEX GPIO_Port:\n"
	" - GPIO_INDEX: index of GPIO group, 0 for GPIO0, 1 for GPIO1 and so on,\n"
	" - GPIO_Port: Port of a GPIO in GPIO group, such as B4, A3 and so on\n");
