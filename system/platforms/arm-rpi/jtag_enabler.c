// Broadcom BCM 2835 Function Select Register Addresses
#define BCM_2835_FUNCTION_SELECT_REG_0 0x20200000
#define BCM_2835_FUNCTION_SELECT_REG_1 0x20200004
#define BCM_2835_FUNCTION_SELECT_REG_2 0x20200008

// Function Selection Values
#define FUNCTION_SELECT_ALT4 0b011
#define FUNCTION_SELECT_ALT5 0b010

// GPIO4, ALT4 provides ARM_TDI
#define GPIO4_FUNCTION_SELECT_REG	BCM_2835_FUNCTION_SELECT_REG_0
#define GPIO4_FUNCTION_SELECT_VALUE	FUNCTION_SELECT_ALT5
#define GPIO4_FUNCTION_BIT_OFFSET	12

// GPIO22, ALT5 provides ARM_TRST
#define GPIO22_FUNCTION_SELECT_REG	BCM_2835_FUNCTION_SELECT_REG_2
#define GPIO22_FUNCTION_SELECT_VALUE	FUNCTION_SELECT_ALT4
#define GPIO22_FUNCTION_BIT_OFFSET	6

// GPIO23, ALT5 provides ARM_RTCK
#define GPIO23_FUNCTION_SELECT_REG	BCM_2835_FUNCTION_SELECT_REG_2
#define GPIO23_FUNCTION_SELECT_VALUE	FUNCTION_SELECT_ALT4
#define GPIO23_FUNCTION_BIT_OFFSET	9

// GPIO24, ALT5 provides ARM_TDO
#define GPIO24_FUNCTION_SELECT_REG	BCM_2835_FUNCTION_SELECT_REG_2
#define GPIO24_FUNCTION_SELECT_VALUE	FUNCTION_SELECT_ALT4
#define GPIO24_FUNCTION_BIT_OFFSET	12

// GPIO25, ALT5 provides ARM_TCK
#define GPIO25_FUNCTION_SELECT_REG	BCM_2835_FUNCTION_SELECT_REG_2
#define GPIO25_FUNCTION_SELECT_VALUE	FUNCTION_SELECT_ALT4
#define GPIO25_FUNCTION_BIT_OFFSET	15

// GPIO25, ALT5 provides ARM_TMS
#define GPIO27_FUNCTION_SELECT_REG	BCM_2835_FUNCTION_SELECT_REG_2
#define GPIO27_FUNCTION_SELECT_VALUE	FUNCTION_SELECT_ALT4
#define GPIO27_FUNCTION_BIT_OFFSET	21

// 3-Bit Mask
#define FUNCTION_SELECT_VALUE_MASK	0b111

void change_gpio_function(int *function_select_register, int function_select_value, int bit_offset);
void clear_gpio_function(int *function_select_register, int bit_offset);
void set_gpio_function(int *function_select_register, int function_select_value, int bit_offset);

void enable_jtag (void) {
	change_gpio_function((int *)GPIO4_FUNCTION_SELECT_REG, GPIO4_FUNCTION_SELECT_VALUE, GPIO4_FUNCTION_BIT_OFFSET);
	change_gpio_function((int *)GPIO22_FUNCTION_SELECT_REG, GPIO22_FUNCTION_SELECT_VALUE, GPIO22_FUNCTION_BIT_OFFSET);
	change_gpio_function((int *)GPIO23_FUNCTION_SELECT_REG, GPIO23_FUNCTION_SELECT_VALUE, GPIO23_FUNCTION_BIT_OFFSET);
	change_gpio_function((int *)GPIO24_FUNCTION_SELECT_REG, GPIO24_FUNCTION_SELECT_VALUE, GPIO24_FUNCTION_BIT_OFFSET);
	change_gpio_function((int *)GPIO25_FUNCTION_SELECT_REG, GPIO25_FUNCTION_SELECT_VALUE, GPIO25_FUNCTION_BIT_OFFSET);
	change_gpio_function((int *)GPIO27_FUNCTION_SELECT_REG, GPIO27_FUNCTION_SELECT_VALUE, GPIO27_FUNCTION_BIT_OFFSET);
}

void change_gpio_function(int *function_select_register, int function_select_value, int bit_offset) {
	clear_gpio_function(function_select_register, bit_offset);
	set_gpio_function(function_select_register, function_select_value, bit_offset);
}

void clear_gpio_function(int *function_select_register, int bit_offset) {
	*function_select_register &= ~(FUNCTION_SELECT_VALUE_MASK << bit_offset);
}

void set_gpio_function(int *function_select_register, int function_select_value, int bit_offset) {
	*function_select_register |= function_select_value << bit_offset;
}
