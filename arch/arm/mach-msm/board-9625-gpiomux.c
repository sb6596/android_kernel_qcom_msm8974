/* Copyright (c) 2012, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/init.h>
#include <linux/ioport.h>
#include <mach/board.h>
#include <mach/gpio.h>
#include <mach/gpiomux.h>

static struct gpiomux_setting gpio_uart_config = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_HIGH,
};

static struct gpiomux_setting gpio_spi_cs_config = {
	.func = GPIOMUX_FUNC_9,
	.drv = GPIOMUX_DRV_12MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gpio_spi_config = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_12MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct msm_gpiomux_config msm_blsp_configs[] __initdata = {
	{
		.gpio      = 8,	       /* BLSP1 UART TX */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_uart_config,
		},
	},
	{
		.gpio      = 9,	       /* BLSP1 UART RX */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_uart_config,
		},
	},
	{
		.gpio      = 69,		/* BLSP6 QUP SPI_CS_N */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_spi_cs_config,
		},
	},
	{
		.gpio      = 20,		/* BLSP6 QUP SPI_DATA_MOSI */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_spi_config,
		},
	},
	{
		.gpio      = 21,		/* BLSP6 QUP SPI_DATA_MISO */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_spi_config,
		},
	},
	{
		.gpio      = 23,		/* BLSP6 QUP SPI_CLK */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_spi_config,
		},
	},

};

static struct gpiomux_setting sdc3_clk_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting sdc3_cmd_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting sdc3_data_0_3_active_cfg = {
	.func = GPIOMUX_FUNC_6,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting sdc3_suspended_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting sdc3_data_1_suspended_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct msm_gpiomux_config sdc3_configs[] __initdata = {
	{
		.gpio      = 25,
		.settings = {
			[GPIOMUX_ACTIVE] = &sdc3_clk_active_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspended_cfg,
		},
	},
	{
		.gpio      = 24,
		.settings = {
			[GPIOMUX_ACTIVE] = &sdc3_cmd_active_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspended_cfg,
		},

	},
	{
		.gpio      = 16,
		.settings = {
			[GPIOMUX_ACTIVE] = &sdc3_data_0_3_active_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspended_cfg,
		},
	},
	{
		.gpio      = 17,
		.settings = {
			[GPIOMUX_ACTIVE] = &sdc3_data_0_3_active_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_data_1_suspended_cfg,
		},
	},
	{
		.gpio      = 18,
		.settings = {
			[GPIOMUX_ACTIVE] = &sdc3_data_0_3_active_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspended_cfg,
		},
	},
	{
		.gpio      = 19,
		.settings = {
			[GPIOMUX_ACTIVE] = &sdc3_data_0_3_active_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspended_cfg,
		},
	},
};

void __init msm9625_init_gpiomux(void)
{
	int rc;

	rc = msm_gpiomux_init(NR_GPIO_IRQS);
	if (rc) {
		pr_err(KERN_ERR "msm9625_init_gpiomux failed %d\n", rc);
		return;
	}

	msm_gpiomux_install(msm_blsp_configs, ARRAY_SIZE(msm_blsp_configs));
	msm_gpiomux_install(sdc3_configs, ARRAY_SIZE(sdc3_configs));
}
