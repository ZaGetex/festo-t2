/** 
 * File:   iomasks.h
 * 
 * Bit masks for process manipulation of FESTO system.
 *
 * @author Thomas Lehmann
 * @date 2016-09-17
 * @version 1
 * Initial version
 */

#ifndef IOMASKS_H
#define	IOMASKS_H

#ifdef	__cplusplus
extern "C" {
#endif

/* Output Masks, Port A low-byte, Port C high-byte */
#define DRIVE_DIRECTION_RIGHT   0x0001
#define DRIVE_DIRECTION_LEFT    0x0002
#define DRIVE_SLOW              0x0004
#define DRIVE_STOP              0x0008
#ifdef OLD_INTERFACE
#define FEED_SEPARATOR          0x0010
#define ALARM_LAMP_GREEN        0x0020
#define ALARM_LAMP_YELLOW       0x0040
#define ALARM_LAMP_RED          0x0080
#else
#define FEED_SEPARATOR          0x0080
#define ALARM_LAMP_GREEN        0x0040
#define ALARM_LAMP_YELLOW       0x0020
#define ALARM_LAMP_RED          0x0010
#endif

#define LED_START_BUTTON        0x0100
#define LED_RESET_BUTTON        0x0200
#define LED_Q1                  0x0400
#define LED_Q2                  0x0800

/* Input Masks, Port B low-byte, Port C high-byte, move to lower nibble */
#define ITEM_DETECTED          (0x0001<<0)
#define ITEM_AT_HEIGHT_SENSOR  (0x0001<<1)
#define ITEM_HEIGHT_FITS       (0x0001<<2)
#define ITEM_AT_JUNCTION       (0x0001<<3)
#define ITEM_IS_METTAL         (0x0001<<4)
#define JUNCTION_IS_OPEN       (0x0001<<5)
#define BUFFER_IS_FULL         (0x0001<<6)
#define ITEM_AT_END            (0x0001<<7)

#define BUTTON_START_PRESSED   (0x0001<<8)
#define BUTTON_STOP_PRESSED    (0x0001<<9)
#define BUTTON_RESET_PRESSED   (0x0001<<10)
#define EMERGENCY_STOP_PRESSED (0x0001<<11)

#ifdef	__cplusplus
}
#endif

#endif	/* IOMASKS_H */

