#include <app.h>

#include "stm32h743xx.h"
#include "usb_host.h"
#include "fatfs.h"

extern SDRAM_HandleTypeDef hsdram1;
void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram);

/**
 * @brief 初始化应用程序
 */
void App_Init(void)
{
	SDRAM_Initialization_Sequence(&hsdram1);
	
}

/**
 * @brief 运行应用程序主逻辑
 */
void App_Run(void)
{
	
}

/**
 * @brief 跳转到应用程序入口
 * @param entry 入口地址
 */
extern USBH_HandleTypeDef hUsbHostHS;
void App_Jump(void)
{
    typedef void (*pFunction)(void);

	USBH_DeInit(&hUsbHostHS);
	// QSPI_MemoryMapped();

	__set_PRIMASK(1);

	SysTick->CTRL = 0;
	SysTick->LOAD = 0;
	SysTick->VAL = 0;

	HAL_RCC_DeInit();

	for (uint32_t i = 0; i < 8; i++) 
	{
		NVIC->ICER[i] = 0xFFFFFFFF;
		NVIC->ICPR[i] = 0xFFFFFFFF;
	}

	__set_PRIMASK(0);

	const pFunction JumpToApplication = (pFunction)(*(__IO uint32_t*)(QSPI_BASE + 4));
	__set_MSP(*(__IO uint32_t*) QSPI_BASE); 
	JumpToApplication();
}



void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram)
{
	FMC_SDRAM_CommandTypeDef command;

	// Step 1: 配置时钟启动命令
	command.CommandMode            = FMC_SDRAM_CMD_CLK_ENABLE;
	command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK2;
	command.AutoRefreshNumber      = 1;
	command.ModeRegisterDefinition = 0;

	HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT);

	// Step 2: 插入延时等待至少100微秒
	HAL_Delay(1);

	// Step 3: 发出全预充电命令
	command.CommandMode            = FMC_SDRAM_CMD_PALL;
	HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT);

	// Step 4: 发出自动刷新命令
	command.CommandMode            = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	command.AutoRefreshNumber      = 8;
	HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT);

	// Step 5: 加载模式寄存器
	command.CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
	command.ModeRegisterDefinition = SDRAM_MODEREG_BURST_LENGTH_1			|
									SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL		|
									SDRAM_MODEREG_CAS_LATENCY_3				|
									SDRAM_MODEREG_OPERATING_MODE_STANDARD	|
									SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
	HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT);

	// Step 6: 设置自动刷新率
	HAL_SDRAM_ProgramRefreshRate(hsdram, 683);  // 设置刷新率
}