#ifndef BIT_UTILS_H
#define BIT_UTILS_H

/*----------------------------------------------------------
 * Bit Manipulation Macros
 *---------------------------------------------------------*/

#define SET_BIT(REG, BIT)       ((REG) |=  (1U << (BIT)))
#define CLEAR_BIT(REG, BIT)     ((REG) &= ~(1U << (BIT)))
#define TOGGLE_BIT(REG, BIT)    ((REG) ^=  (1U << (BIT)))
#define READ_BIT(REG, BIT)      (((REG) >> (BIT)) & 1U)

/* Future additions:
 * MODIFY_BIT()
 * WRITE_REG()
 * READ_REG()
 * etc.
 */

#endif /* BIT_UTILS_H */