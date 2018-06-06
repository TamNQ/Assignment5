#ifndef _FILE_HANDLING_
#define _FILE_HANDLING_
#include <stdint.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief free up memory for list.
 *
 * @param *list Pass by reference pointer point to list want to free memory.
 *
 * @return Empty list.
 */
bool check_type(char line[255]);

bool check_sum(char line[255]);

void read_data2(FILE *fp, int style);

void read_data(FILE *fp);

#endif /* _FILE_HANDLING_ */
