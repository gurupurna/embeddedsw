/*******************************************************************************
 *
 * Copyright (C) 2014 Xilinx, Inc.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * Use of the Software is limited solely to applications:
 * (a) running on a Xilinx device, or
 * (b) that interact with a Xilinx device through a bus or interconnect.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * XILINX CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Except as contained in this notice, the name of the Xilinx shall not be used
 * in advertising or otherwise to promote the sale, use or other dealings in
 * this Software without prior written authorization from Xilinx.
 *
*******************************************************************************/
/******************************************************************************/
/**
 *
 * @file xdptx_selftest_example.c
 *
 * Contains a design example using the XDptx driver. It performs a self test on
 * the DisplayPort TX core that will compare many of the DisplayPort TX core's
 * registers against their default reset values.
 *
 * @note	None.
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who  Date     Changes
 * ----- ---- -------- -----------------------------------------------
 * 1.0   als  06/17/14 Initial creation.
 * </pre>
 *
*******************************************************************************/

/******************************* Include Files ********************************/

#include "xdptx_example_common.h"

/**************************** Function Prototypes *****************************/

u32 Dptx_SelfTestExample(XDptx *InstancePtr, u16 DeviceId);

/**************************** Function Definitions ****************************/

/******************************************************************************/
/**
 * This function is the main function of the XDptx selftest example.
 *
 * @param	None.
 *
 * @return
 *		- XST_SUCCESS if the self test example passed.
 *		- XST_FAILURE if the self test example was unsuccessful - the
 *		  DisplayPort TX's registers do not match their default values
 *		  or no DisplayPort TX instance was found.
 *
 * @note	None.
 *
*******************************************************************************/
int main(void)
{
	u32 Status;

	Status = Dptx_SelfTestExample(&DptxInstance, DPTX_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		xil_printf("XDptx_SelfTest failed, check register values.\n");
		return XST_FAILURE;
	}
	xil_printf("XDptx_SelfTest passed.\n");
	return Status;
}

/******************************************************************************/
/**
 * The main entry point for the selftest example using the XDptx driver. This
 * function will check whether or not the DisplayPort TX's registers are at
 * their default reset values to ensure that the core is in a known and working
 * state.
 *
 * @param	InstancePtr is a pointer to the XDptx instance.
 * @param	DeviceId is the unique device ID of the DisplayPort TX core
 *		instance.
 *
 * @return
 *		- XST_SUCCESS if the DisplayPort TX's registers are at their
 *		  default reset values.
 *		- XST_FAILURE if the DisplayPort TX's registers do not match
 *		  their default values or no DisplayPort TX instance was found.
 *
 * @note	None.
 *
*******************************************************************************/
u32 Dptx_SelfTestExample(XDptx *InstancePtr, u16 DeviceId)
{
	u32 Status;
	XDptx_Config *ConfigPtr;

	/* Obtain the device configuration for the DisplayPort TX core. */
	ConfigPtr = XDptx_LookupConfig(DeviceId);
	if (!ConfigPtr) {
		return XST_FAILURE;
	}
	/* Copy the device configuration into the InstancePtr's Config
	 * structure. */
	XDptx_CfgInitialize(InstancePtr, ConfigPtr, ConfigPtr->BaseAddr);

	/* Run the self test. */
	Status = XDptx_SelfTest(InstancePtr);
	return Status;
}
