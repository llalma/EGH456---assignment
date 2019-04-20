/*
 *  ======== Assignment.c ========
 */

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Types.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Semaphore.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

/* Example/Board Header files */
#include "Board.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"

/* Graphics Library */
#include "grlib/grlib.h"
#include "grlib/widget.h"
#include "grlib/canvas.h"
#include "grlib/checkbox.h"
#include "grlib/container.h"
#include "grlib/pushbutton.h"
#include "grlib/radiobutton.h"
#include "grlib/slider.h"


/* driver Libraries */
//#include "drivers/pinout.h"
#include "drivers/buttons.h"
#include "drivers/opt3001.h"
#include "drivers/Kentec320x240x16_ssd2119_spi.h"


//****************************************************************************
//
// Globals
//
//****************************************************************************

/* Clock settings */
uint32_t g_ui32SysClock;

/* LCD screen- notsure what this is? */
tContext sContext;

/* UART Handling */
UART_Handle uart;

//*****************************************************************************
//
// Forward declarations for the globals required to define the widgets at
// compile-time.
//
//*****************************************************************************
void OnIntroPaint(tWidget *psWidget, tContext *psContext);
extern tCanvasWidget g_psPanels[];


//*****************************************************************************
//
// The first panel, which contains introductory text explaining the
// application.
//
//*****************************************************************************
Canvas(g_sIntroduction, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 0, 24,
       320, 166, (CANVAS_STYLE_FILL | CANVAS_STYLE_TEXT), 0, 0,ClrWhite, &g_sFontCm20, "LCD Working", 0, 0);



/*
 *  ======== UART Init ========
 */

void UART_setup(){
    //Setup UART in interrupt mode.
    //the read& write callback is the functions called when interupt occours

    Board_initUART();

    UART_Params uartParams;

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 9600;
    //uartParams.writeMode = UART_MODE_CALLBACK;
    //uartParams.readMode = UART_MODE_CALLBACK;
    //uartParams.writeCallback =  &writeCallback;
    //uartParams.readCallback =  &readCallback;
    uart = UART_open(Board_UART0, &uartParams);

    //UART_writePolling(uart, "UART Enabled", 12);
}

void LCD_Setup(Types_FreqHz cpufreq){
    //Set up Touch Screen

    //
    // Initialize the display driver.
    //
    Kentec320x240x16_SSD2119Init(cpufreq.lo);

    //
    // Initialize the graphics context.
    //
    GrContextInit(&sContext, &g_sKentec320x240x16_SSD2119);

    WidgetAdd(WIDGET_ROOT,(tWidget*) &g_sIntroduction);
    // Issue the initial paint request to the widgets.
    WidgetPaint(WIDGET_ROOT);
}
/*
 *  ======== main ========
 */
int main(void)
{
    //
    // Set the clocking to run directly from the crystal at 120MHz.
    //
    Types_FreqHz cpufreq;
    BIOS_getCpuFreq(&cpufreq);

    /* Call board init functions */
    Board_initGeneral();
    Board_initGPIO();
    Board_initI2C();

    UART_setup();
    LCD_Setup(cpufreq);




   while(1){
       WidgetMessageQueueProcess();
   }

   return 0;

}
