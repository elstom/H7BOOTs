#include <app.h>

static uint32_t app_entry = APP_ENTRY_ADDR;

/**
 * @brief 初始化应用程序
 */
void App_Init(void)
{
    // 初始化硬件（QSPI、SDRAM、UART 等）
    QSPI_Init();
    FMC_SDRAM_Init();
    UART_Init();

    // 配置应用程序运行时环境（如栈、堆）
    __set_MSP(APP_STACK_SIZE); // 设置栈指针
    // 其他初始化（如中断、时钟）
}

/**
 * @brief 运行应用程序主逻辑
 */
void App_Run(void)
{
    UART_Print("Application running...\n");
    while (1)
    {
        // 应用程序主循环（业务逻辑）
        HAL_Delay(1000); // 示例延迟
        UART_Print("App tick\n");
    }
}

/**
 * @brief 跳转到应用程序入口
 * @param entry 入口地址
 */
void App_Jump(uint32_t entry)
{
    app_entry = entry;
    __disable_irq();           // 关闭中断
    SysTick->CTRL = 0;         // 禁用 SysTick
    SCB->VTOR = app_entry;     // 更新向量表
    ((void (*)())app_entry)(); // 跳转
}