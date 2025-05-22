// static volatile unsigned long paused;
// static volatile int tblink;
// static signed char templ = DEFAULT_TL;
// static signed char temph = DEFAULT_TH;
// static volatile bool motor_must = OFF;
// static volatile bool motor_safe = NO;
// static unsigned long tmr1_us = 0;
// // #define TMR1MAX_US 524288
// // #define TMR1MAX_US 262144
// #define TMR1MAX_US 131072
// // #define TMR1MAX_US 65536
//
//
// const unsigned short tmr1_initial = 65536 - 50000;
//
//
// #define TMR1_START() \
//     TMR1IE = 1; \
//     TMR1ON = 1; \
//     TMR1_RESET()
//
//
// #define TMR1_STOP() \
//     TMR1IE = 0; \
//     TMR1ON = 0; \
//     TMR1_RESET()
//
//
// #define TMR1_RESET() \
//     TMR1IF = 0; \
//     TMR1H = (unsigned char)(tmr1_initial >> 8); \
//     TMR1L = (unsigned char)(tmr1_initial << 8)
//
//
// #define MOTOR_FORCE(s) RELAY_SET(s)
//
//
// static void
// motor_on() {
//     motor_must = ON;
//     if (motor_safe) {
//         MOTOR_FORCE(ON);
//     }
// }
//
//
// static void
// motor_off() {
//     motor_must = OFF;
//     if (RELAY_IS(ON)) {
//         motor_safe = NO;
//         RELAY_SET(OFF);
//         TMR1_START();
//     }
// }
//
//
// void inline
// tmr1_isr() {
//     tmr1_us += TMR1MAX_US;
//     TMR1IF = 0;
//
//     if (paused) {
//         paused--;
//         if (!paused) {
//             TMR1_STOP();
//         }
//         return;
//     }
//
//     if (status == TUNNING) {
//         TMR1_RESET();
//         // LED_SET(!LED);
//         if (LED) {
//             tblink--;
//         }
//         else if (tblink <= 0) {
//             status = IDLE;
//             GPIF = 0;
//             paused = 100000;
//         }
//         return;
//     }
//
//     // if (tmr1_us >= MOTORON_DELAY) {
//     //     tmr1_us = 0;
//     //     TMR1_STOP();
//     //     motor_safe = YES;
//     //     if (motor_must == ON) {
//     //         MOTOR_FORCE(ON);
//     //     }
//     // }
//     // else {
//     //     TMR1_RESET();
//     //     LED_SET(!LED);
//     // }
// }
