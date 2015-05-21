/* mbed Microcontroller Library
 * Copyright (c) 2013-2014 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "mbed.h"

Serial pc(USBTX, USBRX);

#if defined(TARGET_LPC4088)
Serial uart(P4_22, P4_23);
#else
Serial uart(p9, p10);
#endif

DigitalOut led1(LED1);
DigitalOut led2(LED2);

// This function is called when a character goes into the RX buffer.
void rxCallback(void) {
    led1 = !led1;
    pc.putc(uart.getc());
}


int main() {
    // Use a deliberatly slow baud to fill up the TX buffer
    uart.baud(1200);
    uart.attach(&rxCallback, Serial::RxIrq);

    printf("Starting test loop:\n");
    wait(1);

    int c = 'A';
    for (int loop = 0; loop < 512; loop++) {
        uart.printf("%c", c);
        c++;
        if (c > 'Z') c = 'A';
    }

    while (true) {
        led2 = !led2;
        wait(1);
    }
}