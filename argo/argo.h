#ifndef ARGO_H
#define ARGO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef enum
{
	JSON_NUMBER,
	JSON_STRING,
	JSON_OBJECT
} json_type;

typedef struct json
{
	json_type	type;

	union
	{
		int		number;
		char	*string;

		struct
			{
				char **keys;
				struct json **values;
				int size;
			} object;
	} data;

}	json;

int	argo(json *dst, FILE *stream);

#endif



